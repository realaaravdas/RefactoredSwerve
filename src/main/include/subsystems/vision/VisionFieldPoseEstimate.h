#pragma once

#include <units/time.h>
#include <frc/geometry/Pose2d.h>
#include <vector>

struct VisionFieldPoseEstimate {
    units::second_t timestamp;
    frc::Pose2d visionRobotPose;
    std::vector<double> stdDevs;

    units::second_t getTimestamp() const { return timestamp; }
    frc::Pose2d getVisionRobotPose() const { return visionRobotPose; }
};