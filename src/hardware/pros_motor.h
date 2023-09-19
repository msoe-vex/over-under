#pragma once
#include "constant/constants.h"
#include "hardware/pros_motor_cartridge.h"
#include "hardware/pros_motor_definition.h"
#include "interface/encoder.h"
#include "interface/motor.h"
#include "pros.h"

namespace hardware {
/**
 * A class which wraps a single pros::Motor object.
 */
class ProsMotor : public interface::Motor, public interface::Encoder {
 public:
  ProsMotor(ProsMotorDefinition definition, ProsMotorCartridge cartridge)
      : motor_(
            definition.GetProsVirtualPortNumber(),
            ConvertProsMotorCartridge(cartridge)) {}

  ProsMotor(const ProsMotor&) = delete;
  ProsMotor& operator=(const ProsMotor&) = delete;

  ProsMotor(ProsMotor&&) = default;
  ProsMotor& operator=(ProsMotor&&) = default;
  ~ProsMotor() = default;

  void Move(int) override;
  void MoveVoltage(int) override;
  void MoveVelocity(float) override;
  void MoveAbsolute(double position, int max_velocity) override;

  void ResetEncoder() override;
  [[nodiscard]] double position() const override;
  [[nodiscard]] float velocity() const override;

 private:
  [[nodiscard]] ProsMotorCartridge cartridge() const;
  [[nodiscard]] int max_rpm() const;

  [[nodiscard]] inline pros::Motor& motor() { return motor_; }
  [[nodiscard]] inline const pros::Motor& motor() const { return motor_; }

  pros::Motor motor_;
};
}  // namespace hardware