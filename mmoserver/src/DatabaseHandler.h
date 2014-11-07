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

class DatabaseHandler {
public:
	DatabaseHandler();
	virtual ~DatabaseHandler();
	int auth(std::string, std::string);
private:
	pqxx::connection c;
};

#endif /* DATABASEHANDLER_H_ */
