#include "../include/Enemy.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

// enemy remove function need to be done on enemy class

sf::Vector2f Enemy:: getRandomSpawnPosition() {
  static std::random_device rd;
  static std::mt19937 gen(rd());  // Random number generator

  std::uniform_int_distribution<int> sideDist(0, 3);  // Choose a random side (0-3)
  std::uniform_int_distribution<int> xDist(0, windowWidth); // Random x position
  std::uniform_int_distribution<int> yDist(0, windowHeight); // Random y position

  int side = sideDist(gen);  
  float x, y;

  switch (side) {
      case 0: 
          x = xDist(gen);
          y = 0.f;
          break;
      case 1:
          x = windowWidth;
          y = yDist(gen);
          break;
      case 2:
          x = xDist(gen);
          y = windowHeight;
          break;
      case 3:
          x = 0.f;
          y = yDist(gen);
          break;
  }
  return sf::Vector2f(x, y);
}

Enemy::Enemy(int _windowWidth , int _windowHeight){
  windowWidth = _windowWidth;
  windowHeight = _windowHeight;
  center = sf::Vector2f(windowWidth/2 , windowHeight/2);

  shape.setRadius(radius);
  shape.setFillColor(sf::Color::Red);

  shape.setOrigin(radius, radius); 

  sf::Vector2f spawnPoint = getRandomSpawnPosition();
  shape.setPosition(spawnPoint); 
}

void Enemy::show(sf::RenderWindow& window){
  processEvents();
  window.draw(shape);
}

void Destruct(){
          
}

void Enemy::processEvents() {
  sf::Vector2f currentPos = shape.getPosition();
  sf::Vector2f direction(center.x - currentPos.x, center.y - currentPos.y);
  float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

  if (distance < 0.5f) return;

  direction /= distance;
  shape.move(direction * 0.05f);
}
