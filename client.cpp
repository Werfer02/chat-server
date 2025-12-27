#include <iostream>
#include <thread>
#include "boost/asio.hpp"

using boost::asio::ip::tcp;

void receiveLoop(tcp::socket& s){
    while(true){
        char data[1024];
        size_t length = s.read_some(boost::asio::buffer(data));
        std::cout << "\033[G" << "[Server]: " << std::string(data, length) << "\n";
        std::cout << "------------------------------------------------\n[Client]: ";
    }
}

int main(){
    std::cout << "hello world\n\n";
    std::string ip, port;
    std::cout << "ip to connect to:";
    std::cin >> ip;
    std::cout << "port:";
    std::cin >> port;

    boost::asio::io_context io_context;

    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(ip, port);

    tcp::socket socket(io_context);
    std::cout << "connecting to server...\n";
    boost::asio::connect(socket, endpoints);
    std::cout << "connected!\n";

    std::thread receivethread(receiveLoop, std::ref(socket));
    receivethread.detach();

    while(true){
        std::cout << "------------------------------------------------\n[Client]: ";
        std::string msg;
        std::cin >> msg;
        std::cout << "\n";
        boost::asio::write(socket, boost::asio::buffer(msg));
    }
}