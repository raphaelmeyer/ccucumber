#include "WireServer.h"

#include "Socket.h"

#include <json.hpp>

#include <algorithm>
#include <iterator>
#include <iostream>

using nlohmann::json;
using namespace std::string_literals;

namespace ccucumber
{

void WireServer::run(std::uint16_t port) {
  auto socket = Socket::make_socket(port);
  socket.bind();
  socket.listen();

  auto conn = socket.accept();

  while(true) {
    std::vector<char> input{};
    input.resize(1024);
    conn.recv(input);

    std::string input_string;
    std::copy(input.begin(), input.end(), std::back_inserter(input_string));

    auto const request = json::parse(input_string);
    std::cout << "request : " << request << "\n";

    if(request[0] == "step_matches") {
      auto const response = R"(["success",[]])"_json;
      auto const output_string = response.dump();
      std::vector<char> output{};
      std::copy(output_string.begin(), output_string.end(), std::back_inserter(output));
      output.push_back('\n');
      conn.send(output);
    } else {
      auto const error = "[\"error\"]\n"s;
      std::vector<char> output{};
      std::copy(error.begin(), error.end(), std::back_inserter(output));
      conn.send(output);
    }
  }
}

} // namespace

