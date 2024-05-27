//
// Created by Johnnie Otis on 5/26/24.
//

#ifndef SFML_CORE_HEADER_NETWORK_H_
#define SFML_CORE_HEADER_NETWORK_H_

#include <SFML/Network/UdpSocket.hpp>

class Network
{
public:
    sf::Socket::Status OpenPort();
    void ClosePort();
    void HttpRequest();
    sf::Socket::Status ReceiveData();
private:
    sf::UdpSocket socket;
};


#endif //SFML_CORE_HEADER_NETWORK_H_
