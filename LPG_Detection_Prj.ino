#include <Servo.h>

const int gasSensorPin = A0;  
const int buzzerPin = 8;
const int fanPin = 10;  

Servo gasValveServo;

const int gasThreshold = 600;

// Variables
bool servoMoved = false; 
unsigned long buzzerStartTime = 0;
const unsigned long buzzerDuration = 8000;
bool buzzerActive = false; 

void setup() {
  Serial.begin(9600);

  pinMode(gasSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  
  gasValveServo.attach(9);
  gasValveServo.write(0);  // Initial position: Gas valve open
  
  Serial.println("System initialized. Monitoring gas levels...");
}

void loop() {
  int gasLevel = analogRead(gasSensorPin);
  
  Serial.print("Gas Level: ");
  Serial.println(gasLevel);

  // If gas leakage is detected
  if (gasLevel > gasThreshold && !servoMoved) {
    digitalWrite(fanPin, HIGH);
    gasValveServo.write(135);

    if (!buzzerActive) {
      buzzerActive = true;
      buzzerStartTime = millis();       // Record the time when buzzer is activated
      Serial.println("Gas detected! Closing gas valve and activating buzzer.");
    }
  } 

  // Handling buzzer beeping every second
  if (buzzerActive) {
    if (millis() - buzzerStartTime < buzzerDuration) {
      if ((millis() / 1000) % 2 == 0) { 
        digitalWrite(buzzerPin, HIGH); 
      } else {
        digitalWrite(buzzerPin, LOW);  
      }
    } else {
      digitalWrite(buzzerPin, LOW);
      buzzerActive = false;        
      Serial.println("Buzzer off after 5 seconds.");
    }
  } else {
    // No gas detected situation
    if (servoMoved) {
      digitalWrite(fanPin, LOW);
      gasValveServo.write(0);
      servoMoved = false;     
      Serial.println("No gas detected. Opening gas valve.");
    }
  }

  // Delay before next reading
  delay(1000);
}
