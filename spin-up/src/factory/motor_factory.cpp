#include "motor_factory.h"

namespace factory {
drivetrain::HolonomicDrivetrain MakeHolonomicDrivetrain(
    HolonomicDrivetrainDefinition drivetrainDefinition) {
  std::vector<std::unique_ptr<interface::Motor>> motor_ptrs;
  // emplace back constructs the ptr inside the vector instead of copying
  motor_ptrs.emplace_back(std::make_unique<hardware::ProsMotorGroup>(
      drivetrainDefinition.frontRightMotorDefinitions,
      constant::kDrivetrainCartridge));
  motor_ptrs.emplace_back(std::make_unique<hardware::ProsMotorGroup>(
      drivetrainDefinition.backRightMotorDefinitions,
      constant::kDrivetrainCartridge));
  motor_ptrs.emplace_back(std::make_unique<hardware::ProsMotorGroup>(
      drivetrainDefinition.backLeftMotorDefinitions,
      constant::kDrivetrainCartridge));
  motor_ptrs.emplace_back(std::make_unique<hardware::ProsMotorGroup>(
      drivetrainDefinition.frontLeftMotorDefinitions,
      constant::kDrivetrainCartridge));

  return drivetrain::HolonomicDrivetrain(
      drivetrain::HolonomicMotors(std::move(motor_ptrs)));
}
}  // namespace factory