#include "server.hpp"

tcp::socket Server::accept(int port){
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port));
    tcp::socket socket(io_context);
    acceptor.accept(socket);
    return socket;
}