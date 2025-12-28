#include <iostream>
#include <thread>
#include "boost/asio.hpp"

using boost::asio::ip::tcp;

class Client {
    boost::asio::io_context io_context;
public:
    tcp::resolver::results_type resolve(std::string ip, std::string port){
        tcp::resolver resolver(io_context);
        return resolver.resolve(ip, port);
    }
    tcp::socket connect(tcp::resolver::results_type endpoints){
        tcp::socket s(io_context);
        boost::asio::connect(s, endpoints);
        return s;
    }
    tcp::socket resolve_and_connect(std::string ip, std::string port){
        auto endpoints = resolve(ip, port);
        tcp::socket s = connect(endpoints);
        return s;
    }
};

std::string receive(tcp::socket& s){
    boost::asio::streambuf buf;
    boost::asio::read_until(s, buf, '\n');
    std::istream is(&buf);
    std::string data;
    std::getline(is, data);
    return data;
}

void receiveLoop(tcp::socket& s){
    std::string received;
    while(true){
        received = receive(s);
        std::cout << "[Server]: " << received << "\n";
    }
}

#ifdef _WIN32
    void initConsole() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode;
        GetConsoleMode(hConsole, &mode);
        SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING); // add this flag to the console mode
    }
#else
    void initConsole() {}
#endif

int main(){
    std::cout << "hello world\n\n";

    initConsole();
    
    std::string ip, port;
    
    std::cout << "ip to connect to:";
    std::cin >> ip;
    std::cout << "port:";
    std::cin >> port;

    Client client;
    std::cout << "connecting to server...\n";
    tcp::socket socket = client.resolve_and_connect(ip, port);
    std::cout << "connected!\n";

    std::thread receivethread(receiveLoop, std::ref(socket));
    receivethread.detach();

    while(true){
        std::string msg;
        std::getline(std::cin, msg);
        msg.append("\n");
        boost::asio::write(socket, boost::asio::buffer(msg));
    }
}