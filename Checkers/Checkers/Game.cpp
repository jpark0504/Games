#pragma once
//#include "stdafx.h"
#include "Game.h"

Game::Game(int startingPieces) {
	for (int i = 0; i < playerCount; i++)
		pieceTotal[i] = startingPieces;

	victoryFont.loadFromFile("Assets/arial.ttf");
	victoryText.setFont(victoryFont);
	victoryText.setFillColor(sf::Color::Green);
	victoryText.setCharacterSize(60);
	victoryMsg[0] = "Red wins!";
	victoryMsg[1] = "White wins!";

	turnIndicator.setFillColor(sf::Color::Red);
	turnIndicator.setSize({ 50, 50 });
	turnIndicator.setPosition({ 25,25 });
	turnIndicator.setOutlineColor(sf::Color::Black);
	turnIndicator.setOutlineThickness(3.f);
	turnColor = redteam;
}

void Game::changeTurn() {
	//Increment the turn and loop around when it passes the player count
	playerTurn++;
	if (playerTurn >= playerCount) {
		playerTurn = 0;
	}
	switch (playerTurn) {
	case 0:
		turnColor = redteam;
		turnIndicator.setFillColor(sf::Color::Red);
		break;
	case 1:
		turnColor = whiteteam;
		turnIndicator.setFillColor(sf::Color::White);
		break;
	}
}

void Game::drawTurn(sf::RenderWindow& window) {
	window.draw(turnIndicator);
}

void Game::drawVictory(sf::RenderWindow& window) {
	window.draw(victoryText);
}

bool Game::losePiece(checkertype color) {
	//Remove a piece from the player's total and check if that total becomes zero
	pieceTotal[color]--;
	if (pieceTotal[color] == 0) {
		victoryText.setString(victoryMsg[color]);
		return true;
	}
	return false;
}