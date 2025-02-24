#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <random>
#include <memory>

// a letter venum
// movement -> positionla spawn aaganum 
// should move towards center
// should return if collided

class Enemy {
private:
  char letter;
  float radius = 30.f;
  sf::CircleShape shape; 
  sf::Vector2f center;
  int windowWidth , windowHeight;
  sf::Vector2f getRandomSpawnPosition();
public:
  Enemy(int windowWidth , int windowHeight);
  void show(sf::RenderWindow& window);
  void processEvents();
};

#endif // ENEMY_HPP
