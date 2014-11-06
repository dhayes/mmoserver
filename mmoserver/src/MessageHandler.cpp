/*
 * MessageHandler.cpp
 *
 *  Created on: 6 Nov 2014
 *      Author: dilan
 */

#include "MessageHandler.h"

MessageHandler::MessageHandler(Server* server, Game* game) : server_(server), game_(game) {
	// TODO Auto-generated constructor stub

}

MessageHandler::~MessageHandler() {
	// TODO Auto-generated destructor stub
}

void MessageHandler::handleMessage(std::string msg, boost::shared_ptr<Connection> connection) {
	std::cout << "YES\n";
	std::stringstream ss;
	ss << msg;
	boost::property_tree::ptree pt;
	boost::property_tree::read_json(ss, pt);
	std::string type = pt.get<std::string>("type");
	std::cout << type;
	if (type == "login") {
		//game.login
	} else if (type == "logout") {

	} else if (type == "move") {

	}
}
