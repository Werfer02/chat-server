#include <iostream>
#include <thread>
#include "boost/asio.hpp"

using boost::asio::ip::tcp;

class Server {
    boost::asio::io_context io_context;
public:
    tcp::socket accept(int port){
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port));
        tcp::socket socket(io_context);
        acceptor.accept(socket);
        return socket;
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
        std::cout << "[Client]: " << received << "\n";
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

    std::string port;
    std::cout << "port to listen on:";
    std::cin >> port;

    Server server;

    std::cout << "listening on port " << port << "...\n";
    tcp::socket socket = server.accept(stoi(port));
    std::cout << "client connected!\n";

    std::thread receivethread(receiveLoop, std::ref(socket));
    receivethread.detach();

    while(true){
        std::string msg;
        std::getline(std::cin, msg);
        msg.append("\n");
        boost::asio::write(socket, boost::asio::buffer(msg));
    }
    
}