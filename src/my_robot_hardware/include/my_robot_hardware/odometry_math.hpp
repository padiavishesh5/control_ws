#ifndef MY_ROBOT_HARDWARE_ODOMETRY_MATH_HPP
#define MY_ROBOT_HARDWARE_ODOMETRY_MATH_HPP

#include <cmath>

namespace mobile_base_hardware {

constexpr double kVelocityDeadband = 0.03;

// Zeroes out velocity readings below the noise-floor threshold.
// NOTE: the original code called bare `abs()` on a double, which on some
// platforms/includes resolves to the integer <cstdlib> overload and silently
// truncates the argument to 0 before comparing -- i.e. it can zero out real
// velocities, not just noise. Using std::abs() here removes that ambiguity.
inline double apply_velocity_deadband(double velocity, double threshold = kVelocityDeadband)
{
    return (std::abs(velocity) < threshold) ? 0.0 : velocity;
}

struct WheelState {
    double velocity;
    double position;
};

// Applies the deadband to a raw (already sign-corrected) velocity reading and
// integrates position forward by one control period. Mirrors the per-wheel
// logic in MobileBaseHardwareInterface::read().
inline WheelState update_wheel_state(
    double raw_velocity,
    double previous_position,
    double period_seconds,
    double threshold = kVelocityDeadband)
{
    double velocity = apply_velocity_deadband(raw_velocity, threshold);
    double position = previous_position + velocity * period_seconds;
    return WheelState{velocity, position};
}

} // namespace mobile_base_hardware

#endif
