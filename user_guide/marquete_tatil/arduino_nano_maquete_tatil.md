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
* 1 Resistores de 1kΩ
* Cartão MicroSD

OBS: O cabo USB Mini pode ser encontrado também em câmeras antigas, e a fonte de celular na maioria dos casos serve.

## Esquema de Conexões

![Esquema elétrico da Maquete](/user_guide/assets/arduino_nano_maquete_tatil.png)

Observe as conexões na imagem acima e veja que para reproduzir o esquema elétrico da maquete corretamente, as conexões tem que estar de acordo com a imagem. O Ultrason deverá ser conectado nas portas __D9 = Trig -> fio roxo__ e __D12 = Echo -> fio amarelo__, O Módulo MP3 deverá usar as portas __TX = D11 -> fio amarelo__ e __RX = D10 -> fio azul__ da placa. Já os Push Buttons serão conectados da porta __D8__ a __D2__, e também na porta analógia __A0 -> fio marrom claro__, __GND = terra -> fio preto__, __VCC = 5v -> fio vermelho__.

## Instrução de formatação do SD Card

Para conseguir utilizar o módulo __MP3__ corretamente é necessário fazer a formatação do __MicroSD__ para o tipo de sistema de arquivos ```FAT32``` e com o nome da mídia em minúsculo, tudo junto sem acentos e sem espaços em branco, depois de formatado você deverá criar um diretório com o seguinte padrão de nome ```01, 02, ..., 99``` e dentro desse diretório os arquivos de mídia deverão ser do tipo ```.mp3```, e nomeados no seguinte padrão ```001.mp3, 002.mp3, ..., 999.mp3``` dessa forma será possível reproduzir todos os arquivos.

Veja o exemplo abaixo:

├── meu_sdcard<br>
│ &nbsp; &nbsp; &nbsp; └── 01 <br>
│ &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ├── 001.mp3<br>
│ &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ├── 002.mp3<br>
│ &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; └── 003.mp3<br>

## Intruções para Execução

Para reproduzir corretamente o exemplo desta Maquete selecione o modelo correto da placa clicando em ```Tools/Ferramentas```, logo após ache a opção ```Board/Placa``` e procure ```Arduino AVR Boards```, em seguida clique na opção ```Arduino Nano```, mas não é só isso a depender da versão de sua placa Nano será necessário que se escolha também o ```Processor``` dela, que neste projeto foi utilizado o ```ATmega328P (Old Bootloader)```, e o ```Programmer``` no ```Arduino as ISP (ATmega32U4)```.

Para o exemplo em questão utilize os códigos do [seguinte diretório](/arduino_nano/arduino_nano_maquete_tatil/). 

Em seguida coloque o SD Card devidamente formatado com os arquivos de áudio no módulo MP3, e faça upload do código para o Arduino Nano, caso tudo corra bem em poucos instantes será possível visualizar que deu certo no __Monitor Serial__ do Arduino-IDE e ao testar o projeto.

## Observações

Caso haja algum problema verifique as versões das libs instaladas e verifique as conexões dos sensores.

Se estiver tentando subir o código para placa pelo Linux, ao conectar a placa não esqueça de dar a permissão ```sudo chmod 777 /dev/ttyUSB0```. 
