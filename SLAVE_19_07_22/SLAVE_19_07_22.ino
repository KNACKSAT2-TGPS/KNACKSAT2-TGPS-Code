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

#define PIN_SD_MOSI       PIN_SPI_MOSI
#define PIN_SD_MISO       PIN_SPI_MISO
#define PIN_SD_SCK        PIN_SPI_SCK
#define PIN_SD_SS         PIN_SPI_SS

#else

#define PIN_SD_MOSI       PIN_SPI0_MOSI
#define PIN_SD_MISO       PIN_SPI0_MISO
#define PIN_SD_SCK        PIN_SPI0_SCK
#define PIN_SD_SS         PIN_SPI0_SS

#endif

#define _RP2040_SD_LOGLEVEL_       4

// LIBRARY IN TGPS-PAYLOAD
#include <Wire.h>
#include <RP2040_SD.h>
#include <SPI.h>

//SLAVE REGISTER ADDRESS MAP
#define TGPS_ID           0x22  // KNACKSAT_II - TGPS ,ID ADDRESS
#define TGPS_SS           0xCC  // KNACKSAT_II - TGPS ,STATUS ADDRESS 
#define TGPS_MM           0xF5  // KNACKSAT_II - TGPS ,MANAGEMENT

//SLAVE REGISTER VALUE
#define TGPS_DATA_I       0xD1  // KNACKSAT_II - TGPS ,****DATA      SET ADDRESS
#define TGPS_DATA_II      0xD2  // KNACKSAT_II - TGPS ,****DATA      RAY ADDRESS
#define TGPS_DATA_III     0xD3  // KNACKSAT_II - TGPS ,****DATA      SD-CARD ADDRESS

//SLAVE REGISTER COMMAND
#define RESET_TGPS        0xA1  // KNACKSAT_II - TGPS ,****RESET     TGPS-PAYLOAD
#define RESET_SD_CARD     0xA2  // KNACKSAT_II - TGPS ,****RESET     MEMORY DEVICE
#define RESET_SENSOR      0xA3  // KNACKSAT_II - TGPS ,****RESET     MEMORY DEVICE
#define ENABLE_SD_CARD    0xA4  // KNACKSAT_II - TGPS ,****ENABLE    MEMORY DEVICE 
#define DISENABLE_SD_CARD 0xA5  // KNACKSAT_II - TGPS ,****DISENABLE MEMORY DEVICE 
#define ENABLE_SENSOR     0xA6  // KNACKSAT_II - TGPS ,****ENABLE    SENSOR DEVICE
#define DISENABLE_SENSOR  0xA7  // KNACKSAT_II - TGPS ,****DISENABLE SENSOR DEVICE


// PIN SETUP
byte PIN_SD_CS ;    // PIN_SD_CS = PIN OF SD CARD.

//                                   I/O ,DETAIL

byte PIN_SD_CS1          = 17 ;    // O  ,PIN OF SD CARD 1
byte PIN_SD_CS2          = 20 ;    // O  ,PIN OF SD CARD 2
byte PIN_RESET           = 28 ;    // O  ,
byte PIN_POWER_SD        =  8 ;    // O  ,
byte PIN_POWER_SENSOR    =  9 ;    // O  ,
byte PIN_CBUFFER_SHIED   = 10 ;    // I  ,
byte PIN_CBUFFER         = 11 ;    // I  ,
byte SIGN_I              = 15 ;    // I  ,
byte NOISE_I             = 14 ;    // I  ,
byte SIGN_II             = 13 ;    // I  ,
byte NOISE_II            = 12 ;    // I  ,


//LOGIC STEP
bool          REGIS_ADDR        = false          ;  //FOR RECEIVE TO TGPS_PAYLOAD.
bool          REGIS_DATA_I      = false          ;  //FOR SELECT DATA_SET_I   TO TRANSMIT TO KNACKSAT_II(SATERLITE SYSTEM)
bool          REGIS_DATA_II     = false          ;  //FOR SELECT DATA_SET_II  TO TRANSMIT TO KNACKSAT_II(SATERLITE SYSTEM)
bool          REGIS_DATA_III    = false          ;  //FOR SELECT DATA_SET_III TO TRANSMIT TO KNACKSAT_II(SATERLITE SYSTEM)
bool          STATUS_ID         = false          ;  //FOR CHECK OPERATE DEVICE IN TGPS_PAYLOAD.
bool          CMD_TGPS          = false          ;  //FOR RETURN COMMAND.
bool          CMD               = false          ;  //FOR COMMAND MODE.
bool          STATE             = false          ;  //FOR SELECT SD CARD TO READ.
bool          STATE_SECOND_CORE = false          ;  //FOR SETTING THE SECOND CORE STATE.
bool          REQUEST_1         = false          ;  //FOR SETTING STATE WORKING OF REQUEST_1
bool          REQUEST_2         = false          ;  //FOR SETTING STATE WORKING OF REQUEST_2
bool          REQUEST_3         = false          ;  //FOR SETTING STATE WORKING OF REQUEST_3

// VALUE PIN  FOR UPDATE TO STATUS

