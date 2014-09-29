/*
 * Game.h
 *
 *  Created on: 11 Jun 2014
 *      Author: dilan
 */

#ifndef GAME_H_
#define GAME_H_

#include "Server.h"
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "World.h"
#include "Registry.h"
#include "ObjectHandler.h"
#include "ActionHandler.h"
#include "DatabaseHandler.h"
#include "ItemHandler.h"
#include "Player.h"

class Server;

class Game {
public:
	Game();
	virtual ~Game();
	void run();

	World* world;
	Registry* registry;
	ObjectHandler* objecthandler;
	ItemHandler* itemhandler;
	ActionHandler* actionhandler;
	DatabaseHandler* databasehandler;
	std::map<int, boost::shared_ptr<Player> > players;
	Server* server;
private:
};

#endif /* GAME_H_ */
