#include "DriverControlNode.h"

// By default, this constructor calls the constructor for the Node object in
// NodeManager.h
DriverControlNode::DriverControlNode(NodeManager* node_manager, MotorNode* left_swerve_1, MotorNode* left_swerve_2, 
        ADIAnalogInNode* left_swerve_pot, MotorNode* right_swerve_1, MotorNode* right_swerve_2, 
        ADIAnalogInNode* right_swerve_pot, MotorNode* rear_swerve_1, MotorNode* rear_swerve_2, 
        ADIAnalogInNode* rear_swerve_pot, MotorNode* left_intake, MotorNode* right_intake, MotorNode* bottom_rollers,
        MotorNode* ejection_roller, MotorNode* top_rollers, InertialSensorNode* inertial_sensor, ControllerNode* controller_primary) : Node(node_manager, 20), 
    swerveController(left_module_location, right_module_location, rear_module_location, rotation_angle_threshold,
    max_velocity, max_rotation_velocity, kP, kI, kD), left_swerve_1(left_swerve_1), left_swerve_2(left_swerve_2),
    left_swerve_pot(left_swerve_pot), right_swerve_1(right_swerve_1), right_swerve_2(right_swerve_2),
    right_swerve_pot(right_swerve_pot), rear_swerve_1(rear_swerve_1), rear_swerve_2(rear_swerve_2),
    rear_swerve_pot(rear_swerve_pot), left_intake(left_intake), right_intake(right_intake), bottom_rollers(bottom_rollers),
    ejection_roller(ejection_roller), top_rollers(top_rollers), inertial_sensor(inertial_sensor), controller_primary(controller_primary->getController()) {

    left_module_location(0) = left_module_location_x;
    left_module_location(1) = left_module_location_y;
    right_module_location(0) = right_module_location_x;
    right_module_location(1) = right_module_location_y;
    rear_module_location(0) = rear_module_location_x;
    rear_module_location(1) = rear_module_location_y;
}

void DriverControlNode::initialize() {
    Node::m_handle->initNode();
}

/**
 * Spins the front intakes of the robot at the specified voltage
 * Parameters:
 * 		voltage: The voltage, from -127 to 127
 */
void DriverControlNode::m_spinIntakesVoltage(int voltage) {
	left_intake->moveVoltage(voltage);
    right_intake->moveVoltage(voltage);
}

/**
 * Spins the primary set of top and bottom rollers (from a single motor) at the specified voltage
 * Parameters:
 * 		voltage: The voltage, from -127 to 127
 */
void DriverControlNode::m_spinMainRollersVoltage(int voltage) {
	bottom_rollers->moveVoltage(voltage);
    top_rollers->moveVoltage(voltage);
}

/**
 * Spins the ejection roller (from a single motor) at the specified voltage
 * Parameters:
 * 		voltage: The voltage, from -127 to 127
 */
void DriverControlNode::m_spinEjectionRollerVoltage(int voltage) {
	ejection_roller->moveVoltage(voltage);
}

void DriverControlNode::periodic() {
    robot_angle = Eigen::Rotation2D(inertial_sensor->getYaw());
    
    controller_target_velocity(0) = (controller_primary->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) / 127.0) * max_velocity;
    controller_target_velocity(1) = (controller_primary->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0) * max_velocity;
    rotation_velocity = (controller_primary->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127.0) * max_rotation_velocity;

    field_target_velocity = robot_angle.inverse() * controller_target_velocity;

    swerveController.assignActualAngle(left_swerve_pot->getValue(), right_swerve_pot->getValue(), rear_swerve_pot->getValue());

    MotorPowers left_motor_powers = swerveController.calculateLeftModule(field_target_velocity, rotation_velocity);
    MotorPowers right_motor_powers = swerveController.calculateRightModule(field_target_velocity, rotation_velocity);
    MotorPowers rear_motor_powers = swerveController.calculateRearModule(field_target_velocity, rotation_velocity);

    left_swerve_1->move(left_motor_powers.left_motor_power);
    left_swerve_2->move(left_motor_powers.right_motor_power);
    right_swerve_1->move(right_motor_powers.left_motor_power);
    right_swerve_2->move(right_motor_powers.right_motor_power);
    rear_swerve_1->move(rear_motor_powers.left_motor_power);
    rear_swerve_2->move(rear_motor_powers.right_motor_power);

    int intake_voltage = 0;
	int main_rollers_voltage = 0;
	int ejection_roller_voltage = 0;

	if (controller_primary->get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
		intake_voltage = 12000;
		main_rollers_voltage = 12000;
		ejection_roller_voltage = 12000;

		if (controller_primary->get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			ejection_roller_voltage *= -1;
		}
	}
	else if (controller_primary->get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
		intake_voltage = -12000;
		main_rollers_voltage = -12000;
		ejection_roller_voltage = -12000;
	}

	m_spinIntakesVoltage(intake_voltage);
	m_spinMainRollersVoltage(main_rollers_voltage);
	m_spinEjectionRollerVoltage(ejection_roller_voltage);
}

DriverControlNode::~DriverControlNode() { 
    delete m_publisher; 
}
