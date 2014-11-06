/*
 * MessageHandler.h
 *
 *  Created on: 6 Nov 2014
 *      Author: dilan
 */

#ifndef MESSAGEHANDLER_H_
#define MESSAGEHANDLER_H_

#include "Server.h"
#include "Game.h"
#include <boost/noncopyable.hpp>
#include "Connection.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class Server;
class Game;
class Connection;

class MessageHandler {
public:
	MessageHandler(Server*, Game*);
	~MessageHandler();
	void handleMessage(std::string, boost::shared_ptr<Connection>);
private:
	Server* server_;
	Game* game_;
};

#endif /* MESSAGEHANDLER_H_ */
