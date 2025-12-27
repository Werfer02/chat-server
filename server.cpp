#include <iostream>
#include <thread>
#include "boost/asio.hpp"

using boost::asio::ip::tcp;

void receiveLoop(tcp::socket& s){
    while(true){
        char data[1024];
        size_t length = s.read_some(boost::asio::buffer(data));
        std::cout << "\033[G" <<  "[Client]: " << std::string(data, length) << "\n";
        std::cout << "[Server]: ";
    }
}

int main(){
    std::cout << "hello world\n\n";
    std::string port;
    
    std::cout << "port to listen on:";
    std::cin >> port;

    boost::asio::io_context io_context;

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), stoi(port)));

    tcp::socket socket(io_context);

    std::cout << "listening on port " << port << "...\n";
    acceptor.accept(socket);
    std::cout << "client connected!\n";

    std::thread receivethread(receiveLoop, std::ref(socket));
    receivethread.detach();

    while(true){
        std::cout << "[Server]: ";
        std::string msg;
        std::cin >> msg;
        std::cout << "\n";
        boost::asio::write(socket, boost::asio::buffer(msg));
    }
    
}