bool          POWER_SD          = false          ;  //
bool          POWER_SENSOR      = false          ;  //

bool          CMD_DATA_I        = false          ;  //FOR BEGIN OR END ,DEVICE OPERATED.


bool          fx                = 0              ;

//DATA VALUE
byte          STATUS_PAYLOAD    = 0xFF           ;
int           ERROR_CHAR        =  0             ;  //ERROR CHARATER FROM MICRO SD-CARD WHEN IT'S READING DATA.
int           COUNT             =  0             ;  //COUNT CHARATER FROM MICRO SD-CARD WHEN IT'S READING DATA.
unsigned long TEXTNUM           =  0             ;

//TIME
unsigned long PREVIOUSMILLIS    = 0              ;  // SET PREVIOUSTIMETO 0
unsigned long CURRENTMILLIS                      ;  // CURRENT MILLIS
int           TIMIE             = 0              ;  // SET UP POWER IN PAYLOAD

//DOUBLE CONVERT SETUP
union
{
  byte array[8];
  double bigNum;
} The_Double;

//VARIABLE FOR CODING
int           SHIFT                              ;  //SHIFT = DATA FOR SHIFT IN A BYTE.
const byte    ONLY_A_BYTE       = 0xFF           ;

//TEMPORARY ARRAY
unsigned int  ERROR_COUNT         [4]            ;  // FOR TEMPORARY DATA FROM ERROR & COUNT.
byte          TEMPORARY           [4]            ;  // TEMPORARY DATA FOR APPEND TO BUS.
uint8_t       buf                 [10240]        ;  // CHARACTER READ EACH TIME.
double        CPM                 [1]            ;  // CPM FROM THAT WHILE GEIGER READ.
double        CPM_HISTORY         [2]            ;  // CPM HISTORY FROM GEIGER THAT FINISHED READ.

//SETUP OF GEIGER
const double  alpha             = 53.032         ;  // cpm = uSv x alpha

int           con               = 0              ;  // Number of loops
char          msg[256]          = ""             ;  // Message buffer for serial output

int           signCount         = 0              ;  // Counter for Radiation Pulse
int           noiseCount        = 0              ;  // Counter for Noise Pulse

int           sON               = 0              ;  // Lock flag for Radiation Pulse
int           nON               = 0              ;  // Lock flag for Noise Puls

double        cpm               = 0              ;  // Count rate [cpm] of current
double        cpmHistory          [200]          ;  // History of count rates
int           cpmcon            = 0              ;  // Position of current count rate on cpmHistory[]
int           cpmconPrev        = 0              ;  // Flag to prevent duplicative counting

//Timing Settings for Loop Interval
int           prevTime          = 0              ;
int           currTime          = 0              ;

int           totalSec          = 0              ;  // Elapsed time of measurement [sec]
int           totalHour         = 0              ;  // Elapsed time of measurement [hour]

//Time settings for CPM calcuaration
int           cpmTimeMSec       = 0              ;
int           cpmTimeSec        = 0              ;
int           cpmTimeMin        = 0              ;

//String buffers of double values for serial output
char          cpmBuff             [20]           ;
char          uSvBuff             [20]           ;
char          uSvdBuff            [20]           ;
char          count               [20]           ;

//RECEIVE BUFFER
byte          REGIS_CMD[2]      = {0xFF, 0xFF}   ;

// TRANSMIT BUFFER
//                                BUS_I_DATA
//        >>>MICRO SD CARD
//             COUNTING CHECK             :  4 BYTES      0-3 ADDRESS
//             ERROR CHARACTER            :  4 BYTES      4-7 ADDRESS
//        >>>MICRO SD CRAD   (SHIELD)
//             COUNTING CHECK             :  4 BYTES     8-11 ADDRESS
//             ERROR CHARACTER            :  4 BYTES    12-15 ADDRESS
//        >>>GEIGER COUNTER
//             COUNT PER MINUTES CURRENLY :  8 BYTES    16-23 ADDRESS
//        >>>GEIGER COUNTER  (SHIELD)
//             COUNT PER MINUTES CURRENLY :  8 BYTES    24-31 ADDRESS
//             ======================================================
//             TOTAL                        32 BYTES     0-31 ADDRESS
//
//                                BUS_II_DATA
//        >>>GEIGER COUNTER
//             COUNT PER MINUTES HISTORY  :  8 BYTES      0-7 ADDRESS
//             COUNT PER MINUTES HISTORY  :  8 BYTES     8-15 ADDRESS
//        >>>GEIGER COUNTER  (SHIELD)
//             COUNT PER MINUTES HISTORY  :  8 BYTES    16-23 ADDRESS
//             COUNT PER MINUTES HISTORY  :  8 BYTES    24-31 ADDRESS
//             ======================================================
//             TOTAL                        32 BYTES     0-31 ADDRESS
//
//                                BUS_III_DATA
//        >>>MICRO SD CARD
//             COUNTING CHECK             :  4 BYTES      0-3 ADDRESS
//             ERROR CHARACTER            :  4 BYTES      4-7 ADDRESS
//        >>>MICRO SD CRAD   (SHIELD)
//             COUNTING CHECK             :  4 BYTES     8-11 ADDRESS
//             ERROR CHARACTER            :  4 BYTES    12-15 ADDRESS
//             ======================================================
//             TOTAL                        16 BYTES     0-15 ADDRESS
//
byte        BUS_I                 [32]          ;  // FOR BUS_DATA_I
byte        BUS_II                [32]          ;  // FOR BUS_DATA_II
byte        BUS_III               [32]          ;  // FOR BUS_DATA_III
byte        FB_REGIS            = 0xFF          ;  // FOR FEEDBACK STATUS AND COMMAND.
byte        FB_CMD              = 0xFF          ;
byte        SUBSET_BYTE         = 0             ;  // FOR APPEND IN ARRAY BUS.

