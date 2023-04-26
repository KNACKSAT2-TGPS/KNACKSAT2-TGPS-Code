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
#include <SPI.h>

#include "PRINT_ARRAY.h"


// =================<<< DEFINE ADDRESS >>>=================
// ==========<<< COMMUNICATION >>>==========
// SLAVE REGISTER ADDRESS MAP
#define TGPS_ID            0x22  // KNACKSAT_II - TGPS ,ID ADDRESS
#define TGPS_SCR           0xE0  // KNACKSAT_II - TGPS ,STATUS COMMAND RADFET ADDRESS 
#define TGPS_SCC           0xE1  // KNACKSAT_II - TGPS ,STATUS COMMAND SD CARD ADDRESS 
#define TGPS_CMD           0xF1  // KNACKSAT_II - TGPS ,MANAGEMENT

// SLAVE REGISTER VALUE
#define TGPS_DATA_I        0xD0  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.1 ADDRESS
#define TGPS_DATA_II       0xD1  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.2 ADDRESS
#define TGPS_DATA_III      0xD2  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.3 ADDRESS
#define TGPS_DATA_IV       0xD3  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.4 ADDRESS
#define TGPS_DATA_V        0xD4  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.5 ADDRESS
#define TGPS_DATA_VI       0xD5  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.6 ADDRESS
#define TGPS_DATA_VII      0xD6  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.7 ADDRESS
#define TGPS_DATA_VIII     0xD7  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.8 ADDRESS

#define TGPS_DATA_IX       0xD8  // KNACKSAT_II - TGPS ,****DATA   MICRO SD CARD ADDRESS

//SLAVE REGISTER COMMAND
#define TGPS_CMD_I         0xC0  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.1 ADDRESS
#define TGPS_CMD_II        0xC1  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.2 ADDRESS
#define TGPS_CMD_III       0xC2  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.3 ADDRESS
#define TGPS_CMD_IV        0xC3  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.4 ADDRESS
#define TGPS_CMD_V         0xC4  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.5 ADDRESS
#define TGPS_CMD_VI        0xC5  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.6 ADDRESS
#define TGPS_CMD_VII       0xC6  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.7 ADDRESS
#define TGPS_CMD_VIII      0xC7  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.8 ADDRESS

#define TGPS_CMD_IX        0xC8  // KNACKSAT_II - TGPS ,****DATA   MICRO SD CARD ADDRESS



// ===================<<< DEFINE PIN >>>===================
// ============<<< MULTIPLEX >>>============
// ADDRESS SELECT
#define S0                    6  // CHANNEL SELECT 0
#define S1                    7  // CHANNEL SELECT 1
#define S2                    8  // CHANNEL SELECT 2

// ANALOG PIN
#define A                    27  // COMMON OUT/IN

// ==========<<< MICRO SD-CARD >>>==========
byte PIN_SD_CS1              =  17           ;// PIN OF SD-CARD 1 (SHIELD)
byte PIN_SD_CS2              =  20           ;// PIN OF SD CARD 2

byte PIN_SD_CS                               ;// PIN_SD_CS = PIN OF SD CARD.


