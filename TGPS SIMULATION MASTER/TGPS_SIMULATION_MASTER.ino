//     KNACKSAT_II - TGPS (SATERLITE)
//             PROGRAMMING BY
//       - KITTIPHOP  PHANTHACHART
//       - PONGSAPAT  LAKROD

// =====================<<< LIBRARY >>>====================
// LIBRARY IN MASTER SIMULATION 
#include <Wire.h>



// =================<<< DEFINE ADDRESS >>>=================
// ==========<<< COMMUNICATION >>>==========
// SLAVE ADDRESS
#define TGPS_ID            0x22  // KNACKSAT_II - TGPS ,ID ADDRESS

// SLAVE REGISTER ADDRESS
#define TGPS_MISSION       0xF5  // KNACKSAT_II - TGPS ,COMMAND ADDRESS
#define TGPS_DATA          0xD1  // KNACKSAT_II - TGPS ,DATA ADDRESS



// ====================<<< VARIABLE >>>====================
// BUS DATA
byte          RECEIVE_DATA         [250] ;

// TIME
unsigned long BEGIN_TIME_PROCESS = 0     ;
unsigned long END_TIME_PROCESS   = 0     ;

// DATA
uint16_t      RADFET_CH0           [18]  ;  // FOR SAVE ANALOG VALUE OF RADFET CHANNEL 0.
uint16_t      RADFET_CH1           [18]  ;  // FOR SAVE ANALOG VALUE OF RADFET CHANNEL 1.
uint16_t      RADFET_CH2           [18]  ;  // FOR SAVE ANALOG VALUE OF RADFET CHANNEL 2.
uint16_t      RADFET_CH3           [18]  ;  // FOR SAVE ANALOG VALUE OF RADFET CHANNEL 3.
uint16_t      RADFET_CH4           [18]  ;  // FOR SAVE ANALOG VALUE OF RADFET CHANNEL 4.
uint16_t      RADFET_CH5           [18]  ;  // FOR SAVE ANALOG VALUE OF RADFET CHANNEL 5.
uint16_t      RADFET_CH6           [18]  ;  // FOR SAVE ANALOG VALUE OF RADFET CHANNEL 6.
uint16_t      RADFET_CH7           [18]  ;  // FOR SAVE ANALOG VALUE OF RADFET CHANNEL 7.
// ====================================================================
// ==========================<<< BUS PLAN >>>==========================
//
//                                 BUS
//           TITLE                           SIZE      INDEXS
//       >>> READ RADFET SENSOR 8 CHANNEL
//             ANALOG VALUE              : 1.5 BYTES    0-215
//       >>> READ MICRO SD CARD
//             PROCESS START & END STATE :   1 BYTES      216
//             FILE NAME                 :   2 BYTES  217-218
//             COUNTING CHECK            :   4 BYTES  219-222
//             ERROR CHARACTER           :   4 BYTES  223-226
//             TIME PROCESS              :   4 BYTES  227-230
//             CHARACTER TO CHECK        :   1            231
//             FRIST CHARACTER READ      :   1            232
//       >>> READ MICRO SD CRAD   (SHIELD)
//             PROCESS START & END STATE :   1 BYTES      233
//             FILE NAME                 :   2 BYTES  234-235
//             COUNTING CHECK            :   4 BYTES  236-239
//             ERROR CHARACTER           :   4 BYTES  240-243
//             TIME PROCESS              :   4 BYTES  244-247
//             CHARACTER TO CHECK        :   1            248
//             FRIST CHARACTER READ      :   1            249
//             ================================================
//             TOTAL                       250 BYTES    0-249
//             ================================================
//
// ========================<<< BUS PACKET >>>==========================
byte          BUS               [250]        ;  // BUS MAIN MISSION
// ====================================================================

// ========================<<< PRINT_DATA >>>========================

// PRINT : PRINT ARRAY ONLY.

template <typename T, size_t N>
void PRINT(T (&ARRAY)[N])
{
  for (uint64_t i = 0; i < N; i++) {
    if (sizeof(T) == 1)Serial.print(ARRAY[i], DEC);
    if (sizeof(T) >  1)Serial.print(ARRAY[i]);
    Serial.print(" ");
  }
  Serial.println();
}

