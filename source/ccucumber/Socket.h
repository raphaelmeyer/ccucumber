#pragma once

#include <netinet/in.h>

#include <exception>
#include <string>
#include <vector>

class SocketException : public std::exception {
public:
  SocketException(std::string const & _reason);

  virtual char const * what() const noexcept override;

private:
  std::string reason;
};

class Socket {
public:
  Socket();
  Socket(Socket && other);

  ~Socket();

  static Socket make_socket(int _port);

  void bind();
  void listen();
  Socket accept();

  void send(std::vector<char> const & buffer);
  size_t recv(std::vector<char> & buffer);

  void close();

private:
  Socket(int _socket, sockaddr_in _address);
  Socket(Socket const &) = delete;

  sockaddr_in server_address;
  int socket;
};