// ====================<<< VARIABLE >>>====================
// LOGIC STEP
bool          REGIS_ADDR      = false        ;  // FOR RECEIVE TO TGPS_PAYLOAD.
bool          REGIS_DATA_I    = false        ;  // FOR SELECT DATA_SET_I   TO TRANSMIT TO KNACKSAT_II(SATERLITE SYSTEM)
bool          REGIS_DATA_II   = false        ;  // FOR SELECT DATA_SET_II  TO TRANSMIT TO KNACKSAT_II(SATERLITE SYSTEM)
bool          REGIS_DATA_III  = false        ;  // FOR SELECT DATA_SET_II  TO TRANSMIT TO KNACKSAT_II(SATERLITE SYSTEM)
bool          REGIS_DATA_IV   = false        ;  // FOR SELECT DATA_SET_II  TO TRANSMIT TO KNACKSAT_II(SATERLITE SYSTEM)
bool          REGIS_DATA_V    = false        ;  // FOR SELECT DATA_SET_II  TO TRANSMIT TO KNACKSAT_II(SATERLITE SYSTEM)
bool          REGIS_DATA_VI   = false        ;  // FOR SELECT DATA_SET_II  TO TRANSMIT TO KNACKSAT_II(SATERLITE SYSTEM)
bool          REGIS_DATA_VII  = false        ;  // FOR SELECT DATA_SET_II  TO TRANSMIT TO KNACKSAT_II(SATERLITE SYSTEM)
bool          REGIS_DATA_VIII = false        ;  // FOR SELECT DATA_SET_II  TO TRANSMIT TO KNACKSAT_II(SATERLITE SYSTEM)
bool          REGIS_DATA_IX   = false        ;  // FOR SELECT DATA_SET_II  TO TRANSMIT TO KNACKSAT_II(SATERLITE SYSTEM)
bool          STATUS_ID       = false        ;  // FOR CHECK OPERATE DEVICE IN TGPS_PAYLOAD.
bool          CMD_TGPS        = false        ;  // FOR RETURN COMMAND.
bool          CMD             = false        ;  // FOR COMMAND MODE.
bool          STATE           = false        ;  // FOR SELECT MICRO SD CARD TO READ.
bool          REQUEST_I       = false        ;  // FOR SETTING STATE WORKING OF REQUEST_I
bool          REQUEST_II      = false        ;  // FOR SETTING STATE WORKING OF REQUEST_II
bool          REQUEST_III     = false        ;  // FOR SETTING STATE WORKING OF REQUEST_III
bool          REQUEST_IV      = false        ;  // FOR SETTING STATE WORKING OF REQUEST_IV
bool          REQUEST_V       = false        ;  // FOR SETTING STATE WORKING OF REQUEST_V
bool          REQUEST_VI      = false        ;  // FOR SETTING STATE WORKING OF REQUEST_VI
bool          REQUEST_VII     = false        ;  // FOR SETTING STATE WORKING OF REQUEST_VII
bool          REQUEST_VIII    = false        ;  // FOR SETTING STATE WORKING OF REQUEST_VIII
bool          REQUEST_IX      = false        ;  // FOR SETTING STATE WORKING OF REQUEST_IX

uint8_t       PSE             =  0x00        ;  // PROCESS START STATE & END STATE
bool          PSS             = false        ;  // PROCESS START STATE
bool          PES             = false        ;  // PROCESS END STATE
char          FN                             ;  // FILE NAME
unsigned long TP              = 0            ;  // TIME PROCESS
unsigned long TSP             = 0            ;  // TIME START PROCESS
unsigned long TEP             = 0            ;  // TIME END PROCESS
char          CTC                            ;  // CHARACTER TO CHECK
char          FC                             ;  // FRIST CHARACTER THAT READ FROM FILE

uint16_t      RADFET_0          [16]         ;
uint16_t      RADFET_1          [16]         ;
uint16_t      RADFET_2          [16]         ;
uint16_t      RADFET_3          [16]         ;
uint16_t      RADFET_4          [16]         ;
uint16_t      RADFET_5          [16]         ;
uint16_t      RADFET_6          [16]         ;
uint16_t      RADFET_7          [16]         ;

bool          fx              = 0            ;
uint8_t       recentfile                     ;

uint16_t      STATE_BREAK     = 0x0000       ;  // 

// DATA VALUE
byte          STATUS_PAYLOAD  = 0xFF         ;
int           ERROR_CHAR      = 0            ;  // ERROR CHARATER FROM MICRO SD-CARD WHEN IT'S READING DATA.
int           COUNT           = 0            ;  // COUNT CHARATER FROM MICRO SD-CARD WHEN IT'S READING DATA.

