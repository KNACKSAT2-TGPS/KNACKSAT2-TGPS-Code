#include <Wire.h>

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


int N ;
String L;
String M;
byte data_input[32];
byte data_cmd[2] ; 
void setup()
{
  Wire.begin();
  Serial.begin(115200);
  Serial.println("master");
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
            Serial.println("DOWNLOAD 1");
            DOWNLOAD(TGPS_ID, TGPS_DATA_I, data_input, 32  , 50);
            break;
           case 2 :
            Serial.println("DOWNLOAD 2");
            DOWNLOAD(TGPS_ID, TGPS_DATA_II, data_input, 32  , 50);
            break;
           case 3 :
            Serial.println("DOWNLOAD 3");
            DOWNLOAD(TGPS_ID, TGPS_DATA_III, data_input, 32  , 50);
            break;
           case 4 :
            Serial.println("DOWNLOAD STATUS");
            DOWNLOAD(TGPS_ID, TGPS_SS, data_cmd , 1  , 50);
            break;
        }      
    }
    if ( L == "U")
    {
      switch (N) 
        {
           case 1 :
            Serial.print("UPLOAD : ");
            Serial.println(RESET_TGPS,HEX);
            UPLOAD(TGPS_ID, TGPS_MM ,  RESET_TGPS , data_cmd );
            break;
           case 2 :
            Serial.print("UPLOAD : ");
            Serial.println(RESET_SD_CARD,HEX );
            UPLOAD(TGPS_ID, TGPS_MM ,  RESET_SD_CARD  , data_cmd );
            break;
           case 3 :
            Serial.print("UPLOAD : ");
            Serial.println(RESET_SENSOR ,HEX);
            UPLOAD(TGPS_ID, TGPS_MM ,  RESET_SENSOR  , data_cmd );
            break;
           case 4 :
            Serial.print("UPLOAD : ");
            Serial.println(ENABLE_SD_CARD ,HEX);
            UPLOAD(TGPS_ID, TGPS_MM ,  ENABLE_SD_CARD  , data_cmd );
            break;
           case 5 :
            Serial.print("UPLOAD : ");
            Serial.println(DISENABLE_SD_CARD ,HEX);
            UPLOAD(TGPS_ID, TGPS_MM ,  DISENABLE_SD_CARD  , data_cmd );
            break;
           case 6 :
            Serial.print("UPLOAD : ");
            Serial.println(ENABLE_SENSOR ,HEX);
            UPLOAD(TGPS_ID, TGPS_MM ,  ENABLE_SENSOR  , data_cmd );
            break;
           case 7 :
            Serial.print("UPLOAD : ");
            Serial.println(DISENABLE_SENSOR ,HEX);
            UPLOAD(TGPS_ID, TGPS_MM ,  DISENABLE_SENSOR  , data_cmd );
            break;
        }      
    }
  }
}
void DOWNLOAD ( byte ADDR ,  byte RGADDR , byte * data,  byte n, unsigned long microsec)
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
              ,byte cmd // COMMAND 
              ,byte configs
              ,byte *data         
             )
{
  Wire.beginTransmission(ADDR);
  Wire.write(cmd);
  Wire.write(configs); 
  Wire.endTransmission();                 
  delay(10);  
  Wire.requestFrom(ADDR, 1);  
  int i = 0; 
   while(Wire.available() > 0)
  {
     data[i] = Wire.read(); 
     Serial.println(data[i],HEX); 
     i++;
  }
}
