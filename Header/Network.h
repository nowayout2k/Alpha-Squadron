//
// Created by Johnnie Otis on 5/26/24.
//

#ifndef SFML_CORE_HEADER_NETWORK_H_
#define SFML_CORE_HEADER_NETWORK_H_

#include <SFML/Network/UdpSocket.hpp>
#include <future>

class Network
{
public:
	/*
	sf::TcpSocket::connect: Connects the socket to a remote host.
	sf::TcpSocket::disconnect: Disconnects the socket from the remote host.
	sf::TcpSocket::send: Sends data over the TCP socket.
	sf::TcpSocket::receive: Receives data from the TCP socket.
	sf::UdpSocket::bind: Binds the socket to a specific port.
	sf::UdpSocket::unbind: Unbinds the socket from its port.
	sf::UdpSocket::send: Sends data over the UDP socket.
	sf::UdpSocket::receive: Receives data from the UDP socket.
	sf::Http::setHost: Sets the target host for HTTP requests.
	sf::Http::sendRequest: Sends an HTTP request to the target host.
	sf::Http::send: Sends a custom HTTP request to the target host.
	sf::Ftp::connect: Connects to an FTP server.
	sf::Ftp::login: Logs in to the FTP server with a username and password.
	sf::Ftp::download: Downloads a file from the FTP server.
	sf::Ftp::upload: Uploads a file to the FTP server.
	sf::Packet::clear: Clears the packet's contents.
	sf::Packet::append: Appends data to the packet.
	sf::Packet::extract: Extracts data from the packet.
	sf::IpAddress::getLocalAddress: Gets the local machine's IP address.
	sf::IpAddress::getPublicAddress: Gets the public IP address of the machine.
	sf::IpAddress::resolve: Resolves a host name to an IP address.
	 */

	static sf::Socket::Status OpenPort();
	static void ClosePort();
	static std::future<std::string> HttpRequestAsync(const std::string& hostUrl, const std::string& uri);
	static sf::Socket::Status ReceiveData();
private:
	static std::string SendRequest(const std::string& hostUrl, const std::string& uri);
	static sf::UdpSocket socket;
};


#endif //SFML_CORE_HEADER_NETWORK_H_
