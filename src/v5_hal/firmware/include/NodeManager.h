#pragma once

#include <vector>

#include "api.h"
#include "ros_lib/ros.h"

class Node;

// The NodeManager class handles multiple things:
// 1) What nodes need to be called
// 2) When each node needs to be called
//
// Nodes are automatically added to the manager on creation as long as they
// inherit from the Node class below. This means you never should be calling
// addNode() explicitly!
class NodeManager {
private:
    struct NodeStructure {
        Node* node;
        uint32_t triggerMillis;
        uint32_t lastExecutedMillis;
    };

    std::vector<NodeStructure> m_nodeStructures;

    uint32_t(*m_getMillis)(void);

    const uint32_t m_delayTimeMillis = 5;

protected:
    ros::NodeHandle* m_handle;

public:
    NodeManager(uint32_t(*getMilliseconds)(void));

    ros::NodeHandle* addNode(Node* node, uint32_t intervalMilliseconds);

    void initialize();

    void execute();

    ~NodeManager();
};

// The Node class is the parent object of all Nodes on the robot. It outlines
// what a node should have, and gives us a common interface on how to interact
// with nodes.
//
// The constructor of the node object takes in a pointer to the node manager,
// which AUTOMATICALLY ADDS IT to the manager on creation. This means that you
// don't need to add nodes on your own!
//
// The interval at which a node is called is set within the Node's CPP file, in
// the superclass constructor (should look like :Node([manager], [time]))
class Node {
protected:
    ros::NodeHandle* m_handle;

public:
    Node(NodeManager* nodeManager, uint32_t intervalMilliseconds) {
        m_handle = nodeManager->addNode(this, intervalMilliseconds);
    }
    virtual ~Node() {}
    virtual void initialize() {}
    virtual void periodic() = 0;
};