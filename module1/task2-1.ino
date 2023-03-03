// C++ code

#include <Servo.h>

Servo Servo1;

// Define the sensor, servo and LED pins and button pin
#define sensorPin A0
#define servoPin 7
#define ledPin 13
#define buttonPin 3

// Initialize variables for LED state and button press state
bool ledState = false;
bool pressed = false;

void setup()
{
    // Initialize serial communication and set pin modes
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);

    // Set the initial LED state and attach the servo to its pin
    digitalWrite(ledPin, LOW);
    Servo1.attach(servoPin);
    
    // Read the button pin and attach an interrupt to it
    pressed = digitalRead(buttonPin);
    attachInterrupt(0, buttonTrigger, FALLING);
}

void loop()
{
    // Read the temperature from the sensor and convert it to Celsius and servo value
    int reading = analogRead(sensorPin);
    float voltage = reading * (5.0 / 1024.0);
    float temperature = (voltage - 0.5) * 100;
    int value = map(temperature, 0, 100, 0, 180);

    // Print the LED state, temperature and LED state to serial monitor
    Serial.print("LED state: ");
    Serial.print(pressed);
    Serial.print(", Temperature: ");
    Serial.print(temperature);
    Serial.print(", LED: ");
    Serial.println(ledState);

    // Turn the servo based on the temperature value
    if(temperature > 0 && temperature < 100){
        Servo1.write(value);
    } else if(temperature < 0){
        Servo1.write(0);
    } else if(temperature > 100){
        Servo1.write(180);
    }

    // Turn the LED on or off based on the button press
    digitalWrite(ledPin, pressed);

    // Wait for stability
    delay(50);
}

// Function that toggles the button press state
void buttonTrigger(){
    pressed = !pressed;
}
