// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: masterworker.proto

#include "masterworker.pb.h"
#include "masterworker.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace masterworker {

static const char* WorkerImpl_method_names[] = {
  "/masterworker.WorkerImpl/Map",
  "/masterworker.WorkerImpl/Reduce",
};

std::unique_ptr< WorkerImpl::Stub> WorkerImpl::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< WorkerImpl::Stub> stub(new WorkerImpl::Stub(channel));
  return stub;
}

WorkerImpl::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Map_(WorkerImpl_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Reduce_(WorkerImpl_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status WorkerImpl::Stub::Map(::grpc::ClientContext* context, const ::masterworker::Shard& request, ::masterworker::MapReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::masterworker::Shard, ::masterworker::MapReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_Map_, context, request, response);
}

void WorkerImpl::Stub::experimental_async::Map(::grpc::ClientContext* context, const ::masterworker::Shard* request, ::masterworker::MapReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::masterworker::Shard, ::masterworker::MapReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Map_, context, request, response, std::move(f));
}

void WorkerImpl::Stub::experimental_async::Map(::grpc::ClientContext* context, const ::masterworker::Shard* request, ::masterworker::MapReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Map_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::masterworker::MapReply>* WorkerImpl::Stub::PrepareAsyncMapRaw(::grpc::ClientContext* context, const ::masterworker::Shard& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::masterworker::MapReply, ::masterworker::Shard, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_Map_, context, request);
}

::grpc::ClientAsyncResponseReader< ::masterworker::MapReply>* WorkerImpl::Stub::AsyncMapRaw(::grpc::ClientContext* context, const ::masterworker::Shard& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncMapRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status WorkerImpl::Stub::Reduce(::grpc::ClientContext* context, const ::masterworker::ReduceFile& request, ::masterworker::ReduceReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::masterworker::ReduceFile, ::masterworker::ReduceReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_Reduce_, context, request, response);
}

void WorkerImpl::Stub::experimental_async::Reduce(::grpc::ClientContext* context, const ::masterworker::ReduceFile* request, ::masterworker::ReduceReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::masterworker::ReduceFile, ::masterworker::ReduceReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Reduce_, context, request, response, std::move(f));
}

void WorkerImpl::Stub::experimental_async::Reduce(::grpc::ClientContext* context, const ::masterworker::ReduceFile* request, ::masterworker::ReduceReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Reduce_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::masterworker::ReduceReply>* WorkerImpl::Stub::PrepareAsyncReduceRaw(::grpc::ClientContext* context, const ::masterworker::ReduceFile& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::masterworker::ReduceReply, ::masterworker::ReduceFile, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_Reduce_, context, request);
}

::grpc::ClientAsyncResponseReader< ::masterworker::ReduceReply>* WorkerImpl::Stub::AsyncReduceRaw(::grpc::ClientContext* context, const ::masterworker::ReduceFile& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncReduceRaw(context, request, cq);
  result->StartCall();
  return result;
}

WorkerImpl::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      WorkerImpl_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< WorkerImpl::Service, ::masterworker::Shard, ::masterworker::MapReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](WorkerImpl::Service* service,
             ::grpc::ServerContext* ctx,
             const ::masterworker::Shard* req,
             ::masterworker::MapReply* resp) {
               return service->Map(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      WorkerImpl_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< WorkerImpl::Service, ::masterworker::ReduceFile, ::masterworker::ReduceReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](WorkerImpl::Service* service,
             ::grpc::ServerContext* ctx,
             const ::masterworker::ReduceFile* req,
             ::masterworker::ReduceReply* resp) {
               return service->Reduce(ctx, req, resp);
             }, this)));
}

WorkerImpl::Service::~Service() {
}

::grpc::Status WorkerImpl::Service::Map(::grpc::ServerContext* context, const ::masterworker::Shard* request, ::masterworker::MapReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status WorkerImpl::Service::Reduce(::grpc::ServerContext* context, const ::masterworker::ReduceFile* request, ::masterworker::ReduceReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace masterworker

