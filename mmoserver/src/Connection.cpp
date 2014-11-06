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

Connection::Connection(boost::asio::io_service& io_service, ConnectionManager* manager, MessageHandler* messagehandler) : socket_(io_service), connection_manager_(manager), messagehandler_(messagehandler) {}

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
	std::cout << "read header" << std::endl;
	boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.data(), Packet::header_length), boost::bind(&Connection::handle_read_header, this, boost::asio::placeholders::error));
}

void Connection::handle_read_header(const boost::system::error_code& e) {
	std::cout << "handle read header" << std::endl;
	if (!e && read_msg_.decode_header()) {
	      read_body();
	} else {
		connection_manager_->stop(shared_from_this());
	}
}

void Connection::read_body() {
	std::cout << "read body" << std::endl;
	boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.body(), read_msg_.body_length()), boost::bind(&Connection::handle_read_body, this, boost::asio::placeholders::error));
}

void Connection::handle_read_body(const boost::system::error_code& e) {
	std::cout << "handle read body" << std::endl;
	if (!e) {
	    std::string msg;
	    msg.assign(read_msg_.body(), read_msg_.body_length());
	    write(msg);
	    messagehandler_->handleMessage(msg, shared_from_this());
	    std::cout << msg << std::endl;
		read_header();
	} else {
		connection_manager_->stop(shared_from_this());
	}
}

void Connection::write(std::string message) {
	Packet packet(message);
	bool write_in_progress = !write_msgs_.empty();
	write_msgs_.push_back(packet);
	if (!write_in_progress) {
		boost::asio::async_write(socket_, boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()), boost::bind(&Connection::handle_write, this, boost::asio::placeholders::error));
	}
}

void Connection::handle_write(const boost::system::error_code& e) {
	if (!e) {
		write_msgs_.pop_front();
	    if (!write_msgs_.empty()) {
	    	boost::asio::async_write(socket_, boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()), boost::bind(&Connection::handle_write, this, boost::asio::placeholders::error));
	    }
	} else {
		connection_manager_->stop(shared_from_this());
	}
}
