#pragma once

#include <memory>
#include <functional>
#include <frc2/command/SubsystemBase.h>
#include <frc2/command/Command.h>
#include <frc/geometry/Pose2d.h>
#include <frc/kinematics/ChassisSpeeds.h>
#include <frc/Timer.h>
#include <ctre/phoenix6/swerve/SwerveDrivetrain.hpp>

#include "RobotState.h"
#include "Constants.h"

// PathPlanner Includes
#include <pathplanner/lib/config/RobotConfig.h>
#include <pathplanner/lib/controllers/PPHolonomicDriveController.h>
#include <pathplanner/lib/trajectory/PathPlannerTrajectory.h>

namespace frc2025 {

class DriveSubsystem : public frc2::SubsystemBase {
public:
    DriveSubsystem(RobotState& robotState);

    void Periodic() override;

    // Control Methods
    template <typename T>
    void SetControl(T&& request) {
        m_drivetrain.SetControl(std::forward<T>(request));
    }

    void ResetOdometry(const frc::Pose2d& pose);

    // PathPlanner Configuration
    void ConfigurePathPlanner();

    // Accessors
    // Add getModules if needed (custom modules)
    // Helper to access drivetrain
    ctre::phoenix6::swerve::SwerveDrivetrain<ctre::phoenix6::hardware::TalonFX, ctre::phoenix6::hardware::TalonFX, ctre::phoenix6::hardware::CANcoder>& GetDrivetrain() { return m_drivetrain; }

    // For command factories
    frc2::CommandPtr ApplyRequest(std::function<ctre::phoenix6::swerve::requests::SwerveRequest*()> requestSupplier);

private:
    RobotState& m_robotState;

    // CUSTOM MODULES: Define your modules here.
    // Example using CTRE SwerveDrivetrain (Tuner X generated)
    ctre::phoenix6::swerve::SwerveDrivetrain<ctre::phoenix6::hardware::TalonFX, ctre::phoenix6::hardware::TalonFX, ctre::phoenix6::hardware::CANcoder> m_drivetrain;

    // Simulation Support
    // ...

    // PathPlanner Controller
    // std::unique_ptr<pathplanner::PPHolonomicDriveController> m_pathFollowingController;
};

} // namespace frc2025
