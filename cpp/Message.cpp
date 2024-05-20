/**
 * @author      : theo (theo@$HOSTNAME)
 * @file        : Message
 * @created     : Sunday Sep 29, 2019 11:19:39 MDT
 */

#include "Message.hpp"
#include <cstring>

Message::Message() { buffer = create_buffer(); }

Message::Message(const char *data) { *this = data; }

Message::Message(const std::string &data) { *this = data; }

void Message::__parse_from_string__(const char *data) {
  buffer = {.endianess = get_message_endianess(data),
            .message_type = get_message_type(data),
            .message_flags = get_message_flags(data),
            .protocol_version = get_protocol_version(data),
            .byte_length = get_byte_length(data),
            .fields = get_fields(data),
            .index = 0};
  std::memcpy(buffer.data, data, buffer.byte_length);
}

void Message::parse_from_string(const std::string &data) {
  __parse_from_string__(data.c_str());
}

std::string Message::serialize_to_string() {
  to_wire(&buffer);
  return std::string(buffer.data, buffer.byte_length);
}

std::ostream &operator<<(std::ostream &os, Message &msg) {
  os << msg.serialize_to_string();
  return os;
}

std::istream &operator>>(std::istream &is, Message &msg) {
  std::string input{std::istreambuf_iterator<char>(is),
                    std::istreambuf_iterator<char>()};

  msg.parse_from_string(input);
  return is;
}

void Message::operator=(const char *data) { __parse_from_string__(data); }

void Message::operator=(const std::string &data) { parse_from_string(data); }

data_piece Message::operator[](int index) {
  char *temp = get_at_index(buffer.data, index);
  data_piece d = {.size = *reinterpret_cast<uint8_t *>(temp),
                  .type_code = *static_cast<char *>(temp + 1)};
  return d;
}
