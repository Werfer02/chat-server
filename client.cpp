#include <iostream>
#include "boost/asio.hpp"

using boost::asio::ip::tcp;

int main(){
    std::cout << "hello world\n\n";

    boost::asio::io_context io_context;

    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve("127.0.0.1", "4242");

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    std::cout << "connected to server!\n";

    boost::asio::write(socket, boost::asio::buffer("hello from client!"));

    char data[1024];
    size_t length = socket.read_some(boost::asio::buffer(data));
    std::cout << "received from server: " << std::string(data, length) << "\n";

    boost::asio::write(socket, boost::asio::buffer("hello from server!"));
    
}