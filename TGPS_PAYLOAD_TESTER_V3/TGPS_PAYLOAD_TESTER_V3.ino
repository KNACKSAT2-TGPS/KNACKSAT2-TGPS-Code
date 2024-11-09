//       KNACKSAT_II - TGPS (PAYLOAD)
//             PROGRAMMING BY
//       - KITTIPHOP  PHANTHACHART
//       - PONGSAPAT  LAKROD
//       - WICHAN     WICHARYANUPARP
//       - SUPASAKORN WORA-URAI

// PROJECT MEMBER :  - KITTIPHOP  PHANTHACHART
//                   - PONGSAPAT  LAKROD
//                   - WICHAN     WICHARYANUPARP
//                   - SUPASAKORN WORA-URAI
//                   - AKIRAH     NIRUNTRANONT
//                   - SUPRACHAI  MATHASILAWAT
//                   - TRAILUCK   YAEMMEE
//                   - SIRAVIJ    PRAEVISAVAKIJ
//                   - WEERAWONG  CHEAMPONGANUNT
//                   - PONGSAN    WONGSAKPAIROJ
//                   - PHIRAYA    TRIPANAKORN
//                   - NATAPOHN   PHOMSEN
//                   - DOLLAPAT   LESRTVIRIYAJITT
//                   - CHIRATH    SUETRONG
//                   - WONGKOM    PINISATIL
//                   - JIRAPARC   POHNANANTAROJ
//                   - NITHIWAT   BUAPROMMEE
//                   - KUNANON    TREEYAVARANGPHAN
//                   - SORAWIT    PHUNTAREE
//                   - SIRIRAJ    HEMARAT
//                   - NUTWITCHA  PUENGYAIWATTANA
//                   - TANUT      TUNLUENG


//RP2040
#if !defined(ARDUINO_ARCH_RP2040)
#error For RP2040 only
#endif

#if defined(ARDUINO_ARCH_MBED)

#define PIN_SD_MOSI PIN_SPI_MOSI
#define PIN_SD_MISO PIN_SPI_MISO
#define PIN_SD_SCK PIN_SPI_SCK
#define PIN_SD_SS PIN_SPI_SS

#else

#define PIN_SD_MOSI PIN_SPI0_MOSI
#define PIN_SD_MISO PIN_SPI0_MISO
#define PIN_SD_SCK PIN_SPI0_SCK
#define PIN_SD_SS PIN_SPI0_SS

#endif

#define _RP2040_SD_LOGLEVEL_ 4

// =====================<<< LIBRARY >>>====================
// LIBRARY IN TGPS-PAYLOAD
#include <Wire.h>
#include <RP2040_SD.h>
#include <EEPROM.h>
#include <SPI.h>

// =================<<< DEFINE ADDRESS >>>=================
// ==========<<< COMMUNICATION >>>==========
// SLAVE ADDRESS
#define TGPS_ID            0x22  // KNACKSAT_II - TGPS ,ID ADDRESS

// SLAVE REGISTER ADDRESS
#define TGPS_MISSION       0xF5  // KNACKSAT_II - TGPS ,COMMAND ADDRESS
#define TGPS_DATA          0xD1  // KNACKSAT_II - TGPS ,REQUEST DATA ADDRESS


// ===================<<< DEFINE PIN >>>===================
// ============<<< MULTIPLEX >>>============
// ADDRESS SELECT
#define S0                    6  // CHANNEL SELECT 0
#define S1                    7  // CHANNEL SELECT 1
#define S2                    8  // CHANNEL SELECT 2

// ANALOG PIN
#define A                    27  // COMMON OUT/IN

// LED PIN
#define LED_PICO             25  // LED ON PI PICO

// ==========<<< MICRO SD CARD >>>==========
byte PIN_SD_CS1               =  17          ;  // PIN OF SD-CARD 1 (SHIELD)
byte PIN_SD_CS2               =  20          ;  // PIN OF SD CARD 2

byte PIN_SD_CS                               ;  // PIN_SD_CS = PIN OF SD CARD.


// ====================<<< VARIABLE >>>====================
// LOGIC STEP
bool          RECEIVE_STATE   = false        ;  // FOR RECEIVE TO TGPS_PAYLOAD.
bool          COMMAND_STATE   = false        ;  // FOR RETURN COMMAND.

