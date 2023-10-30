/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** UpdateSystem
*/

#include "UpdateSystem.hpp"
#include "CollisionSystem.hpp"

SpriteOn UpdateSystem::updateOn(Registry& registry, Entity entity) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition();
    sf::Vector2f spritePosition;
    sf::Vector2f spriteSize;
    sf::Vector2f spriteScale;
    SpriteOn spriteOn = std::any_cast<SpriteOn>(registry.getComponentEntity(entity, std::type_index(typeid(SpriteOn))));

    for (int i = 0; i != registry.getComponentIndex(std::type_index(typeid(Scale))).size(); i++)
        if (entity.id == registry.getComponentIndex(std::type_index(typeid(Scale))).at(i)) {
            Scale scale = std::any_cast<Scale>(registry.getComponentEntity(entity, std::type_index(typeid(Scale))));
            spriteScale = {scale.x, scale.y};
        }
    for (int i = 0; i != registry.getComponentIndex(std::type_index(typeid(Position))).size(); i++)
        if (entity.id == registry.getComponentIndex(std::type_index(typeid(Position))).at(i)) {
            Position position = std::any_cast<Position>(registry.getComponentEntity(entity, std::type_index(typeid(Position))));
            spritePosition = {position.x, position.y + 50};
        }
    for (int i = 0; i != registry.getComponentIndex(std::type_index(typeid(Size))).size(); i++)
        if (entity.id == registry.getComponentIndex(std::type_index(typeid(Size))).at(i)) {
            Size size = std::any_cast<Size>(registry.getComponentEntity(entity, std::type_index(typeid(Size))));
            spriteSize = {size.width * spriteScale.x + spritePosition.x, size.height  * spriteScale.y + spritePosition.y};
        }

    if (mousePosition.x <= spriteSize.x && mousePosition.x >= spritePosition.x)
        if (mousePosition.y <= spriteSize.y && mousePosition.y >= spritePosition.y)
            if (!spriteOn.isActive) {
                spriteOn.sprite->setTexture(*spriteOn.textureOn);
                spriteOn.isActive = true;
            }
    if (mousePosition.x > spriteSize.x || mousePosition.x < spritePosition.x)
        if (spriteOn.isActive) {
                spriteOn.sprite->setTexture(*spriteOn.texture);
                spriteOn.isActive = false;
            }
    if (mousePosition.y > spriteSize.y || mousePosition.y < spritePosition.y)
        if (spriteOn.isActive) {
                spriteOn.sprite->setTexture(*spriteOn.texture);
                spriteOn.isActive = false;
            }

    return spriteOn;
}

bool UpdateSystem::updateClick(Registry& registry, Entity entity)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition();
    sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y - 50));
    SpriteOn spriteOn = std::any_cast<SpriteOn>(registry.getComponentEntity(entity, std::type_index(typeid(SpriteOn))));


    if (spriteOn.sprite->getGlobalBounds().contains(mousePositionF) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        return true;
    }
    return false;
}

Registry UpdateSystem::updateBulletMovement(Registry& registry, Entity entity)
{
    Speed speed = std::any_cast<Speed>(registry.getComponentEntity(entity, std::type_index(typeid(Speed))));
    Position position = std::any_cast<Position>(registry.getComponentEntity(entity, std::type_index(typeid(Position))));
    CollisionSystem collisionSystem;

    position.x += speed.speed_x;
    position.y += speed.speed_y;

    if (position.x > 1920 || position.y > 1080) {
        registry.removeEntity(entity);
    } else {
        registry = collisionSystem.areEnemiesSpritesColliding(registry, entity);
        std::vector<int> bullets = registry.getComponentIndex(std::type_index(typeid(Bullet)));
        for (int i = 0; i != bullets.size(); i++)
            if (bullets.at(i) == entity.id)
                registry.setComponentIndex(entity.id, position);
    }
    return registry;
}