void setup()
{
  Wire.begin(TGPS_ID);
  Serial.begin(115200);

  pinMode(             PIN_SD_CS1          , OUTPUT);          //PIN SETTING FOR SELECT SD-CARD
    digitalWrite(      PIN_SD_CS1          , HIGH);

  pinMode(             PIN_SD_CS2          , OUTPUT);          //PIN SETTING FOR SELECT SD-CARD (SHIELD)
    digitalWrite(      PIN_SD_CS2          , HIGH);

  pinMode(             SIGN_I              , INPUT_PULLUP);    //PIN
    digitalWrite(      SIGN_I              , HIGH);

  pinMode(             NOISE_I             , INPUT_PULLDOWN);  //PIN
    digitalWrite(      NOISE_I             , HIGH);

  pinMode(             PIN_POWER_SD        , OUTPUT);          //PIN
  pinMode(             PIN_POWER_SENSOR    , OUTPUT);          //PIN
  pinMode(             PIN_RESET           , OUTPUT);          //PIN
    POWER_SD           = false;
    POWER_SENSOR       = false;
    digitalWrite(      PIN_RESET           , LOW);
    digitalWrite(      PIN_POWER_SD        , POWER_SD );
    digitalWrite(      PIN_POWER_SENSOR    , POWER_SENSOR);
    delay(TIMIE);
    POWER_SD           = true;
    POWER_SENSOR       = true;
    digitalWrite(      PIN_RESET           , LOW);
    digitalWrite(      PIN_POWER_SD        , POWER_SD );
    digitalWrite(      PIN_POWER_SENSOR    , POWER_SENSOR);
    delay(TIMIE);

  pinMode(             PIN_CBUFFER         , INPUT_PULLUP);    //PIN
  pinMode(             PIN_CBUFFER_SHIED   , INPUT_PULLUP);    //PIN

  pinMode(             21                  , OUTPUT);
    digitalWrite(      21                  , HIGH);
    delay(TIMIE);
    digitalWrite(      21                  , LOW);

  delay(1000);
  Serial.println("TGPS_ID: 0x" + String(TGPS_ID, HEX));


  Wire.onReceive(TGPS_RECEIVE);
  Wire.onRequest(TGPS_REQUEST);
}

