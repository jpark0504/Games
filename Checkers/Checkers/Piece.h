#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Game.h"

//Enumerator for checkertype moved to Game.h

class Piece {
public:
	Board* boardref;
	Game* gameref;
	int position;
	bool alive = true;
	bool selected = false;
	checkertype color;
	bool kinged = false;
	sf::CircleShape checkerShape;

	Piece();
	Piece(checkertype col, int pos, Board& ref, Game& gref);
	void drawPiece(sf::RenderWindow& window);
	void update(std::vector<Piece*> checkers);
	void selectPiece();
	void placePiece(std::vector<Piece*> checkers);
};