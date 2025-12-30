#include <string>

#include "boost/asio.hpp"

using boost::asio::ip::tcp;

std::string receive(tcp::socket& s);