void setup()
{
  Wire.begin();
  Serial.begin(115200);

  while(!Serial);   // WAIT FOR OPEN SERIAL MONITOR.

  Serial.println("======================<<< MASTER >>>======================");
  Serial.println("REQUSET DATA : TGPS_DATA    (ADDRESS = 0xD1) KEYWORD =  D1 OR  d1");
  Serial.println("RUN MISSION  : TGPS_MISSION (ADDRESS = 0xF5) KEYWORD =  F5 OR  f5");
  Serial.println("UNPACK DATA  : UNPACK MISSION DATA           KEYWORD = UMD OR umd");
  Serial.println("==========================================================");
  Serial.println("ENTER A KEYWORD >> ");
}

void loop()
{
  while (Serial.available() > 0)
  {
    String CMD_HEX = Serial.readStringUntil('\n');
    CMD_HEX.trim();
    byte REGISTER_INPUT = (byte)strtoul(CMD_HEX.c_str(), NULL, 16);
    if (CMD_HEX.length() <= 2)Serial.println("REGISTER INPUT : 0x" + String(REGISTER_INPUT, HEX));
    
    // =================<<< COMMUNICATION TO PAYLOAD >>>=================
    
    switch (REGISTER_INPUT)
    {
      case 0xD1 :
        Serial.println("REGISTER IS TGPS_DATA (0xD1).");
        Serial.println("MASTER IS REQUESTING DATA FROM PAYLOAD.");
        Serial.println("PLEASE WAIT FOR DOWNLOAD.");
        BEGIN_TIME_PROCESS = micros();
        DOWNLOAD(TGPS_ID, TGPS_DATA, RECEIVE_DATA, 250);
        END_TIME_PROCESS   = micros();
        Serial.println("TIME PROCESS REGISTER : " + String((unsigned long)(END_TIME_PROCESS - BEGIN_TIME_PROCESS)) + " MICROSECOND");
        Serial.println("==========================================================");
        break;
      case 0xF5 :
        Serial.println("REGISTER IS TGPS_MISSION (0xF5).");
        Serial.println("MASTER IS COMMAND TO RUN MISSION IN PAYLOAD.");
        Serial.println("PLEASE WAIT FOR UPLOAD.");
        BEGIN_TIME_PROCESS = micros();
        UPLOAD(TGPS_ID, TGPS_MISSION);
        END_TIME_PROCESS   = micros();
        Serial.println("TIME PROCESS REGISTER : " + String((unsigned long)(END_TIME_PROCESS - BEGIN_TIME_PROCESS)) + " MICROSECOND");
        Serial.println("PLEASE WAIT AROUND 10 MINUTE FOR RECORD DATA IN PAYLOAD AND STAND BY TO SEND REQUEST DATA.");
        Serial.println("==========================================================");
        break;
    }
    
    // ====================<<< UNPACK MISSION DATA >>>===================
    
    if (CMD_HEX == "umd" || CMD_HEX == "UMD")
    {
      UNPACK_RADFET(RECEIVE_DATA, RADFET_CH0,   0);
      UNPACK_RADFET(RECEIVE_DATA, RADFET_CH1,  27);
      UNPACK_RADFET(RECEIVE_DATA, RADFET_CH2,  54);
      UNPACK_RADFET(RECEIVE_DATA, RADFET_CH3,  81);
      UNPACK_RADFET(RECEIVE_DATA, RADFET_CH4, 108);
      UNPACK_RADFET(RECEIVE_DATA, RADFET_CH5, 135);
      UNPACK_RADFET(RECEIVE_DATA, RADFET_CH6, 162);
      UNPACK_RADFET(RECEIVE_DATA, RADFET_CH7, 189);
      Serial.println();
      Serial.println("==========================================================");
      Serial.println("                   UNPACK MISSION DATA                    ");
      Serial.println("==========================================================");
      Serial.println();
      Serial.println("===================<<< RADFET DATA >>>====================");
      Serial.println(">>> RADFET OUTSIDE SHIELD DATA");
      Serial.print("CHANNEL 0 : "); PRINT(RADFET_CH0);
      Serial.print("CHANNEL 1 : "); PRINT(RADFET_CH1);
      Serial.print("CHANNEL 4 : "); PRINT(RADFET_CH4);
      Serial.print("CHANNEL 5 : "); PRINT(RADFET_CH5);
      Serial.println(">>> RADFET INSIDE SHIELD DATA");
      Serial.print("CHANNEL 2 : "); PRINT(RADFET_CH2);
      Serial.print("CHANNEL 3 : "); PRINT(RADFET_CH3);
      Serial.print("CHANNEL 6 : "); PRINT(RADFET_CH6);
      Serial.print("CHANNEL 7 : "); PRINT(RADFET_CH7);
      Serial.println("================<<< SD CARD NO.1 DATA >>>=================");
      Serial.println(">>> PROCESS START & END STATUS");
      Serial.println("CHIP SELECT 1       : " + String(RECEIVE_DATA[216] >> 7 & 1 ? "SELECTED" : "NON SELECTED"));
      Serial.println("CHIP SELECT 2       : " + String(RECEIVE_DATA[216] >> 6 & 1 ? "SELECTED" : "NON SELECTED"));
      Serial.println("BEGIN FAILED        : " + String(RECEIVE_DATA[216] >> 5 & 1 ? "BEGIN FAILED" : "BEGIN"));
      Serial.println("TIME OUT            : " + String(RECEIVE_DATA[216] >> 4 & 1 ? "TIME OUT" : "IN TIME"));
      Serial.println("READ RECENT FILE    : " + String(RECEIVE_DATA[216] >> 3 & 1 ? "READ RECENT FILE NAME SUCCESS" : "NO READ RECENT FILE NAME"));
      Serial.println("START CHECK TEXT    : " + String(RECEIVE_DATA[216] >> 2 & 1 ? "START CHECK SUCCESS" : "NO START CHECK"));
      Serial.println("END CHECK TEXT      : " + String(RECEIVE_DATA[216] >> 1 & 1 ? "END CHECK SUCCESS" : "NO END CHECK"));
      Serial.println("SAVE RECENT FILE    : " + String(RECEIVE_DATA[216] & 1 ? "SAVE RECENT FILE NAME SUCCESS" : "NO SAVE RECENT FILE NAME"));
      Serial.println(">>> CHECK TEXT DATA");
      Serial.println("FILE NAME           : " + String(RECEIVE_DATA[217] ? String(RECEIVE_DATA[218] << 8 | RECEIVE_DATA[217]) + ".txt" : "NO FILE NAME."));
      Serial.println("COUNTING CHECK      : " + String(RECEIVE_DATA[222] << 24 | RECEIVE_DATA[221] << 16 | RECEIVE_DATA[220] << 8 | RECEIVE_DATA[219]));
      Serial.println("ERROR CHARACTER     : " + String(RECEIVE_DATA[226] << 24 | RECEIVE_DATA[225] << 16 | RECEIVE_DATA[224] << 8 | RECEIVE_DATA[223]));
      Serial.println("TIME PROCESS        : " + String(RECEIVE_DATA[230] << 24 | RECEIVE_DATA[229] << 16 | RECEIVE_DATA[228] << 8 | RECEIVE_DATA[227]) + " MILLISECOND");
      Serial.println("CHARACTERS TO CHECK : " + String(char(RECEIVE_DATA[231])));
      Serial.println("FIRST CHARACTER     : " + String(char(RECEIVE_DATA[232])));
      Serial.println("============<<< SD CARD NO.2 (SHIELD) DATA >>>============");
      Serial.println(">>> PROCESS START & END STATUS");
      Serial.println("CHIP SELECT 1       : " + String(RECEIVE_DATA[233] >> 7 & 1 ? "SELECTED" : "NON SELECTED"));
      Serial.println("CHIP SELECT 2       : " + String(RECEIVE_DATA[233] >> 6 & 1 ? "SELECTED" : "NON SELECTED"));
      Serial.println("BEGIN FAILED        : " + String(RECEIVE_DATA[233] >> 5 & 1 ? "BEGIN FALIED" : "BEGIN"));
      Serial.println("TIME OUT            : " + String(RECEIVE_DATA[233] >> 4 & 1 ? "TIME OUT" : "IN TIME"));
      Serial.println("READ RECENT FILE    : " + String(RECEIVE_DATA[233] >> 3 & 1 ? "READ RECENT FILE NAME SUCCESS" : "NO READ RECENT FILE NAME"));
      Serial.println("START CHECK TEXT    : " + String(RECEIVE_DATA[233] >> 2 & 1 ? "START CHECK SUCCESS" : "NO START CHECK"));
      Serial.println("END CHECK TEXT      : " + String(RECEIVE_DATA[233] >> 1 & 1 ? "END CHECK SUCCESS" : "NO END CHECK"));
      Serial.println("SAVE RECENT FILE    : " + String(RECEIVE_DATA[233] & 1 ? "SAVE RECENT FILE NAME SUCCESS" : "NO SAVE RECENT FILE NAME"));
      Serial.println(">>> CHECK TEXT DATA");
      Serial.println("FILE NAME           : " + String(RECEIVE_DATA[234] ? String(RECEIVE_DATA[235] << 8 | RECEIVE_DATA[234]) + ".txt" : "NO FILE NAME."));
      Serial.println("COUNTING CHECK      : " + String(RECEIVE_DATA[239] << 24 | RECEIVE_DATA[238] << 16 | RECEIVE_DATA[237] << 8 | RECEIVE_DATA[236]));
      Serial.println("ERROR CHARACTER     : " + String(RECEIVE_DATA[243] << 24 | RECEIVE_DATA[242] << 16 | RECEIVE_DATA[241] << 8 | RECEIVE_DATA[240]));
      Serial.println("TIME PROCESS        : " + String(RECEIVE_DATA[247] << 24 | RECEIVE_DATA[246] << 16 | RECEIVE_DATA[245] << 8 | RECEIVE_DATA[244]) + " MILLISECOND");
      Serial.println("CHARACTERS TO CHECK : " + String(char(RECEIVE_DATA[248])));
      Serial.println("FIRST CHARACTER     : " + String(char(RECEIVE_DATA[249])));
      Serial.println("==========================================================");
    }
  }
}



