#include "util.hpp"

ChatMessage receiveMessage(tcp::socket& s){

    boost::asio::streambuf buf;
    std::istream is(&buf);

    boost::asio::read_until(s, buf, '\n');
    std::string msg;
    std::getline(is, msg);

    boost::asio::read_until(s, buf, '\n');
    std::string author;
    std::getline(is, author);

    return {msg, author};
}

void sendMessage(tcp::socket& s, std::string msg, std::string author){
    std::string formatted = msg + "\n" + author + "\n";
    boost::asio::write(s, boost::asio::buffer(formatted));
}

const std::string clearScreen = "\033[H\033[J";