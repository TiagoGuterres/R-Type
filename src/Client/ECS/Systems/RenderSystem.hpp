/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** SizePoseSystem
*/

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../../Registry/Registry.hpp"

class RenderSystem {
    public:
        RenderSystem(sf::RenderWindow& window) : window(window) {}

        void renderSprite(Entity entity, Registry reg);
        void renderSpriteOn(Entity entity, Registry reg);
    private:
        sf::RenderWindow& window;
};
