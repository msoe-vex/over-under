use crate::smart_motor::SmartMotor;
use alloc::vec::Vec;
use vex_rt::{
    prelude::{Error, Motor},
    *,
};

pub struct MotorGroup {
    motors: Vec<SmartMotor>,
}

impl MotorGroup {
    pub fn new(motors: Vec<SmartMotor>) -> MotorGroup {
        MotorGroup { motors }
    }

    pub fn connect(&mut self) -> Result<Vec<&mut Motor>, Error> {
        self.motors
            .iter_mut()
            .map(|motor| motor.connect())
            .collect::<Result<Vec<_>, _>>()
    }

    pub fn move_i8(&mut self, voltage: i8) -> Result<(), Error> {
        for motor in self.connect()? {
            motor.move_i8(voltage)?;
        }
        Ok(())
    }
    pub fn move_velocity(&mut self, velocity: i32) -> Result<(), Error> {
        for motor in self.connect()? {
            motor.move_velocity(velocity)?;
        }
        Ok(())
    }
    pub fn move_voltage(&mut self, voltage: i32) -> Result<(), Error> {
        for motor in self.connect()? {
            motor.move_voltage(voltage)?;
        }
        Ok(())
    }
}
