#include "drivetrain/tank_drive.h"

namespace drivetrain {
void TankDrive::Drive(const interface::Controller& controller) {
  const drivetrain::TankMotorVoltages voltages;

  voltages.left_motor_voltage = controller.GetJoystickVoltage(
      interface::ControllerJoystick::kLeftY);
  voltages.right_motor_voltage = controller.GetJoystickVoltage(
      interface::ControllerJoystick::kRightY);
  
  tank_motors().SetVoltages(voltages);
}
}
