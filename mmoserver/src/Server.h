/*
 * Server.h
 *
 *  Created on: 11 Jun 2014
 *      Author: dilan
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <boost/asio.hpp>
#include <string>
#include <boost/noncopyable.hpp>
#include "ConnectionManager.h"
#include "MessageHandler.h"
#include "Connection.h"
#include <boost/bind.hpp>
#include <signal.h>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

class ConnectionManager;
class MessageHandler;
class Connection;

class Server : private boost::noncopyable {
public:
  /// Construct the server to listen on the specified TCP address and port, and
  /// serve up files from the given directory.
  explicit Server(int port);
  //initialise with messagehandler
  void init(MessageHandler*);
  /// Run the server's io_service loop.
  void run();

  void kill_connection(boost::shared_ptr<Connection>);

private:
  /// Initiate an asynchronous accept operation.
  void start_accept();

  /// Handle completion of an asynchronous accept operation.
  void handle_accept(const boost::system::error_code& e);

  /// Handle a request to stop the server.
  void handle_stop();

  /// The io_service used to perform asynchronous operations.
  boost::asio::io_service io_service_;

  /// The signal_set is used to register for process termination notifications.
  boost::asio::signal_set signals_;

  /// Acceptor used to listen for incoming connections.
  boost::asio::ip::tcp::acceptor acceptor_;

  /// The connection manager which owns all live connections.
  ConnectionManager* connection_manager_;

  /// The next connection to be accepted.
  boost::shared_ptr<Connection> new_connection_;
  boost::asio::ip::tcp::endpoint endpoint;

  MessageHandler* messagehandler_;

};


#endif /* SERVER_H_ */
