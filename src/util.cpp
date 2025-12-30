#include "util.hpp"

std::string receive(tcp::socket& s){
    boost::asio::streambuf buf;
    boost::asio::read_until(s, buf, '\n');
    std::istream is(&buf);
    std::string data;
    std::getline(is, data);
    return data;
}