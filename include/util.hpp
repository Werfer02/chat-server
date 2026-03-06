#pragma once

#include <string>

#include "boost/asio.hpp"
#include "boost/asio/ssl.hpp"

#include "chat.hpp"

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;

ChatMessage receiveMessage(ssl_socket& s);

void sendMessage(ssl_socket& s, std::string msg, std::string author);

const extern std::string clearScreen;