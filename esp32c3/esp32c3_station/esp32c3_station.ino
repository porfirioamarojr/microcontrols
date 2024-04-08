#include <WiFi.h>
#include "Secret.h"
#include "ThingSpeak.h"
#include "driver/temp_sensor.h"
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

#define DHTTYPE DHT22 // defining model sensor
const int DHTPIN = 7;     // defining pin sensor
const char * myWriteAPIKey = "O93U7MP5N03056B0";
const char * myReadAPIKey = "YHK1465I8DMSXJUJ";
unsigned long myChannelNumber = 2311546;

Adafruit_BMP085 bmp;
WiFiClient client;

DHT dht(DHTPIN, DHTTYPE);

void initTempSensor();
void splitString(String str, char delimiter, String substrings[], int maxSize);

int response, fail = 0;

void setup() {
  Serial.begin(115200);

  while (!Serial) { }
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

  bmp.begin();
  if (!bmp.begin()) {
	  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	  while (1) {}
  }
  
  initTempSensor();//internal temperature sensor
  ThingSpeak.begin(client);
  dht.begin();

  //Code Block for update counter of errs 
  response = ThingSpeak.readMultipleFields(myChannelNumber, myReadAPIKey);
  if(response == 200){
    Serial.println("Get of channel update successful.");
  
  }else{
    Serial.println("Problem in get of channel. HTTP error code " + String(response));
  }
  
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
  float result = 0; // result is the internal temperature
  temp_sensor_read_celsius(&result);
  
  Serial.print(result);
  Serial.print("\n");
  float temperature = dht.readTemperature(); // celcius
  Serial.print(temperature);
  Serial.print("\n");
  float humidity = dht.readHumidity();
  Serial.print(humidity);
  Serial.print("\n");
  int ldr_value = analogRead(A4);
  //int inverted_ldr_value = 1023 - sensor_ldr;
  Serial.print(ldr_value);
  Serial.print("\n");
  int pressuresealevel = bmp.readSealevelPressure();
  Serial.println(pressuresealevel);
  float height = bmp.readAltitude();
  Serial.print(height);
  Serial.print("\n");
  float pressure = bmp.readPressure();
  Serial.print(pressure);
  Serial.print("\n");
  float temperature_bmp = bmp.readTemperature();
  Serial.print(temperature_bmp);
  Serial.print("\n");

  ThingSpeak.setField(1, humidity);
  ThingSpeak.setField(2, temperature);
  ThingSpeak.setField(3, ldr_value);
  ThingSpeak.setField(4, result);
  ThingSpeak.setField(5, temperature_bmp);
  ThingSpeak.setField(6, height);
  ThingSpeak.setField(7, pressure);
  
  //logic for log of status sensors
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
  if(result == 0 || isnan(result)){
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
  
  response = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(response == 200){
    Serial.println("Channel update successful.");
  
  }else{
    Serial.println("Problem updating channel. HTTP error code " + String(response));
  
  }

  delay(15000);

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.disconnect();
    WiFi.reconnect();
    delay(100);
  }
}

//Apenas 
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

//função para pegar a temperatura interna da placa
void initTempSensor(){
    temp_sensor_config_t temp_sensor = TSENS_CONFIG_DEFAULT();
    temp_sensor.dac_offset = TSENS_DAC_L2;  // TSENS_DAC_L2 is default; L4(-40°C ~ 20°C), L2(-10°C ~ 80°C), L1(20°C ~ 100°C), L0(50°C ~ 125°C)
    temp_sensor_set_config(temp_sensor);
    temp_sensor_start();
}

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