// TIME
unsigned long PREVIOUSMILLIS  = 0            ;  // SET PREVIOUSTIMETO 0
unsigned long CURRENTMILLIS                  ;  // CURRENT MILLIS
int           TIMIE           = 0            ;  // SET UP POWER IN PAYLOAD

// TEMPORARY ARRAY
unsigned int  ERROR_COUNT       [4]          ;  // FOR TEMPORARY DATA FROM ERROR & COUNT.
byte          TEMPORARY         [4]          ;  // TEMPORARY DATA FOR APPEND TO BUS.
uint8_t       buf               [10240]      ;  // CHARACTER READ EACH TIME.

// RECEIVE BUFFER
byte          REGIS_CMD[2]    = {0xFF, 0xFF} ;

// TRANSMIT BUFFER
byte          FB_REGIS        = 0xFF         ;  // FOR FEEDBACK STATUS AND COMMAND.
byte          FB_CMD          = 0xFF         ;
byte          SUBSET_BYTE     = 0            ;  // FOR APPEND IN ARRAY BUS.

// ===================================================================
//
//                                   BUS  I
//       >>> RADFET SENSOR CH0                          INDEXS
//             ANALOG VALUE               :  2 BYTES     0-31
//             ================================================
//             TOTAL                        32 BYTES     0-31
//             ================================================
//
//                                   BUS  II
//       >>> RADFET SENSOR CH1                          INDEXS
//             ANALOG VALUE               :  2 BYTES     0-31
//             ================================================
//             TOTAL                        32 BYTES     0-31
//             ================================================
//
//                                   BUS  III
//       >>> RADFET SENSOR CH2                          INDEXS
//             ANALOG VALUE               :  2 BYTES     0-31
//             ================================================
//             TOTAL                        32 BYTES     0-31
//             ================================================
//
//                                   BUS  IV
//       >>> RADFET SENSOR CH3                          INDEXS
//             ANALOG VALUE               :  2 BYTES     0-31
//             ================================================
//             TOTAL                        32 BYTES     0-31
//             ================================================
//
//                                   BUS  V
//       >>> RADFET SENSOR CH4                          INDEXS
//             ANALOG VALUE               :  2 BYTES     0-31
//             ================================================
//             TOTAL                        32 BYTES     0-31
//             ================================================
//
//                                   BUS  VI
//       >>> RADFET SENSOR CH5                          INDEXS
//             ANALOG VALUE               :  2 BYTES     0-31
//             ================================================
//             TOTAL                        32 BYTES     0-31
//             ================================================
//
//                                   BUS  VII
//       >>> RADFET SENSOR CH6                          INDEXS
//             ANALOG VALUE               :  2 BYTES     0-31
//             ================================================
//             TOTAL                        32 BYTES     0-31
//             ================================================
//
//                                   BUS  VIII
//       >>> RADFET SENSOR CH7                          INDEXS
//             ANALOG VALUE               :  2 BYTES     0-31
//             ================================================
//             TOTAL                        32 BYTES     0-31
//             ================================================
//
//                                   BUS  IX
//       >>> READ MICRO SD CARD                         INDEXS
//             COUNTING CHECK             :  4 BYTES      0-3
//             ERROR CHARACTER            :  4 BYTES      4-7
//       >>> READ MICRO SD CRAD   (SHIELD)
//             COUNTING CHECK             :  4 BYTES     8-11
//             ERROR CHARACTER            :  4 BYTES    12-15
//             ================================================
//             TOTAL                        32 BYTES     0-31
//             ================================================
//
// ============================<<< BUS >>>=============================
byte         BUS_I              [32]         ;  // FOR REQUEST_I
byte         BUS_II             [32]         ;  // FOR REQUEST_II
byte         BUS_III            [32]         ;  // FOR REQUEST_III
byte         BUS_IV             [32]         ;  // FOR REQUEST_IIII
byte         BUS_V              [32]         ;  // FOR REQUEST_IIII
byte         BUS_VI             [32]         ;  // FOR REQUEST_IIII
byte         BUS_VII            [32]         ;  // FOR REQUEST_IIII
byte         BUS_VIII           [32]         ;  // FOR REQUEST_IIII
byte         BUS_IX             [32]         ;  // FOR REQUEST_IIII
// ====================================================================

