#include "ChatGrpcClient.h"
#include "RedisMgr.h"

ChatGrpcClient::ChatGrpcClient()
{
	auto& cfg = ConfigMgr::Inst();
	auto server_list = cfg["chatservers"]["Name"];

	std::vector<std::string> words;

	std::stringstream ss(server_list);
	std::string word;

	while (std::getline(ss, word, ',')) {
		words.push_back(word);
	}

	for (auto& word : words) {
		if (cfg[word]["Name"].empty()) {
			continue;
		}
		
		_pools[cfg[word]["Name"]] = std::make_unique<ChatConPool>(5, cfg[word]["Host"], cfg[word]["Port"]);
	}

}

AddFriendRsp ChatGrpcClient::NotifyAddFriend(const AddFriendReq& req)
{
	auto to_uid = req.touid();
	std::string  uid_str = std::to_string(to_uid);
	
	AddFriendRsp rsp;
	return rsp;
}

inline ChatConPool::ChatConPool(size_t poolSize, std::string host, std::string port)
	: poolSize_(poolSize), host_(host), port_(port), b_stop_(false) {
	for (size_t i = 0; i < poolSize_; ++i) {

		std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port,
			grpc::InsecureChannelCredentials());

		connections_.push(ChatService::NewStub(channel));
	}
}

inline ChatConPool::~ChatConPool() {
	std::lock_guard<std::mutex> lock(mutex_);
	Close();
	while (!connections_.empty()) {
		connections_.pop();
	}
}

inline std::unique_ptr<ChatService::Stub> ChatConPool::getConnection() {
	std::unique_lock<std::mutex> lock(mutex_);
	cond_.wait(lock, [this] {
		if (b_stop_) {
			return true;
		}
		return !connections_.empty();
		});
	//如果停止则直接返回空指针
	if (b_stop_) {
		return  nullptr;
	}
	auto context = std::move(connections_.front());
	connections_.pop();
	return context;
}

inline void ChatConPool::returnConnection(std::unique_ptr<ChatService::Stub> context) {
	std::lock_guard<std::mutex> lock(mutex_);
	if (b_stop_) {
		return;
	}
	connections_.push(std::move(context));
	cond_.notify_one();
}

inline void ChatConPool::Close() {
	b_stop_ = true;
	cond_.notify_all();
}
