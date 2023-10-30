/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-evan.engels
** File description:
** main
*/

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Game/Game.hpp"


/**
 * @brief Second main
 * Main with arguments and GameLoop
 * @param ac
 * @param av
 * @return int
 */

int mainException(int ac, char **av)
{
    //if (ac != 3)
    //    throw std::runtime_error("Error: ./r-type_client [ip] [port]");
    //Game game(av[2]);
    Game game("8080");
    return game.gameMain(av);
}

/**
 * @brief Main
 * contains a try catch and go to the 2cd main when the program don't crash
 * @param ac
 * @param av
 * @return int
 */

int main(int ac, char **av) 
{
    //try {
        return mainException(ac, av);
    /*} catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return 84;
    }
    return 0;*/
}
