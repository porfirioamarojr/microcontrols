# Estação ESP32C3

## Material para Reprodução

* Arduino Nano
* Protoboard
* Fonte 12v
* Cabo USB Mini
* Jumpers
* Sensor Ultrason
* Módulo MP3
* 8 Push Buttons
* 2 Resistores de 1kΩ
* Cartão MicroSD

OBS: O cabo USB Mini pode ser encontrado também em câmeras antigas, e a fonte de celular na maioria dos casos serve.

## Esquema de Conexões

![Esquema elétrico da Maquete](/user_guide/assets/arduino_nano_maquete_tatil.png)

Observe as conexões na imagem acima e veja que para reproduzir o esquema elétrico da maquete corretamente, as conexões tem que estar de acordo com a imagem. O Ultrason deverá ser conectado nas portas __D9 = Trig -> fio roxo__ e __D12 = Echo -> fio amarelo__, O Módulo MP3 deverá usar as portas __TX = D11 -> fio amarelo__ e __RX = D10 -> fio azul__ da placa. Já os Push Buttons serão conectados da porta __D8__ a __D2__, e também a __D13 -> fio marrom claro__ sendo importante resaltar que esta deverá conter este resitor de 1kΩ na conexão ao gnd, __GND = terra -> fio preto__, __VCC = 5v -> fio vermelho__.

## Intruções para Execução

Para reproduzir corretamente o exemplo desta Maquete selecione o modelo correto da placa clicando em ```Tools/Ferramentas```, logo após ache a opção ```Board/Placa``` e procure ```Arduino AVR Boards```, em seguida clique na opção ```Arduino Nano```, mas não é só isso a depender da versão de sua placa Nano será necessário que se escolha também o ```Processor``` dela, que neste projeto foi utilizado o ```ATmega328P (Old Bootloader)```, e o ```Programmer``` no ```Arduino as ISP (ATmega32U4)```.

Para o exemplo em questão utilize os códigos do [seguinte diretório](/arduino_nano/arduino_nano_maquete_tatil/). 

Em seguida faça upload do código para o Arduino Nano, caso tudo corra bem em poucos instantes será possível visualizar que deu certo no __Monitor Serial__ do Arduino-IDE e ao testar o projeto.

## Observações

Caso haja algum problema verifique as versões das libs instaladas e verifique as conexões dos sensores.

Se estiver tentando subir o código para placa pelo Linux, ao conectar a placa não esqueça de dar a permissão ```sudo chmod 777 /dev/ttyUSB0```. 
