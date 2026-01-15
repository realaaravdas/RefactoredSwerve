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

namespace Constants {
    using namespace units::literals;

    // Helper for Tuner constants
    // You should define these yourself or generate them using Tuner X
    namespace TunerConstants {
        // Placeholder for generated Tuner constants
        // In a real scenario, you would include the generated header
    }

    constexpr float PI = 3.14159265359;
    constexpr float PI_2 = 1.570796326;

    constexpr bool kIsReplay = false;
    constexpr bool kIsPracticeBot = false; // Implement MAC address check if needed

    constexpr double kSteerJoystickDeadband = 0.05;
    constexpr auto kRobotWidth = 35.625_in;
    constexpr auto kRobotDiagonal = kRobotWidth * std::numbers::sqrt2;
    constexpr auto kRobotMass = 40.0_lb;
    constexpr auto kRobotMomentOfInertia = 2.0 * 9.38 * 1_kg * 1_sq_m; // Verify units
    constexpr auto kCOGHeight = 0.0_in;

    namespace DriveConstants {
        // CUSTOM GYRO: If you are using a different gyro, you might need to adjust these or where they are used.
        constexpr auto kDriveMaxSpeed = 5.2_mps;
        constexpr auto kMaxAcceleration = 8.0_mps_sq;
        constexpr auto kMaxXAcceleration = 8.0_mps_sq;
        constexpr auto kMaxYAcceleration = 8.0_mps_sq;
        constexpr auto kDriveMaxAngularRate = 2.0_rad_per_s;
        constexpr auto kMaxAngularSpeedSquared = 12.0_rad_per_s_sq; // Change later, I have no idea

        constexpr double kHeadingControllerP = 0.04; // Change accordingly
        constexpr double kHeadingControllerI = 0.0;
        constexpr double kHeadingControllerD = 0.01;

        constexpr double kWheelCoefficientOfFriction = 1.0;

        // Standard Deviations for Odometry
        constexpr double kDisabledDriveXStdDev = 1.0;
        constexpr double kDisabledDriveYStdDev = 1.0;
        constexpr double kDisabledDriveRotStdDev = 1.0;

        constexpr double kEnabledDriveXStdDev = 0.3;
        constexpr double kEnabledDriveYStdDev = 0.3;
        constexpr double kEnabledDriveRotStdDev = 0.2;

        constexpr auto kDrivePitchThreshold = 10.0_deg; // No Clue
        constexpr auto kDriveRollThreshold = 10.0_deg; // No Clue
    }

    constexpr double kJoystickThreshold = 0.1;
    constexpr int kDriveGamepadPort = 0; // PS5 Controller Port

    namespace AutoConstants {
        constexpr auto kMaxSpeed = 5.2_mps;
        constexpr auto kMaxAcceleration = 8_mps_sq;
        constexpr auto kMaxAngularSpeed = 5_rad_per_s;
        constexpr auto kMaxAngularAcceleration = 15.0447382_rad_per_s_sq;

        constexpr double kPXYController = 5.0; // No Cluee
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
