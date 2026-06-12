/*
 * MIT License
 * * Copyright (c) 2025 Team Robonavigators
 * * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// --- Pin definitions and variable initialization ---
int IR_sensor = 0;       // Stores the current digital state of the IR sensor
int distance = 0;        // Stores the calculated distance from the ultrasonic sensor
int currentState = -1;   // Tracks the current system state to prevent redundant LCD/Servo updates

// Initialize I2C LCD (Address: 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Initialize Servo object
Servo servo_9;

// --- Ultrasonic sensor distance measurement function ---
long ultrasound_distance_1() {
  long duration, dist;
  digitalWrite(8, LOW);
  delayMicroseconds(2);
  digitalWrite(8, HIGH); // Send 10us trigger pulse
  delayMicroseconds(10);
  digitalWrite(8, LOW);
  duration = pulseIn(7, HIGH); // Read the echo pulse width
  dist = duration / 58;        // Convert pulse duration to distance in cm
  return dist;
}

void setup() {
  // --- Configure pin directions ---
  pinMode(8, OUTPUT); // Trigger pin for HC-SR04 Ultrasonic sensor
  pinMode(7, INPUT);  // Echo pin for HC-SR04 Ultrasonic sensor
  pinMode(4, INPUT_PULLUP); // IR sensor pin (configured with internal pull-up)
  pinMode(5, OUTPUT); // Output pin (e.g., LED or Relay)
  pinMode(2, OUTPUT); // Output pin (e.g., LED or Relay)
  
  servo_9.attach(9); // Attach the servo motor control wire to digital pin 9
  
  lcd.init();      // Initialize the LCD screen
  lcd.backlight(); // Turn on the LCD backlight
  Serial.begin(9600); // Start serial communication for debugging purposes
}

void loop() {
  // --- Read current sensor values ---
  IR_sensor = digitalRead(4);
  distance = ultrasound_distance_1();
  
  // Print sensor readings to the Serial Monitor
  Serial.print("IR: ");
  Serial.println(IR_sensor);
  Serial.print("Distance: ");
  Serial.println(distance);

  // --- CONDITION 1: Vehicle is approaching / positioned at the barrier (0 to 15 cm) ---
  if (distance > 0 && distance < 15) { 
    if (currentState != 1) { 
      servo_9.write(90); // Position servo arm (e.g., lower the barrier gate)
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Welcome");
      lcd.setCursor(0, 1);
      lcd.print("Have a nice day");
      digitalWrite(5, LOW);  // Toggle indicators
      digitalWrite(2, HIGH);
      currentState = 1;      // Update state tracker
    }
    delay(4000); // Hold this message and position for 4 seconds
  } 
  
  // --- CONDITION 2: IR sensor is triggered (e.g., vehicle passing through the gate) ---
  else if (IR_sensor == LOW) { 
    if (currentState != 2) { 
      servo_9.write(90); // Keep barrier closed/stopping while passing
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Thank You");
      lcd.setCursor(0, 1);
      lcd.print("Have a nice day");
      digitalWrite(5, LOW);  // Toggle indicators
      digitalWrite(2, HIGH);
      currentState = 2;      // Update state tracker
    }
    delay(4000); // Hold this message and position for 4 seconds
  } 
  
  // --- CONDITION 3: No vehicle detected (Idle / Open Gate state) ---
  else {
    if (currentState != 0) { 
      servo_9.write(180); // Open the barrier gate (move servo to 180 degrees)
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Welcome To");
      lcd.setCursor(0, 1);
      lcd.print("Toll Gate");
      digitalWrite(5, HIGH); // Toggle indicators
      digitalWrite(2, LOW);
      currentState = 0;      // Update state tracker
    }
  }
  
  delay(100); // Short delay for system stability before the next loop iteration
}
