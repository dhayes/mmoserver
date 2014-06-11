/*
 * Connection.cpp
 *
 *  Created on: 11 Jun 2014
 *      Author: dilan
 */

#include "Connection.h"
#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "ConnectionManager.h"

using boost::asio::ip::tcp;

Connection::Connection(boost::asio::io_service& io_service, ConnectionManager& manager) : socket_(io_service), connection_manager_(manager) {
}

boost::asio::ip::tcp::socket& Connection::socket() {
	return socket_;
}

void Connection::start() {
	read_header();
}

void Connection::stop() {
	socket_.close();
}

void Connection::read_header() {
	boost::asio::async_read(socket_, boost::asio::buffer(data_, 4), boost::bind(&Connection::handle_read_header, this, boost::asio::placeholders::error));
}

void Connection::handle_read_header(const boost::system::error_code& e) {
	if (!e && decode_header()) {
	      read_body();
	} else {
		connection_manager_.stop(shared_from_this());
	}
}

void Connection::read_body() {
	boost::asio::async_read(socket_, boost::asio::buffer((data_+4), body_length_), boost::bind(&Connection::handle_read_body, this, boost::asio::placeholders::error));
}

void Connection::handle_read_body(const boost::system::error_code& e) {
	if (!e) {
	    //////handle message
		read_header();
	} else {
		connection_manager_.stop(shared_from_this());
	}
}

void Connection::write(std::string) {

}

void Connection::handle_write(const boost::system::error_code& e) {

}

bool Connection::decode_header() {
	using namespace std; // For strncat and atoi.
	char header[4 + 1] = "";
	strncat(header, data_, header_length);
	body_length_ = atoi(header);
	if (body_length_ > 8192) {
		body_length_ = 0;
		return false;
	}
	return true;
}
