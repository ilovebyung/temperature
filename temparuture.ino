#include <DHT.h>
#include <TM1637Display.h>

#define DHTPIN 2 // Connect DHT11 data pin to digital pin 2
#define DHTTYPE DHT11 // Define DHT sensor type
#define DIO 3 // Data pin of TM1637 display
#define CLK 4 // Clock pin of TM1637 display

// Create °C symbol
const uint8_t celsius[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Circle
  SEG_A | SEG_D | SEG_E | SEG_F   // C
};

DHT dht(DHTPIN, DHTTYPE);
TM1637Display display(CLK, DIO);

void setup() {
  Serial.begin(9600);
  dht.begin();
  display.setBrightness(0x0f); // Set display brightness
}

void loop() {
  // Read temperature  
  float t = dht.readTemperature();

  // Check if any errors occurred during reading
  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Round temperature to nearest integer
  int tempInt = round(t);

  // Display temperature on TM1637
  display.showNumberDec(tempInt, false, 2, 0); // Display integer temperature with 2 digits
  display.setSegments(celsius, 2, 2);
  delay(3000); // Wait for 3 seconds
  display.clear(); // Clear the display

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");

  delay(1000); // Wait for 1 seconds
}
