#pragma once

#include "NodeManager.h"
#include "api.h"
#include "ros_lib/ros.h"
#include "ros_lib/v5_hal/V5RotationSensor.h"

class RotationSensorNode : public Node {
private:
    pros::Rotation m_rotation_sensor;
    v5_hal::V5RotationSensor m_rotation_msg;
    std::string m_handle_name;
    ros::Publisher* m_publisher;

    void m_populateMessage();

public:
    RotationSensorNode(NodeManager* node_manager, int rotation_port, 
        std::string handle_name);
    
    void initialize();

    int getAngle();

    int getPosition();

    int getVelocity();
    
    void periodic();
    
    ~RotationSensorNode();
};