/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** main
*/

#include "Server.hpp"
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int mainException(int ac, char **av)
{
    if (ac < 2) {
        std::cout << "Try: " << av[0] << " [port]" << std::endl;
        return 84;
    }
    Server server(std::atoi(av[1]));
    sf::Thread thread(&Server::run, &server);
    thread.launch();
    return 0;
}

int main(int ac, char **av)
{
    try {
        return mainException(ac, av);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return 84;
    }
    return 0;
}