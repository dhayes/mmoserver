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
	std::stringstream ss;
	ss << msg;
	try {
		boost::property_tree::ptree pt;
		boost::property_tree::read_json(ss, pt);
		std::string type = pt.get<std::string>("type");
		std::cout << type << std::endl;

		if (type == "login") {
			//boost::property_tree::ptree &m = pt.get_child("message");
			std::string username = pt.get_child("message").get<std::string>("username");
			std::string password = pt.get_child("message").get<std::string>("password");

			int playerid = game_->login(username, password);
			if (playerid) {
				std::cout << "logged in" << std::endl;
				//playerid_connection_map.insert(boost::bimap< int, boost::shared_ptr<Connection> >::value_type(playerid, connection)); //insert into bimap
			} else {
				connection->write("{\"type\": \"login failed\"}"); //send login failed message
				//server_->kill_connection(connection);
			}
		} else if (/*playerid_connection_map.left.find(connection)*/ false) {
			std::cout << "logged in" << std::endl;
		}
	} catch (std::exception const& e) {
		std::cout << "error reading message\n";
	}
}
