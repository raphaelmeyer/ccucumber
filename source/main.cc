#include <iostream>
#include <iterator>
#include <algorithm>

#include <json.hpp>

#include "Socket.h"

int main() {
  try {
    auto socket = Socket::make_socket(3902);
    socket.bind();
    socket.listen();

    std::cout << "listen ...\n";

    auto conn = socket.accept();

    std::cout << "connected\n";

    std::vector<char> input{};
    input.resize(1024);
    conn.recv(input);

    std::cout << "received ";
    std::copy(input.begin(), input.end(), std::ostream_iterator<char>(std::cout));
    std::cout << "\n" << std::flush;
  } catch(SocketException const & e) {
    std::cout << "error : " << e.what() << "\n";
  }
}

