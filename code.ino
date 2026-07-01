/* Author: Meshal Talal Al Mehmady
   ID: 44102105 
   Project: 4-DOF Automated Pick-and-Place Robotic Arm
*/

#include <Wire.h>                          // Include Wire library for I2C communication
#include <Adafruit_PWMServoDriver.h>       // Include Adafruit PCA9685 PWM Servo Driver library

// Instantiate the PWM driver object (Default I2C address: 0x40)
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Define PCA9685 hardware channels for each servo motor
#define BASE_CH  0                         // Channel 0: Base rotation servo
#define RIGHT_CH 1                         // Channel 1: Right linkage arm servo
#define LEFT_CH  2                         // Channel 2: Left linkage arm servo
#define CLAW_CH  3                         // Channel 3: Gripper/Claw servo

// Define safe operational joint boundaries (Angles in degrees)
int baseMin = 0,   baseMax = 90;           // Base horizontal sweep limits
int leftMin = 0,   leftMax = 90;           // Left arm structural motion limits
int rightMin = 40, rightMax = 120;         // Right arm structural motion limits
int clawOpen = 60, clawClose = 90;         // Gripper actuation limits (Open vs. Closed)

void setup() {
  Serial.begin(9600);                      // Initialize serial communication at 9600 bps
  pwm.begin();                             // Initialize the PCA9685 PWM driver
  pwm.setPWMFreq(60);                      // Set PWM frequency to 60Hz (Standard for analog servos)

  // Move all joints to their initial homing/safeguard coordinates
  moveServo(BASE_CH, 0);                   // Home Base to 0 degrees
  moveServo(LEFT_CH, 40);                  // Home Left arm to 40 degrees
  moveServo(RIGHT_CH, 80);                 // Home Right arm to 80 degrees
  moveServo(CLAW_CH, clawOpen);            // Open the claw to standby state
  delay(3000);                             // Wait 3 seconds for stabilization before loop execution
}

void loop() {
  // Step 1: Rotate the base to the pick target location orientation
  moveServo(BASE_CH, 45);      
  delay(2000);                             // Wait 2 seconds for movement completion

  // Step 2: Lower the mechanical linkages toward the object
  moveServo(LEFT_CH, 70);      
  moveServo(RIGHT_CH, 80);
  delay(2000);

  // Step 3: Secure the object by closing the claw/gripper
  moveServo(CLAW_CH, clawClose); 
  delay(2000);

  // Step 4: Retract and lift the object safely back up
  moveServo(LEFT_CH, 20);      
  moveServo(RIGHT_CH, 110);    
  delay(2000);

  // Step 5: Swing the base smoothly to the designated drop zone orientation
  moveServo(BASE_CH, 90);     
  delay(2500);

  // Step 6: Lower the linkages into the placement area coordinate grid
  moveServo(LEFT_CH, 60);      
  moveServo(RIGHT_CH, 90);    
  delay(2000);

  // Step 7: Release the object by fully opening the gripper
  moveServo(CLAW_CH, clawOpen);  
  delay(1500);

  // Step 8: Retract the empty links back up safely clear of the payload
  moveServo(LEFT_CH, 20);      
  moveServo(RIGHT_CH, 110);    
  delay(2000);

  // Step 9: Return all joints back to the safe baseline home configuration
  moveServo(LEFT_CH, 40);
  moveServo(RIGHT_CH, 80);
  moveServo(BASE_CH, 0);
  
  // Print status message to the Serial Monitor and hold execution
  Serial.println("Cycle completed.. Waiting for 5 seconds");
  delay(5000);                             // 5-second stabilization gap before starting the next cycle
}

/**
 * Control function to safely constrain and map angles into hardware PWM pulses
 * @param channel The PCA9685 target channel index (0 to 3)
 * @param angle The desired physical target angle in degrees
 */
void moveServo(uint8_t channel, int angle) {
  int targetAngle = angle;

  // Real-time software limits enforcement to protect physical servo limits
  if (channel == BASE_CH)  targetAngle = constrain(angle, baseMin, baseMax);
  if (channel == LEFT_CH)  targetAngle = constrain(angle, leftMin, leftMax);
  if (channel == RIGHT_CH) targetAngle = constrain(angle, rightMin, rightMax);
  if (channel == CLAW_CH)  targetAngle = constrain(angle, clawOpen, clawClose);

  // Map the safe angle (0-180) to 12-bit duty cycle pulse counts (150-600 ticks)
  int pulse = map(targetAngle, 0, 180, 150, 600); 
  
  // Send the computed pulse value to the specified PCA9685 driver channel
  pwm.setPWM(channel, 0, pulse);
}