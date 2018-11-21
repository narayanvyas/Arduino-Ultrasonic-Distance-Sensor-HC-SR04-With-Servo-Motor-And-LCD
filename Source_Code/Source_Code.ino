/*  Ultrasonic Distance Sensor HC-SR04 With Servo Motor And LCD
 * 
 *  GitHub URL - https://github.com/narayanvyas/Arduino-Ultrasonic-Distance-Sensor-HC-SR04-With-Servo-Motor-And-LCD
 * 
 *  Developed By Web Dev Fusion
 *  URL - https://www.webdevfusion.com
 *  
 * Components
 * ----------
 *  - Arduino Uno
 *  - Ultrasonic Distance Sensor
 *  - An LED
 *  - A 220 Ohm resistor for the LED
 *  - A Buzzer
 *  - A Servo Motor
 *  - A Potentiometer
 *  - a LCD
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
 *      Ultrasonic Echo           |        6
 *      Ultrasonic Trigger        |        7
 *      Servo VCC VCC             |        5V
 *      Servo GND                 |        GND
 *      Servo Out                 |        9
 *      Buzzer GND                |        GND
 *      Buzzer Out                |        8
 *      LED                       |        10
 *      
 *   LCD screen    |    Arduino Uno
 *  ---------------------------------
 *      1  (Vss)  |      GND
 *      2  (Vdd)  |      5V
 *      3  (VO)   |      Potentiometer
 *      4  (RS)   |      12
 *      5  (RW)   |      GND
 *      6  (E)    |      11
 *      7  (D0)   |      Not connected
 *      8  (D1)   |      Not connected
 *      9  (D2)   |      Not connected
 *      10 (D3)   |      Not connected
 *      11 (D4)   |      5
 *      12 (D5)   |      4
 *      13 (D6)   |      3
 *      14 (D7)   |      2
 *      15 (A)    |      5V
 *      16 (K)    |      GND
 *      
 * Also connect an LED to simulate a controlled device. 
 *           220 Ohm
 *    3 ----/\/\/\/\----(LED |)----GND
 *  
 */

#include <Servo.h>      // Loading Servo Motor Header Files
#include <LiquidCrystal.h>

#define echoPin 6
#define trigPin 7
int ledPin   = 10;       // choose the pin for the LED
int buzzer = 8;         // choose pin for the buzzer
int servoPin = 9;       // Servo Pin

Servo Servo1;             // creating servo object

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin (9600);
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);     // declare buzzer as output
  Servo1.attach(servoPin);     // attaching servo pin
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.write("Welcome");
  delay(5000);
  lcd.clear();
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

  if (distance >= 100 || distance <= 0){
    Serial.println("Out of range");
    lcd.clear();
    lcd.print("No Object Found");
    delay(500);
    lcd.clear();
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
    lcd.write("Object Found");
    lcd.setCursor(0, 1);
    lcd.write("Arm Moved");
    delay(7000);
    lcd.clear();
  }
}
