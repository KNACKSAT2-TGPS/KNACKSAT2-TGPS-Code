



void RUNNING_CMD_I()
{
  while (REQUEST_I == true)
  {
    Serial.println("REQUEST_I");

    if (STATE_BREAK != 1)
    {
      Serial.println("BREAK");
      REQUEST_I   = false ;
      break;
    }

    READ_RADFET(0, RADFET_0);

    memcpy( &BUS_I[0],  &RADFET_0[0],  sizeof(RADFET_0[0]));
    memcpy( &BUS_I[2],  &RADFET_0[1],  sizeof(RADFET_0[1]));
    memcpy( &BUS_I[4],  &RADFET_0[2],  sizeof(RADFET_0[2]));
    memcpy( &BUS_I[6],  &RADFET_0[3],  sizeof(RADFET_0[3]));
    memcpy( &BUS_I[8],  &RADFET_0[4],  sizeof(RADFET_0[4]));
    memcpy(&BUS_I[10],  &RADFET_0[5],  sizeof(RADFET_0[5]));
    memcpy(&BUS_I[12],  &RADFET_0[6],  sizeof(RADFET_0[6]));
    memcpy(&BUS_I[14],  &RADFET_0[7],  sizeof(RADFET_0[7]));

    memcpy(&BUS_I[16],  &RADFET_0[8],  sizeof(RADFET_0[8]));
    memcpy(&BUS_I[18],  &RADFET_0[9],  sizeof(RADFET_0[9]));
    memcpy(&BUS_I[20], &RADFET_0[10], sizeof(RADFET_0[10]));
    memcpy(&BUS_I[22], &RADFET_0[11], sizeof(RADFET_0[11]));
    memcpy(&BUS_I[24], &RADFET_0[12], sizeof(RADFET_0[12]));
    memcpy(&BUS_I[26], &RADFET_0[13], sizeof(RADFET_0[13]));
    memcpy(&BUS_I[28], &RADFET_0[14], sizeof(RADFET_0[14]));
    memcpy(&BUS_I[30], &RADFET_0[15], sizeof(RADFET_0[15]));

    PRINT(BUS_I);

    Serial.println("========================================================================");
//    REGIS_CMD = TGPS_DATA_II;
//    REGIS_ADDR = true;
    REQUEST_I   = false ;
    //STATE_BREAK = false ;
  }
}



void RUNNING_CMD_II()
{
  while (REQUEST_II == true)
  {
    Serial.println("REQUEST_II");

    if (STATE_BREAK != 2)
    {
      REQUEST_II  = false ;
      break;
    }

    READ_RADFET(1, RADFET_1);

    memcpy( &BUS_II[0],  &RADFET_1[0],  sizeof(RADFET_1[0]));
    memcpy( &BUS_II[2],  &RADFET_1[1],  sizeof(RADFET_1[1]));
    memcpy( &BUS_II[4],  &RADFET_1[2],  sizeof(RADFET_1[2]));
    memcpy( &BUS_II[6],  &RADFET_1[3],  sizeof(RADFET_1[3]));
    memcpy( &BUS_II[8],  &RADFET_1[4],  sizeof(RADFET_1[4]));
    memcpy(&BUS_II[10],  &RADFET_1[5],  sizeof(RADFET_1[5]));
    memcpy(&BUS_II[12],  &RADFET_1[6],  sizeof(RADFET_1[6]));
    memcpy(&BUS_II[14],  &RADFET_1[7],  sizeof(RADFET_1[7]));

    memcpy(&BUS_II[16],  &RADFET_1[8],  sizeof(RADFET_1[8]));
    memcpy(&BUS_II[18],  &RADFET_1[9],  sizeof(RADFET_1[9]));
    memcpy(&BUS_II[20], &RADFET_1[10], sizeof(RADFET_1[10]));
    memcpy(&BUS_II[22], &RADFET_1[11], sizeof(RADFET_1[11]));
    memcpy(&BUS_II[24], &RADFET_1[12], sizeof(RADFET_1[12]));
    memcpy(&BUS_II[26], &RADFET_1[13], sizeof(RADFET_1[13]));
    memcpy(&BUS_II[28], &RADFET_1[14], sizeof(RADFET_1[14]));
    memcpy(&BUS_II[30], &RADFET_1[15], sizeof(RADFET_1[15]));

    PRINT(BUS_II);

    Serial.println("========================================================================");
//    REGIS_CMD = TGPS_DATA_III;
//    REGIS_ADDR = true;
    REQUEST_II  = false ;
    //STATE_BREAK = false ;
  }
}



