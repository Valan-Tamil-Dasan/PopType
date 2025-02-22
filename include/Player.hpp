#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player{
  private:
    sf::CircleShape shape;
  public:
    Player(float radius , sf::Vector2f position);
    void show(sf::RenderWindow& window);

};

#endif // !PLAYER_HPP

