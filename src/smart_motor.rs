use core::mem;

use alloc::string::String;
use vex_rt::{prelude::*};

pub struct SmartMotor {
    device: Device,
    gearset: Gearset,
    encoder_units: EncoderUnits,
    reverse: bool,
}

enum Device {
    Connected(Motor),
    Disconnected(Option<SmartPort>),
}

impl SmartMotor {
    pub fn new(
        port: SmartPort,
        gearset: Gearset,
        encoder_units: EncoderUnits,
        reverse: bool,
    ) -> SmartMotor {
        let device = if port.plugged_type() == DeviceType::Motor {
            Device::Connected(port.into_motor(gearset, encoder_units, reverse).unwrap())
        } else {
            Device::Disconnected(Some(port))
        };

        SmartMotor {
            device,
            gearset,
            encoder_units,
            reverse,
        }
    }

    pub fn connect(&mut self) -> Result<&mut Motor, Error> {
        let device = &mut self.device;
        match device {
            Device::Connected(motor) => Ok(motor),
            Device::Disconnected(port) => {
                if port
                    .as_mut()
                    .expect("port should never be None outside of this method")
                    .plugged_type()
                    == DeviceType::Motor
                {
                    let old_port = mem::take(port);
                    let motor = old_port
                        .unwrap()
                        .into_motor(Gearset::EighteenToOne, EncoderUnits::Degrees, false)
                        .unwrap();

                    mem::swap(device, &mut Device::Connected(motor));

                    match device {
                        Device::Connected(motor) => Ok(motor),
                        Device::Disconnected(_) => unreachable!(),
                    }
                } else {
                    Err(Error::Custom(String::from("error")))
                }
            }
        }
    }
}