bool          MISSION_DATA    = false        ;  // MISSION DATA STATE FOR REQUSET
bool          MISSION_RUN     = false        ;  // MISSION RUNING STATE

bool          SWITCH_BUS_PART = false        ;  // BUS_SELECTED TELL WHICH BUS PART ARE CURRENTLY SELECTING.

// TIME
unsigned long PREVIOUS_TIME_1 = 0            ;  // SET PREVIOUSTIMETO 0
unsigned long PREVIOUS_TIME_2 = 0            ;  // SET PREVIOUSTIMETO 0
unsigned long SET_TIME_OUT    = 600000       ;  // SET UP TIME OUT OVERALL
unsigned long SET_TIME_READ   = 1000         ;  // SET UP TIME OUT READ RADFET PER TIME SET
unsigned long SET_TIME_OUT_SD = 60000        ;  // SET UP TIME OUT MISSION SD CARD

// HISTORY DATA & PROCESS DATA
uint16_t      RADFET_DATA       [18]         ;  // FOR SAVE ANALOG VALUE OF RADFET CHANNEL 0.

uint8_t       BUFFER_SD         [10240]      ;  // CHARACTER READ EACH TIME.
uint16_t      LASTED_FILE_CS1 = 0            ;  // LASTED FILE OF SD CARD NO.1
uint16_t      LASTED_FILE_CS2 = 0            ;  // LASTED FILE OF SD CARD NO.2 (SHIELD)
unsigned long ERROR_CHAR      = 0            ;  // ERROR CHARATER FROM MICRO SD-CARD ONE FILE.
unsigned long COUNT           = 0            ;  // COUNT CHARATER FROM MICRO SD-CARD ONE FILE.

uint16_t      PSE             = 0x00         ;  // PROCESS START STATE & END STATE
bool          CS1             = false        ;  // CHIP SELECT 1
bool          CS2             = false        ;  // CHIP SELECT 2
bool          BFS             = false        ;  // BEGIN FAILED
bool          TOS             = false        ;  // TIME OUT
bool          RRS             = false        ;  // READ RECENT FILE
bool          SCS             = false        ;  // START CHECK TEXT
bool          ECS             = false        ;  // END CHECK TEXT
bool          SRS             = false        ;  // SAVE RECENT FILE
uint16_t      FN              = 0            ;  // FILE NAME
byte          CTC             = 0            ;  // CHARACTER TO CHECK
char          FC              = 0            ;  // FRIST CHARACTER THAT READ FROM FILE
unsigned long TP              = 0            ;  // TIME PROCESS
unsigned long TSP             = 0            ;  // TIME START PROCESS

// RECEIVE BUS
byte          REGIS_CMD       = 0xFF         ;

// TRANSMIT BUS
byte          FEEDBACK_CMD    = 0xFF         ;

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
// =========================<<< BUS PACKET >>>=========================
byte          BUS                  [250]        ;  // BUS MAIN MISSION
byte          BUS_PART_1           [128]        ;  // BUS MAIN MISSION PART 1
byte          BUS_PART_2           [128]        ;  // BUS MAIN MISSION PART 2
// ====================================================================


// ========================<<< PRINT_DATA >>>========================

// PRINT         : PRINT ARRAY ONLY.

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
  Wire.begin(TGPS_ID);
  EEPROM.begin(512);
  Serial.begin(115200);

  // =========================<<< PIN_MODE >>>=========================

  pinMode(PIN_SD_CS1, OUTPUT) ;  //PIN SETTING FOR SELECT SD-CARD (SHIELD)
  pinMode(PIN_SD_CS2, OUTPUT) ;  //PIN SETTING FOR SELECT SD-CARD

  pinMode(S0,         OUTPUT) ;  // SELECT CHANNEL 0
  pinMode(S1,         OUTPUT) ;  // SELECT CHANNEL 1
  pinMode(S2,         OUTPUT) ;  // SELECT CHANNEL 2

  pinMode(A,           INPUT) ;  // ANALOG CHANNEL

  pinMode(LED_PICO,   OUTPUT) ;  // ANALOG CHANNEL

  // ==========================<<< SETUP >>>===========================

  digitalWrite(PIN_SD_CS1, HIGH);
  digitalWrite(PIN_SD_CS2, HIGH);

  digitalWrite(LED_PICO,   HIGH);

  analogReadResolution(12);

  //delay(5000);         // DELAY FOR SEE SETUP SERIAL PRINT.
  //while(!Serial);      // FOR SEE SETUP SERIAL PRINT USE ARDUINO IDE 2.0+.

  READ_MISSION_DATA() ;  // READ DATA FROM FLASH MEMORY

  // TEST ONLY
  memset(BUS_PART_1, 201, sizeof(BUS_PART_1));
  memset(BUS_PART_2, 202, sizeof(BUS_PART_2));

  // DEFINE BUS PART
  BUS_PART_1[127] = 0x01 ;
  BUS_PART_2[127] = 0x02 ;

  Serial.println("===================<<< TGPS PAYLOAD >>>===================");
  Serial.println("TGPS ID ADDRESS : 0x" + String(TGPS_ID, HEX));
  Serial.println("==========================================================");

  // ====================<<< I2C COMMUNICATION >>>=====================

  Wire.onReceive(TGPS_RECEIVE);
  Wire.onRequest(TGPS_REQUEST);
}

