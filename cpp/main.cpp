/**
 * @author      : theo (theo@$HOSTNAME)
 * @file        : main
 * @created     : Sunday Sep 29, 2019 12:11:14 MDT
 */

#include "CmdVel.hpp"
#include "Message.hpp"

int main() {

  /*
   * Create a cmd vel on the stack (faster insertions)
   */
  CmdVel a;

  /*
   * Set the data (specific to cmd vel, not found in message)
   */
  a.set_data(6.7345, 23.42324);
  std::cout << a.get_ang() << " " << a.get_lin() << std::endl;

  /*
   * Create a cmdvel b to show the transfer of messages
   */
  CmdVel b;
  /*
   * serialize_to_string returns an std::string that contains the data
   */
  std::string msg = a.serialize_to_string();

  /*
   * You can parse from an std::string or char* but char* is private
   */
  b.parse_from_string(msg);

  /*
   * Set data overrides data in the packet
   */
  b.set_data(234.4242, 9.234234);
  std::cout << b.get_ang() << " " << b.get_lin() << std::endl;

  /*
   * Create a new Cmd Vel using a string
   */
  CmdVel c(b.serialize_to_string());
  std::cout << c.get_ang() << " " << c.get_lin() << std::endl;

  /*
   * Serialize_to_string returns std::string, make it a char
   */
  const char *data = c.serialize_to_string().c_str();
  /*
   * Make a new string
   */
  const std::string data2 = c.serialize_to_string();

  /*
   * Showing methods of transfering data, the = sign copies the string into the
   * buffer and initializes index and stuff in the buffer
   */
  CmdVel d = c;
  CmdVel e = data;
  CmdVel f = data2;

  std::cout << d.get_ang() << " " << d.get_lin() << std::endl;
  std::cout << e.get_ang() << " " << e.get_lin() << std::endl;
  std::cout << f.get_ang() << " " << f.get_lin() << std::endl;

  // Showing the range of a message
  e.set_data(2.3232323232323232323232323232323,
             9.01239120937120751273501284750182376718254301275380123985123872);
  std::cout << e.get_ang() << " " << e.get_lin() << std::endl;
  return 1;
}
