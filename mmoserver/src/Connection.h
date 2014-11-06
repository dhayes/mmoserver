/*
 * Connection.h
 *
 *  Created on: 11 Jun 2014
 *      Author: dilan
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <deque>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "ConnectionManager.h"
#include "Player.h"
#include "Packet.h"
#include "MessageHandler.h"

class MessageHandler;
class ConnectionManager;

class Connection : public boost::enable_shared_from_this<Connection> {
public:
  /// Construct a connection with the given io_service.
  explicit Connection(boost::asio::io_service& io_service, ConnectionManager* connection_manager_, MessageHandler*);

  /// Get the socket associated with the connection.
  boost::asio::ip::tcp::socket& socket();

  /// Start the first asynchronous operation for the connection.
  void start();

  /// Stop all asynchronous operations associated with the connection.
  void stop();
private:
  void read_header();
  void handle_read_header(const boost::system::error_code&);
  void read_body();
  void handle_read_body(const boost::system::error_code&);
  void write(std::string);
  void handle_write(const boost::system::error_code&);

  /// Socket for the connection.
  boost::asio::ip::tcp::socket socket_;

  /// The manager for this connection.
  ConnectionManager* connection_manager_;

  ///pointer to player associated with connection
  boost::shared_ptr<Player> player;
  Packet read_msg_;
  std::deque<Packet> write_msgs_;

  MessageHandler* messagehandler_;
};

#endif /* CONNECTION_H_ */
