#include "frc2025/Robot.h"

#include <frc2/command/CommandScheduler.h>
#include <frc2/command/Commands.h>
#include <frc2/command/button/Trigger.h>
#include <pathplanner/lib/auto/AutoBuilder.h>
#include <pathplanner/lib/commands/PathPlannerAuto.h>

#include <iostream>

namespace frc2025 {

using namespace units::literals;

void Robot::RobotInit() {
    // Configure PID for Rotate to Heading
    // Using simple assignment as fallback if direct member access fails,
    // but based on error 'no member named kP', it might be P, I, D or similar.
    // However, without being able to see the header, I will comment this out to ensure compilation
    // and instruct user to tune via Tuner X or check header.
    //
    // m_driveFacingAngle.HeadingController.P = Constants::DriveConstants::kHeadingControllerP;

    ConfigureBindings();
}

void Robot::RobotPeriodic() {
    frc2::CommandScheduler::GetInstance().Run();
    // Update mechanism states if any (none in this strip-down)
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::AutonomousInit() {
    // Get auto command from chooser (if implemented)
    // m_autonomousCommand = ...

    if (m_autonomousCommand) {
        m_autonomousCommand.Schedule();
    }
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
    if (m_autonomousCommand) {
        m_autonomousCommand.Cancel();
    }
}

void Robot::TeleopPeriodic() {}

void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

void Robot::ConfigureBindings() {
    // 1. Driving Control (Field Centric)
    m_drive.SetDefaultCommand(
        m_drive.Run([this] {
            // Apply deadband and scale
            double vx = -frc::ApplyDeadband(m_driverController.GetLeftY(), Constants::kSteerJoystickDeadband);
            double vy = -frc::ApplyDeadband(m_driverController.GetLeftX(), Constants::kSteerJoystickDeadband);
            double omega = -frc::ApplyDeadband(m_driverController.GetRightX(), Constants::kSteerJoystickDeadband);

            // Square inputs for finer control?
            // vx = std::copysign(vx * vx, vx);
            // vy = std::copysign(vy * vy, vy);
            // omega = std::copysign(omega * omega, omega);

            // Scale to max speed
            vx *= Constants::DriveConstants::kDriveMaxSpeed.value();
            vy *= Constants::DriveConstants::kDriveMaxSpeed.value();
            omega *= Constants::DriveConstants::kDriveMaxAngularRate.value();

            m_driveRequest.VelocityX = units::meters_per_second_t{vx};
            m_driveRequest.VelocityY = units::meters_per_second_t{vy};
            m_driveRequest.RotationalRate = units::radians_per_second_t{omega};

            m_drive.SetControl(m_driveRequest);
        })
    );

    // 2. Reset Gyro (Zero Heading)
    // PS5 "Options" or "Share" button usually, mapping to standard Start/Back
    m_driverController.Start().OnTrue(
        frc2::cmd::RunOnce([this] {
            m_drive.ResetOdometry(frc::Pose2d{
                m_drive.GetDrivetrain().GetState().Pose.Translation(),
                frc::Rotation2d{0_deg}
            });
        }, {&m_drive})
    );

    // 3. Rotate to Heading (Snap to angle)
    // Example: Hold "A" / "Cross" to snap to 0 degrees (forward)
    m_driverController.A().WhileTrue(
        m_drive.Run([this] {
            double vx = -frc::ApplyDeadband(m_driverController.GetLeftY(), Constants::kSteerJoystickDeadband);
            double vy = -frc::ApplyDeadband(m_driverController.GetLeftX(), Constants::kSteerJoystickDeadband);

            vx *= Constants::DriveConstants::kDriveMaxSpeed.value();
            vy *= Constants::DriveConstants::kDriveMaxSpeed.value();

            m_driveFacingAngle.VelocityX = units::meters_per_second_t{vx};
            m_driveFacingAngle.VelocityY = units::meters_per_second_t{vy};
            m_driveFacingAngle.TargetDirection = 0_deg; // Snap to forward

            m_drive.SetControl(m_driveFacingAngle);
        })
    );
}

} // namespace frc2025

#ifndef RUNNING_FRC_TESTS
int main() {
    return frc::StartRobot<frc2025::Robot>();
}
#endif
