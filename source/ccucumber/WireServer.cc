#include "WireServer.h"

#include "Socket.h"
#include "TcpServer.h"

#include <json.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>

using nlohmann::json;
using namespace std::string_literals;

namespace ccucumber {

void WireServer::run(std::uint16_t port) {
  TcpServer server;
  server.listen(port);

  do {
    auto const line = server.read_line();
    // handler.process(line);

  } while(not server.connection_is_open());
}

} // namespace ccucumber
