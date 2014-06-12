/*
 * ConnectionManager.cpp
 *
 *  Created on: 11 Jun 2014
 *      Author: dilan
 */

#include "ConnectionManager.h"
#include <algorithm>
#include <boost/bind.hpp>

void ConnectionManager::start(boost::shared_ptr<Connection> c) {
	std::cout << "start connection" << std::endl;
	connections_.insert(c);
	c->start();
}

void ConnectionManager::stop(boost::shared_ptr<Connection> c) {
	std::cout << "stop connection" << std::endl;
	connections_.erase(c);
	c->stop();
}

void ConnectionManager::stop_all() {
	std::for_each(connections_.begin(), connections_.end(), boost::bind(&Connection::stop, _1));
	connections_.clear();
}
