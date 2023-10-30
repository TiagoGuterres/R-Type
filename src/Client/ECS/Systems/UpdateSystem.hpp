/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** UpdateSystem
*/

#pragma once
#include <iostream>

#include "../../Registry/Registry.hpp"

class UpdateSystem {
    public :
        UpdateSystem(Registry& registry, sf::RenderWindow& window) : _registry(registry), _window(window) {}

        SpriteOn updateOn(Registry& reg, Entity entity);
        bool updateClick(Registry& reg, Entity entity);
        Registry updateBulletMovement(Registry& reg, Entity entity);
        Registry updateEnnemy(Registry& reg, Entity entity, bool screen);
        Registry updateWalls(Registry& reg, Entity entity, bool screen);
        Registry updatePlayerHp(Registry& reg, Entity entity);

    private:
        Registry& _registry;
        sf::RenderWindow& _window;
};