void loop()
{
  if (REGIS_ADDR == true )
  {
    REGIS_DATA_I = false;
    REGIS_DATA_II = false;
    REGIS_DATA_III = false;
    switch (REGIS_CMD[0])
    {
      case TGPS_ID:
        FB_REGIS       = TGPS_ID;
        STATUS_ID      = true;
        break;

      case TGPS_DATA_I:
        Serial.println("TGPS_DATA_I");
        REQUEST_1      = true;
        REGIS_DATA_I   = true;
        break;

      case TGPS_DATA_II:
        Serial.println("TGPS_DATA_II");
        REQUEST_2      = true;
        REGIS_DATA_II  = true;
        break;

      case TGPS_DATA_III:
        Serial.println("TGPS_DATA_III");
        REQUEST_3      = true;
        REGIS_DATA_III = true;
        break;

      case TGPS_SS:
        Serial.println("KNACKSAT_II - TGPS ,STATUS ADDRESS "); //STATUS_PAYLOAD
        bitWrite( STATUS_PAYLOAD , 0 ,    digitalRead(PIN_CBUFFER)     );
        bitWrite( STATUS_PAYLOAD , 2 , digitalRead(PIN_CBUFFER_SHIED)  );
        bitWrite( STATUS_PAYLOAD , 4 ,           POWER_SD              );
        bitWrite( STATUS_PAYLOAD , 6 ,         POWER_SENSOR            );
        FB_REGIS   = STATUS_PAYLOAD;
        STATUS_ID = true;
        break;

      case TGPS_MM:
        Serial.println("KNACKSAT_II - TGPS ,MANAGEMENT");
        FB_REGIS = TGPS_MM;
        CMD = true;
        break;
    }
    REGIS_ADDR = false;
  }

  // ========================================= COMMAND PAYLOAD ============================================
  if (CMD == true )
  {
    switch (REGIS_CMD[1])
    {
      case 0xA1:
        digitalWrite(   PIN_RESET       , HIGH);
        FB_CMD   =  RESET_TGPS ;
        CMD_TGPS = true ;
        break;

      case 0xA2:
        POWER_SD           = false;
        digitalWrite(   PIN_POWER_SD    , POWER_SD );
        delay(TIMIE);
        POWER_SD           = true;
        digitalWrite(   PIN_POWER_SD    , POWER_SD );
        delay(TIMIE);
        FB_CMD   =  RESET_SD_CARD ;
        CMD_TGPS = true ;
        break;

      case 0xA3:
        POWER_SENSOR       = false;
        digitalWrite(   PIN_POWER_SENSOR    , POWER_SENSOR );
        delay(TIMIE);
        POWER_SENSOR       = true;
        digitalWrite(   PIN_POWER_SENSOR    , POWER_SENSOR );
        delay(TIMIE);
        FB_CMD   =  RESET_SENSOR ;
        CMD_TGPS = true ;
        break;

      case 0xA4:
        POWER_SD           = true;
        digitalWrite(   PIN_POWER_SD    , POWER_SD );
        FB_CMD   =  ENABLE_SD_CARD ;
        CMD_TGPS = true ;
        break;

      case 0xA5:
        POWER_SD           = false;
        digitalWrite(   PIN_POWER_SD    , POWER_SD );
        FB_CMD   =  DISENABLE_SD_CARD ;
        CMD_TGPS = true ;
        break;

      case 0xA6:
        POWER_SENSOR       = true;
        digitalWrite(   PIN_POWER_SENSOR    , POWER_SENSOR );
        FB_CMD   =  ENABLE_SENSOR ;
        CMD_TGPS = true ;
        break;

      case 0xA7:
        POWER_SENSOR       = false;
        digitalWrite(   PIN_POWER_SENSOR    , POWER_SENSOR );
        FB_CMD   =  DISENABLE_SENSOR ;
        CMD_TGPS = true ;
        break;
    }
    CMD = false ;
  }
}
void loop1()
{
  if (STATE_SECOND_CORE == true)
  {
    Serial.println("STATE_SECOND_CORE");
    while (REQUEST_1 == true)
    {
      Serial.println("REQUEST_1");
      cpmcon = 0 ;
      totalSec = 0;
      totalHour = 0;
      //RESET_DATA( SELECT_ARRAY, NUMBER OF ADDRESS)
      RESET_DATA(        "BUS_I",                32);
      RESET_DATA(  "ERROR_COUNT",                 4);
      
      GEIGER(10000);
      REQUEST_GEIGER_CPM(1);
      //CHECKTEXT( BEGIN_FILE, END_FILE, SELECT_BUS, INTERVAL)
      CHECKTEXT(            1,        20,    "BUS_I",16200000);
      
      if ((REQUEST_1 == true && REQUEST_2 == true) || (REQUEST_1 == true && REQUEST_3 == true) || (REQUEST_2 == true && REQUEST_3 == true))
      {
        REQUEST_1 = false;
        break;
      }
      REQUEST_1 = false;
    }
    while (REQUEST_2 == true)
    {
      Serial.println("REQUEST_2");
      cpmcon = 0 ;
      totalSec = 0;
      totalHour = 0;
      //RESET_DATA( SELECT_ARRAY, NUMBER OF ADDRESS)
      RESET_DATA(       "BUS_II",                32);
      
      GEIGER(10000);
      REQUEST_GEIGER_CPM_HISTORY(2);
      
      if ((REQUEST_1 == true && REQUEST_2 == true) || (REQUEST_1 == true && REQUEST_3 == true) || (REQUEST_2 == true && REQUEST_3 == true))
      {
        REQUEST_2 = false;
        break;
      }
      REQUEST_2 = false;
    }
    while (REQUEST_3 == true)
    {
      Serial.println("REQUEST_3");
      //RESET_DATA( SELECT_ARRAY, NUMBER OF ADDRESS)
      RESET_DATA(      "BUS_III",                32);
      RESET_DATA(  "ERROR_COUNT",                 4);
      
      //CHECKTEXT( BEGIN_FILE, END_FILE, SELECT_BUS, INTERVAL)
      CHECKTEXT(            1,       20,  "BUS_III", 16200000);
      CHECKTEXT(            1,       20,  "BUS_III", 16200000);
      
      if ((REQUEST_1 == true && REQUEST_2 == true) || (REQUEST_1 == true && REQUEST_3 == true) || (REQUEST_2 == true && REQUEST_3 == true))
      {
        REQUEST_3 = false;
        break;
      }
      REQUEST_3 = false;
    }
    STATE_SECOND_CORE = false;
  }
}
//=======================================<<<VOID_FUNCTION>>>=======================================

//=========================<<<TGPS_REQUEST>>>=========================

//TGPS_REQUEST : REQUEST FROM MASTER.

