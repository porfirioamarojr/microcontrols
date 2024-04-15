#include "Secret.h"
#include <Ethernet.h>
#include <Wire.h>
#include "ThingSpeak.h"
#include <DHT.h>
#include <HttpClient.h>
#include <Adafruit_BMP085.h>

//Sensor DHT22
#define DHTTYPE DHT22  // defining model sensor //#define mydht 7 substituida
const int DHTPIN = 7;  // defining pin sensor
DHT dht(DHTPIN, DHTTYPE);

//Ethernet
byte mac[]{ 0x90, 0xA2, 0xDA, 0x00, 0x4A, 0xE0 };
IPAddress ip(192, 168, 0, 10);
IPAddress myDns(192, 168, 0, 1);
EthernetClient client;
EthernetServer server = EthernetServer(80);  //port 80

//Sensor BMP180
Adafruit_BMP085 bmp;

//for ThingSpeak
int response;

void setup() {
  //Serial Initializer
  Serial.begin(115200);

  //Ethernet Initializer
  Ethernet.init(10);
  Ethernet.begin(mac);
  Ethernet.localIP();

  //ThingSpeak Initializer
  ThingSpeak.begin(client);
  
  //DHT Initializer
  dht.begin();

  //BMP180 Initializer
  bmp.begin();
  if (!bmp.begin()) {
	  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	  while (1) {}
  }

}

void loop() {
  //for Log in Serial Monitor
  float temperature = dht.readTemperature();  // celcius
  Serial.print(temperature);
  Serial.print("\n");
  float humidity = dht.readHumidity();
  Serial.print(humidity);
  Serial.print("\n");
  int ldr_value = analogRead(A0);
  Serial.print(ldr_value);
  Serial.print("\n");
  float height = bmp.readAltitude();
  Serial.print(height);
  Serial.print("\n");
  float pressure = bmp.readPressure() * 0.01;// para milibar
  Serial.print(pressure);
  Serial.print("\n");
  float temperature_bmp = bmp.readTemperature();
  Serial.print(temperature_bmp);
  Serial.print("\n");

  //ThingSpeak Fields
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, ldr_value);
  ThingSpeak.setField(4, height);
  ThingSpeak.setField(5, pressure);
  ThingSpeak.setField(6, temperature_bmp);

  //for update of channel into ThingSpeak
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (response == 200) {
    Serial.println("Channel update successful.");
  
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(response));
  }

  delay(15000);
}
