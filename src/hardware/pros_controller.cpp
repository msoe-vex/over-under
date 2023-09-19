#include "hardware/pros_controller.h"

#include "constant/constants.h"

namespace hardware {
pros::controller_analog_e_t GetProsJoystick(
    interface::ControllerJoystick joystick) {
  switch (joystick) {
    case interface::ControllerJoystick::kLeftX:
      return pros::E_CONTROLLER_ANALOG_LEFT_X;
    case interface::ControllerJoystick::kLeftY:
      return pros::E_CONTROLLER_ANALOG_LEFT_Y;
    case interface::ControllerJoystick::kRightX:
      return pros::E_CONTROLLER_ANALOG_RIGHT_X;
    case interface::ControllerJoystick::kRightY:
      return pros::E_CONTROLLER_ANALOG_RIGHT_Y;
    default:
      throw std::invalid_argument("Expected a convertible joystick.");
  }
}

int ProsController::GetJoystickAnalog(
    interface::ControllerJoystick joystick) const {
  return controller().get_analog(GetProsJoystick(joystick));
}

float ProsController::GetJoystickVoltage(
    interface::ControllerJoystick joystick) const {
  return controller().get_analog(GetProsJoystick(joystick)) /
         // cast to float to prevent integer division
         static_cast<float>(constant::kProsMaxJoystickAnalog) *
         constant::kProsMaxMotorVoltage;
}

std::unique_ptr<ProsController> ProsController::MakeDriverController() {
  return std::make_unique<hardware::ProsController>(pros::E_CONTROLLER_MASTER);
}

std::unique_ptr<ProsController> ProsController::MakeSecondaryController() {
  return std::make_unique<hardware::ProsController>(pros::E_CONTROLLER_PARTNER);
}
}  // namespace hardware