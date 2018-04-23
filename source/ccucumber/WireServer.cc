#include "WireServer.h"

#include "Socket.h"
#include "TcpServer.h"

#include <json.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>

#include <experimental/net>
#include <experimental/socket>

using nlohmann::json;
using namespace std::string_literals;

namespace net = std::experimental::net;

namespace ccucumber {

void WireServer::run(std::uint16_t port) {

  net::io_context context;
  net::ip::tcp::endpoint endpoint{net::ip::tcp::v4(), port};
  net::ip::tcp::acceptor acceptor{context, endpoint};

  acceptor.set_option(net::ip::tcp::acceptor::reuse_address{true});
  acceptor.accept(context);

  // todo get stream from socket
  net::ip::tcp::iostream stream{acceptor};

  std::string line;
  while(stream && std::getline(stream, line)) {
    // handler.process(line);
  }
}

} // namespace ccucumber
