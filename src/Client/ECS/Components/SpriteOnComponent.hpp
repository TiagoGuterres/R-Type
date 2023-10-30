/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** SpriteOnComponent
*/

#pragma once
#include <SFML/Graphics.hpp>

struct SpriteOn {
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<sf::Texture> textureOn;
    std::shared_ptr<sf::Sprite> sprite;
    bool isActive;

    SpriteOn() : sprite(nullptr) {}

    SpriteOn(std::shared_ptr<sf::Texture> tmp, std::shared_ptr<sf::Texture> tmp2) {
        texture = tmp;
        textureOn = tmp2;
        sprite = std::make_shared<sf::Sprite>(*tmp);
        isActive = false;
    }
};
