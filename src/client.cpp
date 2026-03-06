#include "client.hpp"

Client::Client() : ssl_context(ssl::context(ssl::context::sslv23)) {}

tcp::resolver::results_type Client::resolve(std::string ip, std::string port){
    tcp::resolver resolver(io_context);
    return resolver.resolve(ip, port);
}

ssl_socket Client::connect(tcp::resolver::results_type endpoints){
    ssl_socket s(io_context, ssl_context);
    boost::asio::connect(s.lowest_layer(), endpoints);
    s.handshake(ssl::stream<tcp::socket>::client);
    return s;
}

ssl_socket Client::resolve_and_connect(std::string ip, std::string port){
    auto endpoints = resolve(ip, port);
    ssl_socket s = connect(endpoints);
    return s;
}