/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"

bool CollisionSystem::areSpritesColliding(Registry registry, Entity entity1, Entity entity2)
{
    Position pos1 = std::any_cast<Position>(registry.getComponentEntity(entity1, std::type_index(typeid(Position))));
    Size siz1 = std::any_cast<Size>(registry.getComponentEntity(entity1, std::type_index(typeid(Size))));
    Position pos2 = std::any_cast<Position>(registry.getComponentEntity(entity2, std::type_index(typeid(Position))));
    Size siz2 = std::any_cast<Size>(registry.getComponentEntity(entity2, std::type_index(typeid(Size))));

    sf::FloatRect hitbox1(pos1.x, pos1.y, siz1.width, siz1.height);
    sf::FloatRect hitbox2(pos2.x, pos2.y, siz2.width, siz2.height);
    if (hitbox1.intersects(hitbox2))
        return true;
    return false;
}

Registry CollisionSystem::areEnemiesSpritesColliding(Registry registry, Entity entity) {
    static std::unordered_map<int, sf::Clock> entitiesLastHitTime;
    sf::Time timeLimit = sf::seconds(1.0);

    for (auto entry : registry.getSpecificComponent(std::type_index(typeid(Enemy)))) {
        Entity enemy = registry.getEntityFromID(entry.first);
        Power entityPower = std::any_cast<Power>(registry.getComponentEntity(entity, std::type_index(typeid(Power))));
        Power enemyPower = std::any_cast<Power>(registry.getComponentEntity(enemy, std::type_index(typeid(Power))));

        if (entitiesLastHitTime.find(entity.id) != entitiesLastHitTime.end()) {
            sf::Time lastHitTime = entitiesLastHitTime[entity.id].getElapsedTime();
            if (lastHitTime < timeLimit) {
                continue;
            }
        }

        if (areSpritesColliding(registry, entity, enemy)) {
            Health health = std::any_cast<Health>(registry.getComponentEntity(entity, std::type_index(typeid(Health))));
            health.hp -= enemyPower.power;
            registry.setComponentIndex(entity.id, health);

            entitiesLastHitTime[entity.id].restart();

            Health enemyHealth = std::any_cast<Health>(registry.getComponentEntity(enemy, std::type_index(typeid(Health))));
            enemyHealth.hp -= entityPower.power;
            registry.setComponentIndex(enemy.id, enemyHealth);

            if (enemyHealth.hp <= 0) {
                registry.removeEntity(enemy);
            }

            if (health.hp <= 0) {
                registry.removeEntity(entity);
                return registry;
            }
        }
    }
    return registry;
}

bool CollisionSystem::isWallHere(Registry registry, Entity entity, sf::Vector2f position)
{
    for (auto entry : registry.getSpecificComponent(std::type_index(typeid(Orientation)))) {
        Entity wall = registry.getEntityFromID(entry.first);
        Position pose = std::any_cast<Position>(registry.getComponentEntity(entity, std::type_index(typeid(Position))));
        pose.x += position.x;
        pose.y += position.y;
        registry.setComponentIndex(entity.id, pose);
        if (areSpritesColliding(registry, entity, wall)) {
            return true;
        }
        pose.x -= position.x;
        pose.y -= position.y;
        registry.setComponentIndex(entity.id, pose);
    }
    return false;
}