# Estação ESP32C3

## Material para Reprodução

* Arduino Uno
* Ethernet Shield
* Protoboard
* Fonte 12v
* Cabo USB-B
* Jumpers
* Sensor DHT22
* Sensor BMP180
* Sensor LDR
* 2 Resistores de 10kΩ

OBS: O cabo que deverá ser usado é o do própio arduino, ou um cabo de impressora, e a fonte de um celular na maioria dos casos serve.


## Esquema de Conexões

![Esquema elétrico da estação](/user_guide/assets/arduino_station.png)

Observe as conexões na imagem acima e veja que para reproduzir a estação corretamente, as conecões tem que estar exatamente de acordo com o esquema. O BMP180 deverá ser conectado nas seguintes portas __SDA = A4 -> fio azul, SCL = A5 -> fio roxo__. O LDR devera usar a porta analógica __A0 -> fio amarelo__ da placa. Já o DHT22 deverá usar a porta digital __D7 -> fio amarelo__, __GND = terra -> fio preto__, __VCC = 5v -> fio vermelho__.
****
## Intruções para execução

Para reproduzir corretamente o exemplo desta estação selecione o modelo da placa clicando em ```Tools/Ferramentas```, logo após ache a opção ```Board/Placa``` e procure ```Arduino AVR Boards```, em seguida clique na opção ```Arduino Uno```.

Primeiramente troque as variáveis no arquivo ```Secrets.h``` e defina corretamente as credênciais que serão utilizadas para se conectar ao __ThingSpeak__.

Para o exemplo em questão utilize os códigos do [seguinte diretório](/arduino_uno/arduino_station/). 

Em seguida faça upload do código para a Arduino Uno, caso tudo corra bem em poucos instantes será possível visualizar o envio dos dados capturados tanto no __Monitor Serial__ do Arduino-IDE quanto no ThingSpeak.

## Observações

Caso haja algum problema verifique as versões das libs instaladas e verifique as conexões dos sensores.

Se estiver tentando subir o código para placa pelo Linux, ao conectar a placa não esqueça de dar a permissão para porta com ```sudo chmod 777 /dev/ttyUSB0```. 

