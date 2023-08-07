#pragma once

namespace interface {
class Motor {
 public:
  virtual void Move(int) = 0;
  virtual void MoveVoltage(int) = 0;
  virtual void MoveVelocity(float) = 0;
  virtual void MoveAbsolute(double position, int max_velocity) = 0;

  virtual ~Motor() = default;
};
}  // namespace interface