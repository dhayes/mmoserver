/*
 * Packet.h
 *
 *  Created on: 11 Jun 2014
 *      Author: dilan
 */

#ifndef PACKET_H_
#define PACKET_H_

#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

class Packet {
public:
  enum { header_length = 4 };
  enum { max_body_length = 512 };

  Packet();
  Packet(std::string);
  const char* data() const;
  char* data();
  size_t length() const;
  const char* body() const;
  char* body();
  size_t body_length() const;
  void body_length(size_t);
  bool decode_header();
  void encode_header();

private:
  char data_[header_length + max_body_length];
  size_t body_length_;
};

#endif /* PACKET_H_ */
