#pragma once
#include "drivetrain/holonomic_drive.h"
#include "hardware/pros_controller.h"
#include "pros.h"

void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);