// ========================<<< FRIST CORE >>>========================

void loop()
{
  if (RECEIVE_STATE == true)
  {
    Serial.println("RECEIVE & COMMAND");
    MISSION_DATA = false ;
    switch (REGIS_CMD)
    {
      case TGPS_DATA    :
        Serial.println("REGISTER IS TGPS_DATA (0xD1)");
        FEEDBACK_CMD  = TGPS_DATA    ;
        MISSION_DATA  = true         ;
        break;
      case TGPS_MISSION :
        Serial.println("REGISTER IS TGPS_MISSION (0xF5)");
        FEEDBACK_CMD  = TGPS_MISSION ;
        COMMAND_STATE = true         ;
        MISSION_RUN   = true         ;
        break;
    }
    RECEIVE_STATE = false;
  }
}

// ========================<<< SECOND CORE >>>=======================

void loop1()
{
  if (MISSION_RUN == true)
  {
    //delay(50);   // DELAY FOR FRIST CORE LOOP DO SERIAL COMMUNICATION TO MONITOR FRIST.

    Serial.println("=================<<< START RUN MISSION >>>================");

    PREVIOUS_TIME_1 = millis();   // SET ZERO

    // ==============<<< READ RADFET, SAVE DATA & PACK >>>==============

    Serial.println("==========<<< READ RADFET, SAVE DATA & PACK >>>===========");

    Serial.print("CHANNEL 0 : "); READ_RADFET(0); PACK_RADFET(   0);
    Serial.print("CHANNEL 1 : "); READ_RADFET(1); PACK_RADFET(  27);
    Serial.print("CHANNEL 2 : "); READ_RADFET(2); PACK_RADFET(  54);
    Serial.print("CHANNEL 3 : "); READ_RADFET(3); PACK_RADFET(  81);
    Serial.print("CHANNEL 4 : "); READ_RADFET(4); PACK_RADFET( 108);
    Serial.print("CHANNEL 5 : "); READ_RADFET(5); PACK_RADFET( 135);
    Serial.print("CHANNEL 6 : "); READ_RADFET(6); PACK_RADFET( 162);
    Serial.print("CHANNEL 7 : "); READ_RADFET(7); PACK_RADFET( 189);

    Serial.println(">>> READ RADFET SUCCESSFULLY.");
    Serial.println(">>> SAVE RADFET MISSION DATA TO BUS SUCCESSFULLY.");
    Serial.println("==========================================================");

    // =========================<<< CHECK TEXT >>>=======================

    CHECKTEXT(0);

    Serial.println(TOS ? ">>> AN SD CARD MISSION HAS TIME OUT." : ">>> CHECK SD CARD SUCCESSFULLY.");

    // =========================<<< SAVE DATA >>>========================

    memcpy(&BUS[216],        &PSE, sizeof(       PSE));
    memcpy(&BUS[217],         &FN, sizeof(        FN));
    memcpy(&BUS[219],      &COUNT, sizeof(     COUNT));
    memcpy(&BUS[223], &ERROR_CHAR, sizeof(ERROR_CHAR));
    memcpy(&BUS[227],         &TP, sizeof(        TP));
    memcpy(&BUS[231],        &CTC, sizeof(       CTC));
    memcpy(&BUS[232],         &FC, sizeof(        FC));

    Serial.println(">>> SAVE SD CARD MISSION DATA TO BUS SUCCESSFULLY.");
    Serial.println("==========================================================");

    // =========================<<< CHECK TEXT >>>=======================

    CHECKTEXT(1);

    Serial.println(TOS ? ">>> AN SD CARD MISSION HAS TIME OUT." : ">>> CHECK SD CARD SUCCESSFULLY.");

    // =========================<<< SAVE DATA >>>========================

    memcpy(&BUS[233],        &PSE, sizeof(       PSE));
    memcpy(&BUS[234],         &FN, sizeof(        FN));
    memcpy(&BUS[236],      &COUNT, sizeof(     COUNT));
    memcpy(&BUS[240], &ERROR_CHAR, sizeof(ERROR_CHAR));
    memcpy(&BUS[244],         &TP, sizeof(        TP));
    memcpy(&BUS[248],        &CTC, sizeof(       CTC));
    memcpy(&BUS[249],         &FC, sizeof(        FC));

    SAVE_MISSION_DATA();

    Serial.println(">>> SAVE SD CARD MISSION DATA TO BUS SUCCESSFULLY.");
    Serial.println("==========================================================");
    Serial.print  (">>> BUS : "); PRINT(BUS);
    Serial.println("==========================================================");
    Serial.println(((unsigned long)(millis() - PREVIOUS_TIME_1) >= SET_TIME_OUT) ? ">>> TIME OUT. (10 MINUTES)" : "MISSION DONE!");
    Serial.println("==========================================================");

    MISSION_RUN = false ;
  }
}



