/*
 * ConnectionManager.h
 *
 *  Created on: 11 Jun 2014
 *      Author: dilan
 */

#ifndef CONNECTIONMANAGER_H_
#define CONNECTIONMANAGER_H_

#include <set>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include "Connection.h"

class Connection;

class ConnectionManager : private boost::noncopyable {
public:
	/// Add the specified connection to the manager and start it.
	void start(boost::shared_ptr<Connection> c);

	/// Stop the specified connection.
	void stop(boost::shared_ptr<Connection> c);

	/// Stop all connections.
	void stop_all();

private:
	/// The managed connections.
	std::set< boost::shared_ptr<Connection> > connections_;
};

#endif /* CONNECTIONMANAGER_H_ */
