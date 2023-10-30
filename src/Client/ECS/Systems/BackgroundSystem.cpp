/*
** EPITECH PROJECT, 2023
** Background
** File description:
** BackgroundSystem
*/

#include "BackgroundSystem.hpp"

/** @brief This Function move the background thanks to the position of the entity and the window, it also reset the position of the background when it's out of the window
 * @param registry 
 * @param window 
 * @param entity 
 * @return
*/ 
Registry BackgroundSystem::parallax(Registry &registry, sf::RenderWindow &window, Entity entity)
{
    Position position = std::any_cast<Position>(registry.getComponentEntity(entity, std::type_index(typeid(Position))));
    Sprite background = std::any_cast<Sprite>(registry.getComponentEntity(entity, std::type_index(typeid(Sprite))));

    if (position.x < -background.sprite->getGlobalBounds().width)
        position.x = window.getSize().x;
    else
        position.x -= 0.5;

    registry.setComponentIndex(entity.id, position);

    return registry;
}