void setup()
{
  Wire.begin(TGPS_ID);
  Serial.begin(115200);

  //
  pinMode(PIN_SD_CS1, OUTPUT);  //PIN SETTING FOR SELECT SD-CARD (SHIELD)
  pinMode(PIN_SD_CS2, OUTPUT);  //PIN SETTING FOR SELECT SD-CARD

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);

  pinMode(A, INPUT);

  digitalWrite(PIN_SD_CS1, HIGH);
  digitalWrite(PIN_SD_CS2, HIGH);

  analogReadResolution(12);

  Serial.println("TGPS_ID: 0x" + String(TGPS_ID, HEX));

  Wire.onReceive(TGPS_RECEIVE);
  Wire.onRequest(TGPS_REQUEST);
  //  REGIS_ADDR = true;
  //  REGIS_CMD = TGPS_DATA_I;
}

void loop()
{
  STATE_BREAK = REQUEST_IX << 8 | REQUEST_VIII << 7 | REQUEST_VII << 6 | REQUEST_VI << 5 | REQUEST_V << 4 | REQUEST_IV << 3 | REQUEST_III << 2 | REQUEST_II << 1 | REQUEST_I;
  if (REGIS_ADDR == true)
  {
    REGIS_DATA_I    = false ;
    REGIS_DATA_II   = false ;
    REGIS_DATA_III  = false ;
    REGIS_DATA_IV   = false ;
    REGIS_DATA_V    = false ;
    REGIS_DATA_VI   = false ;
    REGIS_DATA_VII  = false ;
    REGIS_DATA_VIII = false ;
    REGIS_DATA_IX   = false ;
    switch (REGIS_CMD[0])
    {
      case TGPS_ID        :
        FB_REGIS        = TGPS_ID ;
        STATUS_ID       = true    ;
        break;

      case TGPS_DATA_I    :
        Serial.println("TGPS_DATA_I");
        REGIS_DATA_I    = true ;
        break;

      case TGPS_DATA_II   :
        Serial.println("TGPS_DATA_II");
        REGIS_DATA_II   = true ;
        break;

      case TGPS_DATA_III  :
        Serial.println("TGPS_DATA_III");
        REGIS_DATA_III  = true ;
        break;

      case TGPS_DATA_IV   :
        Serial.println("TGPS_DATA_IV");
        REGIS_DATA_IV   = true ;
        break;

      case TGPS_DATA_V    :
        Serial.println("TGPS_DATA_V");
        REGIS_DATA_V    = true ;
        break;

      case TGPS_DATA_VI   :
        Serial.println("TGPS_DATA_VI");
        REGIS_DATA_VI   = true ;
        break;

      case TGPS_DATA_VII  :
        Serial.println("TGPS_DATA_VII");
        REGIS_DATA_VII  = true ;
        break;

      case TGPS_DATA_VIII :
        Serial.println("TGPS_DATA_VIII");
        REGIS_DATA_VIII = true ;
        break;

      case TGPS_DATA_IX   :
        Serial.println("TGPS_DATA_IX");
        REGIS_DATA_IX = true   ;
        break;

      case TGPS_SCR       :
        Serial.println("KNACKSAT_II - TGPS ,STATUS ADDRESS "); //STATUS_PAYLOAD
        bitWrite( STATUS_PAYLOAD , 0 ,    REQUEST_I    );
        bitWrite( STATUS_PAYLOAD , 1 ,    REQUEST_II   );
        bitWrite( STATUS_PAYLOAD , 2 ,    REQUEST_III  );
        bitWrite( STATUS_PAYLOAD , 3 ,    REQUEST_IV   );
        
        bitWrite( STATUS_PAYLOAD , 4 ,    REQUEST_V    );
        bitWrite( STATUS_PAYLOAD , 5 ,    REQUEST_VI   );
        bitWrite( STATUS_PAYLOAD , 6 ,    REQUEST_VII  );
        bitWrite( STATUS_PAYLOAD , 7 ,    REQUEST_VIII );
        FB_REGIS   = STATUS_PAYLOAD ;
        STATUS_ID  = true           ;
        break;

      case TGPS_SCC       :
        Serial.println("KNACKSAT_II - TGPS ,STATUS ADDRESS "); //STATUS_PAYLOAD
        bitWrite( STATUS_PAYLOAD , 0 ,    REQUEST_IX   );
        FB_REGIS   = STATUS_PAYLOAD ;
        STATUS_ID  = true           ;
        break;

      case TGPS_CMD       :
        Serial.println("KNACKSAT_II - TGPS ,MANAGEMENT");
        FB_REGIS = TGPS_CMD ;
        CMD      = true     ;
        break;
    }
    REGIS_ADDR = false;
  }

  // ==================================<<< COMMAND >>>==================================

  if (CMD == true )
  {
    switch (REGIS_CMD[1])
    {
      case TGPS_CMD_I:
        Serial.println("TGPS_CMD_I");
        FB_CMD    =  TGPS_CMD_I ;
        CMD_TGPS  = true ;
        REQUEST_I = true;
        break;

      case TGPS_CMD_II:
        Serial.println("TGPS_CMD_II");
        FB_CMD    =  TGPS_CMD_II ;
        CMD_TGPS  = true ;
        REQUEST_II      = true ;
        break;

      case TGPS_CMD_III:
        Serial.println("TGPS_CMD_III");
        FB_CMD   =  TGPS_CMD_III ;
        CMD_TGPS = true ;
        REQUEST_III     = true ;
        break;

      case TGPS_CMD_IV:
        Serial.println("TGPS_CMD_VI");
        FB_CMD   =  TGPS_CMD_IV ;
        CMD_TGPS = true ;
        REQUEST_IV      = true ;
        break;

      case TGPS_CMD_V:
        Serial.println("TGPS_CMD_V");
        FB_CMD   =  TGPS_CMD_V ;
        CMD_TGPS = true ;
        REQUEST_V       = true ;
        break;

      case TGPS_CMD_VI:
        Serial.println("TGPS_CMD_VI");
        FB_CMD   =  TGPS_CMD_VI ;
        CMD_TGPS = true ;
        REQUEST_VI      = true ;
        break;

      case TGPS_CMD_VII:
        Serial.println("TGPS_CMD_VII");
        FB_CMD   =  TGPS_CMD_VII ;
        CMD_TGPS = true ;
        REQUEST_VII     = true ;
        break;

      case TGPS_CMD_VIII:
        Serial.println("TGPS_CMD_VIII");
        FB_CMD   =  TGPS_CMD_VII ;
        CMD_TGPS = true ;
        REQUEST_VIII    = true ;
        break;

      case TGPS_CMD_IX:
        Serial.println("TGPS_CMD_IX");
        FB_CMD   =  TGPS_CMD_VII ;
        CMD_TGPS = true ;
        REQUEST_IX    = true   ;
        break;
    }
    CMD = false ;
  }
}

void loop1()
{
  RUNNING_CMD_I();
  RUNNING_CMD_II();
  RUNNING_CMD_III();
  RUNNING_CMD_IV();
  RUNNING_CMD_V();
  RUNNING_CMD_VI();
  RUNNING_CMD_VII();
  RUNNING_CMD_VIII();
  RUNNING_CMD_IX();
}
