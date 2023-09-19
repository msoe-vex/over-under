#include "hardware/pros_motor_cartridge.h"

namespace hardware {
pros::motor_gearset_e_t ConvertProsMotorCartridge(
    ProsMotorCartridge cartridge) {
  switch (cartridge) {
    case ProsMotorCartridge::kBlueCartridge:
      return pros::E_MOTOR_GEARSET_06;
    case ProsMotorCartridge::kGreenCartridge:
      return pros::E_MOTOR_GEARSET_18;
    case ProsMotorCartridge::kRedCartridge:
      return pros::E_MOTOR_GEARSET_36;
    default:
      throw std::invalid_argument(
          "Failed to convert cartridge to pros gearset.");
  }
}

ProsMotorCartridge ConvertProsGearset(pros::motor_gearset_e_t gearset) {
  switch (gearset) {
    case pros::E_MOTOR_GEARSET_06:
      return ProsMotorCartridge::kBlueCartridge;
    case pros::E_MOTOR_GEARSET_18:
      return ProsMotorCartridge::kGreenCartridge;
    case pros::E_MOTOR_GEARSET_36:
      return ProsMotorCartridge::kRedCartridge;
    default:
      throw std::invalid_argument(
          "Failed to convert pros gearset to cartridge.");
  }
}

int GetMaxRpm(ProsMotorCartridge cartridge) {
  switch (cartridge) {
    case ProsMotorCartridge::kBlueCartridge:
      return 600;
    case ProsMotorCartridge::kGreenCartridge:
      return 200;
    case ProsMotorCartridge::kRedCartridge:
      return 100;
    default:
      throw std::invalid_argument("Failed to convert cartridge to max rpm.");
  }
}
}