#include "../include/Game.hpp"
#include <SFML/System/Vector2.hpp>
#include <memory>

char :: Game :: generateRandomChar(){
  int rnd = rand() % 26;
  return (char) (rnd + 'a');
} 

int::Game::findIndex(char ch){
  for(int i = 0;i<enemies.size();i++){
    if(ch == enemies[i]->letter){
      return i; 
    }
  }return -1; 
}

Game::Game(int _windowWidth, int _windowHeight) 
    : windowWidth(_windowWidth), 
      windowHeight(_windowHeight), 
      window(sf::VideoMode(windowWidth, windowHeight), "PopType"),
      player(30.f, sf::Vector2f(windowWidth / 2, windowHeight / 2))
{
}

void Game::run() {
    while (window.isOpen()) {
        render();
        processEvents();
        spawnEnemies();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
                char pressedChar = static_cast<char>(event.key.code + 'a'); 
                int index = findIndex(pressedChar);
                if(index != -1){
                  destructEnemies(index);
                }
            }
        }
    }

}

void Game::spawnEnemies(){
    float timeElapsed = gameClock.getElapsedTime().asSeconds();

    spawnInterval = minimumSpawnInterval + (1.0f - minimumSpawnInterval) * std::exp(-decayRate * timeElapsed);

    if (spawnClock.getElapsedTime().asSeconds() > spawnInterval) {
        enemies.push_back(std::make_unique<Enemy>(windowWidth, windowHeight, generateRandomChar()));
        spawnClock.restart();
    }
} 

void Game::destructEnemies(int index){
  if(index >= 0 && index < enemies.size()){
    enemies.erase(enemies.begin() + index);  
  }
}

void Game::render() {
    window.clear();
    player.show(window); 
    for(auto & enemy : enemies){
      enemy->show(window);
    }
    window.display();
}

