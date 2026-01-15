#include "RobotState.h"
#include <frc/DriverStation.h>

using namespace units::literals;

RobotState::RobotState() : m_fieldToRobot{0_m, 0_m, 0_deg} {}

void RobotState::addOdometryMeasurement(units::second_t timestamp, const frc::Pose2d& pose) {
    m_fieldToRobot = pose;
}

void RobotState::addDriveMotionMeasurements(
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
) {
    m_measuredRobotRelativeSpeeds = measuredSpeeds;
    m_measuredFieldRelativeSpeeds = measuredFieldRelativeSpeeds;
    // Store other values if needed for logging
}

frc::Pose2d RobotState::getLatestFieldToRobot() const {
    return m_fieldToRobot;
}

frc::ChassisSpeeds RobotState::getLatestRobotRelativeChassisSpeed() const {
    return m_measuredRobotRelativeSpeeds;
}

frc::ChassisSpeeds RobotState::getLatestFieldRelativeChassisSpeed() const {
    return m_measuredFieldRelativeSpeeds;
}

frc::Pose2d RobotState::getPredictedFieldToRobot(units::second_t lookaheadTime) const {
    return m_fieldToRobot.Exp(
        frc::Twist2d{
            m_measuredRobotRelativeSpeeds.vx * lookaheadTime,
            m_measuredRobotRelativeSpeeds.vy * lookaheadTime,
            m_measuredRobotRelativeSpeeds.omega * lookaheadTime
        }
    );
}

// void RobotState::updateMegatagEstimate(const VisionFieldPoseEstimate& estimate) {
//     // Implement fusion logic or just pass to consumer if designed that way
// }

bool RobotState::isRedAlliance() const {
    if (frc::DriverStation::GetAlliance()) {
        return frc::DriverStation::GetAlliance().value() == frc::DriverStation::Alliance::kRed;
    }
    return false;
}

void RobotState::setTrajectoryTargetPose(const frc::Pose2d& pose) {
    m_trajectoryTargetPose = pose;
}

std::optional<frc::Pose2d> RobotState::getTrajectoryTargetPose() const {
    return m_trajectoryTargetPose;
}

void RobotState::setTrajectoryCurrentPose(const frc::Pose2d& pose) {
    m_trajectoryCurrentPose = pose;
}

std::optional<frc::Pose2d> RobotState::getTrajectoryCurrentPose() const {
    return m_trajectoryCurrentPose;
}