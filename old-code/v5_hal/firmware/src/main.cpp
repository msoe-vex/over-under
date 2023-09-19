#include "main.h"

NodeManager* node_manager = new NodeManager(pros::millis);

// Declare all nodes here
ControllerNode* primary_controller;

MotorNode* left_front_drive;
MotorNode* left_front_drive_2;
MotorNode* left_rear_drive;
MotorNode* left_rear_drive_2;
MotorNode* right_front_drive;
MotorNode* right_front_drive_2;
MotorNode* right_rear_drive;
MotorNode* right_rear_drive_2;
TankDriveNode* holonomic_drive_node;

ADIEncoderNode* x_odom_encoder;
ADIEncoderNode* y_odom_encoder;

InertialSensorNode* inertial_sensor;

OdometryNode* odom_node;

AutonManagerNode* auton_manager_node;

ConnectionCheckerNode* connection_checker_node;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  Logger::giveNodeManager(node_manager);

  // Define all nodes used by the robot here
  primary_controller = new ControllerNode(node_manager, "primary");

  /* Define the odometry components */
  x_odom_encoder =
      new ADIEncoderNode(node_manager, 'A', 'B', "xOdomEncoder", false);
  y_odom_encoder =
      new ADIEncoderNode(node_manager, 'C', 'D', "yOdomEncoder", false);

  inertial_sensor =
      new InertialSensorNode(node_manager, "inertialSensor", 20);  // Port 14

  /* Define the drivetrain components */
  left_front_drive =
      new MotorNode(node_manager, 17, "leftFrontDrive", true);  // previously 16
  left_front_drive_2 =
      new MotorNode(node_manager, 18, "leftFrontTopDrive", true);
  left_rear_drive = new MotorNode(node_manager, 15, "leftRearDrive", true);
  left_rear_drive_2 = new MotorNode(node_manager, 11, "leftRearTopDrive", true);

  right_front_drive = new MotorNode(node_manager, 13, "rightFrontDrive", false);
  right_front_drive_2 =
      new MotorNode(node_manager, 14, "rightFrontTopDrive", false);
  right_rear_drive =
      new MotorNode(node_manager, 9, "rightRearDrive", false);  // 2 is ded
  right_rear_drive_2 =
      new MotorNode(node_manager, 10, "rightRearTopDrive", false);  // prev

  odom_node = new OdometryNode(
      node_manager, "odometry", x_odom_encoder, y_odom_encoder, inertial_sensor,
      OdometryNode::FOLLOWER);

  TankDriveNode::TankEightMotors holonomic_drive_motors = {
      left_front_drive,  left_front_drive_2, left_rear_drive,
      left_rear_drive_2, right_front_drive,  right_front_drive_2,
      right_rear_drive,  right_rear_drive_2};

  EncoderConfig holonomic_encoder_config = {
      0,    // Initial ticks
      360,  // Ticks per RPM
      3.75  // Wheel diameter
  };

  TankDriveKinematics::TankWheelLocations holonomic_wheel_locations = {
      Vector2d(-5.48, 5.48),  // Left front
      Vector2d(5.48, 5.48),   // Right front
  };

  TankDriveKinematics holonomic_drive_kinematics(
      holonomic_encoder_config, holonomic_wheel_locations);

  holonomic_drive_node = new TankDriveNode(
      node_manager, "drivetrain", primary_controller, holonomic_drive_motors,
      holonomic_drive_kinematics);

  /* Define other components */
  connection_checker_node = new ConnectionCheckerNode(node_manager);

  /* Define autonomous components */
  auton_manager_node = new AutonManagerNode(
      node_manager, holonomic_drive_node, odom_node, inertial_sensor);

  // Call the node manager to initialize all of the nodes above
  node_manager->initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  while (pros::competition::is_disabled()) {
    node_manager->m_handle->spinOnce();
  }
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  // Reset all nodes to default configuration
  node_manager->reset();

  // Reset the chosen autonomous and initialize
  auton_manager_node->selected_auton->AutonInit();

  // Execute autonomous code
  while (pros::competition::is_autonomous()) { node_manager->executeAuton(); }
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 *
 * NOTE: If custom code is needed outside of the node manager, it should be put
 * into a different task with a wait. Each node has an embedded timing control
 * loop and adding a wait to this thread will disrupt the performance of all
 * nodes.
 */
void opcontrol() {
  // Reset all nodes to default configuration
  node_manager->reset();

  // Execute teleop code
  while (true) { node_manager->executeTeleop(); }
}
