/*
 * Packet.cpp
 *
 *  Created on: 11 Jun 2014
 *      Author: dilan
 */

#include "Packet.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

Packet::Packet() : body_length_(0) {}

Packet::Packet(std::string message) {
	body_length_ = message.length();
	memcpy(body(), message.c_str(), body_length());
	encode_header();
}

const char* Packet::data() const {
	return data_;
}

char* Packet::data() {
	return data_;
}

size_t Packet::length() const {
	return header_length + body_length_;
}

const char* Packet::body() const {
	return data_ + header_length;
}

char* Packet::body() {
	return data_ + header_length;
}

size_t Packet::body_length() const {
	return body_length_;
}

void Packet::body_length(size_t new_length) {
	body_length_ = new_length;
    if (body_length_ > max_body_length) {
    	body_length_ = max_body_length;
    }
}

bool Packet::decode_header() {
	using namespace std; // For strncat and atoi.
    char header[header_length + 1] = "";
    strncat(header, data_, header_length);
    body_length_ = atoi(header);
    if (body_length_ > max_body_length) {
    	body_length_ = 0;
    	return false;
    }
    return true;
}

  void Packet::encode_header() {
	  using namespace std; // For sprintf and memcpy.
	  char header[header_length + 1] = "";
	  sprintf(header, "%4d", body_length_);
	  memcpy(data_, header, header_length);
  }
