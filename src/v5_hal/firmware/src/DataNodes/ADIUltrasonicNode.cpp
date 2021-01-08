#include "DataNodes/ADIUltrasonicNode.h"

// By default, this constructor calls the constructor for the Node object in NodeManager.h
ADIUltrasonicNode::ADIUltrasonicNode(NodeManager* nodeManager, int port_ping, int port_echo, 
 std::string handleName):Node(nodeManager, 200) {
    m_ultrasonic = new pros::ADIUltrasonic(port_ping, port_echo);
    m_ultrasonic_msg = new v5_hal::ADIUltrasonicData();
    m_handle = new ros::NodeHandle();
    m_handle_name = handleName;
}

void ADIUltrasonicNode::initialize() {
    // Define a string handle for the ultrasonic sensor
    std::string ultrasonic_handle = "Ultrasonic_" + m_handle_name;

    // Create a publisher with the custom title, and message location
    m_publisher = new ros::Publisher(ultrasonic_handle.c_str(), m_ultrasonic_msg);
    
    // Initialize the handler, and set up data relating to what this node publishes
    m_handle->initNode();
    m_handle->advertise(*m_publisher);
}

void ADIUltrasonicNode::periodic() {
    populateUltrasonicMsg();
    m_publisher->publish(m_ultrasonic_msg);

    m_handle->spinOnce();
}

void ADIUltrasonicNode::populateUltrasonicMsg() {
    m_ultrasonic_msg->distance = m_ultrasonic->get_value();
}

ADIUltrasonicNode::~ADIUltrasonicNode() {
    delete m_ultrasonic;
    delete m_ultrasonic_msg;
    delete m_handle;
}