Registry UpdateSystem::updateEnnemy(Registry& reg, Entity entity, bool screen)
{
    Pattern pattern = std::any_cast<Pattern>(reg.getComponentEntity(entity, std::type_index(typeid(Pattern))));
    CollisionSystem colls;
    Position position = std::any_cast<Position>(reg.getComponentEntity(entity, std::type_index(typeid(Position))));
    Speed speed = std::any_cast<Speed>(reg.getComponentEntity(entity, std::type_index(typeid(Speed))));

    for (auto entry : reg.getSpecificComponent(std::type_index(typeid(Playable)))) {
        Entity ent = reg.getEntityFromID(entry.first);
        Position playerPosition = std::any_cast<Position>(reg.getComponentEntity(ent, std::type_index(typeid(Position))));
        if (pattern.pattern == "static") {
            if (screen && !colls.isWallHere(reg, entity, sf::Vector2f(-0.5, 0)))
                position.x -= 0.5;
            reg.setComponentIndex(entity.id, position);
            return reg;
        }
        if (pattern.pattern == "left\0") {
            if (screen && !colls.isWallHere(reg, entity, sf::Vector2f(-speed.speed_x - 0.5, 0)))
                position.x -= speed.speed_x - 0.5;
            else if (!colls.isWallHere(reg, entity, sf::Vector2f(-speed.speed_x, 0)))
                position.x -= speed.speed_x;
            reg.setComponentIndex(entity.id, position);
            return reg;
        }
        if (pattern.pattern == "top_bot\0") {
            if (screen && !colls.isWallHere(reg, entity, sf::Vector2f(-0.5, 0))) {
                position.x -= 0.5;
            }
            if (!colls.isWallHere(reg, entity, sf::Vector2f(0, speed.speed_y)))
                position.y += speed.speed_y;
            if (position.y >= 800 || position.y <= 200)
                speed.speed_y = -speed.speed_y;
            reg.setComponentIndex(entity.id, position);
            reg.setComponentIndex(entity.id, speed);
            return reg;
        }
        if (pattern.pattern == "bot\0") {
            if (!colls.isWallHere(reg, entity, sf::Vector2f(-speed.speed_x, 0)))
                position.x -= speed.speed_x;
            if (position.y < playerPosition.y && !colls.isWallHere(reg, entity, sf::Vector2f(0, speed.speed_y)))
                position.y += speed.speed_y;
            else if (position.y > playerPosition.y && !colls.isWallHere(reg, entity, sf::Vector2f(0, -speed.speed_y)))
                position.y -= speed.speed_y;
            reg.setComponentIndex(entity.id, position);
            reg.setComponentIndex(entity.id, speed);
            return reg;
        }
    }
    return reg;
}

Registry UpdateSystem::updateWalls(Registry& reg, Entity entity, bool screen)
{
    Position position = std::any_cast<Position>(reg.getComponentEntity(entity, std::type_index(typeid(Position))));
    Orientation orientation =  std::any_cast<Orientation>(reg.getComponentEntity(entity, std::type_index(typeid(Orientation))));
    Sprite sprite =  std::any_cast<Sprite>(reg.getComponentEntity(entity, std::type_index(typeid(Sprite))));

    if (orientation.actual_orientation != orientation.orientation) {
        orientation.actual_orientation = orientation.orientation;
        sprite.sprite->rotate(90);
        reg.setComponentIndex(entity.id, sprite);
        reg.setComponentIndex(entity.id, orientation);
    }
    if (screen)
        position.x -= 0.5;
    reg.setComponentIndex(entity.id, position);
    return reg;
}

Registry UpdateSystem::updatePlayerHp(Registry& reg, Entity entity)
{
    Health playerHP = std::any_cast<Health>(reg.getComponentEntity(entity, std::type_index(typeid(Health))));
    Position playerPose = std::any_cast<Position>(reg.getComponentEntity(entity, std::type_index(typeid(Position))));
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    Entity bar;
    Position pose;
    Scale scale;
    Layer layer;
    Invisible invisible;
    HpBar hp;

    if (reg.getSpecificComponent(std::type_index(typeid(HpBar))).empty()) {
        if (texture->loadFromFile("../assets/health.png")) {
            Sprite sprite(texture);
            scale.x = 1;
            scale.y = 1;
            pose.y = playerPose.y + 60;
            pose.x = playerPose.x;
            layer.layer = 3;
            invisible.isInvisible = false;
            bar.id = reg.getMaxEntityId() + 1;
            hp.isHpBar = true;
            reg.addComponent(bar, pose);
            reg.addComponent(bar, sprite);
            reg.addComponent(bar, scale);
            reg.addComponent(bar, layer);
            reg.addComponent(bar, invisible);
            reg.addComponent(bar, hp);
        }
        return reg;
    } else {
        for (auto entry : _registry.getSpecificComponent(std::type_index(typeid(HpBar)))) {
            Entity bar = _registry.getEntityFromID(entry.first);
            Scale barScale = std::any_cast<Scale>(_registry.getComponentEntity(bar, std::type_index(typeid(Scale))));
            scale.x = float(playerHP.hp) / float(playerHP.maxHp);
            scale.y = barScale.y;
            pose.y = playerPose.y + 60;
            pose.x = playerPose.x;
            reg.setComponentIndex(bar.id, scale);
            reg.setComponentIndex(bar.id, pose);
        }
    }
   
    return reg;
}
