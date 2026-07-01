# 4-DOF Pick-and-Place Robotic Arm

## 🎥 Project Demonstration

<img width="600" height="337" alt="ezgif-65724d8e6520d0eb" src="https://github.com/user-attachments/assets/925d9bd0-48e1-4535-a235-f94e9200682b" />

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

## 🔌 System Wiring & Detailed Architecture
To completely isolate heavy servo motor induction and avoid Arduino Uno hardware brownouts, the power and signals are mapped using a centralized configuration:

### 📍 Hardware Port Mapping
- **I2C Interface:** Arduino `SDA (A4)` $\rightarrow$ PCA9685 `SDA` | Arduino `SCL (A5)` $\rightarrow$ PCA9685 `SCL`.
- **Power Delivery:** Servos run directly from the **5V 3A External DC Adapter** routed through the PCA9685 blue screw terminal block.
- **Common Ground:** Arduino `GND` is tied to the external power supply `GND` for baseline signal reference.

### 🎛️ PCA9685 Servo Channel Routing
| Channel (CH) | Servo Motor Function | Code Variable | Safety Constraints |
| :---: | :--- | :--- | :--- |
| **Channel 0** | **Base Servo** (Horizontal Rotation Control) | `BASE_CH` | $0^\circ \text{ to } 90^\circ$ |
| **Channel 1** | **Right Servo** (Right Linkage/Arm Control) | `RIGHT_CH` | $40^\circ \text{ to } 120^\circ$ |
| **Channel 2** | **Left Servo** (Left Linkage/Arm Control) | `LEFT_CH` | $0^\circ \text{ to } 90^\circ$ |
| **Channel 3** | **Claw/Gripper** (Claw Open & Close Control) | `CLAW_CH` | Open: $60^\circ$ \| Close: $90^\circ$ |

> <img width="597" height="514" alt="image" src="https://github.com/user-attachments/assets/0f55f531-b225-44d8-8541-e01be7fc1dc0" />
---

## 💻 Control Logic & Code Architecture
The software implementation utilizes direct mapping from raw degrees into safe duty-cycle PWM timeslices using a core embedded function:

 ```cpp
void moveServo(uint8_t channel, int angle) {
  int targetAngle = angle;

  // Safe software limits checking (Constraints)
  if (channel == BASE_CH)  targetAngle = constrain(angle, baseMin, baseMax);
  if (channel == LEFT_CH)  targetAngle = constrain(angle, leftMin, leftMax);
  if (channel == RIGHT_CH) targetAngle = constrain(angle, rightMin, rightMax);
  if (channel == CLAW_CH)  targetAngle = constrain(angle, clawOpen, clawClose);

  // Map angles to PCA9685 12-bit Resolution pulses (150 to 600)
  int pulse = map(targetAngle, 0, 180, 150, 600); 
  pwm.setPWM(channel, 0, pulse);
} 
```
### 📸 Project Photos
| Hardware Setup | Robotic Arm Side View |
| :---: | :---: |
| <img width="100%" alt="Hardware Setup" src="https://github.com/user-attachments/assets/e56c211b-a1a4-46a9-927e-90e6ae91505e" /> | <img width="100%" alt="Robotic Arm Side View" src="https://github.com/user-attachments/assets/4e4a0f4c-b2a6-416f-ba5f-47c54feeadf9" /> |
 
## 🔮 Future Enhancements
- **Inverse Kinematics**: Implementation of coordinate-based target tracking instead of hardcoded angles.
- **Ultrasonic Sensors**: Real-time object detection before initiating pick sequences.
- **Wireless Control**: Integration of an HC-05 Bluetooth module for remote operation.
- **Computer Vision**: Camera systems integration for fully autonomous object color/shape sorting.

 ## 📚 References
1. Arduino Uno R3 Official Technical Documentation.
2. Adafruit PCA9685 16-Channel Servo Driver Library Guide.
3. Multi-DOF Robotic Manipulators and Linkage Kinematics Analysis.

---
**Developed by:** Meshal Talal Al Mehmady  
**Affiliation:** Taif University
