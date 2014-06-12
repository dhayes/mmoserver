/*
 * Server.cpp
 *
 *  Created on: 11 Jun 2014
 *      Author: dilan
 */

#include "Server.h"
#include <boost/bind.hpp>
#include <signal.h>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

Server::Server(int port) : io_service_(), signals_(io_service_), acceptor_(io_service_), connection_manager_(),  new_connection_(), endpoint(boost::asio::ip::tcp::v4(), port) {
  // Register to handle the signals that indicate when the server should exit.
  // It is safe to register for the same signal multiple times in a program,
  // provided all registration for the specified signal is made through Asio.
	signals_.add(SIGINT);
	signals_.add(SIGTERM);
#if defined(SIGQUIT)
	signals_.add(SIGQUIT);
#endif // defined(SIGQUIT)
	signals_.async_wait(boost::bind(&Server::handle_stop, this));
	acceptor_.open(endpoint.protocol());
	acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();
    start_accept();
}

void Server::run() {
	// The io_service::run() call will block until all asynchronous operations
	// have finished. While the server is running, there is always at least one
	// asynchronous operation outstanding: the asynchronous accept call waiting
	// for new incoming connections.
	io_service_.run();
}

void Server::start_accept() {
	std::cout << "start accept" << std::endl;
	new_connection_.reset(new Connection(io_service_, connection_manager_));
	acceptor_.async_accept(new_connection_->socket(), boost::bind(&Server::handle_accept, this, boost::asio::placeholders::error));
}

void Server::handle_accept(const boost::system::error_code& e) {
	std::cout << "handle accept" << std::endl;
	// Check whether the server was stopped by a signal before this completion
	// handler had a chance to run.
	if (!acceptor_.is_open()) {
		return;
	}

	if (!e) {
		connection_manager_.start(new_connection_);
	}
	start_accept();
}

void Server::handle_stop() {
	// The server is stopped by cancelling all outstanding asynchronous
	// operations. Once all operations have finished the io_service::run() call
	// will exit.
	acceptor_.close();
	connection_manager_.stop_all();
}

