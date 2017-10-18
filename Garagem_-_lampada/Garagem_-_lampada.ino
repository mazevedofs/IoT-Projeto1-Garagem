const int pinoLed = 8;
const int pinoBotao = 3;
int estadoBotao = LOW;
int ultimoEstadoBotao = LOW;

void setup() {
  pinMode(pinoLed, OUTPUT);
  pinMode(pinoBotao, INPUT);
  Serial.begin(9600);
}

void loop() {
  estadoBotao = digitalRead (pinoBotao);
  if (estadoBotao == HIGH) {
//    Serial.println("HIGH");
    if (ultimoEstadoBotao == HIGH) {
      digitalWrite(pinoLed, LOW);
    } else {
      digitalWrite(pinoLed, HIGH);
    }

    if (ultimoEstadoBotao == HIGH) {
      ultimoEstadoBotao = LOW;

    } else {
      ultimoEstadoBotao = HIGH;
    }

    delay(1000);

  }

}
