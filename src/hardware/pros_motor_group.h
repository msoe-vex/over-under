#pragma once
#include <algorithm>
#include <cstdint>
#include <numeric>
#include <vector>

#include "constant/constants.h"
#include "hardware/pros_motor.h"
#include "hardware/pros_motor_cartridge.h"
#include "hardware/pros_motor_definition.h"
#include "interface/encoder.h"
#include "interface/motor.h"
#include "pros.h"

namespace hardware {
class ProsMotorGroup : public interface::Motor, public interface::Encoder {
 public:
  ProsMotorGroup(
      std::vector<ProsMotorDefinition> definitions,
      ProsMotorCartridge cartridge)
      : motors_(ExtractVirtualPortNumbers(definitions)) {
    motors().set_gearing(static_cast<pros::motor_gearset_e_t>(cartridge));
  }

  ProsMotorGroup(const ProsMotorGroup&) = delete;
  ProsMotorGroup& operator=(const ProsMotorGroup&) = delete;

  ProsMotorGroup(ProsMotorGroup&&) = default;
  ProsMotorGroup& operator=(ProsMotorGroup&&) = default;
  ~ProsMotorGroup() = default;

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

  /**
   * Extracts the virtual port numbers of each ProsMotorDefintion in
   * definitions.
   */
  [[nodiscard]] std::vector<std::int8_t> ExtractVirtualPortNumbers(
      std::vector<ProsMotorDefinition> definitions);
  // [[nodiscard]] std::vector<std::int8_t> FlipPortNumbers(
  //     std::vector<int> port_numbers, std::vector<bool> reverse);

  [[nodiscard]] inline pros::MotorGroup& motors() const { return motors_; }
  [[nodiscard]] inline pros::MotorGroup& motors() { return motors_; }

  // mutable to prevent issues with const methods since
  // Some pros methods are missing const annotations
  mutable pros::MotorGroup motors_;
};
}  // namespace hardware