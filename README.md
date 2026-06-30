# 4-DOF Pick-and-Place Robotic Arm

An efficient, low-cost, and reliable 4-Degree of Freedom (4-DOF) robotic arm designed and implemented for automated point-to-point pick-and-place operations. This project features hardware integration between an Arduino Uno and a dedicated PCA9685 PWM servo driver to ensure smooth and accurate mechanical motion.

## 🚀 Objectives
- Perform fully automated pick-and-place operations.
- Achieve repeatable and reliable joint motion through tailored servo constraints.
- Prevent power drops and microcontroller brownouts using an isolated external power supply.
- Demonstrate an affordable automation solution for industrial or laboratory tasks.

## 🛠️ System Components & Electronics
| Component | Qty | Purpose |
| :--- | :---: | :--- |
| **Arduino Uno R3** | 1 | Main microcontroller unit for high-level logic execution |
| **PCA9685 Servo Driver** | 1 | 16-channel, 12-bit PWM I2C driver to offload servo timing |
| **TowerPro Servo Motors** | 4 | Actuators for Base, Left/Right linkages, and the Claw |
| **5V 3A Power Adapter** | 1 | External power supply isolated for heavy servo loads |
| **4-DOF Acrylic Frame** | 1 | Mechanical chassis and link structure of the manipulator |
| **Jumper Wires** | Pack | Signal routing and common ground connections |

## 📐 Motion Sequence & Constraints
To ensure physical protection and mechanical integrity, all joint movements are digitally locked within safety limits via the code logic (`constrain` limits):
- **Base Joint (`BASE_CH`)**: `0°` to `90°`
- **Left Linkage (`LEFT_CH`)**: `0°` to `90°`
- **Right Linkage (`RIGHT_CH`)**: `40°` to `120°`
- **Claw/Gripper (`CLAW_CH`)**: Open `60°` | Close `90°`

### Operational Loop:
1. **Home/Standby Position** $\rightarrow$ Arm resets to starting angles.
2. **Approach & Pick** $\rightarrow$ Base rotates to approach position, link lowers, claw clamps object.
3. **Lift & Transfer** $\rightarrow$ Arm raises safely, base rotates to placement position.
4. **Release & Reset** $\rightarrow$ Links lower at target destination, claw opens, and the arm swings back to home.

## 🔌 Wiring Layout
- **Protocol**: I2C communication via `SDA` and `SCL` between Arduino and PCA9685.
- **Power Separation**: Servos are powered strictly via the PCA9685 terminal block through the 5V external adapter.
- **Signal Integrity**: A **Common Ground (GND)** is explicitly wired between the Arduino board and the external power supply.

## 🔮 Future Enhancements
- **Inverse Kinematics**: Implementation of coordinate-based target tracking instead of hardcoded angles.
- **Ultrasonic Sensors**: Real-time object detection before initiating pick sequences.
- **Wireless Control**: Integration of an HC-05 Bluetooth module for remote operation.
- **Computer Vision**: Camera systems integration for fully autonomous object color/shape sorting.

---
**Developed by:** Meshal Talal Al Mehmady  
**Affiliation:** Taif University
