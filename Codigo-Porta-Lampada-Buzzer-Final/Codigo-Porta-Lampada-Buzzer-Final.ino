#include <Servo.h>
#include <SPI.h>
#include <UIPEthernet.h>
#include <utility/logging.h>
#include <PubSubClient.h>

const int portaLed = 8;
const int portaBotaoLed = 3;
const int portaBotaoPortao = 4;
const int portaMotorPortao = 6;
const int velocidadePortao = 5;
const int Buzzer = 5;
int valorBuzzer = 500;

int statusLed = LOW;
int statusBotaoLed = LOW;
int statusBotaoPortao = LOW;
int statusPortao = LOW;

Servo portao;

// Endereço fisico do arduino na rede
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xF1, 0x35 };
void callback(char *topic, byte *payload, unsigned int length);




EthernetClient ethClient;
// Cliente de conexão com o mqtt
PubSubClient client("m11.cloudmqtt.com", 10285, callback, ethClient);

// Função que será executada toda vez que o arduino receber uma mensagem dafila
void callback(char *topic, byte *payload, unsigned int length)   {
 int msg = atoi(payload);

 Serial.println(msg);
 Serial.println(topic);
 if (strcmp(topic, "Portao") == 0) {
   Serial.println("topic == Portao");
   if (msg == 1) {
     Serial.println("msg = 1 abre portao");
     abreFechaPortao(true);
     //acende lampada
     acendeApagaLed(portaLed, HIGH);
   }
   else {
     //apaga lampada
      Serial.println("msg = 0 fecha portao");
     abreFechaPortao(false);
     delay(2000);
     acendeApagaLed(portaLed, LOW);
   }

 }else{
   Serial.println("Nao entrou no IF");
   }
 

}

void setup()
{
 Serial.begin(9600);

 pinMode(portaLed, OUTPUT);
 pinMode(portaBotaoLed, INPUT);
 pinMode(portaBotaoPortao, INPUT);

  pinMode(Buzzer, OUTPUT);

 portao.attach(portaMotorPortao);
 Serial.println("Iniciando");
 // Inicializa a conexão na rede de internet
 Ethernet.begin(mac);

 // Faz a conexão no cloud com nome do dispositivo, usuário e senha respectivamente
 if (client.connect("arduino", "arduinonovo", "123"))
 {
   

   // Envia uma mensagem para o cloud no topic portao
  // client.publish("mensagem", 1);

   // Conectando nos topics para receber as mensagens
   client.subscribe("Portao");

   Serial.println("conectado Portao");
 } else {
 
   
   Serial.println("erro ao conectar");
 }
}

void loop()
{
 int estadoBotao = digitalRead(portaBotaoLed);
 int estadoBotaoPortao = digitalRead(portaBotaoPortao);

 verificaEstadoBotaoLed(estadoBotao);
 verificaEstadoBotaoPortao(estadoBotaoPortao);

 client.loop();
}

void verificaEstadoBotaoLed(int estado) {
 if (estado != statusBotaoLed) {
   if (estado == HIGH) {
     if (statusLed == HIGH) {
       acendeApagaLed(portaLed, LOW);
     } else {
       acendeApagaLed(portaLed, HIGH);
     }
   }
   statusBotaoLed = estado;
 }
}

void verificaEstadoBotaoPortao(int estado) {
 if (estado != statusBotaoPortao) {
   if (estado == HIGH) {
     if (statusPortao == HIGH) {
       abreFechaPortao(false);
     } else {
       abreFechaPortao(true);
     }
   }
   statusBotaoPortao = estado;
 }
}

void acendeApagaLed(int pino, int status) {
 digitalWrite(pino, status);
 statusLed = status;
}

void abreFechaPortao(bool abre) {
 if (abre) {
   for (int pos = 0; pos <= 90; pos++) {
     portao.write(pos);
     tone (Buzzer, valorBuzzer, 1000);
     delay(velocidadePortao);
   }
   statusPortao = HIGH;
 } else {
   for (int pos = 90; pos >= 0; pos--) {
     portao.write(pos);
     delay(velocidadePortao);
   }
   statusPortao = LOW;
 }
}