// =======================<<< TGPS_REQUEST >>>=======================

// TGPS_REQUEST : REQUEST COMMUNICATION FROM MASTER.

void TGPS_REQUEST()
{
  Serial.println("PAYLOAD HAVE REQUEST DATA.");

  memcpy(BUS_PART_1, BUS      , 125 * sizeof(BUS[0]));
  memcpy(BUS_PART_2, BUS + 125, 125 * sizeof(BUS[0]));
  if (SWITCH_BUS_PART == 0) Wire.write(BUS_PART_1, 128);
  if (SWITCH_BUS_PART == 1) Wire.write(BUS_PART_2, 128);
  if ((SWITCH_BUS_PART == 1) && (MISSION_RUN == 0)) memset(BUS, 0, sizeof(BUS));
  SWITCH_BUS_PART = !SWITCH_BUS_PART ;


  // =========================<<< SEND DATA >>>========================
//  if (MISSION_DATA == true)
//  {
    //    memcpy(BUS_PART_1, BUS      , 125 * sizeof(BUS[0]));
    //    memcpy(BUS_PART_2, BUS + 125, 125 * sizeof(BUS[0]));
    //    if (SWITCH_BUS_PART == 0) Wire.write(BUS_PART_1, 128);
    //    if (SWITCH_BUS_PART == 1) Wire.write(BUS_PART_2, 128);
    //    if (SWITCH_BUS_PART == 1) memset(BUS, 0, sizeof(BUS));
    //    SWITCH_BUS_PART = !SWITCH_BUS_PART ;
//    Serial.println("SEND MISSION DATA " + String(SWITCH_BUS_PART ? "PART 1" : "PART 2") );
//    Serial.println("==========================================================");
//    REGIS_CMD    = 0xFF  ;
//    MISSION_DATA = false ;
//  }

  // ======================<<< COMMAND MISSION >>>=====================

  if (COMMAND_STATE == true)
  {
    Wire.write(FEEDBACK_CMD);
    Serial.println("SEND FEEDBACK COMMAND : 0x" + String(FEEDBACK_CMD , HEX));
    Serial.println("==========================================================");
    FEEDBACK_CMD  = 0xFF  ;
    REGIS_CMD     = 0xFF  ;
    COMMAND_STATE = false ;
  }
}



// =======================<<< TGPS_RECEIVE >>>=======================

// TGPS_RECEIVE   : RECEIVE COMMUNICATION FROM MASTER.
// RECEIVE_NUMBER : NUMBER OF BYTE THAT HAVE RECEIVE.

