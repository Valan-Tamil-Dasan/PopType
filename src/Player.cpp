#include "../include/Player.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

Player::Player(float radius, sf::Vector2f position) {
    playerRadius = radius;
    shape.setRadius(radius);
    shape.setOrigin(radius, radius); 
    shape.setPosition(position); 
}

void Player::show(sf::RenderWindow& window){
  window.draw(shape);
}

float Player::getRadius(){
  return playerRadius;
}
