#![no_std]
#![no_main]
extern crate alloc;

use core::time::Duration;

use alloc::ffi::CString;
use smart_motor::SmartMotor;
use vex_rt::{prelude::*, select};

mod drive;
mod smart_motor;
struct MyRobot {
    drive: Mutex<drive::Drive>,
    controller: Controller,
}

impl Robot for MyRobot {
    fn new(peripherals: Peripherals) -> Self {
        Self {
            drive: Mutex::new(drive::Drive {
                left_drive: SmartMotor::new(
                    peripherals.port12,
                    Gearset::EighteenToOne,
                    EncoderUnits::Degrees,
                    false,
                ),
                right_drive: SmartMotor::new(
                    peripherals.port13,
                    Gearset::EighteenToOne,
                    EncoderUnits::Degrees,
                    true,
                ),
            }),
            controller: peripherals.master_controller,
        }
    }

    fn initialize(self: &mut MyRobot, _ctx: Context) {
        // Do any extra initialization here.
    }

    fn autonomous(self: &mut MyRobot, _ctx: Context) {
        println!("autonomous");
        // Write your autonomous routine here.
    }

    fn opcontrol(self: &mut MyRobot, ctx: Context) {
        println!("opcontrol");

        let file = unsafe {
            let directory = CString::new("/usd/robotName.txt").unwrap();
            let mode = CString::new("r").unwrap() ;

            libc::fopen(directory.as_ptr() as *const u8, mode.as_ptr() as *const u8)
        };
        
        // This loop construct makes sure the drive is updated every 10
        // milliseconds.
        let mut l = Loop::new(Duration::from_millis(10));
        loop {
            // Update the motors.
            self.drive.lock().run(
                self.controller.left_stick.get_y().unwrap(),
                self.controller.right_stick.get_y().unwrap(),
            );

            select! {
                // If the driver control period is done, break out of the loop.
                _ = ctx.done() => break,

                // Otherwise, when it's time for the next loop cycle, continue.
                _ = l.select() => continue,
            }
        }
    }

    fn disabled(self: &mut MyRobot, _ctx: Context) {
        println!("disabled");
        // This runs when the robot is in disabled mode.
    }
}

entry!(MyRobot);
