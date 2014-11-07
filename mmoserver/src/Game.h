/*
 * Game.h
 *
 *  Created on: 11 Jun 2014
 *      Author: dilan
 */

#ifndef GAME_H_
#define GAME_H_

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
#include "MessageHandler.h"

class MessageHandler;

class Game {
public:
	Game();
	virtual ~Game();
	void init(MessageHandler*);
	int login(std::string, std::string);
	void logout(int);
	void move(int, int, int);

private:
	/*World world;
	Registry registry;
	ObjectHandler objecthandler;
	ItemHandler itemhandler;
	ActionHandler actionhandler;*/
	DatabaseHandler databasehandler;
	std::map<int, boost::shared_ptr<Player> > players;
	MessageHandler* messagehandler_;
};

#endif /* GAME_H_ */
