#include <SigFox.h>
#include <ArduinoLowPower.h>


void setup() {
  Serial.begin(9600);
  while(!Serial){}

  if(!SigFox.begin()){
    Serial.println("Ha fallado algo!!");
    return;
    }

  delay(100);

  enviar("123456789012");

}


void loop(){}

void enviar(String msg){

  SigFox.status();//Limpia las interrupciones pendientes
  delay(100);
  Serial.println("Enviando...");

  SigFox.beginPacket();
  Serial.println("Empezando paquete...");
  SigFox.print(msg);
  Serial.println("Enviando " + msg);
  SigFox.endPacket();
  Serial.print("Hecho!!");

  SigFox.end();
  }
