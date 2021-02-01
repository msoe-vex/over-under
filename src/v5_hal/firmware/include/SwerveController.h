#include "SwerveModule.h"
#include "eigen/Eigen/Dense"

class SwerveController{
    private:
    Eigen::Rotation2Dd left_actual_angle;
    Eigen::Rotation2Dd right_actual_angle;
    Eigen::Rotation2Dd rear_actual_angle;

    SwerveModule leftSwerveModule;
    SwerveModule rightSwerveModule;
    SwerveModule rearSwerveModule;

    MotorPowers left_motor_powers;
    MotorPowers right_motor_powers;
    MotorPowers rear_motor_powers;

    const int LEFT_POT_OFFSET = 2225;
    const int RIGHT_POT_OFFSET = 2875;
    const int REAR_POT_OFFSET = 3623;

public:
    SwerveController(Eigen::Vector2d left_module_location, Eigen::Vector2d right_module_location, Eigen::Vector2d rear_module_location,
    double rotation_angle_threshold, double max_velocity, double max_rotation_velocity, double kP, double kI, double kD);
     
    void assignActualAngle(int left_pot, int right_pot, int rear_pot);

    MotorPowers calculateLeftModule(Eigen::Vector2d target_velocity, double rotation_velocity);

    MotorPowers calculateRightModule(Eigen::Vector2d target_velocity, double rotation_velocity);

    MotorPowers calculateRearModule(Eigen::Vector2d target_velocity, double rotation_velocity);
};