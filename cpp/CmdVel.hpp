/**
 * @author      : theo (theo@$HOSTNAME)
 * @file        : CmdVel
 * @created     : Sunday Sep 29, 2019 19:47:46 MDT
 */

#ifndef CMDVEL_HPP

#define CMDVEL_HPP

#include "Message.hpp"

class CmdVel : public Message
{
public:
  CmdVel();
  CmdVel(const char* data);
  CmdVel(const std::string& data);
  CmdVel(float lin, float ang);

  virtual ~CmdVel() = default;

  void set_data(float lin, float ang);

  float get_lin();
  float get_ang();
};

#endif /* end of include guard CMDVEL_HPP */
