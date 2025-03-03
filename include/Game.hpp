#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <memory>
#include "Player.hpp"
#include "Enemy.hpp"
enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER
};
class Game {
private:
    int windowHeight , windowWidth;
    sf::RenderWindow window;
    Player player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    sf::Clock spawnClock,gameClock;
    sf::Font font;
    sf::Text scoreText ;
    sf::Text menuText;
    sf::Text playText;
    sf::Text quitText;
    sf::Text gameOverText;
    sf::Text finalScoreText;
    int score = 0;
    int finalScore = 0;
    float spawnInterval = 1.0f;
    float minimumSpawnInterval = 0.3f;
    /*float decreaseSpawnInterval = 0.01f;*/
    float decayRate = 0.01f;
    void render();
    void processEvents();
    void spawnEnemies();
    void destructEnemies(int index);
    char generateRandomChar();
    int findIndex(char ch);
    void loadText();
    void resetGame();    
    void play();
    void renderMenu();
    void renderGameOver();
    void checkGameOver();
    GameState gameState;

public:
    Game(int windowWidth , int windowHeight);
    void run();
};

#endif
