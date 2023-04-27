//KNACKSAT_II - TGPS (SATERLITE)


//BY   KITTIPHOP  PHANTHACHART



#include <Wire.h>

//SLAVE REGISTER ADDRESS MAP
#define TGPS_ID            0x22  // KNACKSAT_II - TGPS ,ID ADDRESS
#define TGPS_SCR           0xE0  // KNACKSAT_II - TGPS ,STATUS COMMAND RADFET ADDRESS 
#define TGPS_SCC           0xE1  // KNACKSAT_II - TGPS ,STATUS COMMAND SD CARD ADDRESS 
#define TGPS_CMD           0xF5  // KNACKSAT_II - TGPS ,MANAGEMENT

// SLAVE REGISTER VALUE
#define TGPS_DATA_I        0xD1  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.1 ADDRESS
#define TGPS_DATA_II       0xD2  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.2 ADDRESS
#define TGPS_DATA_III      0xD3  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.3 ADDRESS
#define TGPS_DATA_IV       0xD4  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.4 ADDRESS
#define TGPS_DATA_V        0xD5  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.5 ADDRESS
#define TGPS_DATA_VI       0xD6  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.6 ADDRESS
#define TGPS_DATA_VII      0xD7  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.7 ADDRESS
#define TGPS_DATA_VIII     0xD8  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.8 ADDRESS

#define TGPS_DATA_IX       0xD9  // KNACKSAT_II - TGPS ,****DATA   MICRO SD CARD ADDRESS

//SLAVE REGISTER COMMAND
#define TGPS_CMD_I         0xC1  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.1 ADDRESS
#define TGPS_CMD_II        0xC2  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.2 ADDRESS
#define TGPS_CMD_III       0xC3  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.3 ADDRESS
#define TGPS_CMD_IV        0xC4  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.4 ADDRESS
#define TGPS_CMD_V         0xC5  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.5 ADDRESS
#define TGPS_CMD_VI        0xC6  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.6 ADDRESS
#define TGPS_CMD_VII       0xC7  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.7 ADDRESS
#define TGPS_CMD_VIII      0xC8  // KNACKSAT_II - TGPS ,****DATA     RADFET NO.8 ADDRESS

#define TGPS_CMD_IX        0xC9  // KNACKSAT_II - TGPS ,****DATA   MICRO SD CARD ADDRESS



int N ;
String L;
String M;
byte data_input[32];
byte data_cmd[2] ;
void setup()
{
  Wire.begin();
  Serial.begin(115200);
  Serial.println(" MASTER ");
}