void RUNNING_CMD_III()
{
  while (REQUEST_III == true)
  {
    Serial.println("REQUEST_III");

    if (STATE_BREAK != 4)
    {
      REQUEST_III = false ;
      break;
    }

    READ_RADFET(2, RADFET_2);

    memcpy( &BUS_III[0],  &RADFET_2[0],  sizeof(RADFET_2[0]));
    memcpy( &BUS_III[2],  &RADFET_2[1],  sizeof(RADFET_2[1]));
    memcpy( &BUS_III[4],  &RADFET_2[2],  sizeof(RADFET_2[2]));
    memcpy( &BUS_III[6],  &RADFET_2[3],  sizeof(RADFET_2[3]));
    memcpy( &BUS_III[8],  &RADFET_2[4],  sizeof(RADFET_2[4]));
    memcpy(&BUS_III[10],  &RADFET_2[5],  sizeof(RADFET_2[5]));
    memcpy(&BUS_III[12],  &RADFET_2[6],  sizeof(RADFET_2[6]));
    memcpy(&BUS_III[14],  &RADFET_2[7],  sizeof(RADFET_2[7]));

    memcpy(&BUS_III[16],  &RADFET_2[8],  sizeof(RADFET_2[8]));
    memcpy(&BUS_III[18],  &RADFET_2[9],  sizeof(RADFET_2[9]));
    memcpy(&BUS_III[20], &RADFET_2[10], sizeof(RADFET_2[10]));
    memcpy(&BUS_III[22], &RADFET_2[11], sizeof(RADFET_2[11]));
    memcpy(&BUS_III[24], &RADFET_2[12], sizeof(RADFET_2[12]));
    memcpy(&BUS_III[26], &RADFET_2[13], sizeof(RADFET_2[13]));
    memcpy(&BUS_III[28], &RADFET_2[14], sizeof(RADFET_2[14]));
    memcpy(&BUS_III[30], &RADFET_2[15], sizeof(RADFET_2[15]));

    PRINT(BUS_III);

    Serial.println("========================================================================");
//    REGIS_CMD = TGPS_DATA_IV;
//    REGIS_ADDR = true;
    REQUEST_III = false ;
    //STATE_BREAK = false ;
  }
}



void RUNNING_CMD_IV()
{
  while (REQUEST_IV == true)
  {
    Serial.println("REQUEST_IV");

    if (STATE_BREAK != 8)
    {
      REQUEST_IV = false ;
      break;
    }

    READ_RADFET(3, RADFET_3);

    memcpy( &BUS_IV[0],  &RADFET_3[0],  sizeof(RADFET_3[0]));
    memcpy( &BUS_IV[2],  &RADFET_3[1],  sizeof(RADFET_3[1]));
    memcpy( &BUS_IV[4],  &RADFET_3[2],  sizeof(RADFET_3[2]));
    memcpy( &BUS_IV[6],  &RADFET_3[3],  sizeof(RADFET_3[3]));
    memcpy( &BUS_IV[8],  &RADFET_3[4],  sizeof(RADFET_3[4]));
    memcpy(&BUS_IV[10],  &RADFET_3[5],  sizeof(RADFET_3[5]));
    memcpy(&BUS_IV[12],  &RADFET_3[6],  sizeof(RADFET_3[6]));
    memcpy(&BUS_IV[14],  &RADFET_3[7],  sizeof(RADFET_3[7]));

    memcpy(&BUS_IV[16],  &RADFET_3[8],  sizeof(RADFET_3[8]));
    memcpy(&BUS_IV[18],  &RADFET_3[9],  sizeof(RADFET_3[9]));
    memcpy(&BUS_IV[20], &RADFET_3[10], sizeof(RADFET_3[10]));
    memcpy(&BUS_IV[22], &RADFET_3[11], sizeof(RADFET_3[11]));
    memcpy(&BUS_IV[24], &RADFET_3[12], sizeof(RADFET_3[12]));
    memcpy(&BUS_IV[26], &RADFET_3[13], sizeof(RADFET_3[13]));
    memcpy(&BUS_IV[28], &RADFET_3[14], sizeof(RADFET_3[14]));
    memcpy(&BUS_IV[30], &RADFET_3[15], sizeof(RADFET_3[15]));

    PRINT(BUS_IV);

    Serial.println("========================================================================");
//    REGIS_CMD = TGPS_DATA_V;
//    REGIS_ADDR = true;
    REQUEST_IV  = false ;
    STATE_BREAK = false ;
  }
}



