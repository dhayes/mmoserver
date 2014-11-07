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
	std::string q = "SELECT * FROM players WHERE username='" + username + "' AND password='" + password + "';";
	pqxx::result r = txn.exec(q);
	txn.commit();
	return r[0][0].as<int>();
}

std::string DatabaseHandler::getUsername(int playerid) {
	pqxx::work txn(c);
	std::string q = "SELECT * FROM players WHERE id='";
	q += playerid;
	q += "';";
	pqxx::result r = txn.exec(q);
	txn.commit();
	return r[0][1].as<std::string>();
}

int DatabaseHandler::getXpos(int playerid) {
	pqxx::work txn(c);
	std::string q = "SELECT * FROM players WHERE id = " + boost::lexical_cast<std::string >(playerid) + " ;";
	pqxx::result r = txn.exec(q);
	txn.commit();
	return r[0][3].as<int>();
}

int DatabaseHandler::getYpos(int playerid) {
	pqxx::work txn(c);
	std::string q = "SELECT * FROM players WHERE id = " + boost::lexical_cast<std::string >(playerid) + " ;";
	pqxx::result r = txn.exec(q);
	txn.commit();
	return r[0][4].as<int>();
}

