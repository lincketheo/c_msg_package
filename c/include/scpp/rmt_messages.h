/**
 * @author      : theo (theo.j.lincke@gmail.com)
 * @file        : rmt_messages
 * @created     : Saturday Oct 26, 2019 17:06:35 MDT
 */

#ifndef RMT_MESSAGES_H

#define RMT_MESSAGES_H

// #define LIGHT_MESSAGES
#include "scpp/data_message.h"

typedef struct {
  float lin;
  float ang;
  size_t indexes[2];
  data_buffer buff;
} cmd_vel;

typedef struct {
  float lin_echo;
  float ang_echo;
  size_t indexes[2];
  data_buffer buff;
} data;

typedef struct {
  int16_t lin;
  int16_t ang;
  size_t indexes[2];
  data_buffer buff;
} teensy_msg;

cmd_vel create_cmd_vel();

int cmd_vel_to_wire(cmd_vel *vel);

int cmd_vel_from_wire(cmd_vel *vel, const char *data);

teensy_msg create_teensy_msg();

int teensy_msg_to_wire(teensy_msg *msg);

int teensy_msg_from_wire(teensy_msg *msg, const char *data);

#endif /* end of include guard RMT_MESSAGES_H */
