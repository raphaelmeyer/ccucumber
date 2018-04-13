#pragma once

#include "Socket.h"

#include <cstdint>
#include <string>

namespace ccucumber {

class TcpServer {
public:
  void listen(std::uint16_t port);
  std::string read_line();
  bool connection_is_open() const;

private:
  Socket connection;
};

} // namespace ccucumber
