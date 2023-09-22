#pragma once
#include <vector>

#include "hardware/pros_motor.h"

namespace constant {
const auto kDrivetrainCartridge = hardware::ProsMotorCartridge::kBlueCartridge;
const std::vector<bool> kDrivetrainReverse = {false, true};

// {top motor, bottom motor}
const std::vector<int> kFrontRightMotorPorts = {1, 2};
const std::vector<int> kBackRightMotorPorts = {1, 2};
const std::vector<int> kBackLeftMotorPorts = {1, 2};
const std::vector<int> kFrontLeftMotorPorts = {1, 2};

// shooter - {left, right}
// transfer - {left, right}
}  // namespace constant