void RUNNING_CMD_V()
{
  while (REQUEST_V == true)
  {
    Serial.println("REQUEST_V");

    if (STATE_BREAK != 16)
    {
      REQUEST_V = false ;
      break;
    }

    READ_RADFET(4, RADFET_4);
    
    memcpy( &BUS_V[0],  &RADFET_4[0],  sizeof(RADFET_4[0]));
    memcpy( &BUS_V[2],  &RADFET_4[1],  sizeof(RADFET_4[1]));
    memcpy( &BUS_V[4],  &RADFET_4[2],  sizeof(RADFET_4[2]));
    memcpy( &BUS_V[6],  &RADFET_4[3],  sizeof(RADFET_4[3]));
    memcpy( &BUS_V[8],  &RADFET_4[4],  sizeof(RADFET_4[4]));
    memcpy(&BUS_V[10],  &RADFET_4[5],  sizeof(RADFET_4[5]));
    memcpy(&BUS_V[12],  &RADFET_4[6],  sizeof(RADFET_4[6]));
    memcpy(&BUS_V[14],  &RADFET_4[7],  sizeof(RADFET_4[7]));

    memcpy(&BUS_V[16],  &RADFET_4[8],  sizeof(RADFET_4[8]));
    memcpy(&BUS_V[18],  &RADFET_4[9],  sizeof(RADFET_4[9]));
    memcpy(&BUS_V[20], &RADFET_4[10], sizeof(RADFET_4[10]));
    memcpy(&BUS_V[22], &RADFET_4[11], sizeof(RADFET_4[11]));
    memcpy(&BUS_V[24], &RADFET_4[12], sizeof(RADFET_4[12]));
    memcpy(&BUS_V[26], &RADFET_4[13], sizeof(RADFET_4[13]));
    memcpy(&BUS_V[28], &RADFET_4[14], sizeof(RADFET_4[14]));
    memcpy(&BUS_V[30], &RADFET_4[15], sizeof(RADFET_4[15]));

    PRINT(BUS_V);

    Serial.println("========================================================================");
//    REGIS_CMD = TGPS_DATA_VI;
//    REGIS_ADDR = true;
    REQUEST_V   = false ;
    STATE_BREAK = false ;
  }
}



