#include "../include/Game.hpp"

Game::Game(int windowWidth , int windowHeight) : window(sf::VideoMode(windowWidth, windowHeight), "Typing Dodge Game"), player(30.f, sf::Vector2f(windowWidth / 2 - 15, windowHeight / 2 - 15)) {}

void Game::run() {
    while (window.isOpen()) {
        render();
        processEvents();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}


void Game::render() {
    window.clear();
    player.show(window); 
    window.display();
}
