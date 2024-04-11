#include <SPI.h>
#include <WiFi.h>
#include "Secrets.h"
#include "ThingSpeak.h"
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/temperature_sensor.h"

//for Internal Temperature
static const char *TAG = "example";
temperature_sensor_handle_t temp_sensor; // Variável global para armazenar o identificador do sensor de temperatura

//Sensor BMP280
#define BMP_SCK  (6)
#define BMP_MISO (2)
#define BMP_MOSI (7)
#define BMP_CS   (10)
Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

//Sensor DHT11
#define DHTTYPE DHT22 // defining model sensor
const int DHTPIN = 8;     // defining pin sensor
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
  WiFi.useStaticBuffers(true);
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
  bmp.begin(0x76);
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

  //Internal Temperature Sensor Initializer
  initTempSensor();
  
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
  ESP_LOGI(TAG, "Read temperature");
  float tsens_value;
  ESP_ERROR_CHECK(temperature_sensor_get_celsius(temp_sensor, &tsens_value));
  Serial.print(tsens_value);
  Serial.print("\n");
  float temperature = dht.readTemperature(); // celcius
  Serial.print(temperature);
  Serial.print("\n");
  float humidity = dht.readHumidity();
  Serial.print(humidity);
  Serial.print("\n");
  int ldr_value = analogRead(A4);
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
  ThingSpeak.setField(1, humidity);
  ThingSpeak.setField(2, temperature);
  ThingSpeak.setField(3, ldr_value);
  ThingSpeak.setField(4, tsens_value);
  ThingSpeak.setField(5, temperature_bmp);
  ThingSpeak.setField(6, height);
  ThingSpeak.setField(7, pressure);
  
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
  if(tsens_value == 0 || isnan(tsens_value)){
    myStatus += String("Sensor de temperatura interna falhou\\");
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

//function Internal Temperature Sensor Initializer
void initTempSensor(){
  ESP_LOGI(TAG, "Install temperature sensor, expected temp ranger range: 10~50 ℃");
  temperature_sensor_config_t temp_sensor_config = TEMPERATURE_SENSOR_CONFIG_DEFAULT(10, 50);
  ESP_ERROR_CHECK(temperature_sensor_install(&temp_sensor_config, &temp_sensor));

  ESP_LOGI(TAG, "Enable temperature sensor");
  ESP_ERROR_CHECK(temperature_sensor_enable(temp_sensor));
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
