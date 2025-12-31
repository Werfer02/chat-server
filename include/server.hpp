#pragma once

#include "boost/asio.hpp"

using boost::asio::ip::tcp;

class Server {
    boost::asio::io_context io_context;
public:
    tcp::socket accept(int port);
};