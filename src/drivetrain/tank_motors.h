#pragma once
#include <memory>

#include "constant/motor_constants.h"
#include "hardware/pros_motor_group.h"

namespace drivetrain {
class TankMotors {
  public:
    TankMotors(std::unique_ptr<hardware::ProsMotorGroup> left_motor_group_ptr, 
        std::unique_ptr<hardware::ProsMotorGroup> right_motor_group_ptr)
        : left_motor_group_ptr_(std::move(left_motor_group_ptr)),
          right_motor_group_ptr_(std::move(right_motor_group_ptr)) {}
  
    struct TankMotorVoltages {
      int8_t left_motor_voltage;
      int8_t right_motor_voltage;
    };

    inline void SetVoltages(const TankMotorVoltages& voltages) {
      left_motor_group_ptr_->MoveVoltage(voltages.left_motor_voltage);
      right_motor_group_ptr_->MoveVoltage(voltages.right_motor_voltage);
    }

  private:
    std::unique_ptr<hardware::ProsMotorGroup> left_motor_group_ptr_;
    std::unique_ptr<hardware::ProsMotorGroup> right_motor_group_ptr_;
};
}  // namespace drivetrain