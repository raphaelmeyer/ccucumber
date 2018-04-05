#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <exception>
#include <vector>
#include <string>

#include <iostream>
#include <iterator>
#include <algorithm>

class SocketException : public std::exception {
  public:

    SocketException(std::string const & _reason)
      : reason(_reason)
    {
    }

    virtual char const * what() const noexcept override {
      return reason.c_str();
    }

  private:
    std::string reason;
};

class Socket {
  public:
    Socket()
      : server_address()
      , socket(-1)
     {
     }

    Socket(Socket && other)
      : server_address(other.server_address)
      , socket(other.socket)
    {
      other.server_address = {};
      other.socket = -1;
    }

    ~Socket() {
      ::close(socket);
      std::cout << "close " << socket << "\n";
    }

    static Socket make_socket(int _port)
    {
      auto socket = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
      if(socket < 0) {
        throw SocketException("could not create socket");
      }

      int enable = 1;
      if(::setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0) {
        throw SocketException("could not set socket options");
      }

      sockaddr_in server_address;
      server_address.sin_family = AF_INET;
      server_address.sin_port = htons(_port);
      server_address.sin_addr.s_addr = htonl(INADDR_ANY);

      return Socket{socket, server_address};
    }

    void bind() {


      if(::bind(socket, reinterpret_cast<sockaddr *>(&server_address), sizeof(server_address)) < 0) {
        throw SocketException("could not bind socket");
      }
    }

    void listen() {
      if(::listen(socket, 2) < 0) {
        throw SocketException("cannot listen on socket");
      }
    }

    Socket accept() {
      sockaddr_in client_address{};
      socklen_t client_address_length{0};

      int accept_socket = ::accept(socket, reinterpret_cast<sockaddr *>(&client_address), &client_address_length);
      if(accept_socket < 0) {
        throw SocketException("accept rejected by socket");
      }

      return Socket{accept_socket, client_address};
    }

    void send(std::vector<char> const & buffer) {
      auto sent = ::send(socket, buffer.data(), buffer.size(), 0);
      if(sent < 0) {
        throw SocketException("sending data failed");
      }
    }

    size_t recv(std::vector<char> & buffer) {
      auto received = ::recv(socket, buffer.data(), buffer.size(), 0);
      if(received < 0) {
        throw SocketException("receiving data failed");
      }
      if(received > buffer.size()) {
        throw SocketException("received more data than expected");
      }
      buffer.resize(received);
      return received;
    }

    void close() {
      ::close(socket);
      socket = -1;
      server_address = {};
    }

  private:
    Socket(int _socket, sockaddr_in _address)
      : server_address(_address)
      , socket(_socket)
     {
       std::cout << "created " << socket << "\n";
     }

    Socket(Socket const &) = delete;

    sockaddr_in server_address;
    int socket;
};

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

