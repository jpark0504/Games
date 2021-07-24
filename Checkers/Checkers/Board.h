#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum tiletype {
	black,
	white
};

class Board {
public:
	sf::RectangleShape tileShape;
	int boardH, boardW;
	int tileH, tileW;
	int tilesPerRow;
	int tilesPerCol;
	int tileCount;
	std::vector<tiletype> tileTypes;
	int clickPos;
	bool newClick = false;
	bool pieceJumping = false;

	Board(sf::RenderWindow& window, int height, int width, int tilesInRow, int tilesInCol);
	void drawBoard(sf::RenderWindow& window);
	int getTileN(float x, float y);
	sf::Vector2f getTilePos(int N);
};