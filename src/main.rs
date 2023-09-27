#![no_std]
#![no_main]
extern crate alloc;

use core::time::Duration;

use alloc::ffi::CString;
use robot_15_in::Robot15In;
use robot_24_in::Robot24In;
use smart_motor::SmartMotor;
use vex_rt::{prelude::*, select};

use crate::file_system::{File, FileOpenMode};

pub mod drive;
pub mod file_system;
mod robot_15_in;
mod robot_24_in;
mod smart_motor;

enum RobotController {
    Robot24In(Robot24In),
    Robot15In(Robot15In),
}

impl Robot for RobotController {
    fn new(peripherals: Peripherals) -> Self {
        let robot_name = {
            //TODO: check if file exists
            let file = File::open("/usd/robotName.txt", FileOpenMode::Read);

            file.read().unwrap()
        };

        match robot_name.as_str() {
            "15in" => RobotController::Robot15In(Robot15In::new(peripherals)),
            "25in" => RobotController::Robot24In(Robot24In::new(peripherals)),
            _ => RobotController::Robot24In(Robot24In::new(peripherals)),
        }
    }

    fn initialize(self: &mut RobotController, ctx: Context) {
        match self {
            RobotController::Robot24In(robot) => robot.initialize(ctx),
            RobotController::Robot15In(robot) => robot.initialize(ctx),
        }
    }

    fn autonomous(self: &mut RobotController, ctx: Context) {
        println!("autonomous");
        match self {
            RobotController::Robot24In(robot) => robot.autonomous(ctx),
            RobotController::Robot15In(robot) => robot.autonomous(ctx),
        }
    }

    fn opcontrol(self: &mut RobotController, ctx: Context) {
        println!("opcontrol");
        match self {
            RobotController::Robot24In(robot) => robot.opcontrol(ctx),
            RobotController::Robot15In(robot) => robot.opcontrol(ctx),
        }
    }

    fn disabled(self: &mut RobotController, ctx: Context) {
        println!("disabled");
        match self {
            RobotController::Robot24In(robot) => robot.disabled(ctx),
            RobotController::Robot15In(robot) => robot.disabled(ctx),
        }
    }
}

entry!(RobotController);
