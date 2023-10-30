/*
** EPITECH PROJECT, 2023
** Background
** File description:
** BackgroundSystem
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "../../Registry/Registry.hpp"

class BackgroundSystem {
public:
    BackgroundSystem(Registry &registry, sf::RenderWindow &window) : _registry(registry), _window(window) {}

    Registry parallax (Registry &registry, sf::RenderWindow &window, Entity entity);
private:
    Registry& _registry;
    sf::RenderWindow& _window;
};
