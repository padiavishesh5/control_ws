#include <gtest/gtest.h>
#include "dxl_test/xl330_driver.hpp"

// These exercise only the pure conversion math on XL330Driver -- no port is
// opened and no packets are sent, so this runs fine with no motor attached.

TEST(XL330Conversions, ZeroRadianMapsToCenterTick)
{
  EXPECT_EQ(XL330Driver::radianToDxlPosition(0.0), 2048);
}

TEST(XL330Conversions, CenterTickIsZeroRadian)
{
  EXPECT_NEAR(XL330Driver::dxlPositionToRadian(2048), 0.0, 1e-9);
}

TEST(XL330Conversions, PositionRoundTrip)
{
  double original = 1.2;
  int ticks = XL330Driver::radianToDxlPosition(original);
  double back = XL330Driver::dxlPositionToRadian(ticks);
  EXPECT_NEAR(back, original, 2e-3);
}

TEST(XL330Conversions, NegativePositionRoundTrip)
{
  double original = -1.57;
  int ticks = XL330Driver::radianToDxlPosition(original);
  double back = XL330Driver::dxlPositionToRadian(ticks);
  EXPECT_NEAR(back, original, 2e-3);
}

TEST(XL330Conversions, ZeroVelocityMapsToZero)
{
  EXPECT_EQ(XL330Driver::radianPerSecToDxlVelocity(0.0), 0);
}

TEST(XL330Conversions, VelocityRoundTrip)
{
  double original = 3.14159;
  int dxl_vel = XL330Driver::radianPerSecToDxlVelocity(original);
  double back = XL330Driver::dxlVelocityToRadianPerSec(dxl_vel);
  EXPECT_NEAR(back, original, 1e-2);
}

TEST(XL330Conversions, NegativeVelocityRoundTrip)
{
  double original = -2.0;
  int dxl_vel = XL330Driver::radianPerSecToDxlVelocity(original);
  double back = XL330Driver::dxlVelocityToRadianPerSec(dxl_vel);
  EXPECT_NEAR(back, original, 1e-2);
}

int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
