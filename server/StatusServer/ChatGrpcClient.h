#pragma once
#include "const.h"
#include "Singleton.h"
#include "ConfigMgr.h"
#include <grpcpp/grpcpp.h> 
#include "message.grpc.pb.h"
#include "message.pb.h"

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::AddFriendReq;
using message::AddFriendRsp;

using message::GetChatServerRsp;
using message::LoginRsp;
using message::LoginReq;
using message::ChatService;

class ChatConPool {
public:
	ChatConPool(size_t poolSize, std::string host, std::string port);

	~ChatConPool();

	std::unique_ptr<ChatService::Stub> getConnection();

	void returnConnection(std::unique_ptr<ChatService::Stub> context);

	void Close();

private:
	atomic<bool> b_stop_;
	size_t poolSize_;
	std::string host_;
	std::string port_;
	std::queue<std::unique_ptr<ChatService::Stub>> connections_;
	std::mutex mutex_;
	std::condition_variable cond_;
};

class ChatGrpcClient :public Singleton<ChatGrpcClient>
{
	friend class Singleton<ChatGrpcClient>;
public:
	~ChatGrpcClient() {

	}

	AddFriendRsp NotifyAddFriend(const AddFriendReq& req);

private:
	ChatGrpcClient();
	unordered_map<std::string, std::unique_ptr<ChatConPool>> _pools;	
};



