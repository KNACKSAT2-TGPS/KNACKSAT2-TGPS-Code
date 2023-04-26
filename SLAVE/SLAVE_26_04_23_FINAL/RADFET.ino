//
//
//========================<<<READ_RADFET>>>========================

// READ_RADFET   : READ ANALOG VALUE FROM RADFET SENSOR. (RESOLUTION 12 BITS)
// S             : CHANNEL 0 to 7.
// RADFET_ARRAY  : FOR SAVE TEMPORARY DATA.

void READ_RADFET(uint8_t S, uint16_t RADFET_ARRAY[16])
{
  READ_TIME = 0;
  int i = 0;
  digitalWrite(S2 , S >> 2 & 1); digitalWrite(S1 , S >> 1 & 1); digitalWrite(S0 , S & 1);
  while (i < 16) {
    if (STATE_BREAK != pow(2,S))break;
    if (millis() - READ_TIME >= 1000) {
      digitalWrite(S2 , S >> 2 & 1); digitalWrite(S1 , S >> 1 & 1); digitalWrite(S0 , S & 1);  RADFET_ARRAY[i] = analogRead(A);
      i++;
      READ_TIME = millis();
    }
  }
}
