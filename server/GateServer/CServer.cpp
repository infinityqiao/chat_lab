#include "CServer.h"
#include "HttpConnection.h"

CServer::CServer(boost::asio::io_context& ioc, unsigned short& port): _ioc(ioc),
_acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _socket(ioc) {

}

void CServer::Start() {
	auto self = shared_from_this();
	_acceptor.async_accept(_socket, [self](beast::error_code ec) {
		try {
			// 放弃该链接
			if (ec) {
				self->Start();
				return;
			}

			// 创建新连接，HttpConnection 管理该连接
			std::make_shared<HttpConnection>(std::move(self->_socket))->Start();

			self->Start();
		}
		catch (std::exception& exp) {

		}
		});
}