#include <SPI.h>
#include <ESP8266WiFi.h>
#include "Secret.h" // substitua por "Secrets.h"
#include "ThingSpeak.h"
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

//Sensor BMP280
#define BMP_SCK  (5)
#define BMP_MISO (14)
#define BMP_MOSI (4)
#define BMP_CS   (0)
Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO, BMP_SCK);
//Adafruit_BMP280 bmp;

//Sensor DHT11
#define DHTTYPE DHT22 // defining model sensor
#define DHTPIN D7    // defining pin sensor
DHT dht(DHTPIN, DHTTYPE);

//WiFi
WiFiClient client;

//for Status Counter
void splitString(String str, char delimiter, String substrings[], int maxSize);
int fail = 0;

//for ThingSpeak
int response;

void setup() {
  //Serial Initializer
  Serial.begin(115200);
  while (!Serial) { }
  
  //WiFi Initializer
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  //WiFi.useStaticBuffers(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
  printWifiStatus();
  
  //BMP280 Initializer
  bmp.begin();
  if (!bmp.begin()) {
	  Serial.println("Could not find a valid BMP280 sensor, check wiring!");
	  while (1) {}
  }
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
    
  //DHT Initializer
  dht.begin();
  
  //ThingSpeak Initializer
  ThingSpeak.begin(client);
  response = ThingSpeak.readMultipleFields(myChannelNumber, myReadAPIKey);
  if(response == 200){
    Serial.println("Get of channel update successful.");
  
  }else{
    Serial.println("Problem in get of channel. HTTP error code " + String(response));
  }

  //Code Block for update counter of errs  
  String substrings[37];  //Divide a string em até 37 posições
  String statusMessage = ThingSpeak.getStatus();
  char delimiter = ' ';
  splitString(statusMessage, delimiter, substrings, 37);
  
  for (int i = 0; i < 37 && !substrings[i].isEmpty(); i++) {
    fail = substrings[i].toInt();
  }

}

void loop() {
  String myStatus = "";

  //for Log in Serial Monitor
  float temperature = dht.readTemperature(); // celcius
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
  //Calculo para milibare
  float pressure = bmp.readPressure() * 0.01;//para milibar
  Serial.print(pressure);
  Serial.print("\n");
  float temperature_bmp = bmp.readTemperature();
  Serial.print(temperature_bmp);
  Serial.print("\n");

  //ThingSpeak Fields
  ThingSpeak.setField(1, humidity);
  ThingSpeak.setField(2, temperature);
  ThingSpeak.setField(3, ldr_value);
  ThingSpeak.setField(4, temperature_bmp);
  ThingSpeak.setField(5, height);
  ThingSpeak.setField(6, pressure);
  
  //logic for log of status count
  if(humidity == 0 || isnan(humidity)){
    myStatus += String("Sensor de humidade falhou\\");
    fail += 1;
  }
  if(temperature == 0 || isnan(temperature)){
    myStatus += String("Sensor de temperatura falhou\\");
    fail += 1;
  }
  if(ldr_value < 0 || isnan(ldr_value)){
    myStatus += String("Sensor de sensor de luminosidade falhou\\");
    fail += 1;
  }
  if(temperature_bmp == 0 || isnan(temperature_bmp)){
    myStatus += String("Sensor de temperatura BMP falhou\\");
    fail += 1;
  }
  if(height == 0 || isnan(height)){
    myStatus += String("Sensor de altura falhou\\");
    fail += 1;
  }
  if(pressure == 0 || isnan(pressure)){
    myStatus += String("Sensor de pressão falhou\\");
    fail += 1;
  }

  myStatus += String("Falhas até o momento: " + String(fail));
  ThingSpeak.setStatus(myStatus); //send status and return response
  delay(20);
  
  //for update of channel into ThingSpeak
  response = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(response == 200){
    Serial.println("Channel update successful.");
  
  }else{
    Serial.println("Problem updating channel. HTTP error code " + String(response));
  
  }

  delay(15000);

  //Restart connection
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.disconnect();
    WiFi.reconnect();
    delay(100);
  }
}

//for WiFi Status Log
void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

//for Status Counter
void splitString(String str, char delimiter, String substrings[], int maxSize) {
  int index = 0; // Índice para as substrings
  int lastIndex = 0; // Índice do último caractere de delimitação

  for (int i = 0; i < str.length() && index < maxSize - 1; i++) {
    if (str.charAt(i) == delimiter) {
      substrings[index] = str.substring(lastIndex, i);
      lastIndex = i + 1;
      index++;
    }
  }
  // Adicione a última substring após o último caractere de delimitação
  substrings[index] = str.substring(lastIndex);
}