void TGPS_RECEIVE(int RECEIVE_NUMBER)
{
  RECEIVE_STATE = true;

  int  i = 0;
  Serial.println("PAYLOAD HAVE RECEIVED.");
  while (Wire.available()) //CHECK I2C DATA IS ON BUS
  {
    REGIS_CMD = Wire.read();
    Serial.println("RECEIVE DATA : 0x" + String(REGIS_CMD, HEX) + " INDEX " + String(i));
    i++;
  }
  if (i != RECEIVE_NUMBER)
  {
    Serial.println("AVAILABLE BUS LENGTH IS NOT THE SAME AS RECEIVE.");
    Serial.println("BUS LENGTH RECEIVE : " + String(i) + " RECEIVE " + String(RECEIVE_NUMBER));
  }
}



// =======================<<< READ_RADFET >>>========================

// READ_RADFET  : READ ANALOG VALUE FROM RADFET SENSOR. (RESOLUTION 12 BITS)
// S            : SELECT CHANNEL 0 to 7.

void READ_RADFET(uint8_t S)
{
  int i = 0;
  memset(RADFET_DATA, 0, sizeof(RADFET_DATA));
  PREVIOUS_TIME_2 = millis();   // SET ZERO
  digitalWrite(S2 , S >> 2 & 1); digitalWrite(S1 , S >> 1 & 1); digitalWrite(S0 , S & 1);
  while (i < sizeof(RADFET_DATA) / 2)
  {
    analogRead(A);
    if ((unsigned long)(millis() - PREVIOUS_TIME_1) >= SET_TIME_OUT)break;
    if ((unsigned long)(millis() - PREVIOUS_TIME_2) >= SET_TIME_READ)
    {
      RADFET_DATA[i] = analogRead(A);  Serial.print(String(RADFET_DATA[i]) + " ");
      i++;
      PREVIOUS_TIME_2 = millis();
    }
  }
  Serial.println();
}



// ======================<<< PACKET_RADFET >>>=======================

// PACK_RADFET  : SPECIAL PACKING RADFET DATA TO A SAVE SPACE BUS AND MORE BUS SPACE TO RECORD DATA.
// RADFET_ARRAY : A RADFET ARRAY TO SAVE INTO BUS.
// START_INDEX  : A START INDEX OF BUS TO SAVE RADFET DATA.

void PACK_RADFET(uint16_t START_INDEX)
{
  uint16_t RADFET_DATA_STATE = 0;
  for (int i = 0; i < 18; i++)
  {
    RADFET_DATA_STATE |= RADFET_DATA[i];
  }
  for (int i = 0, j = START_INDEX; i < 18, j < START_INDEX + 26; i += 2, j += 3)
  {
    if ((unsigned long)(millis() - PREVIOUS_TIME_1) >= SET_TIME_OUT && RADFET_DATA_STATE == 0)break;
    BUS[j]     = RADFET_DATA[i] >> 4 ;
    BUS[j + 1] = (RADFET_DATA[i] & 0x000F) << 4 | (RADFET_DATA[i + 1] >> 8) ;
    BUS[j + 2] = RADFET_DATA[i + 1] & 0x00FF ;
  }
}



// =====================<<< SAVE_MISSION_DATA >>>====================

// SAVE_MISSION_DATA : SAVE DATA TO FLASH MEMORY AND WAIT FOR REQUEST.

void SAVE_MISSION_DATA() {
  for (int i = 0; i < 250; i++) {
    EEPROM.write(i + 4, BUS[i]);   // WRITE BUS DATA TO FLASH MEMORY
    if ((unsigned long)(millis() - PREVIOUS_TIME_1) >= SET_TIME_OUT) break;
  }
  Serial.println(EEPROM.commit() ? "FLASH MEMORY SUCCESSFULLY COMMITTED" : "ERROR! FLASH MEMORY COMMIT FALIED");
}



// =====================<<< READ_MISSION_DATA >>>====================

// READ_MISSION_DATA : READ DATA FROM FLASH MEMORY.

void READ_MISSION_DATA() {
  PREVIOUS_TIME_1 = millis();
  for (int i = 0; i < 250; i++) {
    BUS[i] = EEPROM.read(i + 4);   // WRITE BUS DATA TO FLASH MEMORY
    if ((unsigned long)(millis() - PREVIOUS_TIME_1) >= SET_TIME_OUT) break;
  }
}



// ========================<<< CHECKTEXT >>>=========================