void TGPS_REQUEST()
{
  Serial.println("START   TGPS_REQUEST()");

  //======================<<<_I_>>>======================

  if (REGIS_DATA_I == true)
  {
    Wire.write(BUS_I, 32);
    Serial.println("REGIS_DATA_I");
    REGIS_CMD[0]       = 0xFF ; // flash
    STATE_SECOND_CORE  = true;
    REGIS_DATA_I       = false;
  }


  //======================<<<_II_>>>======================

  if (REGIS_DATA_II == true)
  {
    Wire.write(BUS_II, 32);
    Serial.println("REGIS_DATA_II");
    REGIS_CMD[0]       = 0xFF  ; // flash
    STATE_SECOND_CORE  = true;
    REGIS_DATA_II      = false;
  }


  //======================<<<_III_>>>======================

  if (REGIS_DATA_III == true)
  {
    Wire.write(BUS_III, 32);
    Serial.println("REGIS_DATA_III");
    REGIS_CMD[0]       = 0xFF ; // flash
    STATE_SECOND_CORE  = true;
    REGIS_DATA_III     = false;
  }

  if (STATUS_ID == true)
  {
    Wire.write(FB_REGIS);
    Serial.print(" FB_REGIS:  ");
    Serial.println(FB_REGIS , HEX);
    STATUS_PAYLOAD    = 0xFF ;
    FB_REGIS          = 0xFF ;
    REGIS_CMD[0]      = 0xFF ; // flash
    STATUS_ID         = false;
  }
  if (CMD_TGPS == true)
  {
    Wire.write(FB_REGIS);
    Wire.write(FB_CMD);
    Serial.print(" FB_REGIS:  ");
    Serial.println(FB_REGIS , HEX);
    Serial.print("FB_CMD :  ");
    Serial.println(FB_CMD , HEX);
    Serial.println("=================");
    FB_CMD            = 0xFF ;
    FB_REGIS          = 0xFF ;
    REGIS_CMD[0]      = 0xFF ;
    REGIS_CMD[1]      = 0xFF ; // flash
    CMD_TGPS          = false ;
  }

}

//=========================<<<TGPS_RECEIVE>>>=========================

//TGPS_RECEIVE

void TGPS_RECEIVE(int byte_in)
{
  REGIS_ADDR = true;
  byte  j = 0;
  //Serial.println("INPUT");
  while (Wire.available()) //CHECK I2C DATA IS ON BUS
  {
    REGIS_CMD[j] = Wire.read();
    Serial.println("INPUT   " + String(j) + " is " + String(REGIS_CMD[j], HEX));
    j++;
  }
  if (j != byte_in)  Serial.println("ERROR_CHAR!!! :  " + String(j) + " , " + String(byte_in));
}

//=========================<<<REQUEST_DATA>>>=========================

// REQUEST_SD_CARD     : ARRANGE DATA AND APPEND TO BUS.
// SELLECT_BUS         : SELLECT_BUS THAT APPEND.

void REQUEST_SD_CARD(int SELECT_BUS)
{
  Serial.println("Start Run REQUEST_DATA");
  //=============<<<MICRO_ SD_CRAD_1>>>==============
  
  Serial.println("SD_CARD_1");
  //CSTA(         VALUE, NUMBER OF BYTE, BEGIN_ADDRESS, END_ADDRESS, SELECT_BUS, TYPE_VARIABLE)
  CSTA(  ERROR_COUNT[0],              4,             0,           3, SELECT_BUS,     "INTEGER");
  CSTA(  ERROR_COUNT[1],              4,             4,           7, SELECT_BUS,     "INTEGER");

  //=============<<<MICRO_ SD_CRAD_2>>>==============

  Serial.println("SD_CARD_2");
  //CSTA(         VALUE, NUMBER OF BYTE, BEGIN_ADDRESS, END_ADDRESS, SELECT_BUS, TYPE_VARIABLE)
  CSTA(  ERROR_COUNT[2],              4,             8,          11, SELECT_BUS,     "INTEGER");
  CSTA(  ERROR_COUNT[3],              4,            12,          15, SELECT_BUS,     "INTEGER");

  Serial.println(" ");
  Serial.println("END REQUEST_DATA();");
}

//======================<<<REQUEST_GEIGER_CPM>>>======================

// REQUEST_GEIGER_CPM     : ARRANGE DATA AND APPEND TO BUS.
// SELLECT_BUS            : SELLECT_BUS THAT APPEND.

void REQUEST_GEIGER_CPM(int SELECT_BUS)
{
  //===============<<<GEIGER_COUNTER>>>==============

  Serial.println("G1");
  Serial.println(CPM[0], 4);
  //CSTA(         VALUE, NUMBER OF BYTE, BEGIN_ADDRESS, END_ADDRESS, SELECT_BUS, TYPE_VARIABLE)
  CSTA(          CPM[0],              8,            16,          23, SELECT_BUS,      "DOUBLE");

  //===========<<<GEIGER_COUNTER_SHIELD>>>===========

  Serial.println("G2");
  Serial.println(CPM[0], 4);
  //CSTA(         VALUE, NUMBER OF BYTE, BEGIN_ADDRESS, END_ADDRESS, SELECT_BUS, TYPE_VARIABLE)
  CSTA(          CPM[0],              8,            24,          31, SELECT_BUS,      "DOUBLE");

  Serial.println(" ");
  Serial.println("END REQUEST_DATA();");
}
//===================<<<REQUEST_GEIGER_CPM_HISTORY>>>=================

