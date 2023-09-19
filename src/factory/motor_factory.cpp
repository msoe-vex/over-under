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

// TODO: Add checks to ensure that both definitions vectors are the same size.
std::unique_ptr<drivetrain::TankDrive> MakeTankDrive(
    TankDriveDefinition driveDefinition) {
  
  std::unique_ptr<interface::Motor> left_motor_group_ptr;
  std::unique_ptr<interface::Motor> right_motor_group_ptr;

  left_motor_group_ptr = std::make_unique<ProsMotorGroup>(
    driveDefinition.leftMotorDefinitions,
    constant::kDrivetrainCartridge);
  right_motor_group_ptr = std::make_unique<ProsMotorGroup>(
    driveDefinition.rightMotorDefinitions,
    constant::kDrivetrainCartridge);

  return std::make_unique<drivetrain::TankDrive>(
      drivetrain::TankMotors(left_motor_group_ptr, right_motor_group_ptr));
}
}  // namespace factory