void RUNNING_CMD_VI()
{
  while (REQUEST_VI == true)
  {
    Serial.println("REQUEST_VI");

    if (STATE_BREAK != 32)
    {
      REQUEST_VI = false ;
      break;
    }

    READ_RADFET(5, RADFET_5);

    memcpy( &BUS_VI[0],  &RADFET_5[0],  sizeof(RADFET_5[0]));
    memcpy( &BUS_VI[2],  &RADFET_5[1],  sizeof(RADFET_5[1]));
    memcpy( &BUS_VI[4],  &RADFET_5[2],  sizeof(RADFET_5[2]));
    memcpy( &BUS_VI[6],  &RADFET_5[3],  sizeof(RADFET_5[3]));
    memcpy( &BUS_VI[8],  &RADFET_5[4],  sizeof(RADFET_5[4]));
    memcpy(&BUS_VI[10],  &RADFET_5[5],  sizeof(RADFET_5[5]));
    memcpy(&BUS_VI[12],  &RADFET_5[6],  sizeof(RADFET_5[6]));
    memcpy(&BUS_VI[14],  &RADFET_5[7],  sizeof(RADFET_5[7]));

    memcpy(&BUS_VI[16],  &RADFET_5[8],  sizeof(RADFET_5[8]));
    memcpy(&BUS_VI[18],  &RADFET_5[9],  sizeof(RADFET_5[9]));
    memcpy(&BUS_VI[20], &RADFET_5[10], sizeof(RADFET_5[10]));
    memcpy(&BUS_VI[22], &RADFET_5[11], sizeof(RADFET_5[11]));
    memcpy(&BUS_VI[24], &RADFET_5[12], sizeof(RADFET_5[12]));
    memcpy(&BUS_VI[26], &RADFET_5[13], sizeof(RADFET_5[13]));
    memcpy(&BUS_VI[28], &RADFET_5[14], sizeof(RADFET_5[14]));
    memcpy(&BUS_VI[30], &RADFET_5[15], sizeof(RADFET_5[15]));

    PRINT(BUS_VI);

    Serial.println("========================================================================");
//    REGIS_CMD = TGPS_DATA_VII;
//    REGIS_ADDR = true;
    REQUEST_VI  = false ;
    STATE_BREAK = false ;
  }
}



void RUNNING_CMD_VII()
{
  while (REQUEST_VII == true)
  {
    Serial.println("REQUEST_VII");

    if (STATE_BREAK != 64)
    {
      REQUEST_VII = false ;
      break;
    }

    READ_RADFET(6, RADFET_6);

    memcpy( &BUS_VII[0],  &RADFET_6[0],  sizeof(RADFET_6[0]));
    memcpy( &BUS_VII[2],  &RADFET_6[1],  sizeof(RADFET_6[1]));
    memcpy( &BUS_VII[4],  &RADFET_6[2],  sizeof(RADFET_6[2]));
    memcpy( &BUS_VII[6],  &RADFET_6[3],  sizeof(RADFET_6[3]));
    memcpy( &BUS_VII[8],  &RADFET_6[4],  sizeof(RADFET_6[4]));
    memcpy(&BUS_VII[10],  &RADFET_6[5],  sizeof(RADFET_6[5]));
    memcpy(&BUS_VII[12],  &RADFET_6[6],  sizeof(RADFET_6[6]));
    memcpy(&BUS_VII[14],  &RADFET_6[7],  sizeof(RADFET_6[7]));

    memcpy(&BUS_VII[16],  &RADFET_6[8],  sizeof(RADFET_6[8]));
    memcpy(&BUS_VII[18],  &RADFET_6[9],  sizeof(RADFET_6[9]));
    memcpy(&BUS_VII[20], &RADFET_6[10], sizeof(RADFET_6[10]));
    memcpy(&BUS_VII[22], &RADFET_6[11], sizeof(RADFET_6[11]));
    memcpy(&BUS_VII[24], &RADFET_6[12], sizeof(RADFET_6[12]));
    memcpy(&BUS_VII[26], &RADFET_6[13], sizeof(RADFET_6[13]));
    memcpy(&BUS_VII[28], &RADFET_6[14], sizeof(RADFET_6[14]));
    memcpy(&BUS_VII[30], &RADFET_6[15], sizeof(RADFET_6[15]));

    PRINT(BUS_VII);

    Serial.println("========================================================================");
//    REGIS_CMD = TGPS_DATA_VIII;
//    REGIS_ADDR = true;
    REQUEST_VII = false ;
    STATE_BREAK = false ;
  }
}



