/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** Registry
*/

#pragma once
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <typeinfo>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <any>
#include <typeinfo>

#include "../ECS/Entities/Entity.hpp"

#include "../ECS/Components/PlayableComponent.hpp"
#include "../ECS/Components/PositionComponent.hpp"
#include "../ECS/Components/SizeComponent.hpp"
#include "../ECS/Components/SpriteComponent.hpp"
#include "../ECS/Components/SpriteOnComponent.hpp"
#include "../ECS/Components/ScaleComponent.hpp"
#include "../ECS/Components/ClickableComponent.hpp"
#include "../ECS/Components/SpeedComponent.hpp"
#include "../ECS/Components/LayerComponent.hpp"
#include "../ECS/Components/EnemyComponent.hpp"
#include "../ECS/Components/HealthComponent.hpp"
#include "../ECS/Components/BulletComponent.hpp"
#include "../ECS/Components/PatternComponent.hpp"
#include "../ECS/Components/isBackground.hpp"
#include "../ECS/Components/InvincibleComponent.hpp"
#include "../ECS/Components/InvisibleComponent.hpp"
#include "../ECS/Components/BonusComponent.hpp"
#include "../ECS/Components/OrientationComponent.hpp"
#include "../ECS/Components/WeaponComponent.hpp"
#include "../ECS/Components/PowerComponent.hpp"
#include "../ECS/Components/HpBarComponent.hpp"

class Registry {
    public:
        void addComponent(Entity entity, std::any component) {_components[entity.id].push_back(component);};

        std::any getComponentEntity(Entity entity, std::type_index);

        std::vector<int> getComponentIndex(std::type_index);

        std::unordered_map<int, std::vector<std::any>> getComponents() {return _components;};

        std::unordered_map<int, std::any> getSpecificComponent(std::type_index);

        int getMaxEntityId();
        Entity getEntityFromID(int id) {return Entity{id};};
        bool isEntityExist(int id);
        bool isComponentInEntity(Entity, std::type_index);

        void setComponentIndex(int index, std::any comp) {_components[index].at(whichComponentIndex(index, comp.type())) = comp;};

        void setLevel(std::string tmp) {_level = tmp;};
        std::string getLevel() {return _level;};

        int whichComponentIndex(int id, std::type_index);

        void removeEntity(Entity entity);

    protected:

    private:
        std::unordered_map<int, std::vector<std::any>> _components;

        std::unordered_map<int, Entity> _entities;

        std::string _level;
};
