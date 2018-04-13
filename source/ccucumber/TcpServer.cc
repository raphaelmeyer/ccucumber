#include "TcpServer.h"

namespace ccucumber {

void TcpServer::listen(std::uint16_t port) {
  auto socket = Socket::make_socket(port);
  socket.bind();
  socket.listen();

  connection = socket.accept();
}

std::string TcpServer::read_line() {
  return {};
}

bool TcpServer::connection_is_open() const {
  return connection.is_open();
}

}; // namespace ccucumber
