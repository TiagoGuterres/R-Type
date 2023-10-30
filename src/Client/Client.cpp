/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** Client
*/

#include "Client.hpp"
#include <bits/stdc++.h>

Client *Client::_instanceClient = nullptr;

Client::Client(const sf::IpAddress &serverIp, unsigned short serverPort) : _serverIp(serverIp), _serverPort(serverPort), _isConnected(false)
{
    if (_socket.bind(sf::Socket::AnyPort) != sf::Socket::Status::Done)
        std::cerr << "Error: could not bind socket" << std::endl;
}

Client::~Client()
{
    _socket.unbind();
}

void Client::run()
{
    while (true) {
        if (receiveData() != 0)
            return;
    }
}

void Client::sendDataDisconnect()
{
    sf::Packet _connectionPacket;
    _connectionPacket << "Disconnect";
    if (_socket.send(_connectionPacket, _serverIp, _serverPort) != sf::Socket::Status::Done)
        std::cerr << "Error: cannot send message" << std::endl;
}

int Client::receiveDataDisconnect(sf::IpAddress remoteAddress, unsigned short remotePort, std::string response)
{
    if (response == "Disconnected") {
        std::cout << "Disconnected to the server" << std::endl;
        return 0;
    } else {
        std::cout << "Unknown response from server" << std::endl;
        return 1;
    }
}

void Client::sendDataConnect()
{
    sf::Packet _connectionPacket;
    _connectionPacket << "Connect";
    if (_socket.send(_connectionPacket, _serverIp, _serverPort) != sf::Socket::Status::Done)
        std::cerr << "Error: cannot send message" << std::endl;
}

int Client::receiveDataConnect(sf::IpAddress remoteAddress, unsigned short remotePort, std::string response)
{
    if (response == "Connected") {
        std::cout << "Connected to server" << std::endl;
        _isConnected = true;
        return 0;
    } else if (response == "Refused") {
        std::cout << "Server refused connection" << std::endl;
        _isConnected = false;
        return 1;
    } else {
        std::cout << "Unknown response from server" << std::endl;
        return 1;
    }
}

int Client::receiveData()
{
    sf::IpAddress remoteAddress = sf::IpAddress::Any;
    unsigned short remotePort = 0;
    std::string response;
    sf::Packet _Packet;
    std::cout << "Waiting for server response..." << std::endl;

    if (_socket.receive(_Packet, remoteAddress, remotePort) == sf::Socket::Status::Done) {
        _Packet >> response;
        if (receiveDataConnect(remoteAddress, remotePort, response) == 1)
            return 1;
        if (receiveDataDisconnect(remoteAddress, remotePort, response) == 1)
            return 1;
        response.clear();
    }
    return 0;
}
