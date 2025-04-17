# Smart Coffee Machine

## Overview

Smart Coffee Machine is an embedded system that emulates the functionality of an intelligent coffee machine. The project implements a task-based architecture modeled through synchronous finite state machines, allowing for modular design and implementation.

## System Architecture

The Smart Coffee Machine system consists of:

1. **Hardware Components**
   - Arduino microcontroller board
   - LCD display (connected via I2C)
   - PIR motion sensor
   - Sonar distance sensor
   - Servo motor (simulates beverage preparation)
   - Potentiometer
   - Three selection/confirmation buttons
   - TMP36 temperature sensor

2. **Software Components**
   - Arduino program (embedded system)
   - Java application for serial communication and remote management

## Usage

### Coffee Machine Operation
1. The machine starts in boot mode and transitions to ready state
2. When a user approaches (detected by sensors), the machine wakes up if in sleep mode
3. User can select a beverage (coffee, tea, or hot chocolate) using the selection buttons
4. User can adjust sugar level using the potentiometer
5. The machine simulates beverage preparation using the servo motor
6. The LCD displays the current status and instructions throughout the process

### Java Application Features
The Coffee Machine Manager application allows:
- Monitoring the current state of the machine
- Triggering assistance mode remotely
- Viewing system diagnostics and self-test results

## System States

- **Boot**: Initialization state
- **Ready**: Awaiting user input
- **Operating**: Preparing a beverage
- **Sleep**: Power-saving mode when no users are detected
- **Assistance**: Maintenance mode
- **Testing**: Self-diagnostic mode

## Troubleshooting

- If the machine enters assistance mode, check the Java application for specific error information
- Temperature out of bounds will trigger an assistance request
- Periodic self-tests help identify potential issues before they affect operation

## Future Improvements

- Network connectivity for remote monitoring
- User profiles and preferences
- Consumption statistics and analytics
- Integration with smart home systems

## Course Information

This project was developed for the "Embedded Systems and IoT" course.
