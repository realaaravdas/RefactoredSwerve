#include "subsystems/DriveSubsystem.h"
#include "Constants.h"

// Tuner X Generated Constants (Assumed header availability)
#include "TunerConstants.h"

#include <pathplanner/lib/auto/AutoBuilder.h>
#include <pathplanner/lib/config/PIDConstants.h>
#include <pathplanner/lib/config/RobotConfig.h>
#include <pathplanner/lib/controllers/PPHolonomicDriveController.h>
#include <frc/DriverStation.h>

namespace frc2025 {

DriveSubsystem::DriveSubsystem(RobotState& robotState)
    : m_robotState(robotState),
      m_drivetrain(TunerConstants::CreateDrivetrain())
{
    ConfigurePathPlanner();
}

void DriveSubsystem::Periodic() {
    // 1. Read Inputs (Encoders, Gyro) - handled by CTRE internally

    // 2. Update Odometry
    auto pose = m_drivetrain.GetState().Pose;
    m_robotState.addOdometryMeasurement(frc::Timer::GetFPGATimestamp(), pose);

    // 3. Log Data (AdvantageKit / WPILib)
}


void DriveSubsystem::ResetOdometry(const frc::Pose2d& pose) {
    m_drivetrain.ResetPose(pose);
}

void DriveSubsystem::ConfigurePathPlanner() {
    using namespace pathplanner;

    // Load RobotConfig (from GUI settings or manual)
    // RobotConfig config = RobotConfig::fromGUISettings();

    // AutoBuilder::configure(
    //     [this]() { return m_robotState.getLatestFieldToRobot(); },
    //     [this](frc::Pose2d pose) { ResetOdometry(pose); },
    //     [this]() { return m_robotState.getLatestRobotRelativeChassisSpeed(); },
    //     [this](frc::ChassisSpeeds speeds) {
    //         // Drive using speeds
    //         // SetControl(driveRequest.WithSpeeds(speeds));
    //     },
    //     std::make_shared<PPHolonomicDriveController>(
    //         PIDConstants(Constants::AutoConstants::kPLTEController, 0.0, 0.0), // Translation PID
    //         PIDConstants(Constants::AutoConstants::kPThetaController, 0.0, 0.0) // Rotation PID
    //     ),
    //     config,
    //     [this]() {
    //         // Should flip path?
    //         return m_robotState.isRedAlliance();
    //     },
    //     this
    // );
}

frc2::CommandPtr DriveSubsystem::ApplyRequest(std::function<ctre::phoenix6::swerve::requests::SwerveRequest*()> requestSupplier) {
    return Run([this, requestSupplier] {
        SetControl(*requestSupplier());
    });
}

} // namespace frc2025