// CHECKTEXT   : READ DATA THEN CHECK ERROR.
// CHIP_SELECT : SELECT SD CARD.

void CHECKTEXT(bool CHIP_SELECT)
{
  TSP             = millis() ;   // SET ZERO
  PREVIOUS_TIME_2 = millis() ;   // SET ZERO

  // =======================<<< SET DEFAULT >>>========================

  PSE             = 0        ;   // PROCESS STATE
  CS1             = false    ;   // CHIP SELECT 1
  CS2             = false    ;   // CHIP SELECT 2
  BFS             = false    ;   // BEGIN FAILED STATE
  TOS             = false    ;   // TIME OUT STATE
  RRS             = false    ;   // READ RECENT STATE
  SCS             = false    ;   // START CHECK STATE
  ECS             = false    ;   // END CHECK STATE
  SRS             = false    ;   // SAVE RECENT STATE

  LASTED_FILE_CS1 = 0        ;   // RECENT FILE CS1
  LASTED_FILE_CS2 = 0        ;   // RECENT FILE CS2
  ERROR_CHAR      = 0        ;   // ERROR CHARACTER
  COUNT           = 0        ;   // COUNTING CHECK
  FN              = 0        ;   // FILE NAME
  FC              = 0        ;   // FIRST CHARACTER
  TP              = 0        ;   // TIME PROCESS

  Serial.println("============<<< START INITIALISING SD CARD >>>============");
  Serial.println("TIME OUT SET AT " + String(SET_TIME_OUT_SD / 60000) + " MINUTES");

  // =================<<< SETUP CHIP SELECT SD CARD >>>================

  if (CHIP_SELECT == 0 && (unsigned long)(millis() - PREVIOUS_TIME_1) < SET_TIME_OUT)                                                           //OPENSDCARD1
  {
    PIN_SD_CS = PIN_SD_CS1         ;
    CS1       = true               ;
    digitalWrite(PIN_SD_CS1,  LOW) ;
    digitalWrite(PIN_SD_CS2, HIGH) ;
    Serial.println(">>> SD CARD NO.1");
    Serial.println("SELECTED PIN : " + String(PIN_SD_CS));
  }
  if (CHIP_SELECT == 1 && (unsigned long)(millis() - PREVIOUS_TIME_1) < SET_TIME_OUT)                                                           //OPENSDCARD2
  {
    PIN_SD_CS = PIN_SD_CS2         ;
    CS2       = true               ;
    digitalWrite(PIN_SD_CS1, HIGH) ;
    digitalWrite(PIN_SD_CS2,  LOW) ;
    Serial.println(">>> SD CARD NO.2 (SHIELD)");
    Serial.println("SELECTED PIN : " + String(PIN_SD_CS));
  }

  // ===============<<< SD CARD INITIALISATION FAILED >>>==============

  while (!SD.begin(PIN_SD_CS))
  {
    Serial.println("SD CARD INITIALISATION FAILED.");
    if ((unsigned long)(millis() - PREVIOUS_TIME_2) >= SET_TIME_OUT_SD || (unsigned long)(millis() - PREVIOUS_TIME_1) >= SET_TIME_OUT)          //TIMEOUT
    {
      BFS   = true   ;
      TOS   = true   ;
      break;
    }
  }

  // =====================<<< READ RECENT FILE >>>=====================

  if ((unsigned long)(millis() - PREVIOUS_TIME_1) < SET_TIME_OUT)
  {
    EEPROM.get(0, LASTED_FILE_CS1);   // READ FLASH MEMORY FOR SD CARD NO.1
    EEPROM.get(2, LASTED_FILE_CS2);   // READ FLASH MEMORY FOR SD CARD NO.2
    if ((LASTED_FILE_CS1 != 0) || (LASTED_FILE_CS2 != 0))RRS = true ;   // CHECK CAN READ FLASH MEMORY
    if ((LASTED_FILE_CS1 > 1001) || (LASTED_FILE_CS2 > 1001))   // SETUP FLASH MEMORY FOR MISSION
    {
      Serial.println(">>> SETUP FLASH MEMORY FOR MISSION");
      EEPROM.put(0, 0x00010003);
      Serial.println(EEPROM.commit() ? "FLASH MEMORY SUCCESSFULLY COMMITTED" : "ERROR! FLASH MEMORY COMMIT FALIED");
      EEPROM.get(0, LASTED_FILE_CS1);
      EEPROM.get(2, LASTED_FILE_CS2);
    }
    if (CHIP_SELECT == 0)LASTED_FILE_CS1++   ;  // NEXT FILE OF SD CARD NO.1
    if (CHIP_SELECT == 1)LASTED_FILE_CS2++   ;  // NEXT FILE OF SD CARD NO.2
    if (LASTED_FILE_CS1 == 1001)LASTED_FILE_CS1 = 1 ;   // SET FILE 1001 TO 1 OF SD CARD NO.1
    if (LASTED_FILE_CS2 == 1001)LASTED_FILE_CS2 = 1 ;   // SET FILE 1001 TO 1 OF SD CARD NO.2
  }

  // ========================<<< CHECK ERROR >>>=======================

  while (true)
  {
    ERROR_CHAR = 0 ;
    COUNT      = 0 ;

    String FILENAME;
    if (CHIP_SELECT == 0)FILENAME = String(LASTED_FILE_CS1) + ".txt" ;
    if (CHIP_SELECT == 1)FILENAME = String(LASTED_FILE_CS2) + ".txt" ;
    Serial.println("==============================");
    Serial.println("TRY OPEN FILE " + FILENAME);

    if (CHIP_SELECT == 0)FN  = LASTED_FILE_CS1;
    if (CHIP_SELECT == 1)FN  = LASTED_FILE_CS2;

    File f = SD.open(FILENAME, O_RDONLY);   // OPEN FILE FOR READ ONLY
    if (!f)
    {
      Serial.println("FAILE TO OPEN FILE." + FILENAME);
      break;
    }
    Serial.println("PLEASE WAIT FOR CHECK ERROR.");

    while (f.available())
    {
      SCS = true ;

      if ((unsigned long)(millis() - PREVIOUS_TIME_2) >= SET_TIME_OUT_SD || (unsigned long)(millis() - PREVIOUS_TIME_1) >= SET_TIME_OUT)           //TIMEOUT
      {
        TOS = true ;
        break;
      }
      int n = f.read(BUFFER_SD, sizeof(BUFFER_SD));
      FC = BUFFER_SD[0];
      for (int i = 0; i < n; i++)
      {
        if (BUFFER_SD[i] != CTC)    // DATA IN SD CARD IS NOT SAME CHARACTER TO CHECK.
        {
          ERROR_CHAR++;
        }
        COUNT++;
      }
    }
    f.close();  // CLOSE FILE

    Serial.println("==============================");
    Serial.println("COUNTING CHECK  : " + String(     COUNT));
    Serial.println("ERROR CHARACTER : " + String(ERROR_CHAR));
    Serial.println("==============================");

    if (((unsigned long)(millis() - PREVIOUS_TIME_2) >= SET_TIME_OUT_SD) || (unsigned long)(millis() - PREVIOUS_TIME_1) >= SET_TIME_OUT)          //TIMEOUT
    {
      TOS = true ;
      break;
    }

    ECS = true ;
    break;
  }

  // =====================<<< SAVE RECENT FILE >>>=====================

  if ((unsigned long)(millis() - PREVIOUS_TIME_1) < SET_TIME_OUT)
  {
    EEPROM.put(0, LASTED_FILE_CS1);   // WRITE FLASH MEMORY FOR SD CARD NO.1
    EEPROM.put(2, LASTED_FILE_CS2);   // WRITE FLASH MEMORY FOR SD CARD NO.2
    if (EEPROM.commit())
    {
      Serial.println("FLASH MEMORY SUCCESSFULLY COMMITTED");
      SRS = true ;
    }
    else
    {
      Serial.println("ERROR! FLASH MEMORY COMMIT FALIED");
    }
  }

  // ======================<<< WRITE BIT STATE >>>=====================

  bitWrite(PSE, 0, SRS);
  bitWrite(PSE, 1, ECS);
  bitWrite(PSE, 2, SCS);
  bitWrite(PSE, 3, RRS);
  bitWrite(PSE, 4, TOS);
  bitWrite(PSE, 5, BFS);
  bitWrite(PSE, 6, CS2);
  bitWrite(PSE, 7, CS1);

  TP    = millis() - TSP ;   // TIME PROCESS
}
