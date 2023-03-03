// C++ code
//

// Define the pin number for the temperature sensor
#define sensorPin A0

// Define the pin number for the LED
const int ledPin = 8;

// Initialize the LED state to off
bool ledState = false;

// Setup function runs once when the board starts
void setup()
{
  // Start the serial communication with a baud rate of 9600
  Serial.begin(9600);

  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // Turn off the LED to start
  digitalWrite(ledPin, LOW);
}

// Loop function runs repeatedly
void loop()
{
  // Read the analog value from the temperature sensor
  int reading = analogRead(sensorPin);

  // Convert the analog value to voltage
  float voltage = reading * (5.0 / 1024.0);

  // Convert the voltage to Celsius
  float temperature = (voltage - 0.5) * 100;

  // Print the temperature and LED state to the serial monitor
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(", LED: ");
  Serial.println(ledState);

  // Turn on the LED if the temperature is higher than 29°C
  if(temperature > 29){
    digitalWrite(ledPin, HIGH);
    ledState = true;
  } 
  // Otherwise, turn off the LED
  else {
    digitalWrite(ledPin, LOW);
    ledState = false;
  }

  // Wait for 50 milliseconds to ensure stability
  delay(50);
}
