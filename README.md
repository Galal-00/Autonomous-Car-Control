# Autonomous Car Control System 🚗💨

## Overview

A communication and control system for an autonomous car prototype, enabling a PC to send control commands and receive real-time data updates. The objective is for the PC to control the car's speed, direction (forward or backward), and wheel angle through a UART communication interface. A dashboard in the form of an LCD Display shows the interpreted commands of the message and the current time.

#### MCU Connected Components
- DC Motor (represents speed) 🏎️
- Stepper and Servo Motors (represent Angle) 🔄
- LCD (represents dashboard) 📊
- Virtual Terminal (for communication) 💬

#### Description
1. **Current Time ⏰:**
   - MCU uses 8-bit Timer and GPIO to interface with LCD Display and display time in 'hh:mm:ss' format.
   - Time starts at 00:00:00 and is updated continuously using the Timer and interrupt controller.
   
2. **Speed and Angle Control 🎮:**
   - User types a message in the Virtual Terminal and presses Enter key to end the message.
   - MCU reads the message and checks that it complies with the used communication frame standard.
   - Speed and direction are interpreted from the message, and DC motor speed is set.
   - Angle and direction are interpreted from the message, and stepper and servo motors angles are set.
 
3. **Dashboard Display 📊:**
   - After the message is interpreted, The LCD Displays the current speed and angle.
   - The +/- sign represents forward/backward in case of speed, and right or left in case of angle.

### Communication Frame

The UART-PC communication frame follows this structure:
```
XXXAYYBE
```
1. **XXX:** Speed of the DC motor, controlling the wheels' speed (0 to 100) 🚦.
2. **A:** Direction of the DC motor, controlling the wheels' speed (F for forward, B for backward) ↕️.
3. **YY:** Angle of the stepper/servo motor, controlling the wheel angle (0 to 45) 🔄.
4. **B:** Direction of the stepper/servo motor (R for Right, L for Left), with the north of the car as the reference 🧭.
5. **E:** Indicator of the end of the frame 🛑.

### Examples
1. `076F18LE` - Change car speed to 76%, move forward, and tilt wheels 18 degrees to the left.
2. `76F18RE` - Valid frame but violates the agreed standard length.
3. `F100R09E` - Invalid frame (does not match the standard).
4. `076F18R` - Valid frame, missing 'E', considered as noise and ignored.

Invalid messages cause the MCU to send `INVALID MESSAGE` through the virtual terminal 🛑.

## Simulation Assumptions 🤖

1. DC motor:
   - ACW (Anti-Clockwise) represents forward movement ⬅️.
   - CW (Clockwise) represents backward movement ➡️.
2. Stepper motor:
   - Each step equals one degree 🔄.

## Dashboard Format 📊

The Dashboard follows this format:
```
Speed: ±X%, Direction ±Y
Time: hh:mm:ss
```
1. **X:** Speed of the DC motor (0 to 100) 🚦.
2. **Y:** Angle of the stepper/servo motor, controlling the wheel angle (0 to 45) 🔄.

## Implementation Details

- **Virtual Terminal Communication:** Receive and messages using UART and interrupts 📬.
- **DC Motor:** Uses GPIO for direction control, and PWM for speed control 🚦.
- **Stepper Motor:** Uses GPIO for angle control 🔄.
- **Servo Motor:** Uses PWM for angle control 🔄.
- **Dashboard Display:** Uses GPIO to display the messages. Timer is used to calculate the time 🕰️.
- **Simulation:** Proteus 🤖.
- **Code Editor:** Microchip Studio 👨‍💻.
