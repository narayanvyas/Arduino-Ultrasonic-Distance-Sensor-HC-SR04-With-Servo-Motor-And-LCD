/*  PIR Motion Sensor With Servo Motor
 * 
 *  GitHub URL - https://github.com/narayanvyas/Arduino-PIR-Motion-Sensor-SC-SR501-With-Servo-Motor
 * 
 *  Developed By Web Dev Fusion
 *  URL - https://www.webdevfusion.com
 *  
 *  Designed By S-Kit
 *  
 * Components
 * ----------
 *  - Arduino Uno
 *  - Infrared Motion Sensor
 *  - Ultrasonic Distance Sensor
 *  - An LED
 *  - A 220 Ohm resistor for the LED
 *  - A Buzzer
 *  - A Servo Motor
 *  
 *  Libraries
 *  ---------
 *  - None
 *
 * Connections
 * -----------
 *  Break out    |    Arduino Uno
 *  --------------------------------------------
 *      Ultrasonic VCC            |        5V
 *      Ultrasonic GND            |        GND
 *      Ultrasonic Echo           |        12
 *      Ultrasonic Trigger        |        13
 *      Servo VCC VCC             |        5V
 *      Servo GND                 |        GND
 *      Servo Out                 |        5
 *      Buzzer GND                |        GND
 *      Buzzer Out                |        8
 *      LED                       |        4
 *      
 * Also connect an LED to simulate a controlled device. 
 *           220 Ohm
 *    3 ----/\/\/\/\----(LED |)----GND
 *  
 */

#include <Servo.h>      // Loading Servo Motor Header Files

#define echoPin 12
#define trigPin 13
int ledPin   = 4;       // choose the pin for the LED
int buzzer = 8;         // choose pin for the buzzer
int servoPin = 5;       // Servo Pin

Servo Servo1;             // creating servo object

void setup() {
  Serial.begin (9600);
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);     // declare buzzer as output
  Servo1.attach(servoPin);     // attaching servo pin
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  if (distance >= 300 || distance <= 0){
    Serial.println("Out of range");
    digitalWrite(ledPin, LOW); // turn LED OFF
    noTone(buzzer);
    Servo1.write(0);
  }
  else {
    Serial.print("Object is ");
    Serial.print(distance);
    Serial.print(" cm");
    Serial.println(" far from the machine");
    digitalWrite(ledPin, HIGH);  // turn LED ON
    tone(buzzer, 1000);
    Servo1.write(180);
    Serial.println("Arm Moved");
    delay(7000);
  }
  delay(200);
}