void RUNNING_CMD_VIII()
{
  while (REQUEST_VIII == true)
  {
    Serial.println("REQUEST_VIII");

    if (STATE_BREAK != 128)
    {
      REQUEST_VIII = false ;
      break;
    }

    READ_RADFET(7, RADFET_7);

    memcpy( &BUS_VIII[0],  &RADFET_7[0],  sizeof(RADFET_7[0]));
    memcpy( &BUS_VIII[2],  &RADFET_7[1],  sizeof(RADFET_7[1]));
    memcpy( &BUS_VIII[4],  &RADFET_7[2],  sizeof(RADFET_7[2]));
    memcpy( &BUS_VIII[6],  &RADFET_7[3],  sizeof(RADFET_7[3]));
    memcpy( &BUS_VIII[8],  &RADFET_7[4],  sizeof(RADFET_7[4]));
    memcpy(&BUS_VIII[10],  &RADFET_7[5],  sizeof(RADFET_7[5]));
    memcpy(&BUS_VIII[12],  &RADFET_7[6],  sizeof(RADFET_7[6]));
    memcpy(&BUS_VIII[14],  &RADFET_7[7],  sizeof(RADFET_7[7]));

    memcpy(&BUS_VIII[16],  &RADFET_7[8],  sizeof(RADFET_7[8]));
    memcpy(&BUS_VIII[18],  &RADFET_7[9],  sizeof(RADFET_7[9]));
    memcpy(&BUS_VIII[20], &RADFET_7[10], sizeof(RADFET_7[10]));
    memcpy(&BUS_VIII[22], &RADFET_7[11], sizeof(RADFET_7[11]));
    memcpy(&BUS_VIII[24], &RADFET_7[12], sizeof(RADFET_7[12]));
    memcpy(&BUS_VIII[26], &RADFET_7[13], sizeof(RADFET_7[13]));
    memcpy(&BUS_VIII[28], &RADFET_7[14], sizeof(RADFET_7[14]));
    memcpy(&BUS_VIII[30], &RADFET_7[15], sizeof(RADFET_7[15]));

    PRINT(BUS_VIII);

    Serial.println("========================================================================");
//    REGIS_CMD = TGPS_DATA_IX;
//    REGIS_ADDR = true;
    REQUEST_VIII = false ;
    STATE_BREAK  = false ;
  }
}



void RUNNING_CMD_IX()
{
  while (REQUEST_IX == true)
  {
    Serial.println("REQUEST_IX");

    if (STATE_BREAK != 256)
    {
      REQUEST_IX = false ;
      break;
    }
    
    CHECKTEXT(6000);

    PSE = PSS << 7 | PES;

    memcpy( &BUS_IX[0],        &PSE, sizeof(       PSE));
    memcpy( &BUS_IX[1],         &FN, sizeof(        FN));
    memcpy( &BUS_IX[2],      &COUNT, sizeof(     COUNT));
    memcpy( &BUS_IX[6], &ERROR_CHAR, sizeof(ERROR_CHAR));
    memcpy(&BUS_IX[10],         &TP, sizeof(        TP));
    memcpy(&BUS_IX[14],        &CTC, sizeof(       CTC));
    memcpy(&BUS_IX[15],         &FC, sizeof(        FC));

    PSE = 0x00  ;
    PSS = false ;
    PES = false ;

    CHECKTEXT(6000);

    PSE = PSS << 7 | PES ;

    memcpy(&BUS_IX[16],        &PSE, sizeof(       PSE));
    memcpy(&BUS_IX[17],         &FN, sizeof(        FN));
    memcpy(&BUS_IX[18],      &COUNT, sizeof(     COUNT));
    memcpy(&BUS_IX[22], &ERROR_CHAR, sizeof(ERROR_CHAR));
    memcpy(&BUS_IX[26],         &TP, sizeof(        TP));
    memcpy(&BUS_IX[30],        &CTC, sizeof(       CTC));
    memcpy(&BUS_IX[31],         &FC, sizeof(        FC));

    PSE = 0x00  ;
    PSS = false ;
    PES = false ;

    PRINT(BUS_IX);
    
    Serial.println("========================================================================");
//    REGIS_CMD = TGPS_DATA_I;
//    REGIS_ADDR = true;
    REQUEST_IX = false;
  }
}
