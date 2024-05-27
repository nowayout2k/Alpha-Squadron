//
// Created by Johnnie Otis on 5/26/24.
//

#include "../Header/Network.h"
#include <SFML/Network.hpp>
#include <iostream>

void Network::HttpRequest()
{
    // HTTP example
    sf::Http http("http://www.example.com");
    sf::Http::Request request("/");
    sf::Http::Response response = http.sendRequest(request);

    std::cout << "Status: " << response.getStatus() << std::endl;
    std::cout << "Response body: " << response.getBody() << std::endl;
}

sf::Socket::Status Network::OpenPort()
{
    return socket.bind(54000);
}

void Network::ClosePort()
{
	socket.unbind();
}

sf::Socket::Status Network::ReceiveData()
{
    char data[100];
    std::size_t received;
    sf::IpAddress sender;
    unsigned short port;

    sf::Socket::Status status = socket.receive(data, 100, received, sender, port);

    std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;
    return status;
}
