/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** PlayableSystem
*/

#pragma once
#include <iostream>

#include "../../Registry/Registry.hpp"
#include "CollisionSystem.hpp"
#include <chrono>

class PlayableSystem {
    public:
        Registry controlPlayer(Registry &registry, bool screen);
        Registry shootMissile(Registry &registry, Entity entity);
        Registry changeWeapon(Registry &registry, Entity entity);

        Registry whichBullet(Registry &registry, Entity entity);
        Registry piercingBullet(Registry &registry, Entity entity);
        Registry bigBullet(Registry &registry, Entity entity);
        Registry enemyBullet(Registry &registry, Entity entity);

    private:
        std::chrono::high_resolution_clock::time_point _lastShootTime;
        std::chrono::seconds _shootCooldown = std::chrono::seconds(1);

        std::chrono::high_resolution_clock::time_point _lastDamageTime;
        std::chrono::seconds _damageCooldown = std::chrono::seconds(1);

        std::chrono::high_resolution_clock::time_point _lastWeaponTime;
        std::chrono::seconds _weaponCooldown = std::chrono::seconds(1);
};
