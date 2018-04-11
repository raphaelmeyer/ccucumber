#pragma once

#include <cstdint>

namespace ccucumber
{

class WireServer {
  public:
    void run(std::uint16_t port);
};

} // namespace


