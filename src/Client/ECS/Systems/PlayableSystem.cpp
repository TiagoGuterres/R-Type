/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** PlayableSystem
*/

#include "PlayableSystem.hpp"
#include <chrono>

Registry PlayableSystem::piercingBullet(Registry &registry, Entity entity)
{
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    Entity missile;
    Position pose = std::any_cast<Position>(registry.getComponentEntity(entity, std::type_index(typeid(Position))));
    Size size;
    Speed speed;
    Scale scale;
    Layer layer;
    Bullet bullet;
    Health health;
    Power power;
    Invisible invisible;
    if (texture->loadFromFile("../assets/piercingBullet.png")) {
        Sprite sprite(texture);
        speed.speed_x = 2;
        speed.speed_y = 0;
        scale.x = 2;
        scale.y = 2;
        size.width = 100;
        size.height = 50;
        pose.y = pose.y + (size.height) / 2;
        pose.x = pose.x + size.width;
        layer.layer = 1;
        power.power = 1;
        health.hp = 5;
        bullet.isBullet = true;
        invisible.isInvisible = false;
        missile.id = registry.getMaxEntityId() + 1;
        registry.addComponent(missile, pose);
        registry.addComponent(missile, speed);
        registry.addComponent(missile, sprite);
        registry.addComponent(missile, size);
        registry.addComponent(missile, scale);
        registry.addComponent(missile, layer);
        registry.addComponent(missile, bullet);
        registry.addComponent(missile, health);
        registry.addComponent(missile, power);
        registry.addComponent(missile, invisible);
    }
    return registry;
}

Registry PlayableSystem::bigBullet(Registry &registry, Entity entity)
{
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    Entity missile;
    Position pose = std::any_cast<Position>(registry.getComponentEntity(entity, std::type_index(typeid(Position))));
    Size size;
    Speed speed;
    Scale scale;
    Layer layer;
    Bullet bullet;
    Health health;
    Invisible invisible;
    Power power;
    if (texture->loadFromFile("../assets/bigBullet.png")) {
        Sprite sprite(texture);
        speed.speed_x = 2;
        speed.speed_y = 0;
        scale.x = 2;
        scale.y = 2;
        size.width = 100;
        size.height = 50;
        pose.y = pose.y + (size.height) / 2;
        pose.x = pose.x + size.width;
        layer.layer = 1;
        power.power = 3;
        health.hp = 1;
        invisible.isInvisible = false;
        bullet.isBullet = true;
        missile.id = registry.getMaxEntityId() + 1;
        registry.addComponent(missile, pose);
        registry.addComponent(missile, speed);
        registry.addComponent(missile, sprite);
        registry.addComponent(missile, size);
        registry.addComponent(missile, scale);
        registry.addComponent(missile, layer);
        registry.addComponent(missile, bullet);
        registry.addComponent(missile, health);
        registry.addComponent(missile, invisible);
        registry.addComponent(missile, power);
    }
    return registry;
}

Registry PlayableSystem::enemyBullet(Registry &registry, Entity entity)
{
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    Entity missile;
    Position pose = std::any_cast<Position>(registry.getComponentEntity(entity, std::type_index(typeid(Position))));
    Size size;
    Speed speed;
    Scale scale;
    Layer layer;
    Bullet bullet;
    Health health;
    Power power;
    Invisible invisible;
    if (texture->loadFromFile("../assets/piercingBullet.png")) {
        Sprite sprite(texture);
        speed.speed_x = -2;
        speed.speed_y = 0;
        scale.x = -2;
        scale.y = 2;
        size.width = 100;
        size.height = 50;
        pose.y = pose.y + (size.height) / 2;
        pose.x = pose.x + size.width;
        layer.layer = 1;
        power.power = 1;
        health.hp = 1;
        bullet.isBullet = true;
        invisible.isInvisible = false;
        missile.id = registry.getMaxEntityId() + 1;
        registry.addComponent(missile, pose);
        registry.addComponent(missile, speed);
        registry.addComponent(missile, sprite);
        registry.addComponent(missile, size);
        registry.addComponent(missile, scale);
        registry.addComponent(missile, layer);
        registry.addComponent(missile, bullet);
        registry.addComponent(missile, health);
        registry.addComponent(missile, power);
        registry.addComponent(missile, invisible);
    }
    return registry;
}

