#include "../include/Game.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
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

void Game :: loadText(){
  font.loadFromFile("../assets/font.ttf");
  scoreText.setFont(font);
  scoreText.setCharacterSize(30.f);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition(windowWidth - 500.f , 100.f);
  
  menuText.setFont(font);
  menuText.setCharacterSize(48);
  sf::FloatRect menuBounds = menuText.getLocalBounds();
  menuText.setOrigin(menuBounds.width / 2, menuBounds.height / 2);
  menuText.setFillColor(sf::Color::White);
  menuText.setString("PopType");
  menuText.setPosition(windowWidth / 2 - 100, 100);

  playText.setFont(font);
  playText.setCharacterSize(48);
  sf::FloatRect playBounds = playText.getLocalBounds();
  playText.setOrigin(playBounds.width / 2, playBounds.height / 2);
  playText.setFillColor(sf::Color::Blue);
  playText.setString("Play");
  playText.setPosition(windowWidth / 2 - 100 , 200);

  quitText.setFont(font);
  quitText.setCharacterSize(48);
  sf::FloatRect quitBounds = quitText.getLocalBounds();
  quitText.setOrigin(quitBounds.width / 2, quitBounds.height/2);
  quitText.setFillColor(sf::Color::Blue);
  quitText.setString("Quit");
  quitText.setPosition(windowWidth / 2 - 100 , 300);

  gameOverText.setFont(font);
  gameOverText.setCharacterSize(48);
  sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
  gameOverText.setOrigin(gameOverBounds.width / 2, gameOverBounds.height/2);
  gameOverText.setFillColor(sf::Color::Blue);
  gameOverText.setString("Game Over");
  gameOverText.setPosition(windowWidth / 2 - 100 , 100);
}

void Game::checkGameOver() {
    bool captured = false;
    for (int i = 0; i < enemies.size(); i++) {
        sf::Vector2f playerOrigin(windowWidth / 2, windowHeight / 2);
        sf::Vector2f enemyOrigin = enemies[i]->getPosition();
        
        float playerRadius = player.getRadius();
        float enemyRadius = enemies[i]->getRadius();

        float dx = enemyOrigin.x - playerOrigin.x;
        float dy = enemyOrigin.y - playerOrigin.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= (playerRadius + enemyRadius)) {
            captured = true;
            break;
        }
    }

    if (captured) {
      resetGame();
      gameState = GameState::GAME_OVER;
    }
}

void Game :: resetGame(){
  finalScore = score;
  score = 0;
  while(enemies.size() != 0){
    enemies.erase(enemies.begin());
  } 
}

Game::Game(int _windowWidth, int _windowHeight) 
    : windowWidth(_windowWidth), 
      windowHeight(_windowHeight), 
      window(sf::VideoMode(windowWidth, windowHeight), "PopType", sf::Style::Titlebar | sf::Style::Close),
      player(30.f, sf::Vector2f(windowWidth / 2, windowHeight / 2))
{
   loadText(); 
   gameState = GameState::MENU;
}

void Game::run() {
    while (window.isOpen()) {
        render();
        processEvents();
        checkGameOver();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (gameState == GameState::PLAYING && event.type == sf::Event::KeyPressed) {
            if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
                char pressedChar = static_cast<char>(event.key.code + 'a'); 
                int index = findIndex(pressedChar);
                if(index != -1){
                  score += 10;
                  destructEnemies(index);
                }else{
                  score -= 30;
                  score = std::max(0,score);
                }
            }
        }
        if (event.type == sf::Event::Resized){
          sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
          window.setView(sf::View(visibleArea));
        }
        if(event.type == sf::Event::MouseButtonPressed && gameState != GameState::PLAYING){
          sf::Vector2i mousepos = sf::Mouse::getPosition(window);
          if(playText.getGlobalBounds().contains(mousepos.x , mousepos.y)){
            gameState = GameState::PLAYING;
          }
          if(quitText.getGlobalBounds().contains(mousepos.x , mousepos.y)){
            window.close();
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
void Game::play(){
  player.show(window); 
  spawnEnemies();
  for(auto & enemy : enemies){
    enemy->show(window);
  }
  scoreText.setString("SCORE: "+std::to_string(score));
  window.draw(scoreText);
}
void Game::renderMenu(){
  window.draw(menuText);
  window.draw(playText);
  window.draw(quitText);
}
void Game::renderGameOver(){
  window.draw(gameOverText);
  scoreText.setString("SCORE: "+std::to_string(finalScore));
  window.draw(scoreText);
  window.draw(playText);
  window.draw(quitText);
}
void Game::render() {
    window.clear();
    if(gameState == GameState::MENU){
      renderMenu();
    }else if(gameState == GameState::PLAYING){
      play();
    }else if(gameState == GameState::GAME_OVER){
      renderGameOver();
    }

    window.display();
}

