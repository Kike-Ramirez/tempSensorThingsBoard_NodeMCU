/*
    MIT License
    Copyright (c) 2018, Enrique Ramírez
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/


// Library Import for OLED Display
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// For touch Sensor
#include <CapacitiveSensor.h>

// For temperature & humidity sensor
#include <DHT.h>
// #include <DHT_U.h>

// For main operations & Thinger.io processes
#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

/*
 * 
 * PIN DEFINITIONS -----------> DHT, TOUCH & DISPLAY
 * 
 */
#define DHTPIN            D6         // Pin which is connected to the DHT sensor.
#define DHTTYPE           DHT22     // DHT 22 (AM2302)

#define CAP_TX            D8
#define CAP_RX            D7
#define TOUCH_LEVEL       25.0

#define OLED_RESET        LED_BUILTIN

// WIFI ACCESS PARAMETERS -----------> SSID & PASSWORD FOR WIFI ACCESS (NOT 5G)
#define SSID "CarmenLauraKike"
#define SSID_PASSWORD "Carmen2016"

// THINGER.IO -----------> USER, PWD & DEVICE CREDENTIALS, TOKEN, ETC.
#define USERNAME "KikeRamirez"
#define DEVICE_ID "NodeMCU"
#define DEVICE_CREDENTIAL "YSqMCv9y%0Xo"

// GENERAL PARAMETERS -----------> TIMINGS, FLAGS, DATA, ETC.
#define TIMER_MEASURE 1000.0
#define TIMER_SLEEP 5000.0
#define VERBOSITY 1

// GLOBAL VARIABLES -----------> TIMINGS, FLAGS, DATA, ETC.
float temperature, humidity;
float timeMeasure, timeSleep;

// INITIALIZE OBJECTS FOR -----------> NODE IOT, DISPLAY, TOUCH SENSOR, TEMP&HUMID SENSOR.
Adafruit_SSD1306 display(OLED_RESET);
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
DHT dht(DHTPIN, DHTTYPE);
CapacitiveSensor cs = CapacitiveSensor(CAP_TX,CAP_RX);


/*
 * 
 * SETUP PROCESS -----------> INITIALIZE EVERYTHING AND SETS ZERO CONDITION
 * 
 */

void setup()   {                

  if (VERBOSITY) {
    Serial.begin(9600);
    Serial.println("Starting...");
  }
  
  // Initialize IOT Node and connect to WIFI
  thing.add_wifi(SSID, SSID_PASSWORD);
  
  // Declare output parameter "temperature"
  thing["temperature"] >> [](pson& out){
        out = dht.readTemperature();
  };

  // Declare output parameter "humidity"
  thing["humidity"] >> [](pson& out){
        out = dht.readHumidity();
  };  
  
  // Initialize OLED Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  
  // Clear the buffer.
  display.clearDisplay();

  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);  
  
  // Initialize touch sensor
  cs.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - TOUCH SENSOR

  // Initialize temp & humidity sensor
  dht.begin();    
}


/*
 * 
 * LOOP -----------> 
 * 
 */

void loop() {

  // Manage Thinger.io updates
  thing.handle();

  display.clearDisplay();  

  // If awake, update display
  if (isAwake()) {
    updateDisplay();
  }

  // Print logs
  if (VERBOSITY) Serial.println("Measure done!");

}

/*
 * 
 * CHECK TOUCH SENSOR -----------> UPDATES SLEEP MODE DEPENDING ON TOUCHES & TIMERS
 * 
 */

bool isAwake() {

  if (VERBOSITY) Serial.println("  -> Checking TOUCH SENSOR level");

  // Updating touching status & timings
  if ( cs.capacitiveSensor(30) > TOUCH_LEVEL) return true;
  else return false;

}

/*
 * 
 * UPDATE DISPLAY -----------> UPDATES DISPLAY WITH NEW DATA, SPRITES, ANIMATIONS, ETC.
 * 
 */

float updateDisplay() {

      if (VERBOSITY) Serial.println("  -> Printing on OLED Display");

      // Reset Position
      display.setCursor(0,0);

      // Print temperature
      display.print("T: ");
      display.print(dht.readTemperature());
      display.println(" C");

      // Print humidity
      display.print("H: ");
      display.print(dht.readHumidity());
      display.println("%");

      // Send to OLED
      display.display();

}
