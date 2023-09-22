#include "drivetrain/holonomic_drive.h"

namespace drivetrain {
void HolonomicDirectDrivetrain::Drive(const interface::Controller& controller) {
  const std::vector<float> voltages = {
      controller.GetJoystickVoltage(interface::ControllerJoystick::kLeftX),
      controller.GetJoystickVoltage(interface::ControllerJoystick::kLeftY),
      controller.GetJoystickVoltage(interface::ControllerJoystick::kRightX),
      controller.GetJoystickVoltage(interface::ControllerJoystick::kRightY)};
  holonomic_motors().SetVoltages(voltages);
}
}  // namespace drivetrain