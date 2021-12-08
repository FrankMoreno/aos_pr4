#pragma once

#include "mapreduce_spec.h"
#include "file_shard.h"
#include <grpcpp/grpcpp.h>
#include "masterworker.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using masterworker::WorkerImpl;
using masterworker::MapReply;
using masterworker::Shard;
using masterworker::ShardFileInfo;

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
};


/* CS6210_TASK: This is all the information your master will get from the framework.
	You can populate your other class data members here if you want */
Master::Master(const MapReduceSpec& mr_spec, const std::vector<FileShard>& file_shards) {
	this->spec = mr_spec;
	this->file_shards = file_shards;
}


/* CS6210_TASK: Here you go. once this function is called you will complete whole map reduce task and return true if succeeded */
bool Master::run() {
	std::shared_ptr<Channel> channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
	std::unique_ptr<WorkerImpl::Stub> stub(WorkerImpl::NewStub(channel));

	Shard request;
	ShardFileInfo *fileInfo;
	MapReply reply;
	ClientContext context;

	for (FileInfo current_file : this->file_shards[0].files) {
		std::cout << current_file.file_name << "\n";
		fileInfo = request.add_files();
		fileInfo->set_filename(current_file.file_name);
		fileInfo->set_start(current_file.start);
		fileInfo->set_finish(current_file.finish);
	}

	Status status = stub->Map(&context, request, &reply);

	if(status.ok()) {
		std::cout << "Finished" << "\n";
	}

	return true;
}