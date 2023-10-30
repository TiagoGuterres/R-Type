/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** Server
*/

#pragma once

#include <SFML/Network.hpp>
#include "../bits/stdc++.hpp"

class Server {
    public:
        Server(unsigned short port);
        ~Server();
        void run();
        void receiveDataConnect(sf::IpAddress remoteAddress, unsigned short remotePort, std::string response);
        void receiveDataDisconnect(sf::IpAddress remoteAddress, unsigned short remotePort, std::string response);

    protected:
    private:
        std::vector<sf::IpAddress> _connectPlayers;
        std::vector<sf::IpAddress> _disconnectPlayers;
        int playeralreadyconnected = 0;
        sf::UdpSocket _socket;
        void receiveData();


};