// REQUEST_GEIGER_CPM_HISTORY  : ARRANGE DATA AND APPEND TO BUS.
// SELLECT_BUS                 : SELLECT_BUS THAT APPEND.

void REQUEST_GEIGER_CPM_HISTORY(int SELECT_BUS)
{
  //===============<<<GEIGER_COUNTER>>>==============

  Serial.println("G1");
  Serial.println(CPM_HISTORY[0]);
  Serial.println(CPM_HISTORY[1]);
  
  //CSTA(         VALUE, NUMBER OF BYTE, BEGIN_ADDRESS, END_ADDRESS, SELECT_BUS, TYPE_VARIABLE)
  CSTA(  CPM_HISTORY[0],              8,             0,           7, SELECT_BUS,      "DOUBLE");
  CSTA(  CPM_HISTORY[1],              8,             8,          15, SELECT_BUS,      "DOUBLE");

  //===========<<<GEIGER_COUNTER_SHIELD>>>===========

  Serial.println("G2");
  Serial.println(CPM_HISTORY[0]);
  Serial.println(CPM_HISTORY[1]);
  
  //CSTA(         VALUE, NUMBER OF BYTE, BEGIN_ADDRESS, END_ADDRESS, SELECT_BUS, TYPE_VARIABLE)
  CSTA(  CPM_HISTORY[0],              8,            16,          23, SELECT_BUS,      "DOUBLE");
  CSTA(  CPM_HISTORY[1],              8,            24,          31, SELECT_BUS,      "DOUBLE");

  Serial.println(" ");
  Serial.println("END REQUEST_DATA();");
}

//==================<<<CONVERT_&_STORAGE_TO_ARRAY>>>==================

// CSTA             : CONVERT & STORAGE TO ARRAY.
// VALUE            : VALUE OF INPUT DATA.
// NOB              : NUMBER OF BYTE.
// BEGIN_ADDRESS    : FRIST ADDRESS IN THOSE NUMBER OF DATA.
// END_ADDRESS      : LAST ADDRESS IN THOSE NUMBER OF DATA.

void CSTA(int VALUE, int NOB, int BEGIN_ADDRESS, int END_ADDRESS, int SELECT_BUS, String TYPE_VARIABLE)
{
  //RESET_DATA( SELECT_ARRAY, NUMBER OF ADDRESS)
  RESET_DATA(    "TEMPORARY",                 4);
  if (TYPE_VARIABLE == "INTEGER")
  {
    SHIFT = VALUE;
    SUBSET_BYTE  = 0;
    for (int i = 0, j = BEGIN_ADDRESS; i < NOB, j <= END_ADDRESS; i++, j++)
    {
      SUBSET_BYTE  = SHIFT & ONLY_A_BYTE;
      SHIFT = SHIFT >> 8;
      Serial.print("Byte = "); Serial.print(SUBSET_BYTE , BIN); Serial.print(" => "); Serial.println(SUBSET_BYTE);
      TEMPORARY[i] = SUBSET_BYTE ;
      if (SELECT_BUS == 1)
      {
        BUS_I[j] = TEMPORARY[i];
      }
      if (SELECT_BUS == 2)
      {
        BUS_II[j] = TEMPORARY[i];
      }
      if (SELECT_BUS == 3)
      {
        BUS_III[j] = TEMPORARY[i];
      }
    }
    SUBSET_BYTE  = 0;
    Serial.print("Data input : "); Serial.println(VALUE);
    Serial.print("NO.byte    : "); Serial.println(NOB);
    Serial.println("================================");
  }
  else if (TYPE_VARIABLE == "DOUBLE")
  {
    The_Double.bigNum = VALUE;

    for (int i = 0; i < sizeof(double); i++)
    {
      Serial.println(The_Double.array[i], BIN);  // Send to wherever
    }
    Serial.println("__________");   // Send to wherever

    for (int i = 0, j = BEGIN_ADDRESS; i < NOB, j <= END_ADDRESS; i++, j++)
    {
      if (SELECT_BUS == 1)
      {
        BUS_I[j] = The_Double.array[i];
      }
      if (SELECT_BUS == 2)
      {
        BUS_II[j] = The_Double.array[i];
      }
      if (SELECT_BUS == 3)
      {
        BUS_III[j] = The_Double.array[i];
      }
    }
  }
}

//=========================<<<RESET_DATA>>>=========================

// RESET_DATA        : SET ALL DATA IN ARRAY TO 0.
// SELECT_ARRAY      : ARRAY THAT WANT TO RESET.
// NOA               : NUMBER OF ADDRESS.

void RESET_DATA(String SELECT_ARRAY, int NOA)
{
  for (int i = 0; i < NOA; i++)
  {
    if (SELECT_ARRAY == "BUS_I")
    {
      BUS_I[i] = 0;
    }
    if (SELECT_ARRAY == "BUI_II")
    {
      BUS_II[i] = 0;
    }
    if (SELECT_ARRAY == "BUS_III")
    {
      BUS_III[i] = 0;
    }
    if (SELECT_ARRAY == "ERROR_COUNT")
    {
      ERROR_COUNT[i] = 0;
    }
    if (SELECT_ARRAY == "TEMPORARY")
    {
      TEMPORARY[i] = 0;
    }
    if (SELECT_ARRAY == "CPM")
    {
      CPM[i] = 0;
    }
    if (SELECT_ARRAY == "CPM_HISTORY")
    {
      CPM_HISTORY[i] = 0;
    }
  }
}

