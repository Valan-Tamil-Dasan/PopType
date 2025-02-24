#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <memory>
#include "Player.hpp"
#include "Enemy.hpp"

class Game {
private:
    int windowHeight , windowWidth;
    sf::RenderWindow window;
    Player player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    sf::Clock spawnClock;
    void render();
    void processEvents();
    void spawnEnemies();
    void destructEnemies(int index);
public:
    Game(int windowWidth , int windowHeight);
    void run();
};

#endif
