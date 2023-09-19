#pragma once
#include "tank_motors.h"
#include "interface/controller.h"
#include "interface/motor.h"

namespace drivetrain {
class TankDrive {
  public:
    TankDrive(TankMotors tank_motors)
        : tank_motors_(std::move(tank_motors)) {}
    
    void Drive(const interface::Controller&);
  
  protected:
    [[nodiscard]] inline TankMotors& tank_motors() {
      return tank_motors_;
    }

  private:
    TankMotors tank_motors_;
}
}
