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
  fx = 0 ;

  if (STATE == 0)
  {
    PIN_SD_CS = PIN_SD_CS1;
    digitalWrite(PIN_SD_CS1,  LOW);
    digitalWrite(PIN_SD_CS2, HIGH);
  }
  if (STATE == 1)
  {
    PIN_SD_CS = PIN_SD_CS2;
    digitalWrite(PIN_SD_CS1, HIGH);
    digitalWrite(PIN_SD_CS2,  LOW);
  }

  while (!SD.begin(PIN_SD_CS))
  {
    CURRENTMILLIS = millis();
    if ((unsigned long)(CURRENTMILLIS - PREVIOUSMILLIS) >= INTERVAL)
    {
      STATE = !STATE;
      return;
    }
    if (STATE_REQUEST != 256)
    {
      REQUEST_IX = false ;
      break;
    }
  }

  READ_RECENTFILE();
  while (true)
  {
    if (((unsigned long)(CURRENTMILLIS - PREVIOUSMILLIS) >= INTERVAL) || fx == 1 )
    {
      break;
    }
    PSS            = true          ;
    ERROR_CHAR = 0;
    COUNT = 0;
    if (LASTED_FILE <= 122)
    {
      LASTED_FILE++;
    }
    if (LASTED_FILE >= 123)
    {
      LASTED_FILE = 97;
    }
    String FILENAME = String(char(LASTED_FILE)) + ".txt" ;
    File f = SD.open(FILENAME, O_RDONLY);
    if (!f)
    {
      break;
    }

    while (f.available())
    {
      FN = LASTED_FILE;
      CURRENTMILLIS = millis();
      if ((unsigned long)(CURRENTMILLIS - PREVIOUSMILLIS) >= INTERVAL)
      {
        fx = 1 ;
        break;
      }
      if (STATE_REQUEST != 256)
      {
        REQUEST_IX = false ;
        break;
      }
      int n = f.read(BUFFER, sizeof(BUFFER));
      FC = BUFFER[0];
      for (int i = 0; i < n; i++)
      {
        if (BUFFER[i] != 48)
        {
          ERROR_CHAR++;
        }
        COUNT++;
      }
    }
    f.close();
    PES            = true          ;
    break;
  }
  SAVE_RECENTFILE();
  STATE          = !STATE        ;
  TEP            = millis()      ;
  TP             = TEP - TSP     ;
}



void READ_RECENTFILE() { 
  File myFile;
  String fileName = "rf.txt";
  if (!SD.begin(PIN_SD_CS))
  {
    return;
  }

  myFile = SD.open(fileName, FILE_READ);
  if (myFile)
  {
    while (myFile.available())
    {
      LASTED_FILE = myFile.read();
    }
    myFile.close();
  }
}

void SAVE_RECENTFILE() {
  String fileName = "rf.txt";
  File myFile;
  if (!SD.begin(PIN_SD_CS))
  {
    return;
  }
  SD.remove(fileName);              //DELETE OLD FILE
  myFile = SD.open(fileName, FILE_WRITE);
  if (myFile)
  {
    myFile.print(String(char(LASTED_FILE)));
    myFile.close();
  }
}
