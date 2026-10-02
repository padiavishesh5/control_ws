#include <gtest/gtest.h>
#include "my_robot_hardware/odometry_math.hpp"

using mobile_base_hardware::apply_velocity_deadband;
using mobile_base_hardware::update_wheel_state;

// These exercise only the pure math pulled out of
// MobileBaseHardwareInterface::read() -- no ROS2 node, no driver, no
// hardware needed.

TEST(OdometryMath, DeadbandZeroesTinyVelocity)
{
  EXPECT_DOUBLE_EQ(apply_velocity_deadband(0.02), 0.0);
  EXPECT_DOUBLE_EQ(apply_velocity_deadband(-0.02), 0.0);
}

TEST(OdometryMath, DeadbandPassesRealVelocity)
{
  EXPECT_DOUBLE_EQ(apply_velocity_deadband(0.5), 0.5);
  EXPECT_DOUBLE_EQ(apply_velocity_deadband(-1.2), -1.2);
}

TEST(OdometryMath, DeadbandBoundaryIsExclusive)
{
  // threshold check is strictly "<", so exactly-at-threshold should pass through
  EXPECT_DOUBLE_EQ(apply_velocity_deadband(0.03), 0.03);
}

TEST(OdometryMath, StoppedWheelDoesNotDriftPosition)
{
  auto state = update_wheel_state(/*raw_velocity=*/0.01, /*previous_position=*/1.0, /*period_seconds=*/0.02);
  EXPECT_DOUBLE_EQ(state.velocity, 0.0);
  EXPECT_DOUBLE_EQ(state.position, 1.0);
}

TEST(OdometryMath, MovingWheelIntegratesPositionForward)
{
  auto state = update_wheel_state(/*raw_velocity=*/1.0, /*previous_position=*/0.0, /*period_seconds=*/0.1);
  EXPECT_DOUBLE_EQ(state.velocity, 1.0);
  EXPECT_NEAR(state.position, 0.1, 1e-9);
}

TEST(OdometryMath, NegativeVelocityIntegratesPositionBackward)
{
  // Confirms the already-sign-flipped right-wheel velocity integrates correctly.
  auto state = update_wheel_state(/*raw_velocity=*/-2.0, /*previous_position=*/5.0, /*period_seconds=*/0.5);
  EXPECT_DOUBLE_EQ(state.velocity, -2.0);
  EXPECT_NEAR(state.position, 4.0, 1e-9);
}

int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