//=========================<<<CHECKTEXT>>>=========================

// CHECKTEXT     : READ DATA THEN CHECK ERROR AND STORAGE TO ARRAY.
// BEGIN_FILE    : FRIST NUMBER NAME OF FILE.
// END_FILE      : LAST NUMBER NAME OF FILE.
// NOC           : NUMBER OF CHARACTER.
// INTERVAL      : VALUE OF TIME OUT.

void CHECKTEXT(int BEGIN_FILE, int END_FILE, String SELECT_BUS, unsigned long INTERVAL)
{
  ERROR_CHAR = 0;
  COUNT = 0;
  CURRENTMILLIS = millis();
  PREVIOUSMILLIS = CURRENTMILLIS;
  Serial.println("Initialising SD card...");
  fx = 0 ;
  if (STATE == 0)
  {
    PIN_SD_CS = PIN_SD_CS1;
    Serial.println("PINSD1");
  }

  if (STATE == 1)
  {
    PIN_SD_CS = PIN_SD_CS2;
    Serial.println("PINSD2");
  }
  while (!SD.begin(PIN_SD_CS))
  {
    Serial.println("Micro SD-card initialisation failed.");
    delay(500);
    CURRENTMILLIS = millis();
    if ((unsigned long)(CURRENTMILLIS - PREVIOUSMILLIS) >= INTERVAL)
    {
      Serial.println("Time out");
      if (SELECT_BUS == "BUS_I")
      {
        REQUEST_SD_CARD(1);
      }
      if (SELECT_BUS == "BUS_II")
      {
        REQUEST_SD_CARD(2);
      }
      if (SELECT_BUS == "BUS_III")
      {
        REQUEST_SD_CARD(3);
      }
      STATE = !STATE;
      return;
    }
    if ((REQUEST_1 == true && REQUEST_2 == true) || (REQUEST_1 == true && REQUEST_3 == true) || (REQUEST_2 == true && REQUEST_3 == true))
    {
      break;
    }
  }
  Serial.println("Micro SD-card initialised. Please wait : " + String(INTERVAL));

  for (byte i = BEGIN_FILE; i <= END_FILE; i++)
  {
    if (((unsigned long)(CURRENTMILLIS - PREVIOUSMILLIS) >= INTERVAL) || fx == 1 )
    {
      break;
    }
    String FILENAME =  "a" + String(i) + ".txt" ;
    Serial.print("Opening file "); Serial.println(FILENAME);
    File f = SD.open(FILENAME, O_RDONLY);
    if (!f)
    {
      Serial.println("Failed to open file.");
      break;
    }
    Serial.println("Checking error");
    while (f.available())
    {
      CURRENTMILLIS = millis();
      if ((unsigned long)(CURRENTMILLIS - PREVIOUSMILLIS) >= INTERVAL)
      {
        Serial.println("Time out");
        fx = 1 ;
        break;
      }
      if ((REQUEST_1 == true && REQUEST_2 == true) || (REQUEST_1 == true && REQUEST_3 == true) || (REQUEST_2 == true && REQUEST_3 == true))
      {
        break;
      }
      int n = f.read(buf, sizeof(buf));
      for (int i = 0; i < n; i++)
      {
        if (buf[i] != 75)
        {
          ERROR_CHAR++;
          Serial.println(char(buf[i]));
        }
        COUNT++;
      }
    }
    f.close();
    Serial.print("Bit error count : "); Serial.println(ERROR_CHAR);
    Serial.print("From : "); Serial.println(COUNT);
    if (PIN_SD_CS == PIN_SD_CS1)
    {
      ERROR_COUNT[0] = ERROR_CHAR;
      ERROR_COUNT[1] = COUNT;
    }
    if (PIN_SD_CS == PIN_SD_CS2)
    {
      ERROR_COUNT[2] = ERROR_CHAR;
      ERROR_COUNT[3] = COUNT;
    }
  }
  Serial.println("================================");
  Serial.print("Error in array : "); Serial.println(ERROR_COUNT[0]);
  Serial.print("Count in array : "); Serial.println(ERROR_COUNT[1]);
  TEXTNUM = 0;
  if (SELECT_BUS == "BUS_I")
  {
    REQUEST_SD_CARD(1);
  }
  if (SELECT_BUS == "BUS_II")
  {
    REQUEST_SD_CARD(2);
  }
  if (SELECT_BUS == "BUS_III")
  {
    REQUEST_SD_CARD(3);
  }
  STATE = !STATE;
}

//=========================<<<GEIGER>>>=========================

// GEIGER       : READ AND STROGE DATA TO ARRAY.
// SECOND       : TIME FOR GEIGER TO READ.

