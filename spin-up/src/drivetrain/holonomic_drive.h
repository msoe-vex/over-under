#pragma once
#include <vector>

#include "drivetrain/holonomic_motors.h"
#include "interface/controller.h"
#include "interface/motor.h"

namespace drivetrain {
class HolonomicDrivetrain {
 public:
  HolonomicDrivetrain(HolonomicMotors holonomic_motors)
      : holonomic_motors_(std::move(holonomic_motors)) {}

 protected:
  [[nodiscard]] inline HolonomicMotors& holonomic_motors() {
    return holonomic_motors_;
  }

 private:
  HolonomicMotors holonomic_motors_;
};

/**
 * Implements a holonomic drive system.
 */
class FieldOrientedHolonomicDrivetrain : public HolonomicDrivetrain {
 public:
  using HolonomicDrivetrain::HolonomicDrivetrain;
};

class HolonomicDirectDrivetrain : virtual public HolonomicDrivetrain {
 public:
  using HolonomicDrivetrain::HolonomicDrivetrain;  // constructor inheritance

  void Drive(const interface::Controller&);
};
}  // namespace drivetrain