#include <DHT.h>
#include <TM1637Display.h>

#define DHTPIN 2 // Connect DHT11 data pin to digital pin 2
#define DHTTYPE DHT11 // Define DHT sensor type
#define DIO 3 // Data pin of TM1637 display
#define CLK 4 // Clock pin of TM1637 display

// Create °C and % symbols
const uint8_t celsius[] = {
  SEG_A | SEG_B | SEG_F | SEG_G, // Circle
  SEG_A | SEG_D | SEG_E | SEG_F // C
};

const uint8_t percent[] = {
  SEG_A | SEG_B | SEG_F | SEG_G, // Circle
  SEG_C | SEG_D | SEG_E | SEG_G  // %
};

DHT dht(DHTPIN, DHTTYPE);
TM1637Display display(CLK, DIO);

void setup() {
  Serial.begin(9600);
  dht.begin();
  display.setBrightness(0x0f); // Set display brightness
}

void loop() {
  // Read temperature and humidity
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  // Check if any errors occurred during reading
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Round temperature and humidity to nearest integer
  int tempInt = round(t);
  int humInt = round(h);

  // Display temperature on TM1637
  display.showNumberDec(tempInt, false, 2, 0); // Display integer temperature with 2 digits
  display.setSegments(celsius, 2, 2); 
  delay(3000); // Wait for 3 seconds
  display.clear(); 

  // Display humidity on TM1637
  display.showNumberDec(humInt, false, 2, 0); // Display integer humidity with 2 digits
  display.setSegments(percent, 2, 2);
  delay(3000); // Wait for 3 seconds
  display.clear(); 

  Serial.print("Temperature: "); 
  Serial.print(t); 
  Serial.print(" °C, Humidity: "); 
  Serial.print(h); 
  Serial.println(" %");   

  delay(100); // Wait for 1 seconds
}
