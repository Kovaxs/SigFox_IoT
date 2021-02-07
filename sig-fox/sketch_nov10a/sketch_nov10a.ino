#include <SigFox.h>
#include <RBD_LightSensor.h>
#include <ArduinoLowPower.h>
#include <SimpleDHT.h>
// #include <Ultrasonic.h>

RBD::LightSensor light_sensor(A2);
int pinDHT11 = A1;
SimpleDHT11 dht11(pinDHT11);
// int triggerPin = A2;
// int echoPin = 2;
// UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);
// Ultrasonic ultrasonic(triggerPin, echoPin);
typedef struct
{
  uint8_t temp;
  uint8_t hum;
  uint8_t phot;
  uint8_t batt;

} SigfoxMessage;

void setup() {
  Serial.begin(9600);
  while(!Serial){}

  if(!SigFox.begin()){
    Serial.println("Ha fallado algo!!");
    return;
    }

  delay(100);

}

void loop() {
  SigfoxMessage msg;
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
  msg.temp = (uint8_t)temperature;
  Serial.print(msg.temp); Serial.print(" C, "); 
  msg.hum = (uint8_t)humidity;
  Serial.print(msg.hum); Serial.println(" H");
 
  Serial.println(" ");
  Serial.println("Sample Photo...");
  msg.phot = (uint8_t)light_sensor.getInversePercentValue ();
  Serial.println(msg.phot); Serial.println(" %");
  // Serial.print(ultrasonic.read(CM)); Serial.print(" cm");
  Serial.println(" ");
  msg.batt = (uint8_t)5;
  Serial.println(" ");
  Serial.println(msg.batt); Serial.println(" V");
  // delay(1500);
  enviar(msg);

  delay(1000 * 10 * 60);
}

void enviar(SigfoxMessage msg){

  SigFox.begin();
  SigFox.status();//Limpia las interrupciones pendientes
  delay(100);
  Serial.println("Enviando...");

  SigFox.beginPacket();
  Serial.println("Empezando paquete...");
  SigFox.write((uint8_t*)&msg, sizeof(msg));
  SigFox.debug();
  Serial.println("Enviando... ");
  SigFox.endPacket(false);
  Serial.print("Hecho!!");

  SigFox.end();
  }
