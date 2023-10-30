/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** Server
*/

#include "Server.hpp"
#include <optional>

Server::Server(unsigned short port)
{
    if (_socket.bind(port) != sf::Socket::Status::Done)
        throw std::runtime_error("Error: could not bind socket");
}

void Server::run()
{
    while (true) {
        std::cout << "Waiting for data..." << std::endl;
        receiveData();
    }
}

void Server::receiveDataConnect(sf::IpAddress remoteAddress, unsigned short remotePort, std::string response)
{
    if (response == "Connect") {
        if (_connectPlayers.size() == 0) {
            playeralreadyconnected = 0;
        }
        if (playeralreadyconnected >= 4) {
            sf::Packet rejectPacket;
            rejectPacket << "Refused";
            std::cout << "Player rejected: " << remoteAddress << ":" << remotePort << std::endl;
             if (_socket.send(rejectPacket, remoteAddress, remotePort) != sf::Socket::Status::Done)
                std::cerr << "Error: cannot send message" << std::endl;
            playeralreadyconnected = 4;
            return;
        }
        if (_connectPlayers.size() < 4) {
            playeralreadyconnected++;
            _connectPlayers.push_back(remoteAddress);
            std::cout << "number of players: " << _connectPlayers.size() << std::endl;
            std::cout << "number of players already connected: " << playeralreadyconnected << std::endl;
            std::cout << "New player connected: " << remoteAddress << ":" << remotePort << std::endl;
            sf::Packet acceptPacket;
            acceptPacket << "Connected";
            if (_socket.send(acceptPacket, remoteAddress, remotePort) != sf::Socket::Status::Done)
                std::cerr << "Error: cannot send message" << std::endl;
        } else {
            sf::Packet rejectPacket;
            rejectPacket << "Refused";
            std::cout << "Player rejected: " << remoteAddress << ":" << remotePort << std::endl;
             if (_socket.send(rejectPacket, remoteAddress, remotePort) != sf::Socket::Status::Done)
                std::cerr << "Error: cannot send message" << std::endl;
        }
    }
    response.clear();
}

void Server::receiveDataDisconnect(sf::IpAddress remoteAddress, unsigned short remotePort, std::string response)
{
    if (response == "Disconnect") {
        sf::Packet disconnectPacket;
        disconnectPacket << "Disconnected";
        for (const auto &playerAddress : _connectPlayers) {
            if (_socket.send(disconnectPacket, playerAddress, remotePort) != sf::Socket::Status::Done)
                std::cerr << "Error: cannot send message" << std::endl;
        }
        std::cout << "Player disconnected: " << remoteAddress << ":" << remotePort << std::endl;
        auto it = std::find(_connectPlayers.begin(), _connectPlayers.end(), remoteAddress);
        if (it != _connectPlayers.end())
            _connectPlayers.erase(it);
        std::cout << "number of players: " << _connectPlayers.size() << std::endl;
    }
    response.clear();
}

void Server::receiveData()
{
    sf::IpAddress remoteAddress = sf::IpAddress::Any;
    unsigned short remotePort = 0;
    sf::Packet packet;

    if (_socket.receive(packet, remoteAddress, remotePort) == sf::Socket::Status::Done) {
        std::string response;
        packet >> response;
        receiveDataConnect(remoteAddress, remotePort, response);
        receiveDataDisconnect(remoteAddress, remotePort, response);
    }
}

Server::~Server()
{
    _socket.unbind();
}
