use alloc::vec::Vec;
use vex_rt::*;
use crate::smart_motor::SmartMotor;

pub struct MotorGroup {
    motors: Vec<SmartMotor>,
}

impl MotorGroup {
    pub fn new(motors: Vec<SmartMotor>,) -> MotorGroup{
        this.motors = motors
    } 

    
        
    pub fn connect(self) -> Result<Vec<&mut Motor>, Error> {
        self
            .motors
            .iter()
            .map(|motor| motor.connect())
            .collect::<Result<Vec<_>, _>>()
    }

    pub fn move_i8(self, voltage: i8) {
        self.connect().unwrap().iter().for_each(|motor| motor.move_i8(voltage));
    }
    pub fn move_velocity(&mut self, velocity: i32) {
        self.connect().unwrap().iter().for_each(|motor| motor.move_velocity(self,velocity));
    }
    pub fn move_voltage(&mut self, velocity: i32) {
        self.connect().unwrap().iter().for_each(|motor| motor.move_voltage(self,voltage));
    }
    
}
