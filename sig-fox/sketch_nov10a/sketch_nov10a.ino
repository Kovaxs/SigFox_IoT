#include <Ultrasonic.h>

#include <RBD_LightSensor.h>

#include <SigFox.h>
#include <ArduinoLowPower.h>
#include <SimpleDHT.h>

RBD::LightSensor light_sensor(A2);
int pinDHT11 = A1;
SimpleDHT11 dht11(pinDHT11);
// int triggerPin = A2;
// int echoPin = 2;
// UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);
// Ultrasonic ultrasonic(triggerPin, echoPin);


void setup() {
  Serial.begin(9600);
  while(!Serial){}

  if(!SigFox.begin()){
    Serial.println("Ha fallado algo!!");
    return;
    }

  delay(100);

  // enviar("123456789012");

}

void loop() {
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
  Serial.println(" ");
  Serial.println("=================================");
  Serial.println("Sample SR04...");
  Serial.println(light_sensor.getInversePercentValue ());
  // double distance = distanceSensor.measureDistanceCm();
  // Serial.print(ultrasonic.read(CM)); Serial.print(" cm");
  Serial.println(" ");
  // delay(500);
  // DHT11 sampling rate is 1HZ.
  delay(1500);
}
// void loop(){}




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
