#include <iostream>
#include "boost/asio.hpp"

using boost::asio::ip::tcp;

int main(){
    std::cout << "hello world\n\n";

    boost::asio::io_context io_context;

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 4242));

    tcp::socket socket(io_context);

    std::cout << "listening on port 4242...\n";
    acceptor.accept(socket);
    std::cout << "client connected!\n";

    char data[1024];
    size_t length = socket.read_some(boost::asio::buffer(data));
    std::cout << "received from client: " << std::string(data, length) << "\n";

    boost::asio::write(socket, boost::asio::buffer("hello from server!"));
    
}