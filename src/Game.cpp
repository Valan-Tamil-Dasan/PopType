#include "../include/Game.hpp"
#include <SFML/System/Vector2.hpp>
#include <memory>

char :: Game :: generateRandomChar(){
  int rnd = rand() % 26;
  return (char) (rnd + 'a');
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
    }
}

void Game::spawnEnemies(){
  if (spawnClock.getElapsedTime().asSeconds() > 1.f) {
    enemies.push_back(std::make_unique<Enemy> (windowWidth , windowHeight ,generateRandomChar()));
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

// vector of Enemies
// when created it is pushed
// when poped it needs to be removed from the vector
// enemy remove function need to be done on enemy class
// Here remove from the vector and and call Enemy.end function
// lets see when a key is pressed I need to pop one out
