#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

  const int sensorPin = A0;
  int sensorValue;
  float voltage;
  float temperature;

void setup()
{
    Serial.begin(9600);    // Debugging only
    pinMode(sensorPin, INPUT);
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    sensorValue = analogRead(sensorPin);
    voltage = sensorValue * (5000/1024);
    temperature = (voltage/10);
    char msg[5];
    //char symb = 'C';
    dtostrf(temperature, 5, 1, msg);
    //append(msg, symb);
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(1000);
}
//Funksjon for å legge til tekst til msg.
void append(char* s, char c) {
  int len = strlen(s);
  s[len] = c;
  s[len+1] = '\0';
}
