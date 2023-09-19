#pragma once

namespace hardware {
struct ProsMotorDefinition {
 public:
  int port_number;
  bool reverse;

  ProsMotorDefinition(int port_number, bool reverse)
      : port_number(port_number), reverse(reverse) {}

  /**
   * Returns the virtual port number which can be consumed by pros::Motor and
   * pros::MotorGroup directly.
   * @see https://pros.cs.purdue.edu/v5/api/cpp/motors.html#constructor-s
   */
  inline int GetProsVirtualPortNumber() {
    return port_number * (reverse ? -1 : 1);
  }
};
}  // namespace hardware