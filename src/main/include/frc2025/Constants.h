#pragma once

#include <numbers>
#include <string>

#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/geometry/Transform2d.h>
#include <frc/geometry/Translation2d.h>
#include <frc/trajectory/TrapezoidProfile.h>
#include <units/acceleration.h>
#include <units/angle.h>
#include <units/angular_acceleration.h>
#include <units/angular_velocity.h>
#include <units/length.h>
#include <units/mass.h>
#include <units/moment_of_inertia.h>
#include <units/velocity.h>

#include "ctre/phoenix6/configs/Configs.hpp"

namespace frc2025 {

namespace Constants {
    using namespace units::literals;

    // Helper for Tuner constants
    // You should define these yourself or generate them using Tuner X
    namespace TunerConstants {
        // Placeholder for generated Tuner constants
        // In a real scenario, you would include the generated header
    }

    constexpr bool kIsReplay = false;
    constexpr bool kIsPracticeBot = false; // Implement MAC address check if needed

    constexpr double kSteerJoystickDeadband = 0.05;
    constexpr auto kRobotWidth = 35.625_in;
    constexpr auto kRobotDiagonal = kRobotWidth * std::numbers::sqrt2;
    constexpr auto kRobotMass = 147.92_lb;
    constexpr auto kRobotMomentOfInertia = 2.0 * 9.38 * 1_kg * 1_sq_m; // Verify units
    constexpr auto kCOGHeight = 0.0_in;

    namespace DriveConstants {
        // CUSTOM GYRO: If you are using a different gyro, you might need to adjust these or where they are used.
        constexpr auto kDriveMaxSpeed = 3.6_mps;
        constexpr auto kMaxAcceleration = 10.0_mps_sq;
        constexpr auto kMaxXAcceleration = 10.0_mps_sq;
        constexpr auto kMaxYAcceleration = 10.0_mps_sq;
        constexpr auto kDriveMaxAngularRate = 8.2_rad_per_s;
        constexpr auto kMaxAngularSpeedSquared = 20.0_rad_per_s_sq;

        constexpr double kHeadingControllerP = 5.0;
        constexpr double kHeadingControllerI = 0.0;
        constexpr double kHeadingControllerD = 0.0;

        constexpr double kWheelCoefficientOfFriction = 1.0;

        // Standard Deviations for Odometry
        constexpr double kDisabledDriveXStdDev = 1.0;
        constexpr double kDisabledDriveYStdDev = 1.0;
        constexpr double kDisabledDriveRotStdDev = 1.0;

        constexpr double kEnabledDriveXStdDev = 0.3;
        constexpr double kEnabledDriveYStdDev = 0.3;
        constexpr double kEnabledDriveRotStdDev = 0.2;

        constexpr auto kDrivePitchThreshold = 10.0_deg;
        constexpr auto kDriveRollThreshold = 10.0_deg;
    }

    constexpr double kJoystickThreshold = 0.1;
    constexpr int kDriveGamepadPort = 0; // PS5 Controller Port

    namespace AutoConstants {
        constexpr auto kMaxSpeed = 3.6_mps;
        constexpr auto kMaxAcceleration = 1.74_mps_sq;
        constexpr auto kMaxAngularSpeed = 6.5_rad_per_s;
        constexpr auto kMaxAngularAcceleration = 31.538_rad_per_s_sq;

        constexpr double kPXYController = 5.0;
        constexpr double kPLTEController = 3.0;
        constexpr double kPCTEController = 6.0;
        constexpr double kPThetaController = 5.0;

        // Constraint for the motion profiled robot angle controller
        const frc::TrapezoidProfile<units::radians>::Constraints kThetaControllerConstraints{
            kMaxAngularSpeed, kMaxAngularAcceleration};
    }

    namespace VisionConstants {
        // Add Limelight / Vision constants here
        // Usually dependent on camera mounting
    }

} // namespace Constants
} // namespace frc2025
