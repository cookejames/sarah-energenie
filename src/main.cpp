#define VERSION "1"
#include "SarahHome.h"
#include <RCSwitch.h>

SarahHome sarahHome("switches");

#define RC_PIN 2
RCSwitch energenie = RCSwitch();

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Received ");

  char code[length+1];
  for (int i=0; i<length; i++) {
    code[i]= (char)payload[i];
  }
  code[length] = '\0';
  Serial.println(code);

  energenie.send(atoi(code), 24);
}


void setup() {
  Serial.begin(9600);
  sarahHome.setup(VERSION);

  sarahHome.mqttClient.subscribe("switches/commands");
  sarahHome.mqttClient.setCallback(mqttCallback);

  energenie.enableTransmit(RC_PIN);
}

void loop() {
  sarahHome.loop();
}