void loop()
{
  while (Serial.available() > 0)
  {
    L = Serial.readStringUntil(' ');
    M = Serial.readStringUntil(' ');
    N = M.toInt();
    Serial.println(L);
    Serial.println(M);
    if ( L == "D")
    {
      switch (N)
      {
        case 1 :
          Serial.println("DOWNLOAD I");
          DOWNLOAD(TGPS_ID,    TGPS_DATA_I, data_input, 32  , 50);
          break;
        case 2 :
          Serial.println("DOWNLOAD II");
          DOWNLOAD(TGPS_ID,   TGPS_DATA_II, data_input, 32  , 50);
          break;
        case 3 :
          Serial.println("DOWNLOAD III");
          DOWNLOAD(TGPS_ID,  TGPS_DATA_III, data_input, 32  , 50);
          break;
        case 4 :
          Serial.println("DOWNLOAD IV");
          DOWNLOAD(TGPS_ID,   TGPS_DATA_IV, data_input, 32  , 50);
          break;
        case 5 :
          Serial.println("DOWNLOAD V");
          DOWNLOAD(TGPS_ID,    TGPS_DATA_V, data_input, 32  , 50);
          break;
        case 6 :
          Serial.println("DOWNLOAD VI");
          DOWNLOAD(TGPS_ID,   TGPS_DATA_VI, data_input, 32  , 50);
          break;
        case 7 :
          Serial.println("DOWNLOAD VII");
          DOWNLOAD(TGPS_ID,  TGPS_DATA_VII, data_input, 32  , 50);
          break;
        case 8 :
          Serial.println("DOWNLOAD VIII");
          DOWNLOAD(TGPS_ID, TGPS_DATA_VIII, data_input, 32  , 50);
          break;
        case 9 :
          Serial.println("DOWNLOAD IX");
          DOWNLOAD(TGPS_ID,   TGPS_DATA_IX, data_input, 32  , 50);
          break;
        case 11 :
          Serial.println("DOWNLOAD STATUS CMD RADFET");
          DOWNLOAD(TGPS_ID,        TGPS_SCR,  data_cmd ,  1  , 50);
          break;
        case 12:
          Serial.println("DOWNLOAD STATUS CMD SD CARD");
          DOWNLOAD(TGPS_ID,        TGPS_SCC,  data_cmd ,  1  , 50);
          break;
      }
    }
    if ( L == "U")
    {
      switch (N)
      {
        case 1 :
          Serial.print("UPLOAD : ");Serial.println(TGPS_CMD_I, HEX);
          UPLOAD(TGPS_ID, TGPS_CMD ,     TGPS_CMD_I, data_cmd );
          break;
        case 2 :
          Serial.print("UPLOAD : ");Serial.println(TGPS_CMD_II, HEX );
          UPLOAD(TGPS_ID, TGPS_CMD ,    TGPS_CMD_II, data_cmd );
          break;
        case 3 :
          Serial.print("UPLOAD : ");Serial.println(TGPS_CMD_III, HEX);
          UPLOAD(TGPS_ID, TGPS_CMD ,   TGPS_CMD_III, data_cmd );
          break;
        case 4 :
          Serial.print("UPLOAD : ");Serial.println(TGPS_CMD_IV, HEX);
          UPLOAD(TGPS_ID, TGPS_CMD ,    TGPS_CMD_IV, data_cmd );
          break;
        case 5 :
          Serial.print("UPLOAD : ");Serial.println(TGPS_CMD_V, HEX);
          UPLOAD(TGPS_ID, TGPS_CMD ,     TGPS_CMD_V, data_cmd );
          break;
        case 6 :
          Serial.print("UPLOAD : ");Serial.println(TGPS_CMD_VI, HEX);
          UPLOAD(TGPS_ID, TGPS_CMD ,    TGPS_CMD_VI, data_cmd );
          break;
        case 7 :
          Serial.print("UPLOAD : ");Serial.println(TGPS_CMD_VII, HEX);
          UPLOAD(TGPS_ID, TGPS_CMD ,   TGPS_CMD_VII, data_cmd );
          break;
        case 8 :
          Serial.print("UPLOAD : ");Serial.println(TGPS_CMD_VIII, HEX);
          UPLOAD(TGPS_ID, TGPS_CMD ,  TGPS_CMD_VIII, data_cmd );
          break;
        case 9 :
          Serial.print("UPLOAD : ");Serial.println(TGPS_CMD_IX, HEX);
          UPLOAD(TGPS_ID, TGPS_CMD ,    TGPS_CMD_IX, data_cmd );
          break;
      }
    }
  }
}
void DOWNLOAD (
  byte ADDR
  , byte RGADDR
  , byte * data
  , byte n
  , unsigned long microsec
)
{
  Wire.beginTransmission(ADDR);
  Wire.write(RGADDR);
  Wire.endTransmission();

  delay(microsec);

  int i = 0;
  Wire.requestFrom(ADDR, n);
  Serial.println(RGADDR, HEX);
  Serial.println("=========================================");
  while (Wire.available() > 0)
  {
    data[i] = Wire.read();
    Serial.print(String(data[i]) + " ");
    i++;
  }
  Serial.println(" End");
  Serial.println("=========================================");
  if (i != n)
    Serial.println("Error!!! :" + String(i) + "  ,  " + String(n));
  //Serial.println( " , ");
}



void UPLOAD (
  byte ADDR
  , byte cmd // COMMAND
  , byte configs
  , byte *data
)
{
  Wire.beginTransmission(ADDR);
  Wire.write(cmd);
  Wire.write(configs);
  Wire.endTransmission();
  delay(10);
  Wire.requestFrom(ADDR, 1);
  int i = 0;
  while (Wire.available() > 0)
  {
    data[i] = Wire.read();
    Serial.println(data[i], HEX);
    i++;
  }
}
