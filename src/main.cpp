#include <iostream>
#include <thread>

#include "chat.hpp"
#include "client.hpp"
#include "server.hpp"
#include "util.hpp"

void receiveLoop(tcp::socket& s, Chat& c){
    ChatMessage received;
    while(true){
        received = receiveMessage(s);
        c.addMessage(received);
        std::cout << clearScreen << c;
    }
}

void writeLoop(tcp::socket& s, Chat& c){
    while(true){
        std::string msg;
        std::getline(std::cin, msg);

        sendMessage(s, msg, c.username);

        c.addMessage({msg, c.username});
        std::cout << clearScreen << c;
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
    std::cin >> choice;
    
    if(choice == "Client" || choice == "client" || choice == "C" || choice == "c"){
        chat.username = "Client";
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
        writeLoop(socket, chat);
    }
    else if(choice == "Server" || choice == "server" || choice == "S" || choice == "s"){
        chat.username = "Server";
        std::string port;

        std::cout << "port to listen on:";
        std::cin >> port;

        Server server;
        std::cout << "listening on port " << port << "...\n";
        tcp::socket socket = server.accept(stoi(port));
        std::cout << "connected!";

        std::thread receivethread(receiveLoop, std::ref(socket), std::ref(chat));
        receivethread.detach();
        writeLoop(socket, chat);
    }
    else {
        std::cout << "WRONG!!!\n";
        return 1;
    }
}