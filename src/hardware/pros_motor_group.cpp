#include "hardware/pros_motor_group.h"

namespace hardware {
void ProsMotorGroup::Move(int value) { motors().move(value); }
void ProsMotorGroup::MoveVoltage(int voltage) {
  motors().move_voltage(voltage);
}
void ProsMotorGroup::MoveVelocity(float velocity) {
  float rpm = (velocity / constant::kMaxVelocity) * max_rpm();
  motors().move_velocity(rpm);
}
void ProsMotorGroup::MoveAbsolute(double position, int max_velocity) {
  motors().move_absolute(position, max_velocity);
}
void ProsMotorGroup::ResetEncoder() { motors().tare_position(); }

double ProsMotorGroup::position() const {
  // manual member access to avoid automatically calling const motors()
  std::vector<double> positions = motors().get_positions();
  return std::reduce(positions.begin(), positions.end()) / positions.size();
}
float ProsMotorGroup::velocity() const {
  std::vector<double> motor_rpms = motors().get_actual_velocities();
  float rpm =
      std::reduce(motor_rpms.cbegin(), motor_rpms.cend()) / motor_rpms.size();
  return (rpm / max_rpm()) * constant::kMaxVelocity;
}

std::vector<std::int8_t> ProsMotorGroup::ExtractVirtualPortNumbers(
    std::vector<ProsMotorDefinition> definitions) {
  std::vector<std::int8_t> result;
  std::transform(
      definitions.cbegin(), definitions.cend(), std::back_inserter(result),
      [](ProsMotorDefinition definition) {
        return static_cast<std::int8_t>(definition.GetProsVirtualPortNumber());
      });
  return result;
}

ProsMotorCartridge ProsMotorGroup::cartridge() const {
  return ConvertProsGearset(motors()[0].get_gearing());
}
int ProsMotorGroup::max_rpm() const { return GetMaxRpm(cartridge()); }
}  // namespace hardware