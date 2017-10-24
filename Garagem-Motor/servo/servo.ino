#include <Servo.h>
#define SERVO 6 // Porta Digital 6 PWM

Servo portao; // Variável Servo
int pos; // Posição Servo

void setup ()
{
  portao.attach(SERVO);
  Serial.begin(9600);
  portao.write(0); // Inicia motor posição zero


}

void loop()
{

  AbrePortao();


}

void AbrePortao() {
  for (pos = 0; pos < 90; pos++)
  {
    portao.write(pos);
    delay(15);
  }

  delay(1000);

  void FechaPortao();

  for (pos = 90; pos >= 0; pos--)
  {
    portao.write(pos);
    delay(15);
  }
}
