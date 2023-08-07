#pragma once

#include "pros.h"

namespace hardware {
enum class ProsMotorCartridge {
  // equal to pros value to enable casting
  kBlueCartridge = pros::E_MOTOR_GEAR_BLUE,   // 600 rpm
  kGreenCartridge = pros::E_MOTOR_GEAR_GREEN,  // 200 rpm
  kRedCartridge = pros::E_MOTOR_GEAR_RED  // 100 rpm
};

/**
 * Converts a ProsMotorCartridge to a pros gearset.
 */
[[nodiscard]] pros::motor_gearset_e_t ConvertProsMotorCartridge(
    ProsMotorCartridge);

/**
 * Converts a pros gearset to a ProsMotorCartridge.
 */
[[nodiscard]] ProsMotorCartridge ConvertProsGearset(pros::motor_gearset_e_t);

[[nodiscard]] int GetMaxRpm(const ProsMotorCartridge);
}  // namespace hardware