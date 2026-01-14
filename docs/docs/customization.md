---
sidebar_position: 3
---

# Customization

This codebase is designed to be adapted to your specific robot hardware.

## 1. Tuner X Constants

The most important step is to generate your swerve constants using **CTRE Tuner X**.

1.  Open Tuner X and connect to your robot.
2.  Use the Swerve Generator to configure your modules, CAN IDs, offsets, and physical properties.
3.  Generate the code for **C++**.
4.  Copy the generated `TunerConstants.h` file into `src/main/include/frc2025/generated/`.
5.  Update `src/main/include/frc2025/subsystems/drive/DriveSubsystem.h` to use your specific drivetrain type if it differs from the default `SwerveDrivetrain<4>`.

## 2. Robot Constants

Edit `src/main/include/frc2025/Constants.h` to match your physical robot:

*   **Robot Dimensions**: `kRobotWidth`, `kRobotLength`.
*   **Drive Constraints**: `kDriveMaxSpeed`, `kMaxAcceleration`.
*   **Controller Ports**: `kDriveGamepadPort` (Defaults to 0).

## 3. Custom Gyro

If you are NOT using a Pigeon 2 attached to the CANivore as configured in Tuner X:

1.  Modify `TunerConstants.h` (or your generated file) to not include the Pigeon 2 config if possible, or ignore it.
2.  In `DriveSubsystem.cpp`, inside `Periodic()`, manually update the odometry with your gyro's heading if the CTRE `SwerveDrivetrain` class doesn't support your specific gyro directly (it is tightly coupled with Pigeon 2 for best performance).
    *   *Note: Using a non-CTRE gyro with the `SwerveDrivetrain` helper class is difficult. It is highly recommended to use a Pigeon 2.*

## 4. Custom Modules

If you are using custom swerve modules (not supported by Tuner X directly or custom mechanics):

1.  You may need to write your own `SwerveModule` class or adapt the `DriveSubsystem` to not use the `ctre::phoenix6::swerve::SwerveDrivetrain` helper.
2.  Look for `CUSTOM MODULES` comments in `DriveSubsystem.h`.

## 5. Input Bindings

Edit `ConfigureBindings()` in `src/main/cpp/frc2025/Main.cpp` to change button mappings.
*   Default: PS5 Controller
    *   Left Stick: Strafe
    *   Right Stick: Rotate
    *   Start/Options: Reset Gyro
    *   Cross/A: Rotate to 0 degrees
