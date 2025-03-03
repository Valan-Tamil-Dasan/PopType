#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player{
  private:
    sf::CircleShape shape;
    float playerRadius;
  public:
    Player(float radius , sf::Vector2f position);
    float getRadius();
    void show(sf::RenderWindow& window);

};

#endif // !PLAYER_HPP

