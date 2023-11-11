#pragma once
//! functions associated with driver control
namespace DriverControl{
  ///@brief get the change in controller axes
  void getAxisChange();

  void switchDir();

  ///@brief adjust drivetrain motor velocities based off change in controller axes for an XDrive
  ///@param axis3 value of controller axis 3
  ///@param axis4 value of controller axis 4
  ///@param axis1 value of controller axis 1
  ///@param axis2 value of controller axis 2
  ///@param maxVelocityPer maximum motor velocity in percent
  void combineDriveAndSpinMotionXDrive(int axis3, int axis4, int axis1, int axis2, float maxVelocityPer);

  ///@brief compute relative motion based on orientation of robot relative to the field coordinate system
  ///@param axis3 value of controller axis 3
  ///@param axis4 value of controller axis 4
  ///@param axis1 value of controller axis 1
  ///@param axis2 value of controller axis 2
  ///@param maxVelocityPer maximum motor velocity in percent
  void computeRelativeMotion(int axis3, int axis4, int axis1, int axis2, float maxVelocityPer);

  ///@brief adjust drivetrain motor velocities based off change in controller axes for a Standard Drive
  ///@param axis3 value of controller axis 3
  ///@param axis4 value of controller axis 4
  ///@param axis1 value of controller axis 1
  ///@param axis2 value of controller axis 2
  ///@param maxVelocityPer maximum motor velocity in percent
  void combineDriveAndSpinMotionStandardDrive(int axis3, int axis4, int axis1, int axis2, float maxVelocityPer);
}