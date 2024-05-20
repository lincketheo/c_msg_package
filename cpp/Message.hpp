/**
 * @author      : theo (theo@$HOSTNAME)
 * @file        : Message
 * @created     : Sunday Sep 29, 2019 09:55:26 MDT
 */

#ifndef MESSAGE_HPP

#define MESSAGE_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <cstring>

extern "C"
{
#include "messages.h"
}

typedef struct
{
  uint8_t size;
  char type_code;
} data_piece;

class Message
{
public:
  Message();
  Message(const char* data);
  Message(const std::string& data);
  virtual ~Message() = default;

  /* main */
  void parse_from_string(const std::string& data);
  std::string serialize_to_string();

  /* Operators */
  data_piece operator[](int);
  void operator=(const char* data);
  void operator=(const std::string& data);

  friend std::ostream& operator<<(std::ostream& os, Message& msg);
  friend std::istream& operator>>(std::istream& os, Message& msg);

protected:
  void serialize(void const* const data, uint8_t num_bytes, char type_code)
  {
    serialize_data(&buffer, data, num_bytes, type_code);
  }
  char* get_data(size_t index) { return get_at_index(buffer.data, index); }
  void reset() { buffer = create_buffer(); }
  size_t get_num_bytes() { return get_byte_length(buffer.data); }
  void to_serialize_wire() { to_wire(&buffer); }

private:
  void __parse_from_string__(const char* data);
  message_buffer buffer;
};

#endif /* end of include guard MESSAGE_HPP */
