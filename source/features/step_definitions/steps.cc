#include <ccucumber/ccucumber.h>

#include <WireServer.h>

namespace
{

ccucumber::WireServer server;

using namespace ccucumber;

Define steps {{

Given("a C++ wire server", []{
  std::uint16_t port = 2345;
  server.run(port);
})

}};

}

