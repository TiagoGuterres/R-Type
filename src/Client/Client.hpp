/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** Client
*/

#pragma once

#include <SFML/Network.hpp>
#include "../bits/stdc++.hpp"

class Client {
    public:
        Client(const sf::IpAddress &serverIp, unsigned short serverPort);
        ~Client();
        void run();
        void sendDataConnect();
        int receiveDataConnect(sf::IpAddress remoteAddress, unsigned short remotePort, std::string response);

        void sendDataDisconnect();
        int receiveDataDisconnect(sf::IpAddress remoteAddress, unsigned short remotePort, std::string response);
        int receiveData();
        bool getIsConnected() const
        {
            return _isConnected;
        }
        
        static Client *getInstance()
        {
            return _instanceClient;
        }
        static Client *initInstance(char **av)
        {
            if (_instanceClient != nullptr)
                throw std::runtime_error("Error: Client::initInstance: Client already initialized");
            _instanceClient = new Client(sf::IpAddress::LocalHost, std::stoi(av[2]));
            return _instanceClient;
        }

    protected:
    private:
        static Client *_instanceClient;
        sf::UdpSocket _socket;
        sf::IpAddress _serverIp;
        unsigned short _serverPort;
        bool _isConnected = false;
};
