//
// timer.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Game.h"
#include "Server.h"
#include "MessageHandler.h"

int main() {
	Server server(8080);
	Game game;
	MessageHandler messagehandler(&server, &game);
	server.init(&messagehandler);
	server.run();
	return 0;
}
