#include "hardware/pros_motor.h"

namespace hardware {
void ProsMotor::Move(int value) { motor().move(value); }
void ProsMotor::MoveVoltage(int voltage) { motor().move_voltage(voltage); }
void ProsMotor::MoveVelocity(float velocity) {
  float rpm = (velocity / constant::kMaxVelocity) * max_rpm();
  motor().move_velocity(rpm);
}
void ProsMotor::MoveAbsolute(double position, int max_velocity) {
  motor().move_absolute(position, max_velocity);
}

void ProsMotor::ResetEncoder() { motor().tare_position(); }

double ProsMotor::position() const { return motor().get_position(); }
float ProsMotor::velocity() const {
  float rpm = motor().get_actual_velocity();
  return (rpm / max_rpm()) * constant::kMaxVelocity;
}

ProsMotorCartridge ProsMotor::cartridge() const {
  return ConvertProsGearset(motor().get_gearing());
}
int ProsMotor::max_rpm() const { return GetMaxRpm(cartridge()); }
}  // namespace hardware