// =========================<<< DOWNLOAD >>>=========================

// DOWNLOAD   : DOWLOAD DATA FROM SLAVE.
// ID_ADDRESS : A SLAVE ID ADDRESS.
// REGISTER   : A REGISTER ADDRESS TO REQUEST DATA FROM SLAVE.
// DATA       : A DATA TO RECEIVE.
// SIZE       : A SIZE OF DATA THAT WANT TO REQUEST.

void DOWNLOAD(byte ID_ADDRESS, byte REGISTER, byte *DATA, int SIZE)
{
  Wire.beginTransmission(ID_ADDRESS);
  Wire.write(REGISTER);
  Wire.endTransmission();

  delay(50);

  int i = 0;
  Wire.requestFrom(ID_ADDRESS, SIZE);
  Serial.println("REGISTER REQUSET : 0x" + String(REGISTER, HEX));
  Serial.println("==========================================================");
  while (Wire.available() > 0)
  {
    DATA[i] = Wire.read();
    Serial.print(String(DATA[i]) + " ");
    i++;
  }
  Serial.println();
  Serial.println("==========================================================");
  if (i != SIZE)
  {
    Serial.println("BUS LENGTH IS NOT THE SAME AS REQUEST.");
    Serial.println("BUS LENGTH RECEIVE : " + String(i) + " (BYTE) REQUEST " + String(SIZE) + " (BYTES)");
  }
  Serial.println(">>> DOWNLOAD DONE!");
}



