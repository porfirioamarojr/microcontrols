# Estação ESP8266

## Material para Reprodução

* Esp8266
* Protoboard
* Fonte 12v
* Cabo Micro A/B
* Jumpers
* Sensor DHT22
* Sensor BMP280
* Sensor LDR
* 2 Resistores de 10kΩ

OBS: O cabo micro A/B, em resumo cabo de celular antigo, que deve suportar a transferência de dados, caso contário não conseguirá subir o código para a placa, e a fonte de celular na maioria dos casos serve.

## Esquema de Conexões

![Esquema elétrico da estação](/user_guide/assets/esp8266_station.png)

Observe as conexões na imagem acima e veja que para reproduzir a estação corretamente, as conecões tem que estar exatamente de acordo com o esquema. O BMP280 deverá ser conectado nas seguintes portas __SDA = D2 -> fio roxo, SCL = D1 -> fio azul, SDO = D5 -> fio marrom, CSB = D3 -> fio branco__. O LDR devera usar a porta analógica __A0 -> fio amarelo__ da placa. Já o DHT22 deverá usar a porta digital __D7 -> fio amarelo__, __GND = terra -> fio preto__, __VCC = 5v -> fio vermelho__.

## Intruções para Execução

Para reproduzir corretamente o exemplo desta estação selecione o modelo da placa clicando em ```Tools/Ferramentas```, logo após ache a opção ```Board/Placa``` e procure ```esp8266```, em seguida clique na opção ```NodeMCU 1.0 (ESP-12E Module)```.

Primeiramente troque as variáveis no arquivo ```Secrets.h``` e defina corretamente as credênciais que serão utilizadas para se conectar ao __ThingSpeak__ e a __Rede__.

Para o exemplo em questão utilize os códigos do [seguinte diretório](/esp8266/esp8266_station/). 

Em seguida faça upload do código para a Esp8266, caso tudo corra bem em poucos instantes será possível visualizar o envio dos dados capturados tanto no __Monitor Serial__ do Arduino-IDE quanto no ThingSpeak.

## Observações

Caso haja algum problema verifique as versões das libs instaladas e verifique as conexões dos sensores.

Se estiver tentando subir o código para placa pelo Linux, ao conectar a placa não esqueça de dar a permissão ```sudo chmod 777 /dev/ttyUSB0```. 

