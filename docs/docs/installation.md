---
sidebar_position: 2
---

# Installation

## Prerequisites

*   **WPILib 2025**: Ensure you have the latest WPILib installed.
*   **CTRE Phoenix 6**: Install the Phoenix 6 Tuner X and libraries.
*   **PathPlanner**: Install the PathPlanner application and libraries.

## Setup

1.  **Clone the Repository**:
    ```bash
    git clone https://github.com/your-org/frc2025-swerve.git
    ```

2.  **Open in VS Code**:
    Open the project folder in VS Code with the WPILib extension installed.

3.  **Build**:
    Run the "Build Robot Code" task (Shift+F5 or via Command Palette).
    ```bash
    ./gradlew build
    ```

4.  **Deploy**:
    Connect to the robot and run "Deploy Robot Code".

## Vendor Dependencies

The project comes with the following vendor dependencies configured in `vendordeps/`:
*   `Phoenix6-frc2025-latest.json`
*   `PathplannerLib-2025.2.7.json`

If you need to update them, use the "Manage Vendor Libraries" command in VS Code.