// ==========================<<< UPLOAD >>>==========================

// UPLOAD     : UPLOAD DATA TO SLAVE.
// ID_ADDRESS : A SLAVE ID ADDRESS.
// REGISTER   : A REGISTER ADDRESS TO WRITE DATA TO SLAVE.

void UPLOAD(byte ID_ADDRESS, byte REGISTER)
{
  Wire.beginTransmission(ID_ADDRESS);
  Wire.write(REGISTER);
  Wire.endTransmission();

  delay(10);

  int i = 0;
  Wire.requestFrom(ID_ADDRESS, 1);
  Serial.println("REGISTER REQUSET : 0x" + String(REGISTER, HEX));
  while (Wire.available() > 0)
  {
    Serial.println("PAYLOAD FEEDBACK : 0x" + String(Wire.read(), HEX) + " INDEX " + String(i));
    i++;
  }
  Serial.println(">>> UPLOAD DONE!");
}



// ======================<<< UNPACK_RADFET >>>=======================

// UNPACK_RADFET : UNPACK DATA FROM SLAVE TO GET RADFET DATA IN EACH CHANNEL.
// DATA          : A DATA HAD RECEIVE.
// RADFET_ARRAY  : A RADFET ARRAY WANT TO SAVE.
// START_INDEX   : A START INDEX OF BUS TO SAVE RADFET DATA.

void UNPACK_RADFET(byte *DATA, uint16_t *RADFET_ARRAY, int START_INDEX) {
  for (int i = START_INDEX, j = 0; i < START_INDEX + 26, j < 18; i += 3, j += 2) 
  {
    RADFET_ARRAY[j]   = DATA[i] << 4 | (DATA[i + 1] >> 4);
    RADFET_ARRAY[j + 1] = (DATA[i + 1] & 0x000F) << 8 | DATA[i + 2];
  }
}
