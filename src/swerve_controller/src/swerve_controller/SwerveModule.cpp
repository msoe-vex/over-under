#include "swerve_controller/SwerveModule.h"

SwerveModule::SwerveModule(Eigen::Vector2d module_location, double rotation_angle_threshold, 
    double max_velocity, double max_rotation_velocity) : 
    m_module_location(module_location),
    m_rotation_angle_threshold(rotation_angle_threshold), 
    m_max_velocity(max_velocity), 
    m_max_rotation_velocity(max_rotation_velocity) {

}

MotorPowers SwerveModule::InverseKinematics(Eigen::Vector2d target_velocity, double target_rotation_velocity, Eigen::Rotation2Dd module_actual_angle) {
    ROS_INFO("Target Velocity - x:%.2f y:%.2f", target_velocity(0), target_velocity(1));
    ROS_INFO("Target Rotation Velocity: %.2f", target_rotation_velocity);

    // If you aren't trying to move, make sure to send no velocity to the motors
    if ((target_velocity(0) == 0) && (target_velocity(1) == 0) && (target_rotation_velocity == 0)) { //not sure if this works, might need to be reworked
        double scaled_motor_1_mag = 0;
        double scaled_motor_2_mag = 0;

        MotorPowers motor_powers;
        
        motor_powers.left_motor_power = scaled_motor_1_mag;
        motor_powers.right_motor_power = scaled_motor_2_mag;

        return motor_powers;
    }

    // Create a maximum power vector for translating motor into percent motor output power
    Eigen::Vector2d max_motor_vector(m_max_velocity, m_max_rotation_velocity);

    // Find the length of the maxium power vector, but divide by sqrt(2) to account for the fact that later
    // we will be projecting vectors onto this vector and due to the 45-45-90 nature of this conversion need to 
    // divide this vector by sqrt(2)
    float max_motor_power = max_motor_vector.norm() / sqrt(2); 

    // Take the vector from the origin to the module (module_location) and rotate it to 
    // make it orthogonal to the current (module_location) vector
    Eigen::Vector2d rotated_module_location = Eigen::Rotation2Dd(M_PI / 2) * m_module_location;

    // Multiply the orthogonal vector (rotated_module_location) by the target angular velocity
    // (target_rotation_velocity) to create your target rotation vector
    Eigen::Vector2d target_rotation_vector = target_rotation_velocity * rotated_module_location;

    // Add the target velocity and rotation vectors to get a resultant target vector
    Eigen::Vector2d target_vector = target_velocity + target_rotation_vector;

    ROS_INFO("Target Vector - x:%.2f y:%.2f", target_vector(0), target_vector(1));

    // Get the angle of the target vector by taking tangent inverse of y and x components
    // of the vector, and convert to a Rotation2D angle object
    Eigen::Rotation2Dd target_vector_angle = Eigen::Rotation2Dd(atan2(target_vector(1), target_vector(0)));

    ROS_INFO("Current Angle: %.2f", module_actual_angle.angle());
    ROS_INFO("Target Angle: %.2f", target_vector_angle.angle());

    // Subtract the actual module vector from the target to find the change in angle needed
    double module_rotation_delta = (target_vector_angle * module_actual_angle.inverse()).smallestAngle();

    // Determine if we need to only turn the module, or if we can move while turning. Current limit
    // is 60 degrees, if above we will exclusively turn, and if below we turn proportional to the
    // angle needed
    Eigen::Vector2d motor_power_vector;
    if (module_rotation_delta >= m_rotation_angle_threshold) {
        // Exclusively turn to the target (max speed turn)
        motor_power_vector(1) = 1.0;
        motor_power_vector(0) = 0.0;
    } else {
        // Turn proportional to how far off we are from the target
        motor_power_vector(1) = module_rotation_delta / m_rotation_angle_threshold; 

        // Set the power as the magnitude of the vector
        motor_power_vector(0) = target_vector.norm() / m_max_velocity;
    }



    ROS_INFO("Motor Power Vector - x:%.2f y:%.2f", motor_power_vector(0), motor_power_vector(1));


    // We are working in the (m/s Forward)-(rpm Speed of Rotation) plane now
    // Project the target vector onto each max motor vector to get components
    // This finds the projection magnitude onto the max motor vector
    double scaled_motor_1_mag = motor_power_vector.dot(Eigen::Vector2d(1, 1));
    double scaled_motor_2_mag = motor_power_vector.dot(Eigen::Vector2d(-1, 1));

    ROS_INFO("Max Motor Mag: %.2f", max_motor_power);

    ROS_INFO("Scaled Motor 1 Mag (START): %.2f", scaled_motor_1_mag);
    ROS_INFO("Scaled Motor 2 Mag (START): %.2f", scaled_motor_2_mag);

    float max_scaled_motor_mag = fmax(fabs(scaled_motor_1_mag), fabs(scaled_motor_2_mag));

    // If the max of the two motor powers is more than we can ouput, scale both down so the max motor's power
    // is equal to the max_motor_power
    if(max_scaled_motor_mag > 1.0) {
        scaled_motor_1_mag /= max_scaled_motor_mag;
        scaled_motor_2_mag /= max_scaled_motor_mag;
    }

    ROS_INFO("Scaled Motor 1 Mag (1): %.2f", scaled_motor_1_mag);
    ROS_INFO("Scaled Motor 2 Mag (1): %.2f", scaled_motor_2_mag);

    // Scale motors between -127 and 127
    scaled_motor_1_mag = scaled_motor_1_mag * 127.0;
    scaled_motor_2_mag = scaled_motor_2_mag * 127.0;

    ROS_INFO("Scaled Motor 1 Mag (FINAL): %.2f", scaled_motor_1_mag);
    ROS_INFO("Scaled Motor 2 Mag (FINAL): %.2f", scaled_motor_2_mag);

    // Set and return the motor powers as a pointer
    MotorPowers motor_powers;

    motor_powers.left_motor_power = (int8_t)scaled_motor_1_mag;
    motor_powers.right_motor_power = (int8_t)scaled_motor_2_mag;

    return motor_powers;
}
