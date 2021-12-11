#pragma once

#include "mapreduce_spec.h"
#include "file_shard.h"
#include <grpcpp/grpcpp.h>
#include "masterworker.grpc.pb.h"
#include <experimental/filesystem>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using masterworker::WorkerImpl;
using masterworker::MapReply;
using masterworker::Shard;
using masterworker::ShardFileInfo;
using masterworker::ReduceFile;
using masterworker::ReduceReply;

namespace fs = std::experimental::filesystem;

/* CS6210_TASK: Handle all the bookkeeping that Master is supposed to do.
	This is probably the biggest task for this project, will test your understanding of map reduce */
class Master {

	public:
		/* DON'T change the function signature of this constructor */
		Master(const MapReduceSpec&, const std::vector<FileShard>&);

		/* DON'T change this function's signature */
		bool run();

	private:
		/* NOW you can add below, data members and member functions as per the need of your implementation*/
		MapReduceSpec spec;
		std::vector<FileShard> file_shards;

		void AssignMap(FileShard currentShard, std::unique_ptr<WorkerImpl::Stub> &stub) {
			Shard request;
			ShardFileInfo *fileInfo;
			MapReply reply;
			ClientContext context;

			request.set_noutputfiles(this->spec.n_output_files);

			for (FileInfo current_file : currentShard.files) {
				fileInfo = request.add_files();
				fileInfo->set_filename(current_file.file_name);
				fileInfo->set_start(current_file.start);
				fileInfo->set_finish(current_file.finish);
			}

			Status status = stub->Map(&context, request, &reply);

			if(status.ok()) {
				// std::cout << reply.mapfile() << "\n";
			} else {
				std::cout << "ERROR: Failed mapping this shard\n";
			}
		}

		void AssignReduce(std::string directoryName, std::unique_ptr<WorkerImpl::Stub> &stub) {
			ReduceFile request;
			ReduceReply reply;
			ClientContext context;

			request.set_directoryname(directoryName);
			request.set_outputdirectory(this->spec.output_dir);
			Status status = stub->Reduce(&context, request, &reply);

			if(status.ok()) {
				// std::cout << reply.message() << "\n";
			} else {
				std::cout << "ERROR: Failed to reduce this directory\n";
			}
		}	
};


/* CS6210_TASK: This is all the information your master will get from the framework.
	You can populate your other class data members here if you want */
Master::Master(const MapReduceSpec& mr_spec, const std::vector<FileShard>& file_shards) {
	this->spec = mr_spec;
	this->file_shards = file_shards;
}


/* CS6210_TASK: Here you go. once this function is called you will complete whole map reduce task and return true if succeeded */
bool Master::run() {
	fs::create_directory(this->spec.output_dir);

	std::vector<std::unique_ptr<WorkerImpl::Stub>> stubs;
	for(int i = 0; i < this->spec.n_workers; i++) {
		std::shared_ptr<Channel> channel = grpc::CreateChannel(this->spec.worker_ipaddr_ports[i], grpc::InsecureChannelCredentials());
		std::unique_ptr<WorkerImpl::Stub> stub(WorkerImpl::NewStub(channel));
		stubs.push_back(std::move(stub));
	}

	for (int i = 0; i < this->spec.n_output_files; i++) {
		fs::create_directory(std::to_string(i));
	}

	for (FileShard currentShard : this->file_shards) {
		AssignMap(currentShard, stubs[0]);
	}

	for (int i = 0; i < this->spec.n_output_files; i++) {
		AssignReduce(std::to_string(i), stubs[0]);
		fs::remove_all(std::to_string(i));
	}

	return true;
}