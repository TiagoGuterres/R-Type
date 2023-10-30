/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** CollisionSystem
*/

#pragma once

#include "../../Registry/Registry.hpp"

class CollisionSystem {
    public:
        bool areSpritesColliding(Registry, Entity, Entity);
        Registry areEnemiesSpritesColliding(Registry, Entity);
        bool isWallHere(Registry, Entity, sf::Vector2f);
    protected:
    private:
};
