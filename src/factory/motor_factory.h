#pragma once
#include <vector>

#include "drivetrain/holonomic_drive.h"
#include "drivetrain/holonomic_motors.h"
#include "hardware/pros_motor.h"
#include "hardware/pros_motor_definition.h"

namespace factory {
// enum class Robot { kRobotOne, kRobotTwo };

struct HolonomicDrivetrainDefinition {
  public:
    std::vector<hardware::ProsMotorDefinition> frontRightMotorDefinitions;
    std::vector<hardware::ProsMotorDefinition> backRightMotorDefinitions;
    std::vector<hardware::ProsMotorDefinition> backLeftMotorDefinitions;
    std::vector<hardware::ProsMotorDefinition> frontLeftMotorDefinitions;
};

struct TankDriveDefinition {
  public:
    std::vector<hardware::ProsMotorDefinition> 
        leftMotorDefinitions, rightMotorDefinitions;
}

[[nodiscard]] drivetrain::HolonomicDrivetrain MakeHolonomicDrivetrain(
    HolonomicDrivetrainDefinition drivetrainDefinition);

[[nodiscard]] std::unique_ptr<drivetrain::TankDrive> MakeTankDrive(
  TankDriveDefinition driveDefinition);

// [[nodiscard]] MakeProsMotor();
}  // namespace factory