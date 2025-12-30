#include <iostream>
#include <thread>

#include "chat.hpp"
#include "client.hpp"
#include "server.hpp"
#include "util.hpp"

void receiveLoop(tcp::socket& s, Chat& c){
    std::string received;
    while(true){
        received = receive(s);
        c.addMessage({received, (c.username == "Client" ? "Server" : "Client")});
        std::cout << "\033[H\033[J" << c;
    }
}

#ifdef _WIN32
    void initConsole() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode;
        GetConsoleMode(hConsole, &mode);
        SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
#else
    void initConsole() {}
#endif

int main(){
    std::cout << "hello world\n\n";

    initConsole();

    Chat chat;

    std::string choice;
    std::cout << "client or server:";
    
    if(choice == "Client" || choice == "client" || choice == "C" || choice == "c"){
        choice = "Client";
        std::string ip, port;
    
        std::cout << "ip to connect to:";
        std::cin >> ip;
        std::cout << "port:";
        std::cin >> port;

        Client client;
        std::cout << "connecting to server...\n";
        tcp::socket socket = client.resolve_and_connect(ip, port);
        std::cout << "connected!\n";

        std::thread receivethread(receiveLoop, std::ref(socket), std::ref(chat));
        receivethread.detach();
    }
    else if(choice == "Server" || choice == "server" || choice == "S" || choice == "s"){
        choice = "Server";
        std::string port;

        std::cout << "port to listen on:";
        std::cin >> port;

        Server server;
        std::cout << "listening on port " << port << "...\n";
        tcp::socket socket = server.accept(stoi(port));
        std::cout << "connected!";

        std::thread receivethread(receiveLoop, std::ref(socket), std::ref(chat));
        receivethread.detach();
    }
    else {
        std::cout << "WRONG!!!\n";
        return;
    }

    while(true){
        std::string msg;
        std::getline(std::cin, msg);

        chat.addMessage({msg, choice});
        std::cout << "\033[H\033[J" << chat;

        msg.append("\n");
        boost::asio::write(socket, boost::asio::buffer(msg));
    }
}