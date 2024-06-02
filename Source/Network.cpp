//
// Created by Johnnie Otis on 5/26/24.
//

#include "../Header/Network.h"
#include "../Header/Logger.h"
#include <SFML/Network.hpp>
#include <iostream>

sf::UdpSocket Network::socket;

std::future<std::string> Network::HttpRequestAsync(const std::string& hostUrl, const std::string& uri)
{
	return std::async(std::launch::async, &SendRequest, hostUrl, uri);
}

std::string Network::SendRequest(const std::string& hostUrl, const std::string& uri)
{
	// HTTP example
	sf::Http http(hostUrl);
	sf::Http::Request request(uri);
	sf::Http::Response response = http.sendRequest(request);

	Logger::Log(LogType::Verbose, "Status: " + std::to_string(response.getStatus()));
	Logger::Log(LogType::Verbose, "Response body: " + response.getBody());
	return response.getBody();
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

	Logger::Log(LogType::Verbose,  "Received " + std::to_string(received) + " bytes from " + sender.toString() + " on port " + std::to_string(port));
    return status;
}
