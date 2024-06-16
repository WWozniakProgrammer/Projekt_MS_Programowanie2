#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Menu.h"
#include "DB.h"

int main() {
	DB db;
	db.selectData("SELECT * FROM Players");
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Gra");
	sf::Event event;
	sf::Clock gameClock;
	sf::Time gameTime;
	float dt;
	sf::Vector2f MouseWorldPos{ 0, 0 };
	Game game(&window);
	Menu menu(&window);

	enum class GameState
	{
		MainMenu,
		Playing
		GameOver,
		Closed
	};

	GameState gamestate{};
	while (window.isOpen()) {
		gameTime = gameClock.restart();
		dt = gameTime.asSeconds();
		if (gamestate == GameState::MainMenu) {
			sf::Vector2i mousepos = sf::Mouse::getPosition(window);
			MouseWorldPos = window.mapPixelToCoords(mousepos);

			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
				{
					gamestate = GameState::Closed;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					gamestate = GameState::Closed;
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && menu.latwy.getGlobalBounds().contains(MouseWorldPos))
				{
					gamestate = GameState::Playing;
				}
			}
			menu.run();
		}


		if (gamestate == GameState::Closed) window.close();

		if (gamestate == GameState::Playing) {
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					gamestate = GameState::Closed;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					gamestate = GameState::Closed;
			}
			game.run();
		}

	}
	return 0;
}