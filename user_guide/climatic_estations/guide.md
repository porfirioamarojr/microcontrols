# Instruções para reprodução do projeto

## Tipos de Estações

* [Arduino Estation](arduino_estation.md) é uma estação do tipo fixa e que tem acesso a internet via cabo com o módulo Ethernet Shield
<br>

* [ESP32C3 Estation](esp32c3_estation.md) é uma estação do tipo móvel que se conecta a internet via WiFi e pode ser transportada para outros locais sem que exista a necessidade de cabos para isso.

## Informações Gerais

Antes de escolher qual tipo de estação que será resproduzida é necessário que seja feita a instalação de algumas bibliotecas com as respectivas versões:

* Para o [ThingSpeak](https://thingspeak.com/) utilize a lib ```ThingSpeak by MathWorks <support@thingspeak.com>``` na versão __2.0.1__.
* Para o sensor [Adafruit BMP085](https://github.com/adafruit/Adafruit-BMP085-Library)
utilize a lib ```Adafruit BMP0850 Library by Adafruit``` na versão __1.2.4__.
* Para a placa [Esp32c3](https://github.com/espressif/arduino-esp32) utilize a lib ```esp32 by Espressif Systems``` na versão __3.0.0-alpha3__.
* Para o sensor [DHT 11/22](https://github.com/adafruit/DHT-sensor-library)
 utilize a lib ```DHT sensor library by Adafruit``` na versão __1.4.6__.
* Para o sensor [Adafruit BMP280](https://github.com/adafruit/Adafruit_BMP280_Library) utilize a lib ```Adafruit BMP280 Library by Adafruit``` na versão __2.6.8__.
* Para a placa [Arduino Uno](https://www.arduino.cc/) utilize a lib ```Arduino AVR Boards by Arduino``` na versão __1.8.6__.
* Para a [HttpClient](https://github.com/amcewen/HttpClient) utilize a lib ```HttpClient by Adrian McEwen <adrianm@mcqn.com>``` na versão __2.2.0__.
* Para a [Ethernet](https://www.arduino.cc/) utilize a lib ```Ethernet by Various (see AUTHORS file for details)``` na versão __2.0.2__.