/*
 * Game.cpp
 *
 *  Created on: 11 Jun 2014
 *      Author: dilan
 */

#include "Game.h"

Game::Game() {
	// TODO Auto-generated constructor stub

}

void Game::init(MessageHandler* messagehandler) {
	messagehandler_ = messagehandler;
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

int Game::login(std::string username, std::string password) {
	if (username == "aaa" && password == "bbb") {
		return 567;
	}
	return 0;
}

void Game::logout(int) {
	//logout player
}

void Game::move(int playerid, int x, int y) {
	std::cout << "IIII" << std::endl;
}
