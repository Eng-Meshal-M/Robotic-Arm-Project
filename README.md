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

## 🔌 System Wiring & Diagram
To avoid microcontroller brownouts, the servos are powered by an external 5V 3A supply through the PCA9685 terminal block.
- **SDA/SCL:** I2C communication link between Arduino and Driver.
- **Common GND:** Essential for signal integrity across all components.

> 📸 **Drop your Wiring Diagram Photo below (اسحب صورة مخطط التوصيل والأردوينو هنا):**
<img width="240" height="210" alt="download" src="https://github.com/user-attachments/assets/b6bd45d2-28ab-4c7f-b1a5-6af1175152b4" />


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

## 🎬 Live Demo & Visuals
> 💡 *This section displays the actual project functionality and mechanical implementation.*

### 🎥 Project Video (التطبيق الحي للروبوت)
> 🎬 **Drop your Video file below (اسحب ملف الفيديو حق الروبوت وهو يتحرك هنا ليعمل مباشرة):**
[Watch the Robotic Arm in Action](https://via.placeholder.com/800x450?text=Drag+and+Drop+Your+Project+Video+Here)

### 📸 Project Photos
| Hardware Setup | Robotic Arm Side View |
| :---: | :---: |
| ![Setup](https://via.placeholder.com/400x300?text=Setup+Photo) | ![Side View](https://via.placeholder.com/400x300?text=Robotic+Arm+Photo) |

## 🔮 Future Enhancements
- **Inverse Kinematics**: Implementation of coordinate-based target tracking instead of hardcoded angles.
- **Ultrasonic Sensors**: Real-time object detection before initiating pick sequences.
- **Wireless Control**: Integration of an HC-05 Bluetooth module for remote operation.
- **Computer Vision**: Camera systems integration for fully autonomous object color/shape sorting.

---
**Developed by:** Meshal Talal Al Mehmady  
**Affiliation:** Taif University
