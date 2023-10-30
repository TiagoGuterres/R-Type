/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** Level
*/

#include "Level.hpp"

void Level::loadLevel(std::string filename) {
    std::ifstream file(filename);
    std::string line;
    Entity currentEntity;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line == "Entity") {
                currentEntity = createEntity();
            } else if (line == "Position") {
                Position position;
                file >> position.x >> position.y;
                _registry.addComponent(currentEntity, position);
            } else if (line == "Size") {
                Size size;
                file >> size.width >> size.height;
                _registry.addComponent(currentEntity, size);
            } else if (line == "Sprite") {
                std::string spritePath;
                file >> spritePath;
                std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
                Invisible invisible;
                invisible.isInvisible = false;
                if (texture->loadFromFile("../assets/" + spritePath)) {
                    Sprite sprite(texture);
                    _registry.addComponent(currentEntity, sprite);
                    _registry.addComponent(currentEntity, invisible);
                }
            } else if (line == "SpriteOn") {
                std::string spritePath;
                std::string spriteOnPath;
                file >> spritePath >> spriteOnPath;
                std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
                std::shared_ptr<sf::Texture> textureOn = std::make_shared<sf::Texture>();
                Invisible invisible;
                invisible.isInvisible = false;
                if (texture->loadFromFile("../assets/" + spritePath) && textureOn->loadFromFile("../assets/" + spriteOnPath)) {
                    SpriteOn spriteOn(texture, textureOn);
                    _registry.addComponent(currentEntity, spriteOn);
                    _registry.addComponent(currentEntity, invisible);
                }
            } else if (line == "Scale") {
                Scale scale;
                file >> scale.x >> scale.y;
                _registry.addComponent(currentEntity, scale);
            } else if (line == "Clickable") {
                std::string click;
                Clickable clickable;
                file >> click;
                if (click == "true")
                    clickable.clickable = true;
                else
                    clickable.clickable = false;
                _registry.addComponent(currentEntity, clickable);
            } else if (line == "Playable") {
                std::string play;
                Playable playable;
                file >> play;
                if (play == "true")
                    playable.playable = true;
                else
                    playable.playable = false;
                _registry.addComponent(currentEntity, playable);
            } else if (line == "Layer") {
                Layer layer;
                file >> layer.layer;
                _registry.addComponent(currentEntity, layer);
            } else if (line == "Enemy") {
                std::string enem;
                Enemy enemy;
                file >> enem;
                if (enem == "true")
                    enemy.isEnemy = true;
                else
                    enemy.isEnemy = false;
                _registry.addComponent(currentEntity, enemy);
            } else if (line == "Health") {
                Health health;
                file >> health.hp;
                health.maxHp = health.hp;
                _registry.addComponent(currentEntity, health);
            } else if (line == "Pattern") {
                Pattern pattern;
                file >> pattern.pattern;
                _registry.addComponent(currentEntity, pattern);
            } else if (line == "Speed") {
                Speed speed;
                file >> speed.speed_x >> speed.speed_y;
                _registry.addComponent(currentEntity, speed);
            } else if (line == "isBackground") {
                isBackground x;
                file >> x.x;
                _registry.addComponent(currentEntity, x);
            } else if (line == "Bonus") {
                Bonus bonus = createRandomBonus();
                _registry.addComponent(currentEntity, bonus);
            } else if (line == "Orientation") {
                Orientation orientation;
                file >> orientation.orientation;
                orientation.actual_orientation = 0;
                _registry.addComponent(currentEntity, orientation);
            } else if (line == "Power") {
                Power power;
                file >> power.power;
                _registry.addComponent(currentEntity, power);
            }
        }
        file.close();
    }
}

Bonus Level::createRandomBonus() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int random = (std::rand() % 1) + 1;
    Bonus bonus;

    if (random == 1) {
        bonus.bonus = "Piercing_bullets";
    }

    std::cout << random << std::endl;

    return bonus;
}

Entity Level::createEntity() {
    static int entityIdCounter = 0;
    return Entity{entityIdCounter++};
}