Registry PlayableSystem::whichBullet(Registry &registry, Entity entity)
{
    Weapon weapon = std::any_cast<Weapon>(registry.getComponentEntity(entity, std::type_index(typeid(Weapon))));

    if (weapon.active == 1)
        registry = piercingBullet(registry, entity);
    else if (weapon.active == 2)
        registry = bigBullet(registry, entity);
    return registry;
}

Registry PlayableSystem::shootMissile(Registry &registry, Entity entity)
{
    if (!registry.isComponentInEntity(entity, std::type_index(typeid(Weapon)))) {
        Weapon weapon;
        weapon.active = 1;
        weapon.inventory = 2;
        registry.addComponent(entity, weapon);
    }
    registry = whichBullet(registry, entity);

    return registry;
}

Registry PlayableSystem::controlPlayer(Registry &registry, bool screen)
{
    CollisionSystem colls;
    for (auto entry : registry.getSpecificComponent(std::type_index(typeid(Playable)))) {
        Entity entity = registry.getEntityFromID(entry.first);
        if (std::any_cast<Playable>(registry.getComponentEntity(entity, std::type_index(typeid(Playable)))).playable) {
            Position pose = std::any_cast<Position>(registry.getComponentEntity(entity, std::type_index(typeid(Position))));
            Size size = std::any_cast<Size>(registry.getComponentEntity(entity, std::type_index(typeid(Size))));
            Scale scale = std::any_cast<Scale>(registry.getComponentEntity(entity, std::type_index(typeid(Scale))));;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                if (pose.y >= 0 && !colls.isWallHere(registry, entity, sf::Vector2f(0, -2)))
                    pose.y = pose.y - 2;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                if (pose.y <= 1080 - size.height * (scale.y - 1)  && !colls.isWallHere(registry, entity, sf::Vector2f(0, 2)))
                    pose.y = pose.y + 2;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                if (pose.x >= 0  && !colls.isWallHere(registry, entity, sf::Vector2f(-2, 0)))
                    pose.x = pose.x - 2;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                if (!colls.isWallHere(registry, entity, sf::Vector2f(2, 0)))
                    pose.x = pose.x + 2;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                auto currentTime = std::chrono::high_resolution_clock::now();
                auto timeElapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - _lastShootTime);

                if (timeElapsed >= _shootCooldown) {
                    registry = shootMissile(registry, entity);
                    _lastShootTime = currentTime;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                auto currentTime = std::chrono::high_resolution_clock::now();
                auto timeElapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - _lastWeaponTime);

                if (timeElapsed >= _weaponCooldown) {
                    registry = changeWeapon(registry, entity);
                    _lastWeaponTime = currentTime;
                }
            }
            if (screen && pose.x > 0)
                pose.x -= 0.5;
            registry = colls.areEnemiesSpritesColliding(registry, entity);
            if (registry.isEntityExist(entity.id)) {
                registry.setComponentIndex(entity.id, pose);
                return registry;
            } else
                return registry;
        }
    }
    return registry;
}

Registry PlayableSystem::changeWeapon(Registry &registry, Entity entity)
{
    if (!registry.isComponentInEntity(entity, std::type_index(typeid(Weapon)))) {
        Weapon weapon;
        weapon.active = 1;
        weapon.inventory = 2;
        registry.addComponent(entity, weapon);
    }

    Weapon weapon = std::any_cast<Weapon>(registry.getComponentEntity(entity, std::type_index(typeid(Weapon))));
    int stock = weapon.active;

    weapon.active = weapon.inventory;
    weapon.inventory = stock;
    registry.setComponentIndex(entity.id, weapon);
    return registry;
}
