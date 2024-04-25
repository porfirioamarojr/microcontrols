#include <SPI.h>
#include <Ultrasonic.h>   
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

const short int triggerPin = 9; //Pino 9 envia o pulso para gerar o echo
const short int echoPin = 12; //Pino 12 recebe o pulso do echo   
#define button1 A0
#define button2 2
#define button3 3
#define button4 4
#define button5 5
#define button6 6
#define button7 7
#define button8 8
const short int pinRx = 10; //informe aqui qual porta Rx está sendo utilizada.
const short int pinTx = 11; //informe aqui qual porta Tx está sendo utilizada.

Ultrasonic ultrasonic(triggerPin, echoPin);

SoftwareSerial playerMP3Serial(pinRx, pinTx);
DFRobotDFPlayerMini playerMP3;
short int volumeMP3 = 30; //definimos o volume, entre 0 e 30.
#define DEBUG

void setup() {
  Serial.begin(9600);
  playerMP3Serial.begin(9600);

  pinMode(triggerPin, OUTPUT);  // define o pino triger como saida.   
  pinMode(echoPin, INPUT);  // define o pino echo como entrada.   
  pinMode(button1, INPUT_PULLUP); //declaramos Button como INPUT.
  pinMode(button2, INPUT_PULLUP); //declaramos Button como INPUT_PULLUP.
  pinMode(button3, INPUT_PULLUP); //declaramos Button como INPUT_PULLUP.
  pinMode(button4, INPUT_PULLUP); //declaramos Button como INPUT_PULLUP.
  pinMode(button5, INPUT_PULLUP); //declaramos Button como INPUT_PULLUP.
  pinMode(button6, INPUT_PULLUP); //declaramos Button como INPUT_PULLUP.
  pinMode(button7, INPUT_PULLUP); //declaramos Button como INPUT_PULLUP.
  pinMode(button8, INPUT_PULLUP); //declaramos Button como INPUT_PULLUP.

  Serial.println();
  Serial.println(F("Iniciando DFPlayer ... (Espere 3~5 segundos)"));
  if (!playerMP3.begin(playerMP3Serial)) {  // COMUNICAÇÃO REALIZADA VIA SOFTWARE SERIAL
    Serial.println(F("Falha:"));
    Serial.println(F("1.conexões!"));
    Serial.println(F("2.cheque o cartão SD!"));
    while(true){
      delay(0);
    }
  }
  Serial.println(F("DFPlayer iniciado!"));
  playerMP3.volume(volumeMP3);
  playerMP3.EQ(0); 
  
  #ifdef DEBUG
    Serial.println("o Setup acabou");
  #endif

}

void loop() {
  int distancia;

  distancia = (ultrasonic.read()); //exibido no computador qual a medicao do sensor. Essa função faz todo os calculos e fornece as respostas   
  if (distancia > 10 && distancia < 15){
    playerMP3.playFolder(1, 5);
    Serial.println("Tocando pasta 01, musica 002 -SENSOR-");
    //Serial.println("Estou funcionando!!!");
    delay(1000);
  }/*else
    Serial.println("Estou inativo :)");*/

  if (digitalRead(button1) == false){
    playerMP3.playFolder(1, 8);
    Serial.println("Tocando pasta 01, musica 001 button1");
    delay(1000);
  }

  if (digitalRead(button2) == false){
    playerMP3.playFolder(1, 5);
    Serial.println("Tocando pasta 01, musica 002 button2");
    delay(1000);
  }
  if (digitalRead(button3) == false){
    playerMP3.playFolder(1, 1);
    Serial.println("Tocando pasta 01, musica 001 button3");
    delay(1000);
  }
  if (digitalRead(button4) == false){
    playerMP3.playFolder(1, 2);
    Serial.println("Tocando pasta 01, musica 002 button4");
    delay(1000);
  }
  if (digitalRead(button5) == false){
    playerMP3.playFolder(1, 7);
    Serial.println("Tocando pasta 01, musica 001 button5");
    delay(1000);
  }
  if (digitalRead(button6) == false){
    playerMP3.playFolder(1, 2);
    Serial.println("Tocando pasta 01, musica 002 button6");
    delay(1000);
  }
  if (digitalRead(button7) == false){
    playerMP3.playFolder(1, 1);
    Serial.println("Tocando pasta 01, musica 001 button7");
    delay(1000);
  }
  if (digitalRead(button8) == false){
    playerMP3.playFolder(1, 2);
    Serial.println("Tocando pasta 01, musica 002 button8");
    delay(1000);
  }
}
