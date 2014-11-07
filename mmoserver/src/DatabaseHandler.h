/*
 * DatabaseHandler.h
 *
 *  Created on: 11 Jun 2014
 *      Author: dilan
 */

#ifndef DATABASEHANDLER_H_
#define DATABASEHANDLER_H_

#include <iostream>
#include <pqxx/pqxx>
#include <boost/lexical_cast.hpp>

class DatabaseHandler {
public:
	DatabaseHandler();
	virtual ~DatabaseHandler();
	int auth(std::string, std::string);
	std::string getUsername(int);
	int getXpos(int);
	int getYpos(int);
private:
	pqxx::connection c;
};

#endif /* DATABASEHANDLER_H_ */
