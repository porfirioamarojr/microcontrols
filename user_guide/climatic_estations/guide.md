# Instruções básicas para reprodução do projeto

## Tipos de Estações

* [Arduino Estation](arduino_station.md) é uma estação do tipo fixa e que tem acesso a internet via cabo com o módulo Ethernet Shield. A escolha por repoduzir esta estação faz se necessário a instalação das seguintes bibliotecas com as respectivas versões:
  
  - Para a placa [Arduino Uno](https://www.arduino.cc/) utilize a lib ```Arduino AVR Boards by Arduino``` na versão __1.8.6__.
  - Para a [HttpClient](https://github.com/amcewen/HttpClient) utilize a lib ```HttpClient by Adrian McEwen <adrianm@mcqn.com>``` na versão __2.2.0__.
  - Para a [Ethernet](https://www.arduino.cc/) utilize a lib ```Ethernet by Various (see AUTHORS file for details)``` na versão __2.0.2__.
  - Para o sensor [Adafruit BMP085](https://github.com/adafruit/Adafruit-BMP085-Library) utilize a lib ```Adafruit BMP085 Library by Adafruit``` na versão __1.2.4__.

* [ESP32C3 Estation](esp32c3_station.md) é uma estação do tipo móvel que se conecta a internet via WiFi e pode ser transportada para outros locais sem que exista a necessidade de cabos para isso. A escolha por repoduzir esta estação faz se necessário a instalação das seguintes bibliotecas com as respectivas versões
  
  - Para a placa [Esp32c3](https://github.com/espressif/arduino-esp32) utilize a lib ```esp32 by Espressif Systems``` na versão __3.0.0-alpha3__.
  - Para o sensor [Adafruit BMP280](https://github.com/adafruit/Adafruit_BMP280_Library) utilize a lib ```Adafruit BMP280 Library by Adafruit``` na versão __2.6.8__.
  - Para o [SPI](https://github.com/adafruit/Adafruit_BusIO) utilize a lib ```Adafruit BusyIO by Adafruit``` na versão __1.15.0__.
  - Para o [WiFi](https://www.arduino.cc/reference/en/libraries/wifi/) utilize a lib ```WiFi by Arduino``` na versão __1.2.7__.
  
* [ESP8266 Estation](esp8266_station.md) também é uma estação do tipo móvel que se conecta a internet via WiFi e pode ser transportada para outros locais sem que exista a necessidade de cabos para isso. A escolha por repoduzir esta estação faz se necessário a instalação das seguintes bibliotecas com as respectivas versões
  
  - Para a placa [Esp8266](https://github.com/esp8266/Arduino) utilize a lib ```esp8266 by ESP8266 Community``` na versão __3.1.2__.
  - Para o sensor [Adafruit BMP280](https://github.com/adafruit/Adafruit_BMP280_Library) utilize a lib ```Adafruit BMP280 Library by Adafruit``` na versão __2.6.8__.
  - Para o [SPI](https://github.com/adafruit/Adafruit_BusIO) utilize a lib ```Adafruit BusyIO by Adafruit``` na versão __1.15.0__.
  - Para o [ESP8266WiFi](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi) utilize a lib ```esp8266 by ESP8266 Community``` na versão __3.1.2__.

## Bibliotecas Padrão

Antes de escolher o tipo da estação para qualquer uma delas que será resproduzida deverá ser feita a instalação das bibliotecas a seguir com as respectivas versões:

* Para o [ThingSpeak](https://thingspeak.com/) utilize a lib ```ThingSpeak by MathWorks <support@thingspeak.com>``` na versão __2.0.1__.
* Para o sensor [DHT 11/22](https://github.com/adafruit/DHT-sensor-library)
 utilize a lib ```DHT sensor library by Adafruit``` na versão __1.4.6__.

__Obsrvação__ a lib do WiFi da Esp8266 já deve vir inclusa quando se instala a lib da placa.