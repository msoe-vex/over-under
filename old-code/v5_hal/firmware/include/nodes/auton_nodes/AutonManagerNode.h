#pragma once

#include "api.h"
#include "auton/auton_routines/TestPathAuton.h"
#include "auton/auton_routines/TestPoseAuton.h"
#include "auton/auton_routines/TestTurnAuton.h"
#include "nodes/NodeManager.h"
#include "nodes/odometry_nodes/OdometryNode.h"
#include "nodes/sensor_nodes/InertialSensorNode.h"
#include "nodes/subsystems/drivetrain_nodes/IDriveNode.h"
#include "pathing/PathManager.h"

class AutonManagerNode : public Node {
 private:
  Auton* m_test_path_auton;

 public:
  AutonManagerNode(
      NodeManager* node_manager, IDriveNode* drive_node,
      OdometryNode* odometry_node, InertialSensorNode* inertial_sensor_node);

  Auton* selected_auton;

  void initialize();

  void autonPeriodic();
};
