#pragma once

#include <string>

#include "boost/asio.hpp"

#include "chat.hpp"

using boost::asio::ip::tcp;

ChatMessage receiveMessage(tcp::socket& s);

void sendMessage(tcp::socket& s, std::string msg, std::string author);

const extern std::string clearScreen;