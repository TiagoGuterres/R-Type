/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** SpriteComponent
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

struct Sprite {
    std::shared_ptr<sf::Sprite> sprite;
    std::shared_ptr<sf::Texture> texture;

    Sprite() : sprite(nullptr) {}

    Sprite(std::shared_ptr<sf::Texture> tmp) {
        texture = tmp;
        sprite = std::make_shared<sf::Sprite>(*texture);
    }
};
