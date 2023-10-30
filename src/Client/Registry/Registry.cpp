/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** Registry
*/

#include "Registry.hpp"

int Registry::getMaxEntityId() 
{
    int maxId = 0;
    for (auto entry : _components) {
        maxId = std::max(maxId, entry.first);
    }

    return maxId;
}

std::vector<int> Registry::getComponentIndex(std::type_index type) {
    std::vector<int> ret;

    for (const auto& entry : _components)
        for (int i = 0; i != entry.second.size(); i++)
            if (whichComponentIndex(entry.first, type) != -1)
                ret.push_back(entry.first);
    return ret;
}

void Registry::removeEntity(Entity entity)
{
    _components.erase(entity.id);
    _entities.erase(entity.id);
}

int Registry::whichComponentIndex(int id, std::type_index type)
{
    for (int i = 0; i != _components[id].size(); i++)
        if (_components[id].at(i).type() == type)
            return i;
    return -1;
}

std::any Registry::getComponentEntity(Entity entity, std::type_index type)
{
    for (int i = 0; i != _components[entity.id].size(); i++)
        if (_components[entity.id].at(i).type() == type)
            return _components[entity.id].at(i);
    return 0;
}

std::unordered_map<int, std::any> Registry::getSpecificComponent(std::type_index type)
{
    std::unordered_map<int, std::any> ret;
    int verifIndex;

    for (const auto& entry : _components)
        for (int i = 0; i != entry.second.size(); i++) {
            verifIndex = whichComponentIndex(entry.first, type);
            if (verifIndex != -1)
                ret[entry.first] = entry.second.at(verifIndex);
        }
    return ret;
}

bool Registry::isEntityExist(int id)
{
    for (const auto& entry : _components)
        if (entry.first == id)
            return true;
    return false;
}

bool Registry::isComponentInEntity(Entity entity, std::type_index comp)
{
    std::vector<int> allComp = getComponentIndex(comp);

    for (int i = 0; i != allComp.size(); i++)
        if (allComp.at(i) == entity.id)
            return true;
    return false;
}