//=========================<<<CHECKTEXT>>>=========================

// CHECKTEXT     : READ DATA THEN CHECK ERROR AND STORAGE TO ARRAY.
// BEGIN_FILE    : FRIST NUMBER NAME OF FILE.
// END_FILE      : LAST NUMBER NAME OF FILE.
// NOC           : NUMBER OF CHARACTER.
// INTERVAL      : VALUE OF TIME OUT.

void CHECKTEXT(unsigned long INTERVAL)
{
  TSP            = millis()      ;
  CTC            = 48            ;
  CURRENTMILLIS  = millis()      ;
  PREVIOUSMILLIS = CURRENTMILLIS ;
  Serial.println("Initialising SD card...");
  fx = 0 ;
  if (STATE == 0)
  {
    PIN_SD_CS = PIN_SD_CS1;
    digitalWrite(PIN_SD_CS1,  LOW);
    digitalWrite(PIN_SD_CS2, HIGH);
    Serial.println("PINSD1");
  }
  if (STATE == 1)
  {
    PIN_SD_CS = PIN_SD_CS2;
    digitalWrite(PIN_SD_CS1, HIGH);
    digitalWrite(PIN_SD_CS2,  LOW);
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
      STATE = !STATE;
      return;
    }
    /*if (REQUEST_I == true || REQUEST_II == true || REQUEST_III == true || REQUEST_IV == true)
      {
      break;
      }*/
  }
  Serial.println("Micro SD-card initialised. Please wait : " + String(INTERVAL));
  readrecentfile();
  while (true)
  {
    if (((unsigned long)(CURRENTMILLIS - PREVIOUSMILLIS) >= INTERVAL) || fx == 1 )
    {
      break;
    }
    PSS            = true          ;
    ERROR_CHAR = 0;
    COUNT = 0;
    if (recentfile <= 122)
    {
      recentfile++;
    }
    if (recentfile >= 123)
    {
      recentfile = 97;
    }
    String FILENAME = String(char(recentfile)) + ".txt" ;
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
      FN = recentfile;
      CURRENTMILLIS = millis();
      if ((unsigned long)(CURRENTMILLIS - PREVIOUSMILLIS) >= INTERVAL)
      {
        Serial.println("Time out");
        fx = 1 ;
        break;
      }
      if (STATE_BREAK != 256)
      {
        REQUEST_IX = false ;
        break;
      }
      int n = f.read(buf, sizeof(buf));
      FC = buf[0];
      for (int i = 0; i < n; i++)
      {
        if (buf[i] != 48)
        {
          ERROR_CHAR++;
          Serial.println(buf[i]);
        }
        COUNT++;
      }
    }
    f.close();
    Serial.print("Bit error count : "); Serial.println(ERROR_CHAR);
    Serial.print("From : "); Serial.println(COUNT);
    PES            = true          ;
    break;
  }
  Serial.print("Bit error count : "); Serial.println(ERROR_CHAR);
  Serial.print("From : "); Serial.println(COUNT);
  saverecentfile();
  STATE          = !STATE        ;
  TEP            = millis()      ;
  TP             = TEP - TSP     ;
}



void readrecentfile() {
  File myFile;
  String fileName = "rf.txt";
  if (!SD.begin(PIN_SD_CS))
  {
    Serial.println("Initialization failed!");
    return;
  }
  Serial.println("Initialization done.");
  myFile = SD.open(fileName, FILE_READ);
  if (myFile)
  {
    Serial.print("Reading from "); Serial.println(fileName);
    Serial.println("SD" + String(PIN_SD_CS));
    Serial.println("===============");
    while (myFile.available())
    {
      recentfile = myFile.read();
      Serial.println(char(recentfile));
    }
    myFile.close();
    Serial.println("===============");
  }
  else
  {
    Serial.print("Error opening "); Serial.println(fileName);
  }
}

void saverecentfile() {
  String fileName = "rf.txt";
  File myFile;
  if (!SD.begin(PIN_SD_CS))
  {
    Serial.println("Initialization failed!");
    return;
  }
  Serial.println("Initialization done.");
  SD.remove(fileName);              //DELETE OLD FILE
  myFile = SD.open(fileName, FILE_WRITE);
  if (myFile)
  {
    Serial.print("Writing to "); Serial.print(fileName); Serial.print(" ==> "); Serial.println(String(char(recentfile)));
    myFile.print(String(char(recentfile)));
    myFile.close();
    Serial.println("done.");
  }
  else
  {
    // if the file didn't open, print an error:
    Serial.print("Error opening "); Serial.println(fileName);
  }
}
