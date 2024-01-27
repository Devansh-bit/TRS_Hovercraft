
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>
#include <Servo.h>

Servo ESC; 

RF24 radio(7, 8);  // CE, CSN
const byte address[6] = "00001";

void setupRadio(){
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void setup()
{
  Serial.begin(9600);
  ESC.attach(3,1000,2000);
  ESC.write(0);
  setupRadio();
  delay(5000);
}

struct Message{
  int v_thrust;
  int h_thrust;
  int rudder;  
};

void loop()
{
  struct Message message; 
  if (radio.available())
  {
    radio.read(&message, sizeof(message));
    //Serial.println(message.v_thrust);
    Serial.println();
        Serial.println("_________");
    Serial.println("_________");

    Serial.println(message.h_thrust);
    Serial.println(message.rudder);
    Serial.println("_________");
    Serial.println("_________");
    Serial.println();
  }
  int potValue = map(message.h_thrust, 0, 1023, 0, 180);
  ESC.write(potValue);
  Serial.println(message.h_thrust);
}
