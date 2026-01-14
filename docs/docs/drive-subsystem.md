---
sidebar_position: 4
---

# Drive Subsystem API

## `frc2025::DriveSubsystem`

The main interface for the drivetrain.

### `SetControl(const ctre::phoenix6::swerve::SwerveRequest& request)`

Sends a control request to the drivetrain. This is the primary way to drive the robot.

**Common Requests:**
*   `FieldCentric`: Standard field-relative driving.
*   `RobotCentric`: Robot-relative driving.
*   `SwerveDriveBrake`: Locks wheels in an X pattern.
*   `FieldCentricFacingAngle`: Drives field-relative while targeting a specific heading.

### `ResetOdometry(const frc::Pose2d& pose)`

Resets the robot's estimated pose on the field.
*   **Usage**: Call this when you want to "zero" the field position, or when initializing auto.
*   **Gyro**: This effectively resets the gyro offset relative to the field.

### `ApplyRequest(std::function<ctre::phoenix6::swerve::SwerveRequest*()> requestSupplier)`

Creates a command that continuously applies a swerve request. Useful for binding to joystick triggers or buttons.

---

## `frc2025::RobotState`

Handles state estimation.

### `getLatestFieldToRobot()`

Returns the current estimated `Pose2d` of the robot.

### `getPredictedFieldToRobot(units::second_t lookaheadTime)`

Returns where the robot will be in `lookaheadTime` seconds, assuming constant velocity. Useful for compensating for latency in vision or shooting calculations.
