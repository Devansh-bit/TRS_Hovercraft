#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>

#define joyX A0
#define joyY A1
RF24 radio(7, 8);  // CE, CSN
const byte address[6] = "00001";

struct Message{
  int v_thrust;
  int h_thrust;
  int rudder;  
};

void setup()
{
  Serial.begin(9600);
  radio.begin();  
  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop()
{
  int h_thrust = (analogRead(joyX)-514)*2;
  if (h_thrust < 0) h_thrust = 0;
  int rudder = analogRead(joyY);
  struct Message message = {1023, h_thrust, rudder};
  radio.write(&message, sizeof(message));
}
