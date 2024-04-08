# Estação ESP32C3

## Material para Reprodução

* Esp32c3
* Protoboard
* Fonte 12v
* Cabo Micro A/B
* Jumpers
* Sensor DHT11
* Sensor BMP280
* Sensor LDR

OBS: O cabo micro A/B, em resumo cabo de celular antigo, que deve suportar a transferência de dados, caso contário não conseguirá subir o código para a placa, e a fonte de celular na maioria dos casos serve.

## Esquema de Conexões

xxxxxxxxx

## Intruções para execução

Para reproduzir corretamente o exemplo desta estação selecione o modelo da placa clicando em ```Tools/Ferramentas```, logo após ache a opção ```Board/Placa``` e procure ```esp32```, em seguida clique na opção ```ESP32C3 Dev Module```.

Primeiramente troque as variáveis no arquivo ```Secrets.h``` e defina corretamente as credênciais que serão utilizadas para se conectar ao __ThingSpeak__ e a __Rede__.

Para o exemplo em questão utilize os códigos do [seguinte diretório](/esp32c3/esp32c3_station/). 

Em seguida faça upload do código para a Esp32c3, caso tudo corra bem em poucos instantes será possível visualizar o envio dos dados capturados tanto no __Monitor Serial__ do Arduino-IDE quanto no ThingSpeak.

## Observações

Caso haja algum problema verifique as versões das libs instaladas e verifique as conexões dos sensores.

Se estiver tentando subir o código para placa pelo Linux, ao conectar a placa não esqueça de dar a permissão ```sudo chmod 777 /dev/ttyUSB0```. 

