/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** Level
*/

#pragma once
#include <string>
#include <iostream>
#include <fstream>

#include "../Registry/Registry.hpp"

class Level {
public:
    Level(std::string filename) {loadLevel(filename);}

    void loadLevel(std::string filename);

    Registry getRegistry() {return _registry;};

    Entity createEntity();

    Bonus createRandomBonus();
private:

    Registry _registry;
};
