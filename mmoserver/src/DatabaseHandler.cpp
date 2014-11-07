/*
 * DatabaseHandler.cpp
 *
 *  Created on: 11 Jun 2014
 *      Author: dilan
 */

#include "DatabaseHandler.h"

DatabaseHandler::DatabaseHandler() : c("user=postgres hostaddr=127.0.0.1 password=aaa dbname=mmodb") {
	// TODO Auto-generated constructor stub
	if (c.is_open()) {
		std::cout << "database connection made" << std::endl;
	}
}

DatabaseHandler::~DatabaseHandler() {
	// TODO Auto-generated destructor stub
}

int DatabaseHandler::auth(std::string username, std::string password) {


	pqxx::work txn(c);
	pqxx::result r = txn.exec("SELECT 1");
	txn.commit();
	return r[0][0].as<int>();
}

