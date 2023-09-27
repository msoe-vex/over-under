use core::mem;

use alloc::string::String;
use vex_rt::prelude::*;

pub enum SmartMotor {
    Connected(Motor),
    Disconnected(Option<SmartPort>, Gearset, EncoderUnits, bool),
}

impl SmartMotor {
    pub fn new(
        port: SmartPort,
        gearset: Gearset,
        encoder_units: EncoderUnits,
        reverse: bool,
    ) -> SmartMotor {
        if port.plugged_type() == DeviceType::Motor {
            SmartMotor::Connected(port.into_motor(gearset, encoder_units, reverse).unwrap())
        } else {
            SmartMotor::Disconnected(Some(port), gearset, encoder_units, reverse)
        }
    }

    pub fn connect(&mut self) -> Result<&mut Motor, Error> {
        match self {
            SmartMotor::Connected(motor) => Ok(motor),
            SmartMotor::Disconnected(port, gearset, encoder_units, reverse) => {
                if port
                    .as_mut()
                    .expect("port should never be None outside of this method")
                    .plugged_type()
                    == DeviceType::Motor
                {
                    let taken_port = mem::take(port);
                    let motor = taken_port
                        .unwrap()
                        .into_motor(*gearset, *encoder_units, *reverse)
                        .unwrap();

                    mem::swap(self, &mut SmartMotor::Connected(motor));

                    match self {
                        SmartMotor::Connected(motor) => Ok(motor),
                        SmartMotor::Disconnected(..) => unreachable!(),
                    }
                } else {
                    Err(Error::Custom(String::from("error")))
                }
            }
        }
    }
}
