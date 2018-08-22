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


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <CapacitiveSensor.h>


#define DHTPIN            D6         // Pin which is connected to the DHT sensor.
#define OLED_RESET LED_BUILTIN
#define DHTTYPE           DHT22     // DHT 22 (AM2302)
#define CAP_TX            D8
#define CAP_RX            D7


DHT_Unified dht(DHTPIN, DHTTYPE);

CapacitiveSensor   cs = CapacitiveSensor(CAP_TX,CAP_RX);        // 1Mohm resistor between pins 4 & 2, pin 2 is sensor pin


uint32_t timerMeasure, timeMeasure;
float temperature, humidity;

Adafruit_SSD1306 display(OLED_RESET);

boolean sleept = false;
float timerSleep, timeSleep;


  
void setup()   {                
  Serial.begin(9600);
  Serial.println("Working");

  cs.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - TOUCH SENSOR


  dht.begin();
  Serial.println("DHTxx Unified Sensor Example");
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor Min Delay:       "); Serial.println(sensor.min_delay);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");  
  Serial.println("------------------------------------");
  
  // Set delay between sensor readings based on sensor details.
  timerMeasure = 1000.0;
  timeMeasure = millis();

  timerSleep = 5000.0;
  timeSleep = millis();
  
  temperature = 0.0;
  humidity = 0.0;

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  // Clear the buffer.
  display.clearDisplay();

  
  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
}


void loop() {

  if (millis() - timeMeasure > timerMeasure) {

    // Delay between measurements.
    timeMeasure = millis();
    
    display.clearDisplay();
  
    display.setCursor(0,0);
    
    // Get temperature event and print its value.
    sensors_event_t event;  
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      Serial.println("Error reading temperature!");
    }
    else {

      temperature = event.temperature;
    }
    // Get humidity event and print its value.
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      Serial.println("Error reading humidity!");
    }
    else {
      humidity = event.relative_humidity;
    }

    display.print("T: ");
    display.print(temperature);
    display.println(" C");

    display.print("H: ");
    display.print(humidity);
    display.println("%");

    display.display();
    Serial.println("Measure done!");

  }

    long start = millis();

    long touch_measure =  cs.capacitiveSensor(30);
    Serial.print("Touch measure: ");
    Serial.println(touch_measure);
    Serial.print("Elapsed time: ");
    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.println(" ms.");
    Serial.println();

    delay(200);



}
