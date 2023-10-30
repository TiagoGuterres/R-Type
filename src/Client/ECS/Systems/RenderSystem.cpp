/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** RenderSystem
*/

#include "RenderSystem.hpp"

void RenderSystem::renderSprite(Entity entity, Registry reg) {
    Position position = std::any_cast<Position>(reg.getComponentEntity(entity, std::type_index(typeid(Position))));
    Scale scale = std::any_cast<Scale>(reg.getComponentEntity(entity, std::type_index(typeid(Scale))));
    Sprite sprite = std::any_cast<Sprite>(reg.getComponentEntity(entity, std::type_index(typeid(Sprite))));

    if (position.x < 1920) {
        sprite.sprite->setPosition({position.x, position.y});
        sprite.sprite->setScale({scale.x, scale.y});
        window.draw(*sprite.sprite);
    }
}

void RenderSystem::renderSpriteOn(Entity entity, Registry reg) {
    Position position = std::any_cast<Position>(reg.getComponentEntity(entity, std::type_index(typeid(Position))));
    Scale scale = std::any_cast<Scale>(reg.getComponentEntity(entity, std::type_index(typeid(Scale))));
    SpriteOn sprite = std::any_cast<SpriteOn>(reg.getComponentEntity(entity, std::type_index(typeid(SpriteOn))));

    if (position.x < 1920) {
        sprite.sprite->setPosition({position.x, position.y});
        sprite.sprite->setScale({scale.x, scale.y});
        window.draw(*sprite.sprite);
    }
}
