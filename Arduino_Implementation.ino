
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DHT.h>
#include <SPI.h>

// Pin Definitions
#define LED_PIN 8
#define MOTOR_IN1 9
#define MOTOR_IN2 10
#define DHT_PIN 2
#define DHT_TYPE DHT11

// OLED Display Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DHT Sensor
DHT dht(DHT_PIN, DHT_TYPE);

// Variables
int motorSpeed = 0; // Motor speed (0-255)

void setup() {
  // Initialize Serial
  Serial.begin(115200);

  // Initialize GPIO Pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);

  // Initialize DHT Sensor
  dht.begin();

  // Initialize OLED Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);

  // Display Welcome Message
  displayMessage("System Ready");
  delay(2000);
}

void loop() {
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    message.trim();

    if (message == "Action1") {
      turnLedOn();
    } else if (message == "Action2") {
      turnLedOff();
    } else if (message == "Action3") {
      motorSpeedUp();
    } else if (message == "Action4") {
      motorSpeedDown();
    } else if (message == "Action5") {
      checkTemperature();
    }
  }
}

// Function to Turn LED On
void turnLedOn() {
  digitalWrite(LED_PIN, HIGH);
  displayMessage("LED: ON");
  Serial.println("LED is ON");
}

// Function to Turn LED Off
void turnLedOff() {
  digitalWrite(LED_PIN, LOW);
  displayMessage("LED: OFF");
  Serial.println("LED is OFF");
}

// Function to Increase Motor Speed
void motorSpeedUp() {
  motorSpeed = constrain(motorSpeed + 50, 0, 255);
  analogWrite(MOTOR_IN1, motorSpeed);
  digitalWrite(MOTOR_IN2, LOW);
  displayMessage("Motor Speed Up");
  Serial.println("Motor Speed Increased");
}

// Function to Decrease Motor Speed
void motorSpeedDown() {
  motorSpeed = constrain(motorSpeed - 50, 0, 255);
  analogWrite(MOTOR_IN1, motorSpeed);
  digitalWrite(MOTOR_IN2, LOW);
  displayMessage("Motor Speed Down");
  Serial.println("Motor Speed Decreased");
}

// Function to Check Temperature and Humidity
void checkTemperature() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    displayMessage("Temp Read Error");
    Serial.println("Failed to read temperature!");
  } else {
    String message = "Temp: " + String(temp) + "C\nHumidity: " + String(hum) + "%";
    displayMessage(message);
    Serial.println(message);
  }
}

// Function to Display Messages on OLED
void displayMessage(String message) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(message);
  display.display();
}

----updated code----
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DHT.h>
#include <SPI.h>

// Pin Definitions
#define LED_PIN 8
#define MOTOR_IN1 9
#define MOTOR_IN2 10
#define DHT_PIN 2
#define DHT_TYPE DHT11

// OLED Display Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DHT Sensor
DHT dht(DHT_PIN, DHT_TYPE);

// Variables
int motorSpeed = 0; // Motor speed (0-255)

void setup() {
  // Initialize Serial
  Serial.begin(115200);

  // Initialize GPIO Pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);

  // Initialize DHT Sensor
  dht.begin();

  // Initialize OLED Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);

  // Display Welcome Message
  displayMessage("System Ready");
  delay(2000);
}

void loop() {
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    message.trim();

    if (message == "Device ON") {
      turnLedOn();
    } else if (message == "Device OFF") {
      turnLedOff();
    } else if (message == "Level Up (FAN)") {
      motorSpeedUp();
    } else if (message == "Level Down (FAN)") {
      motorSpeedDown();
    } else if (message == "Check Temperature") {
      checkTemperature();
    }
  }
}

// Function to Turn LED On
void turnLedOn() {
  digitalWrite(LED_PIN, HIGH);
  displayMessage("LED: ON");
  Serial.println("LED is ON");
}

// Function to Turn LED Off
void turnLedOff() {
  digitalWrite(LED_PIN, LOW);
  displayMessage("LED: OFF");
  Serial.println("LED is OFF");
}

// Function to Increase Motor Speed
void motorSpeedUp() {
  motorSpeed = constrain(motorSpeed + 50, 0, 255);
  analogWrite(MOTOR_IN1, motorSpeed);
  digitalWrite(MOTOR_IN2, LOW);
  displayMessage("Motor Speed Up");
  Serial.println("Motor Speed Increased");
}

// Function to Decrease Motor Speed
void motorSpeedDown() {
  motorSpeed = constrain(motorSpeed - 50, 0, 255);
  analogWrite(MOTOR_IN1, motorSpeed);
  digitalWrite(MOTOR_IN2, LOW);
  displayMessage("Motor Speed Down");
  Serial.println("Motor Speed Decreased");
}

// Function to Check Temperature and Humidity
void checkTemperature() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    displayMessage("Temp Read Error");
    Serial.println("Failed to read temperature!");
  } else {
    String message = "Temp: " + String(temp) + "C\nHumidity: " + String(hum) + "%";
    displayMessage(message);
    Serial.println(message);
  }
}

// Function to Display Messages on OLED
void displayMessage(String message) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(message);
  display.display();
}
