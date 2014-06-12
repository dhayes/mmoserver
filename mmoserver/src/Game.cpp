/*
 * Game.cpp
 *
 *  Created on: 11 Jun 2014
 *      Author: dilan
 */

#include "Game.h"

Game::Game() : server(8080) {
	// TODO Auto-generated constructor stub

}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::run() {
	server.run();
}

