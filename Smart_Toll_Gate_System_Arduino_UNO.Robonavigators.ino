#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

int IR_sensor = 0;
int distance = 0;
int currentState = -1;

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo_9;

long ultrasound_distance_1() {
  long duration, dist;
  digitalWrite(8, LOW);
  delayMicroseconds(2);
  digitalWrite(8, HIGH);
  delayMicroseconds(10);
  digitalWrite(8, LOW);
  duration = pulseIn(7, HIGH);
  dist = duration / 58;
  return dist;
}

void setup() {
  pinMode(8, OUTPUT);
  pinMode(7, INPUT);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  pinMode(2, OUTPUT);
  
  servo_9.attach(9);
  
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  IR_sensor = digitalRead(4);
  distance = ultrasound_distance_1();
  
  Serial.print("IR: ");
  Serial.println(IR_sensor);
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance < 15) { 
    if (currentState != 1) { 
      servo_9.write(90);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Welcome");
      lcd.setCursor(0, 1);
      lcd.print("Have a nice day");
      digitalWrite(5, LOW);
      digitalWrite(2, HIGH);
      currentState = 1;
    }
    delay(4000); 
  } 
  
  else if (IR_sensor == LOW) { 
    if (currentState != 2) { 
      servo_9.write(90);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Thank You");
      lcd.setCursor(0, 1);
      lcd.print("Have a nice day");
      digitalWrite(5, LOW);
      digitalWrite(2, HIGH);
      currentState = 2;
    }
    delay(4000); 
  } 
  
  else {
    if (currentState != 0) { 
      servo_9.write(180);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Welcome To");
      lcd.setCursor(0, 1);
      lcd.print("Toll Gate");
      digitalWrite(5, HIGH);
      digitalWrite(2, LOW);
      currentState = 0;
    }
  }
  
  delay(100); 
}