use vex_rt::prelude::*;

use crate::smart_motor::SmartMotor;
use crate::smart_motor_group::MotorGroup;

pub struct Drive {
    pub left_drive: MotorGroup,
    pub right_drive: MotorGroup,
}

impl Drive {
    pub fn run(&mut self, left: i8, right: i8) -> Result<(), Error> {
        self.left_drive.connect()?.move_i8(left)?;
        self.right_drive.connect()?.move_i8(right)?;
        Ok(())
    }
}
