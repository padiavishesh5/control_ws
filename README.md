# control_ws

ROS 2 workspace implementing hardware control for a differential-drive mobile robot using **ros2_control**.

## Packages
- **my_robot_hardware**: custom ros2_control hardware interface (pluginlib) for a mobile base, with a Dynamixel XL330 driver and odometry math header.
- **my_robot_description**: URDF/Xacro robot model, including the ros2_control hardware description, plus RViz config.
- **my_robot_bringup**: controller configuration (YAML) and launch files (Python and XML) to bring up the robot.
- **dxl_test**: standalone XL330 driver test utility for motor bring-up.

## Testing
Unit tests written with **GoogleTest (gtest)**:
- XL330 unit conversions (`test_xl330_conversions.cpp`)
- Odometry math (`test_odometry_math.cpp`)

Run with:
    colcon build && colcon test && colcon test-result --verbose

## Tech
ROS 2 Jazzy, ros2_control, C++, pluginlib, Xacro/URDF, GoogleTest, Dynamixel XL330
