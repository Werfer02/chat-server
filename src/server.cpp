#include "server.hpp"

Server::Server() : ssl_context(ssl::context(ssl::context::sslv23)){
    ssl_context.use_certificate_chain_file("keys/server.crt");
    ssl_context.use_private_key_file("keys/server.key", ssl::context::pem);
}

ssl_socket Server::accept(int port){
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port));
    tcp::socket socket(io_context);
    acceptor.accept(socket);

    ssl_socket s(std::move(socket), ssl_context);
    s.handshake(ssl::stream_base::server);

    return s;
}