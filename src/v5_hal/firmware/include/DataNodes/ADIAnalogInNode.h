#pragma once

#include "NodeManager.h"
#include "api.h"
#include "ros_lib/ros.h"
#include "ros_lib/std_msgs/Int16.h"

class ADIAnalogInNode : public Node {
private:
    pros::ADIAnalogIn m_analog_in;
    std_msgs::Int16 m_analog_in_msg;
    std::string m_handle_name;
    ros::Publisher* m_publisher;

    void m_populateMessage();

public:
    ADIAnalogInNode(NodeManager* node_manager, int port,
        std::string handle_name);

    void initialize();

    void periodic();

    ~ADIAnalogInNode();
};
