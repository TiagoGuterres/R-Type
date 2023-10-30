/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** Game
*/

#pragma once

#include "../Registry/Registry.hpp"
#include "../Client.hpp"
#include "../ECS/Systems/UpdateSystem.hpp"
#include "../ECS/Systems/PlayableSystem.hpp"
#include "../ECS/Systems/RenderSystem.hpp"
#include "../ECS/Systems/BackgroundSystem.hpp"
#include "../Levels/Level.hpp"

class Game {
    public:
        Game(std::string port);
        ~Game() = default;

        int gameMain(char **av);
        void windowDraw(sf::RenderWindow &window);
        void changeLvl(Client &client, sf::RenderWindow &window);
        void updateEntities(sf::RenderWindow &window);

    protected:
    private:
        Registry _registry;
        std::string _port;

        bool _skibidi;
        bool _isConnected = false;
};
