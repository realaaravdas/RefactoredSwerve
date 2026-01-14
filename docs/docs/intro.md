---
sidebar_position: 1
---

# Introduction

This repository contains a stripped-down, high-performance Swerve Drivebase implementation for FRC 2025, ported to C++ from Team 254's Java codebase.

## Features

*   **WPILib C++ 2025 Support**: Built for the latest FRC season.
*   **CTRE Phoenix 6 Integration**: Uses the latest Swerve API from CTRE (Tuner X compatible).
*   **PathPlanner Support**: Integrated PathPlanner for autonomous path following.
*   **Robot State Tracking**: Robust state estimation and odometry.
*   **PS5 Controller Support**: Pre-configured bindings for PS5 controllers.

## Architecture

The project is structured to be minimal but extensible:
*   `frc2025::DriveSubsystem`: The core subsystem managing the swerve drivetrain.
*   `frc2025::RobotState`: Centralized state management for odometry and vision (if added).
*   `frc2025::Constants`: centralized configuration.
