#include <Servo.h>
#define SERVO 6 // Porta Digital 6 PWM

Servo portao; // Variável Servo
int pos; // Posição Servo

const int pinoBotaoPortao = 4; //botao portao
int estadoBotaoPortao = LOW;
int ultimoEstadoBotaoPortao = LOW;

const int pinoLed = 8;  //
const int pinoBotaoLed = 3;  //botao led
int estadoBotaoLed = LOW;
int ultimoEstadoBotaoLed = LOW;


void setup ()
{
      portao.attach(SERVO);
      Serial.begin(9600);
      portao.write(0); // Inicia motor posição zero
      pinMode(pinoBotaoPortao, INPUT);
      pinMode(pinoLed, OUTPUT);
      pinMode(pinoBotaoLed, INPUT);
    }
    
    void loop()
    {
      estadoBotaoPortao = digitalRead(pinoBotaoPortao);
      if ( estadoBotaoPortao == HIGH ) {
        if (ultimoEstadoBotaoPortao == HIGH) {
          Serial.println("FechaPortao");
          FechaPortao();
    
        } else {
          Serial.println("AbrePortao");
          AbrePortao();
    
        }
        if (ultimoEstadoBotaoPortao == HIGH) {
    
          ultimoEstadoBotaoPortao = LOW;
        }
        else {
    
          ultimoEstadoBotaoPortao = HIGH;
        }
        delay(1000);
      }
      else {
        Serial.println("ultimo else");
        //delay(1000);
      }
    
      /// controle led
      estadoBotaoLed = digitalRead (pinoBotaoLed);
      Serial.println("circuito led");
      if (estadoBotaoLed == HIGH) {
          Serial.println("estadoBotaoLed == HIGH");
          if (ultimoEstadoBotaoLed == HIGH) {
          digitalWrite(pinoLed, LOW);
        } else {
          digitalWrite(pinoLed, HIGH);
        }
    
        if (ultimoEstadoBotaoLed == HIGH) {
          ultimoEstadoBotaoLed = LOW;
    
        } else {
          ultimoEstadoBotaoLed = HIGH;
        }
        Serial.println("utlimo else do led");
        delay(1000);
    
      }
     
    }
    
    void AbrePortao() {
      portao.write(110);
      delay(15);
    }
    
    void FechaPortao() {
      portao.write(20);
      delay(15);
    }

