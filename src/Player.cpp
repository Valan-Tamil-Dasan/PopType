#include "../include/Player.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

Player::Player(float radius , sf::Vector2f position){
  shape.setRadius(radius);
  shape.setPosition(position); 
}

void Player::show(sf::RenderWindow& window){
  window.draw(shape);
}
