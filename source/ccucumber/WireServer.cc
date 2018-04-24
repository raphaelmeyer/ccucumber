#include "WireServer.h"

#include <json.hpp>

#include <experimental/net>

#include <algorithm>
#include <iostream>
#include <iterator>

using nlohmann::json;
using namespace std::string_literals;

namespace net = std::experimental::net;

namespace ccucumber {

void WireServer::run(std::uint16_t port) {

  net::io_context context;
  net::ip::tcp::endpoint endpoint{net::ip::tcp::v4(), port};
  net::ip::tcp::acceptor acceptor{context, endpoint};
  acceptor.set_option(net::ip::tcp::acceptor::reuse_address{true});

  net::ip::tcp::iostream stream{acceptor.accept(context)};

  std::string line;
  while(stream && std::getline(stream, line)) {
    std::cout << line << "\n";
    stream << "[\"success\", []]\n";
  }
}

} // namespace ccucumber
