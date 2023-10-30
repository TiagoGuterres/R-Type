/*
** EPITECH PROJECT, 2023
** AudioComponent
** File description:
** SoundsComponent
*/

#pragma once

#include <SFML/Audio.hpp>
#include <memory>

struct Sounds {
    std::shared_ptr<sf::SoundBuffer> buffer;
    std::shared_ptr<sf::Sound> sound;

    Sounds() : sound(nullptr) {}

    Sounds(std::shared_ptr<sf::SoundBuffer> tmp) {
        buffer = tmp;
        sound = std::make_shared<sf::Sound>(*buffer);
    }
};