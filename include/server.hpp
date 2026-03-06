#pragma once

#include "boost/asio.hpp"
#include "boost/asio/ssl.hpp"

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;

class Server {
    boost::asio::io_context io_context;
    ssl::context ssl_context;
public:
    Server();
    ssl_socket accept(int port);
};