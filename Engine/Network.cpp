//
// Created by Johnnie Otis on 5/26/24.
//

#include "Network.h"
#include "Debug.h"
#include <SFML/Network.hpp>
#include <iostream>

sf::UdpSocket Network::m_socket;

std::future<std::string> Network::httpRequestAsync(const std::string& hostUrl, const std::string& uri)
{
	return std::async(std::launch::async, &sendRequest, hostUrl, uri);
}

std::string Network::sendRequest(const std::string& hostUrl, const std::string& uri)
{
	// HTTP example
	sf::Http http(hostUrl);
	sf::Http::Request request(uri);
	sf::Http::Response response = http.sendRequest(request);

	Debug::log("Status: " + std::to_string(response.getStatus()));
	Debug::log("Response body: " + response.getBody());
	return response.getBody();
}

sf::Socket::Status Network::openPort()
{
    return m_socket.bind(54000);
}

void Network::closePort()
{
	m_socket.unbind();
}

sf::Socket::Status Network::receiveData()
{
    char data[100];
    std::size_t received;
    sf::IpAddress sender;
    unsigned short port;

    sf::Socket::Status status = m_socket.receive(data, 100, received, sender, port);

	Debug::log("Received " + std::to_string(received) + " bytes from " + sender.toString() + " on port "
			+ std::to_string(port));
    return status;
}
