#pragma once
#include <SFML/Graphics.hpp>
#include <string>

const int playerCount = 2;

enum checkertype {
	redteam,
	whiteteam
};

class Game {
public:
	int playerTurn = 0;
	sf::RectangleShape turnIndicator;
	checkertype turnColor;
	int pieceTotal[playerCount];

	std::string victoryMsg[playerCount];
	sf::Text victoryText;
	sf::Font victoryFont;

	Game(int startingPieces);
	void changeTurn();
	void drawTurn(sf::RenderWindow& window);
	void drawVictory(sf::RenderWindow& window);
	bool losePiece(checkertype color);
};