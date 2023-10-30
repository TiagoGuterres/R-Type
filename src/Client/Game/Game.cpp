/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** Game
*/

#include "Game.hpp"

Game::Game(std::string port)
{
    _port = port;
}

void Game::updateEntities(sf::RenderWindow &window)
{
    UpdateSystem updateSystem(_registry, window);
    BackgroundSystem backgroundSystem(_registry, window);

    for (auto entry : _registry.getSpecificComponent(std::type_index(typeid(SpriteOn)))) {
        Entity entity = _registry.getEntityFromID(entry.first);
        SpriteOn sprite = updateSystem.updateOn(_registry, entity);
        _registry.setComponentIndex(entry.first, sprite);
    }
    for (auto entry : _registry.getSpecificComponent(std::type_index(typeid(Bullet)))) {
        Entity entity = _registry.getEntityFromID(entry.first);
        _registry = updateSystem.updateBulletMovement(_registry, entity);
    }
    for (auto entry : _registry.getSpecificComponent(std::type_index(typeid(Pattern)))) {
        Entity entity = _registry.getEntityFromID(entry.first);
        _registry = updateSystem.updateEnnemy(_registry, entity, _skibidi);
    }
    for (auto entry : _registry.getSpecificComponent(std::type_index(typeid(isBackground)))) {
        Entity entity = _registry.getEntityFromID(entry.first);
        _registry = backgroundSystem.parallax(_registry, window, entity);
    }
    for (auto entry : _registry.getSpecificComponent(std::type_index(typeid(Orientation)))) {
        Entity entity = _registry.getEntityFromID(entry.first);
        _registry = updateSystem.updateWalls(_registry, entity, _skibidi);
    }
    if (_registry.getSpecificComponent(std::type_index(typeid(Playable))).empty()) {
        for (auto entry : _registry.getSpecificComponent(std::type_index(typeid(HpBar)))) {
            Entity bar = _registry.getEntityFromID(entry.first);
            Scale barScale = std::any_cast<Scale>(_registry.getComponentEntity(bar, std::type_index(typeid(Scale))));
            barScale.x = 0;
            _registry.setComponentIndex(bar.id, barScale);
        }
    } else
        for (auto entry : _registry.getSpecificComponent(std::type_index(typeid(Playable)))) {
            Entity entity = _registry.getEntityFromID(entry.first);
            _registry = updateSystem.updatePlayerHp(_registry, entity);
        }
}

void Game::windowDraw(sf::RenderWindow &window)
{
    RenderSystem renderSystem(window);
    for (int i = 0; i != 5; i++) {
        for (auto entry : _registry.getSpecificComponent(std::type_index(typeid(Sprite)))) {
            Entity entity = _registry.getEntityFromID(entry.first);
            if (std::any_cast<Layer>(_registry.getComponentEntity(entity, std::type_index(typeid(Layer)))).layer == i) {
                Invisible invisible = std::any_cast<Invisible>(_registry.getComponentEntity(entity, std::type_index(typeid(Invisible))));
                if (!invisible.isInvisible)
                    renderSystem.renderSprite(entity, _registry);
            }
        }
        for (auto entry : _registry.getSpecificComponent(std::type_index(typeid(SpriteOn)))) {
            Entity entity = _registry.getEntityFromID(entry.first);
            if (std::any_cast<Layer>(_registry.getComponentEntity(entity, std::type_index(typeid(Layer)))).layer == i) {
                Invisible invisible = std::any_cast<Invisible>(_registry.getComponentEntity(entity, std::type_index(typeid(Invisible))));
                if (!invisible.isInvisible)
                    renderSystem.renderSpriteOn(entity, _registry);
            }
        }
    }
}

void Game::changeLvl(Client &client, sf::RenderWindow &window)
{
    UpdateSystem updateSystem(_registry, window);

    for (auto entry : _registry.getSpecificComponent(std::type_index(typeid(Clickable)))) {
        Entity entity = _registry.getEntityFromID(entry.first);
        if (std::any_cast<Clickable>(_registry.getComponentEntity(entity, std::type_index(typeid(Clickable)))).clickable)
            if (updateSystem.updateClick(_registry, entity) && entity.id == 0) {
                _registry = Level("../LevelFolder/Level1.txt").getRegistry();
                _registry.setLevel("Level1");
                break;
            }
            if (updateSystem.updateClick(_registry, entity) && entity.id == 1) {
                client.sendDataConnect();
                _registry = Level("../LevelFolder/Level1.txt").getRegistry();
                break;
            }
    }
}

int Game::gameMain(char **av)
{

    Client::initInstance(av);
    Client &client = *Client::getInstance();
    sf::Thread thread(&Client::run, &client);
    thread.launch();

    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "RType");
    window.setFramerateLimit(240);

    Level level("../LevelFolder/Menu.txt");
    _registry = level.getRegistry();
    _registry.setLevel("Menu");
    PlayableSystem playableSystem;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                if (Client::getInstance()->getIsConnected() == true) {
                    client.sendDataDisconnect();
                    window.close();
                } else
                    window.close();
            }
        }
        updateEntities(window);
        window.clear();
        windowDraw(window);
        window.display();
        if (_registry.getLevel() == "Menu")
            changeLvl(client, window);
        else
            _registry = playableSystem.controlPlayer(_registry, _skibidi);
    }
    thread.terminate();
    return 0;
}