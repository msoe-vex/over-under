#pragma once
#include <memory>

#include "constant/motor_constants.h"
#include "hardware/pros_motor_group.h"

namespace drivetrain {
class HolonomicMotors {
 public:
  HolonomicMotors(std::vector<std::unique_ptr<interface::Motor>> motor_ptrs)
      : motor_ptrs_(std::move(motor_ptrs)) {}

  // Delete copy constructor and assignment operator to prevent issues with
  // wrapped unique_ptrs
  HolonomicMotors(const HolonomicMotors&) = delete;
  HolonomicMotors& operator=(const HolonomicMotors&) = delete;

  // Add move operators
  HolonomicMotors(HolonomicMotors&&) = default;
  HolonomicMotors& operator=(HolonomicMotors&&) = default;
  ~HolonomicMotors() = default;

  inline void SetVoltages(const std::vector<float>& voltages) const {
    for (int i = 0; i < voltages.size(); ++i) {
      motor_ptrs()[i]->MoveVoltage(voltages[i]);
    }
  };

 private:
  [[nodiscard]] inline std::vector<std::unique_ptr<interface::Motor>>&
  motor_ptrs() {
    return motor_ptrs_;
  }
  [[nodiscard]] inline const std::vector<std::unique_ptr<interface::Motor>>&
  motor_ptrs() const {
    return motor_ptrs_;
  }

  std::vector<std::unique_ptr<interface::Motor>> motor_ptrs_;
};
}  // namespace drivetrain