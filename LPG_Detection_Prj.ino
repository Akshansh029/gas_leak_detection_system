#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Servo.h>

// OLED display setup
#define i2c_Address 0x3c // I2C address of the OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin not used
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Gas sensor and control pin setup
const int gasSensorPin = A0;  
const int buzzerPin = 8;
const int fanPin = 10;  
Servo gasValveServo;

const int gasThreshold = 600; // Gas threshold for detection

// Variables for gas detection
bool servoMoved = false; 
unsigned long buzzerStartTime = 0;
const unsigned long buzzerDuration = 8000;
bool buzzerActive = false; 

void setup() {
  // Initialize serial monitor
  Serial.begin(9600);

  // Initialize pins
  pinMode(gasSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  
  // Initialize gas valve servo
  gasValveServo.attach(9);
  gasValveServo.write(0);  // Gas valve is open initially

  // Initialize OLED display
  display.begin(i2c_Address, true); 
  display.display(); 
  delay(2000);  // Wait for OLED to initialize
  display.clearDisplay();

  // Print the initial message on the OLED
  display.setTextSize(1);       
  display.setTextColor(SH110X_WHITE);  
  display.setCursor(0, 0);     
  display.println("System Initialized");
  display.display();
  delay(2000);
  display.clearDisplay(); 
}

void loop() {
  // Read the gas sensor value
  int gasLevel = analogRead(gasSensorPin);
  
  // Print gas level to serial monitor
  Serial.print("Gas Level: ");
  Serial.println(gasLevel);

  // Display gas level on OLED
  display.clearDisplay();
  display.setTextSize(2);       // Larger text size for readability
  display.setTextColor(SH110X_WHITE);  
  display.setCursor(0, 0);     
  display.print("Gas Level: ");
  display.setCursor(0, 30);     
  display.println(gasLevel);   // Print the gas level on OLED
  display.display();           // Update the OLED display

  // If gas leakage is detected
  if (gasLevel > gasThreshold && !servoMoved) {
    digitalWrite(fanPin, HIGH);
    gasValveServo.write(135);  // Close the gas valve

    if (!buzzerActive) {
      buzzerActive = true;
      buzzerStartTime = millis();  // Record the time when the buzzer is activated
      Serial.println("Gas detected! Closing gas valve and activating buzzer.");
    }
  } 

  // Handling buzzer activation
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
      Serial.println("Buzzer off after 8 seconds.");
    }
  } else {
    // No gas detected scenario
    if (servoMoved) {
      digitalWrite(fanPin, LOW);
      gasValveServo.write(0);  // Open the gas valve
      servoMoved = false;     
      Serial.println("No gas detected. Opening gas valve.");
    }
  }

  // Delay before next reading
  delay(1000);
}
