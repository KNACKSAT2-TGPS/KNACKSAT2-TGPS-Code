// THIS PROGRAM USE FOR SETUP RECENT FILE START NAME.

// CODE BY PONGSAPAT LAKROD

// =====================<<< LIBRARY >>>====================
// LIBRARY IN MASTER SIMULATION 
#include <EEPROM.h>

uint16_t INDEX       =  0 ;
uint16_t VALUE       =  0 ;
uint16_t AFTER_VALUE =  0 ;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);

  delay(5000);   // DELAY FOR WATCH THAT MATER CAN SERIAL COMMUNICATON.
  
  Serial.println("=============<<< SETUP START RECENT FILE >>>==============");
  Serial.println("KEYWORD : INDEX/VALUE                                     ");
  Serial.println("NOTE    : AT INDEX 0-511 USE 1-512 INSTEAD.               ");
  Serial.println("==========================================================");

}

void loop() {

  if(Serial.available() > 0) 
  {
    INDEX = Serial.parseInt();
    Serial.read();
    VALUE = Serial.parseInt();
  }

  if(INDEX > 0) 
  {
    INDEX = INDEX - 1 ;
    Serial.println("=============================="); 
    Serial.println("INPUT INDEX : " + String(INDEX));
    Serial.println("INPUT VALUE : " + String(VALUE));

    EEPROM.put(INDEX, VALUE);

    if (EEPROM.commit())
    {
      Serial.println("FLASH MEMORY SUCCESSFULLY COMMITTED");
    }
    else
    {
      Serial.println("ERROR! FLASH MEMORY COMMIT FALIED");
    }

    Serial.println(">>> INSIDE AFTER SAVE FLASH MEMORY.");

    AFTER_VALUE = EEPROM.get(INDEX, VALUE);

    Serial.println("INDEX : " + String(INDEX));
    Serial.println("VALUE : " + String(AFTER_VALUE));
    Serial.println("==============================");

  }

}
