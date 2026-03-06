#pragma once

#include "boost/asio.hpp"
#include "boost/asio/ssl.hpp"

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;

class Client {
    boost::asio::io_context io_context;
    ssl::context ssl_context;
public:
    Client();
    tcp::resolver::results_type resolve(std::string ip, std::string port);
    ssl_socket connect(tcp::resolver::results_type endpoints);
    ssl_socket resolve_and_connect(std::string ip, std::string port);
};