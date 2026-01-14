#pragma once

#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/geometry/Twist2d.h>
#include <frc/kinematics/ChassisSpeeds.h>
#include <frc/DriverStation.h>
#include <units/time.h>
#include <units/velocity.h>
#include <units/acceleration.h>
#include <units/angular_velocity.h>
#include <optional>
#include <functional>

#include "subsystems/VisionFieldPoseEstimate.h"

using namespace units::literals;

class RobotState {
public:
    RobotState();

    void addOdometryMeasurement(units::second_t timestamp, const frc::Pose2d& pose);
    void addDriveMotionMeasurements(
        units::second_t timestamp,
        units::radians_per_second_t rollVel,
        units::radians_per_second_t pitchVel,
        units::radians_per_second_t yawVel,
        units::radian_t pitch,
        units::radian_t roll,
        units::meters_per_second_squared_t accelX,
        units::meters_per_second_squared_t accelY,
        const frc::ChassisSpeeds& measuredSpeeds,
        const frc::ChassisSpeeds& measuredFieldRelativeSpeeds
    );

    frc::Pose2d getLatestFieldToRobot() const;
    frc::ChassisSpeeds getLatestRobotRelativeChassisSpeed() const;
    frc::ChassisSpeeds getLatestFieldRelativeChassisSpeed() const;

    frc::Pose2d getPredictedFieldToRobot(units::second_t lookaheadTime) const;

    // void updateMegatagEstimate(const VisionFieldPoseEstimate& estimate);

    bool isRedAlliance() const;

    void setTrajectoryTargetPose(const frc::Pose2d& pose);
    std::optional<frc::Pose2d> getTrajectoryTargetPose() const;

    void setTrajectoryCurrentPose(const frc::Pose2d& pose);
    std::optional<frc::Pose2d> getTrajectoryCurrentPose() const;

private:
    frc::Pose2d m_fieldToRobot;
    frc::ChassisSpeeds m_measuredRobotRelativeSpeeds;
    frc::ChassisSpeeds m_measuredFieldRelativeSpeeds;

    std::optional<frc::Pose2d> m_trajectoryTargetPose;
    std::optional<frc::Pose2d> m_trajectoryCurrentPose;

    // Add buffers/history if needed for latency compensation (removed for simplicity in this port)
};