void GEIGER(int SECOND)
{

  //PIN setting for Radiation Pulse
  pinMode(SIGN_I, INPUT_PULLUP);
  digitalWrite(SIGN_I, HIGH);

  //PIN setting for Noise Pulse
  pinMode(NOISE_I, INPUT);
  digitalWrite(NOISE_I, HIGH);
  for (int i = 0; i < 200; i++ )
  {
    cpmHistory[i] = 0;
  }

  //Get start time of a loop
  prevTime = millis();
  unsigned  int starttime = millis();
  while (millis() <= starttime + SECOND)
  {
    bool sign = digitalRead(SIGN_I);

    // Raw data of Noise Pulse: Not-detected -> Low, Detected -> High
    bool noise = digitalRead(NOISE_I);

    //Radiation Pulse normally keeps low for about 100[usec]
    if (sign == 0 && sON == 0)
    { //Deactivate Radiation Pulse counting for a while
      sON = 1;
      signCount++;
    } else if (sign == 1 && sON == 1) {
      sON = 0;
    }

    //Noise Pulse normally keeps high for about 100[usec]
    if (noise == 1 && nON == 0)
    { //Deactivate Noise Pulse counting for a while
      nON = 1;
      noiseCount++;
    } else if (noise == 0 && nON == 1) {
      nON = 0;
    }

    //Output readings to serial port, after 10000 loops
    if (con == 10000) //About 160-170 msec in Arduino Nano(ATmega328)
    {
      //Get current time
      currTime = millis();

      //No noise detected in 10000 loops
      if (noiseCount == 0)
      {
        //Shift an array for counting log for each 6 sec.
        if ( totalSec % 6 == 0 && cpmconPrev != totalSec)
        {
          cpmconPrev = totalSec;
          Serial.print("Time2 :"); Serial.println(cpmcon);
          cpmcon++;
          if (cpmcon > 200)
          {
            cpmcon = 0;
          }

          if (cpmHistory[cpmcon] > 0)
          {
            cpm -= cpmHistory[cpmcon];
          }
          cpmHistory[cpmcon] = 0;
        }
        //Store count log
        cpmHistory[cpmcon] += signCount;
        //Add number of counts
        cpm += signCount;
        //Serial.print("B");Serial.println(cpm);

        //Get ready time for 10000 loops
        cpmTimeMSec += abs(currTime - prevTime);
        //Transform from msec. to sec. (to prevent overflow)
        if (cpmTimeMSec >= 1000)
        {
          cpmTimeMSec -= 1000;
          //Add measurement time to calcurate cpm readings (max=20min.)
          if ( cpmTimeSec >= 20 * 60 )
          {
            cpmTimeSec = 20 * 60;
          }
          else

          {
            cpmTimeSec++;
          }

          //Total measurement time
          totalSec++;
          //Transform from sec. to hour. (to prevent overflow)
          if (totalSec >= 3600)
          {
            totalSec -= 3600;
            totalHour++;
          }
        }

        //Elapsed time of measurement (max=20min.)
        double min = cpmTimeSec / 60.0;
        if (min != 0)
        {
          //Calculate cpm, uSv/h and error of uSv/h
          dtostrf(cpm / min, -1, 3, cpmBuff);
          dtostrf(cpmHistory[cpmcon] / min, -1, 3, count);
          dtostrf(cpm / min / alpha, -1, 3, uSvBuff);
          dtostrf(sqrt(cpm) / min / alpha, -1, 3, uSvdBuff);
          CPM[0] = cpm / min;
          if (cpmcon < 2)
          {
            CPM_HISTORY[cpmcon] = cpmHistory[cpmcon] / min;
          }
        }
        else {
          //Devision by zerobn
          dtostrf(0, -1, 3, cpmBuff);
          dtostrf(0, -1, 3, count);
          dtostrf(0, -1, 3, uSvBuff);
          dtostrf(0, -1, 3, uSvdBuff);
        }

        //Create message for serial port
        sprintf(msg, "%d,%d.%03d,%d,%s,%s,%s,%s",
                totalHour, totalSec,
                cpmTimeMSec,
                signCount,
                cpmBuff,
                uSvBuff,
                uSvdBuff,
                count
               );
        //Send message to serial port
        Serial.println(msg);
      }
      //Initialization for next 10000 loops
      prevTime = currTime;
      signCount = 0;
      noiseCount = 0;
      con = 0;
      //Serial.print("D");Serial.println(cpm);
    }
    con++;
    if ((REQUEST_1 == true && REQUEST_2 == true) || (REQUEST_1 == true && REQUEST_3 == true) || (REQUEST_2 == true && REQUEST_3 == true))
    {
      break;
    }
  }
  Serial.print("Time2 : "); Serial.println(cpmcon);
  for (int i = 0; i < 200; i++)
  {
    Serial.print(i); Serial.print(" >>> "); Serial.println(cpmHistory[i], 4);
    if ((REQUEST_1 == true && REQUEST_2 == true) || (REQUEST_1 == true && REQUEST_3 == true) || (REQUEST_2 == true && REQUEST_3 == true))
    {
      break;
    }
  }
  Serial.print("C"); Serial.println(cpm);
}
