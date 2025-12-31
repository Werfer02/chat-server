#pragma once

#include "boost/asio.hpp"

using boost::asio::ip::tcp;

class Client {
    boost::asio::io_context io_context;
public:
    tcp::resolver::results_type resolve(std::string ip, std::string port);
    tcp::socket connect(tcp::resolver::results_type endpoints);
    tcp::socket resolve_and_connect(std::string ip, std::string port);
};