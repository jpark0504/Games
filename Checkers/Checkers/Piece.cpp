#pragma once
//#include "stdafx.h"
#include "Piece.h"

Piece::Piece() {}

Piece::Piece(checkertype col, int pos, Board& ref, Game& gref) {
	//Create a game piece with red or white team at a position index.
	color = col;
	position = pos;
	boardref = &ref;
	gameref = &gref;
	if (color == whiteteam) {
		checkerShape.setFillColor(sf::Color::White);
	}
	else {
		checkerShape.setFillColor(sf::Color::Red);
	}
	checkerShape.setOutlineColor(sf::Color::Green);
	checkerShape.setOutlineThickness(0.f);
	checkerShape.setRadius(boardref->tileW * 0.4); //Sets a radius to 40% of a tile's width
	checkerShape.setOrigin(-boardref->tileW * 0.1, -boardref->tileH * 0.1);
}

void Piece::drawPiece(sf::RenderWindow& window) {
	checkerShape.setPosition(boardref->getTilePos(position));
	window.draw(checkerShape);
}

void Piece::update(std::vector<Piece*> checkers) {
	//Update function can be created as a series of functions to help organize what should happen each game loop
	selectPiece();
	placePiece(checkers);
}

void Piece::selectPiece() {
	//Select piece
	if (color == gameref->turnColor && boardref->pieceJumping == false && boardref->clickPos == position && selected == false && boardref->newClick == true) {
		selected = true;
		checkerShape.setOutlineThickness(8.f);
	}
	//Deselect piece
	else if (boardref->clickPos == position && selected == true && boardref->newClick == true) {
		//Clicked on piece again
		checkerShape.setOutlineThickness(0.f);
		selected = false;
		if (boardref->pieceJumping == true) {
			//Player chose to end turn after jumping a piece
			gameref->changeTurn();
		}
		boardref->pieceJumping = false;
	}
}

void Piece::placePiece(std::vector<Piece*> checkers) {
	//Place a piece by checking if the next click is in a valid location
	if (selected == true && boardref->clickPos != position) {
		//Check all pieces to see if one of them is blocking the new click position
		bool pieceBlocked = false;
		for (Piece* checker : checkers) {
			if (boardref->clickPos == checker->position && checker->alive) {
				//Location is blocked by another piece
				pieceBlocked = true;
				break;
			}
		}
		//Piece is not blocked and the tile is black (black is the playable space)
		if (pieceBlocked == false && boardref->tileTypes[boardref->clickPos] == black) {
			if (color == redteam && kinged == false) {
				//Red moves down
				if (boardref->pieceJumping == false && (boardref->clickPos == position + boardref->tilesPerRow - 1 || boardref->clickPos == position + boardref->tilesPerRow + 1)) {
					//Valid position, no jump
					checkerShape.setOutlineThickness(0.f);
					position = boardref->clickPos;
					selected = false;
					//End of turn
					gameref->changeTurn();
				}
				//Red jumps down and left
				if (boardref->clickPos == position + (boardref->tilesPerRow - 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos - (boardref->tilesPerRow - 1) == checker->position && checker->color == whiteteam) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					//For jumping pieces, reusing the same pieceBlocked variable to check if there was actually an enemy piece to jump over
					if (pieceBlocked == true) {
						//Valid position, jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//Red jumps down and right
				if (boardref->clickPos == position + (boardref->tilesPerRow + 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos - (boardref->tilesPerRow + 1) == checker->position && checker->color == whiteteam) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//King a piece if it reaches the other side 
				if (position >= boardref->tileCount - boardref->tilesPerRow) {
					kinged = true;
					checkerShape.setFillColor(sf::Color(200, 0, 0));
				}
			}
			else if (color == whiteteam && kinged == false) {
				//White moves up
				if (boardref->pieceJumping == false && (boardref->clickPos == position - boardref->tilesPerRow - 1 || boardref->clickPos == position - boardref->tilesPerRow + 1)) {
					//Valid position, no jump
					checkerShape.setOutlineThickness(0.f);
					position = boardref->clickPos;
					selected = false;
					//End of turn
					gameref->changeTurn();
				}
				//White jumps up and left
				if (boardref->clickPos == position - (boardref->tilesPerRow + 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos + (boardref->tilesPerRow + 1) == checker->position && checker->color == redteam) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//White jumps up and right
				if (boardref->clickPos == position - (boardref->tilesPerRow - 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos + (boardref->tilesPerRow - 1) == checker->position && checker->color == redteam) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//King a piece if it reaches the other side 
				if (position <= boardref->tilesPerRow) {
					kinged = true;
					checkerShape.setFillColor(sf::Color(200, 200, 255));
				}
			}
			else if (kinged == true) {
				//King moves
				if (boardref->pieceJumping == false && (boardref->clickPos == position - boardref->tilesPerRow - 1 || boardref->clickPos == position - boardref->tilesPerRow + 1
					|| boardref->clickPos == position + boardref->tilesPerRow - 1 || boardref->clickPos == position + boardref->tilesPerRow + 1)) {
					//Valid position, no jump
					checkerShape.setOutlineThickness(0.f);
					position = boardref->clickPos;
					selected = false;
					//End of turn
					gameref->changeTurn();
				}
				//King jumps up and left
				if (boardref->clickPos == position - (boardref->tilesPerRow + 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos + (boardref->tilesPerRow + 1) == checker->position && checker->color != color) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//King jumps up and right
				if (boardref->clickPos == position - (boardref->tilesPerRow - 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos + (boardref->tilesPerRow - 1) == checker->position && checker->color != color) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//King jumps down and left
				if (boardref->clickPos == position + (boardref->tilesPerRow - 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos - (boardref->tilesPerRow - 1) == checker->position && checker->color != color) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
				//King jumps down and right
				if (boardref->clickPos == position + (boardref->tilesPerRow + 1) * 2) {
					//Check if jump is valid
					for (Piece* checker : checkers) {
						if (boardref->clickPos - (boardref->tilesPerRow + 1) == checker->position && checker->color != color) {
							//Enemy piece is being jumped over
							checker->alive = false;
							checker->position = boardref->tileCount;
							pieceBlocked = true;
							break;
						}
					}
					if (pieceBlocked == true) {
						//Valid position, jumped
						position = boardref->clickPos;
						boardref->pieceJumping = true;
					}
				}
			}
		}
		//Clicked location that is open, but cannot be moved to
		//Jumping pieces must jump again or end turn (by clicking on piece)
		else if (boardref->pieceJumping == false) {
			checkerShape.setOutlineThickness(0.f);
			selected = false;
		}
	}
}