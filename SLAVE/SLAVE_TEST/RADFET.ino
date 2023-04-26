//
//
//=========================<<<MULTIPLEX>>>=========================

// MULTIPLEX     : READ ANALOG VALUE FROM RADFET SENSOR.
// A0-A7         : ANALOG CHANNEL 0 to 7.
// RESOLUTION    : 10 BITS ANALOG READ.
// RETURN        : 16 BITS, 2 BYTES.

void READ_RADFET(uint8_t S, uint16_t RADFET_ARRAY[16])
{
  bool S_0 = S & 1      ;
  bool S_1 = S >> 1 & 1 ;
  bool S_2 = S >> 2 & 1 ;
  unsigned long READ_TIME = 0;
  int i = 0;
  digitalWrite(S2 , S_2); digitalWrite(S1 , S_1); digitalWrite(S0 , S_0);
  while (i < 16) {
    if (STATE_BREAK != pow(2,S))break;
    if (millis() - READ_TIME >= 1000) {
      digitalWrite(S2 , S_2); digitalWrite(S1 , S_1); digitalWrite(S0 , S_0);  RADFET_ARRAY[i] = analogRead(A);  Serial.print(String(RADFET_ARRAY[i]) + " ");
      i++;
      READ_TIME = millis();
    }
  }
  Serial.println();
}
