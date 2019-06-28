#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#include <LiquidCrystal.h>

RH_ASK driver;

LiquidCrystal lcd(12, 10, 5, 4, 3, 2);

void setup()
{
    Serial.begin(9600);  // Debugging only
    lcd.begin(16,2);
    lcd.print("Hello World!");
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    uint8_t buf[5];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      // Message with a good checksum received, dump it.
      buf[strlen(buf) - 1] = '\0';
      Serial.print("Message: ");
      Serial.println((char*)buf);
      lcd.clear();
      lcd.print("Temperatur:");
      lcd.setCursor(0,1);
      lcd.print((char*)buf);
      lcd.print(" C");
      lcd.setCursor(0,0);        
    }
}
