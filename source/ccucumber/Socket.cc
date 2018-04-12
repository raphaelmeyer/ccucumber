#include "Socket.h"

#include <sys/socket.h>
#include <unistd.h>

SocketException::SocketException(std::string const & _reason) : reason(_reason) {
}

char const * SocketException::what() const noexcept {
  return reason.c_str();
}

Socket::Socket() : server_address(), socket(-1) {
}

Socket::Socket(Socket && other) : server_address(other.server_address), socket(other.socket) {
  other.server_address = {};
  other.socket = -1;
}

Socket::Socket(int _socket, sockaddr_in _address) : server_address(_address), socket(_socket) {
}

Socket::~Socket() {
  ::close(socket);
}

Socket Socket::make_socket(int _port) {
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

void Socket::bind() {
  if(::bind(socket, reinterpret_cast<sockaddr *>(&server_address), sizeof(server_address)) < 0) {
    throw SocketException("could not bind socket");
  }
}

void Socket::listen() {
  if(::listen(socket, 2) < 0) {
    throw SocketException("cannot listen on socket");
  }
}

Socket Socket::accept() {
  sockaddr_in client_address{};
  socklen_t client_address_length{0};

  int accept_socket = ::accept(socket, reinterpret_cast<sockaddr *>(&client_address), &client_address_length);
  if(accept_socket < 0) {
    throw SocketException("accept rejected by socket");
  }

  return Socket{accept_socket, client_address};
}

void Socket::send(std::vector<char> const & buffer) {
  auto sent = ::send(socket, buffer.data(), buffer.size(), 0);
  if(sent < 0) {
    throw SocketException("sending data failed");
  }
}

size_t Socket::recv(std::vector<char> & buffer) {
  auto received = ::recv(socket, buffer.data(), buffer.size(), 0);
  if(received < 0) {
    throw SocketException("receiving data failed");
  }
  if(static_cast<size_t>(received) > buffer.size()) {
    throw SocketException("received more data than expected");
  }
  buffer.resize(received);
  return received;
}

void Socket::close() {
  ::close(socket);
  socket = -1;
  server_address = {};
}
