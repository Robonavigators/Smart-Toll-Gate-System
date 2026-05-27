# Smart Toll Gate System

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

An automated, Arduino-based toll gate system that manages vehicle entry and exit using ultrasonic and IR sensors. This project features a servo-operated gate, an I2C LCD screen for driver greetings, and LED status indicators.

## Features

* **Automated Entry:** Uses an Ultrasonic sensor to detect approaching vehicles and open the gate.
* **Automated Exit:** Uses an IR sensor to detect vehicles leaving the toll area.
* **LCD Interface:** Displays "Welcome", "Thank You", and standby messages based on the current state.
* **LED Indicators:** Green LED indicates the gate is open; Red LED indicates the gate is closed.
* **Flicker-Free Display:** Implements state-tracking to ensure the LCD only updates when the gate status changes, preventing screen flickering.

## Hardware Requirements

* Arduino Uno (or compatible board)
* 1x Ultrasonic Sensor (HC-SR04)
* 1x IR Obstacle Avoidance Sensor
* 1x 16x2 LCD Display with I2C module
* 1x Servo Motor (e.g., SG90)
* 1x Red LED
* 1x Green LED
* 2x 220-ohm Resistors (for LEDs)
* Breadboard and Jumper Wires

## Pin Configuration

| Component | Arduino Pin |
| :--- | :--- |
| Ultrasonic Trig | Digital 8 |
| Ultrasonic Echo | Digital 7 |
| IR Sensor OUT | Digital 4 |
| Servo Signal | Digital 9 |
| Red LED (Closed) | Digital 5 |
| Green LED (Open) | Digital 2 |
| I2C LCD SDA | A4 (or dedicated SDA pin) |
| I2C LCD SCL | A5 (or dedicated SCL pin) |

## Dependencies

Before uploading the code, ensure you have the following libraries installed in your Arduino IDE:
* `Wire.h` (Built-in)
* `Servo.h` (Built-in)
* `LiquidCrystal_I2C.h` (Install via Library Manager)

## Installation and Usage

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/yourusername/smart-toll-gate.git](https://github.com/yourusername/smart-toll-gate.git)
    ```
2.  **Wire the components:** Follow the pin configuration table above to connect all components to your Arduino.
3.  **Open the Code:** Open the `.ino` file in the Arduino IDE.
4.  **Upload:** Connect your Arduino to your computer, select the correct COM port and board, and click **Upload**.
5.  **Test:** Place an object in front of the Ultrasonic sensor (< 15cm) to trigger an entry. Trigger the IR sensor to test the exit.

## How It Works

1.  **Idle State:** The gate remains closed (Servo at 180°), the Red LED is ON, and the LCD reads "Welcome To Toll Gate".
2.  **Entry Detected:** When the Ultrasonic sensor detects an object within 15 units, the gate opens (Servo at 90°), the Green LED turns ON, and the LCD welcomes the driver. The gate stays open for 4 seconds.
3.  **Exit Detected:** When the IR sensor detects an object, the gate opens, the Green LED turns ON, and the LCD displays "Thank You". The gate stays open for 4 seconds.

## License

This project is open-source and available under the [MIT License](LICENSE).
