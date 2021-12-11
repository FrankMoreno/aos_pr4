#pragma once

#include <mr_task_factory.h>
#include "mr_tasks.h"
#include <grpcpp/grpcpp.h>
#include "masterworker.grpc.pb.h"
#include <fstream>
#include <sstream>
#include <functional>
#include <experimental/filesystem>

using grpc::ServerBuilder;
using grpc::Server;
using grpc::Status;
using grpc::ServerContext;
using masterworker::WorkerImpl;
using masterworker::MapReply;
using masterworker::Shard;
using masterworker::ShardFileInfo;
using masterworker::ReduceFile;
using masterworker::ReduceReply;

extern std::shared_ptr<BaseMapper> get_mapper_from_task_factory(const std::string& user_id);
extern std::shared_ptr<BaseReducer> get_reducer_from_task_factory(const std::string& user_id);

namespace fs = std::experimental::filesystem;

/* CS6210_TASK: Handle all the task a Worker is supposed to do.
	This is a big task for this project, will test your understanding of map reduce */
class Worker final : public WorkerImpl::Service {

	public:
		/* DON'T change the function signature of this constructor */
		Worker(std::string ip_addr_port);

		/* DON'T change this function's signature */
		bool run();

	private:
		/* NOW you can add below, data members and member functions as per the need of your implementation*/
		std::string ip_addr_port;

		Status Map(ServerContext* context, const Shard* request, MapReply* reply) override {
			auto mapper = get_mapper_from_task_factory("cs6210");

			for (int i = 0; i < request->files_size(); i++) {
				// https://www.delftstack.com/howto/cpp/read-file-into-string-cpp/
				MapFile(request->files(i), mapper);
			}

			std::vector<std::ofstream> responseFiles;

			for (int i = 0; i < request->noutputfiles(); i++) {
				std::string responseFileName = std::to_string(i) + "/" + this->ip_addr_port + ".txt";
				std::ofstream responseFile(responseFileName, std::ios_base::app);
				responseFiles.push_back(std::move(responseFile));
			}

			std::multimap <std::string, std::string> :: iterator itr;
			std::hash<std::string> str_hash;

			for (itr = mapper->impl_->key_value_pairs.begin(); itr != mapper->impl_->key_value_pairs.end(); ++itr) {
				int hash_index = str_hash(itr->first) % request->noutputfiles();
				responseFiles.at(hash_index) << itr->first << " " << itr->second << "\n";
			}

			for (int i = 0; i < request->noutputfiles(); i++) {
				responseFiles[i].close();
			}

			reply->set_mapfile(this->ip_addr_port);

			return Status::OK;
		}

		void MapFile(ShardFileInfo fileInfo, std::shared_ptr<BaseMapper> mapper) {
			// https://www.delftstack.com/howto/cpp/read-file-into-string-cpp/
			std::size_t size = fileInfo.finish() - fileInfo.start() + 1;
			std::string buffer;
			buffer.resize(size);

			std::ifstream input_file(fileInfo.filename());
			input_file.seekg(fileInfo.start());
			input_file.read(&buffer[0], size);

			// Instructions specified to process input based on newline
			std::stringstream buffer_stream(buffer);
			std::string line;
			while(std::getline(buffer_stream, line)) {
				mapper->map(line);
			}

			input_file.close();
		}

		Status Reduce(ServerContext* context, const ReduceFile* request, ReduceReply* reply) override {
			auto reducer = get_reducer_from_task_factory("cs6210");
			std::map<std::string, std::vector<std::string>> key_value_pairs;

			for (const auto & entry : fs::directory_iterator(request->directoryname())) {
				std::ifstream input_file(entry.path());
				std::string line;
				std::vector<std::string> tokens;

				while(std::getline(input_file, line)) {
					std::stringstream line_stream(line);
					std::vector<std::string> tokens;
					std::string temp;

					while (line_stream >> temp)
        				tokens.push_back(temp);
					
					std::string key = tokens[0];
					std::string value = tokens[1];

					if(key_value_pairs.count(key)) {
						key_value_pairs[key].push_back(value);
					} else {
						key_value_pairs.insert(std::pair<std::string, std::vector<std::string>>(key, {value}));
					}
				}
			}


			std::map<std::string, std::vector<std::string>>::iterator it;
			for (it = key_value_pairs.begin(); it != key_value_pairs.end(); it++) {
				reducer->reduce(it->first, it->second);
			}


			std::string outputFileName = request->outputdirectory() + "/" + request->directoryname() + ".txt";
			std::ofstream responseFile(outputFileName, std::ios_base::app);
			std::multimap <std::string, std::string> :: iterator itr;

			for (itr = reducer->impl_->key_value_pairs.begin(); itr != reducer->impl_->key_value_pairs.end(); ++itr) {
				responseFile << itr->first << " " << itr->second << "\n";
			}

			responseFile.close();

			return Status::OK;
		}
};


/* CS6210_TASK: ip_addr_port is the only information you get when started.
	You can populate your other class data members here if you want */
Worker::Worker(std::string ip_addr_port) {
	this->ip_addr_port = ip_addr_port;
}

/* CS6210_TASK: Here you go. once this function is called your woker's job is to keep looking for new tasks 
	from Master, complete when given one and again keep looking for the next one.
	Note that you have the access to BaseMapper's member BaseMapperInternal impl_ and 
	BaseReduer's member BaseReducerInternal impl_ directly, 
	so you can manipulate them however you want when running map/reduce tasks*/
bool Worker::run() {
	// fs::create_directory(this->ip_addr_port);

	ServerBuilder builder;
	builder.AddListeningPort(this->ip_addr_port, grpc::InsecureServerCredentials());
	builder.RegisterService(this);
	std::unique_ptr<Server> server(builder.BuildAndStart());
	server->Wait();

	return true;
}
