# Gas Leakage Detection and Control System
This project is an automated gas leakage detection and control system using an MQ-5 gas sensor, a servo motor to control the gas valve, a fan for ventilation, and a buzzer for audible alerts. The system monitors gas levels and reacts to ensure safety by closing the gas valve, turning on an exhaust fan, and beeping the buzzer when gas is detected.

![Project](https://github.com/user-attachments/assets/67382ce2-d27e-4be1-8fdc-39e50e0e19ac)


## Table of Contents
- [Features](#features)
- [Components](#components)
- [Circuit Diagram](#circuit-diagram)
- [Pin Configuration](#pin-configuration)
- [How It Works](#how-it-works)
- [Installation](#installation)
- [Usage](#usage)
- [Future Scope](#future-scope)
- [License](#license)

## Features
- **Gas Detection**: Uses the MQ-5 gas sensor to detect dangerous levels of gases.
- **Automated Response**: Closes a gas valve automatically via a servo motor when gas is detected.
- **Audible Alert**: Activates a buzzer to provide an audible alert in "beep-beep" mode for 5 seconds when gas levels exceed the threshold.
- **Ventilation System**: Turns on a fan to ventilate the area in case of gas leakage.
- **Safety Mechanism**: Gas valve automatically opens again when gas levels return to normal.

## Components
- **Arduino Uno** (or any compatible microcontroller)
- **MQ-5 Gas Sensor**
- **Servo Motor** (to control gas valve)
- **Buzzer**
- **Exhaust Fan** (controlled via MOSFET)
- **Jumper wires**
- **Breadboard** (optional)

## Circuit Diagram
Here is the circuit configuration for the project:
- **MQ-5 Gas Sensor**: Connect the analog output to pin `A0` on the Arduino.
- **Servo Motor**: Connect the signal wire to pin `9` on the Arduino.
- **Buzzer**: Connect the positive leg to pin `8` on the Arduino.
- **Fan**: Connect the control wire via MOSFET to pin `10` on the Arduino.

Ensure to power the sensor, motor, and fan as required.

## Pin Configuration
| Component      | Pin  | Description                     |
| -------------- | ---- | ------------------------------- |
| MQ-5 Gas Sensor| A0   | Reads gas concentration         |
| Servo Motor    | 9    | Controls gas valve              |
| Buzzer         | 8    | Provides an audible alert       |
| Fan            | 10   | Activates fan for ventilation   |

## How It Works
1. **Gas Detection**: The MQ-5 sensor reads the gas concentration level. If the concentration exceeds a certain threshold (default: 600), it triggers the system.
2. **Servo Activation**: The servo motor closes the gas valve (set to 0°) to stop gas flow.
3. **Fan Activation**: The exhaust fan is turned on to ventilate the area.
4. **Buzzer Beeping**: The buzzer beeps every 1 second for 5 seconds and then shuts off after a total duration of 15 seconds.
5. **Gas Normalization**: If gas levels return to normal (below the threshold), the system reopens the valve (servo back to 90°), turns off the fan, and resets.

## Installation
1. Clone or download the project from this repository.
2. Install the **Servo** library if not already installed. You can do this in the Arduino IDE by navigating to `Sketch > Include Library > Manage Libraries` and searching for "Servo".
3. Connect the components as per the circuit diagram.

## Usage
1. Upload the provided code to your Arduino board.
2. Power the system and open the Serial Monitor to see gas level readings and system actions.
3. Once the system detects gas levels above the threshold, it will automatically:
   - Close the gas valve.
   - Start the exhaust fan.
   - Beep the buzzer every second for 5 seconds and turn it off after a total of 15 seconds.
   - Once gas levels normalize, the gas valve will reopen, and the fan will turn off.

## Future Scope
Here are a few ideas for future development to enhance this project:
1. **IoT Integration**: Connect the system to the cloud to send real-time alerts and logs to a mobile app or dashboard.
2. **Mobile Notifications**: Integrate SMS or mobile notifications using services like Twilio to alert users when gas leakage is detected.
3. **Automatic Shutdown**: Include additional safety mechanisms like shutting off the main power supply in case of gas detection.
4. **Battery Backup**: Add a backup battery to ensure the system works even in case of power failure.
5. **Multi-gas Detection**: Expand the system to detect multiple types of hazardous gases (e.g., MQ-6 for LPG and MQ-7 for carbon monoxide).
6. **Calibrating Gas Levels**: Improve the accuracy of the gas sensor by implementing calibration functions for various environments.
