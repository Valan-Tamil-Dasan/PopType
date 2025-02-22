#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Game {
private:
    sf::RenderWindow window;
    Player player;
public:
    Game(int windowWidth , int windowHeight);
    void run();
private:
    void render();
    void processEvents();
};

#endif
