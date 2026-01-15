#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/Commands.h>
#include <frc2/command/button/CommandXboxController.h>
#include <frc2/command/button/CommandPS5Controller.h>

#include "Constants.h"
#include "RobotState.h"
#include "subsystems/DriveSubsystem.h"
#include "subsystems/vision/QuestNav.h"

// Tuner X includes (for requests)
#include <ctre/phoenix6/swerve/SwerveDrivetrain.hpp>

class Robot : public frc::TimedRobot {
public:
    void RobotInit() override;
    void RobotPeriodic() override;
    void DisabledInit() override;
    void DisabledPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void SimulationInit() override;
    void SimulationPeriodic() override;

private:
    // Subsystems
    RobotState m_robotState;
    DriveSubsystem m_drive{m_robotState};

    QuestNav questnav;

    // Controllers
    // PS5 Controller is usually detected as a GenericHID or XboxController in WPILib depending on driver
    // CommandXboxController works well for generic mapping usually, or use CommandPS5Controller
    frc2::CommandPS5Controller m_driverController{Constants::kDriveGamepadPort};

    // Swerve Requests
    ctre::phoenix6::swerve::requests::FieldCentric m_driveRequest;
    ctre::phoenix6::swerve::requests::SwerveDriveBrake m_brakeRequest;
    ctre::phoenix6::swerve::requests::FieldCentricFacingAngle m_driveFacingAngle;

    // Autonomous Command
    frc2::CommandPtr m_autonomousCommand{frc2::cmd::None()};

    void ConfigureBindings();
};
