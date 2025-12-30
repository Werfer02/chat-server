    #include "client.hpp"
    
    tcp::resolver::results_type Client::resolve(std::string ip, std::string port){
        tcp::resolver resolver(io_context);
        return resolver.resolve(ip, port);
    }

    tcp::socket Client::connect(tcp::resolver::results_type endpoints){
        tcp::socket s(io_context);
        boost::asio::connect(s, endpoints);
        return s;
    }
    
    tcp::socket Client::resolve_and_connect(std::string ip, std::string port){
        auto endpoints = resolve(ip, port);
        tcp::socket s = connect(endpoints);
        return s;
    }