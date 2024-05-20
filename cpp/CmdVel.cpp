/**
 * @author      : theo (theo@$HOSTNAME)
 * @file        : CmdVel
 * @created     : Sunday Sep 29, 2019 19:51:06 MDT
 */

#include "CmdVel.hpp"

CmdVel::CmdVel() : Message() {}

CmdVel::CmdVel(const char *data) : Message(data) {}

CmdVel::CmdVel(const std::string &data) : Message(data) {}

void CmdVel::set_data(float lin, float ang) {
  if (get_num_bytes() > 0)
    reset();
  serialize(&lin, sizeof(float), FLOAT);
  serialize(&ang, sizeof(float), FLOAT);
  to_serialize_wire();
}

float CmdVel::get_ang() {
  float ret = *((float *)(get_data(0) + 2));
  return ret;
}

// TODO make better
float CmdVel::get_lin() {
  // copy dat bitch
  float ret = *((float *)(get_data(1) + 2));
  return ret;
}
