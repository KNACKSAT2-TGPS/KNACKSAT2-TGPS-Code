



void RUNNING_CMD_I()
{
  while (REQUEST_I == true)
  {
    if (STATE_REQUEST != 1)
    {
      REQUEST_I   = false ;
      break;
    }

    READ_RADFET(0, RADFET_I);

    memcpy( &BUS_I[0],  &RADFET_I[0],  sizeof(RADFET_I[0]));
    memcpy( &BUS_I[2],  &RADFET_I[1],  sizeof(RADFET_I[1]));
    memcpy( &BUS_I[4],  &RADFET_I[2],  sizeof(RADFET_I[2]));
    memcpy( &BUS_I[6],  &RADFET_I[3],  sizeof(RADFET_I[3]));
    memcpy( &BUS_I[8],  &RADFET_I[4],  sizeof(RADFET_I[4]));
    memcpy(&BUS_I[10],  &RADFET_I[5],  sizeof(RADFET_I[5]));
    memcpy(&BUS_I[12],  &RADFET_I[6],  sizeof(RADFET_I[6]));
    memcpy(&BUS_I[14],  &RADFET_I[7],  sizeof(RADFET_I[7]));

    memcpy(&BUS_I[16],  &RADFET_I[8],  sizeof(RADFET_I[8]));
    memcpy(&BUS_I[18],  &RADFET_I[9],  sizeof(RADFET_I[9]));
    memcpy(&BUS_I[20], &RADFET_I[10], sizeof(RADFET_I[10]));
    memcpy(&BUS_I[22], &RADFET_I[11], sizeof(RADFET_I[11]));
    memcpy(&BUS_I[24], &RADFET_I[12], sizeof(RADFET_I[12]));
    memcpy(&BUS_I[26], &RADFET_I[13], sizeof(RADFET_I[13]));
    memcpy(&BUS_I[28], &RADFET_I[14], sizeof(RADFET_I[14]));
    memcpy(&BUS_I[30], &RADFET_I[15], sizeof(RADFET_I[15]));

    REQUEST_I   = false ;
  }
}



void RUNNING_CMD_II()
{
  while (REQUEST_II == true)
  {
    if (STATE_REQUEST != 2)
    {
      REQUEST_II  = false ;
      break;
    }

    READ_RADFET(1, RADFET_II);

    memcpy( &BUS_II[0],  &RADFET_II[0],  sizeof(RADFET_II[0]));
    memcpy( &BUS_II[2],  &RADFET_II[1],  sizeof(RADFET_II[1]));
    memcpy( &BUS_II[4],  &RADFET_II[2],  sizeof(RADFET_II[2]));
    memcpy( &BUS_II[6],  &RADFET_II[3],  sizeof(RADFET_II[3]));
    memcpy( &BUS_II[8],  &RADFET_II[4],  sizeof(RADFET_II[4]));
    memcpy(&BUS_II[10],  &RADFET_II[5],  sizeof(RADFET_II[5]));
    memcpy(&BUS_II[12],  &RADFET_II[6],  sizeof(RADFET_II[6]));
    memcpy(&BUS_II[14],  &RADFET_II[7],  sizeof(RADFET_II[7]));

    memcpy(&BUS_II[16],  &RADFET_II[8],  sizeof(RADFET_II[8]));
    memcpy(&BUS_II[18],  &RADFET_II[9],  sizeof(RADFET_II[9]));
    memcpy(&BUS_II[20], &RADFET_II[10], sizeof(RADFET_II[10]));
    memcpy(&BUS_II[22], &RADFET_II[11], sizeof(RADFET_II[11]));
    memcpy(&BUS_II[24], &RADFET_II[12], sizeof(RADFET_II[12]));
    memcpy(&BUS_II[26], &RADFET_II[13], sizeof(RADFET_II[13]));
    memcpy(&BUS_II[28], &RADFET_II[14], sizeof(RADFET_II[14]));
    memcpy(&BUS_II[30], &RADFET_II[15], sizeof(RADFET_II[15]));

    REQUEST_II  = false ;
  }
}



void RUNNING_CMD_III()
{
  while (REQUEST_III == true)
  {
    if (STATE_REQUEST != 4)
    {
      REQUEST_III = false ;
      break;
    }

    READ_RADFET(2, RADFET_III);

    memcpy( &BUS_III[0],  &RADFET_III[0],  sizeof(RADFET_III[0]));
    memcpy( &BUS_III[2],  &RADFET_III[1],  sizeof(RADFET_III[1]));
    memcpy( &BUS_III[4],  &RADFET_III[2],  sizeof(RADFET_III[2]));
    memcpy( &BUS_III[6],  &RADFET_III[3],  sizeof(RADFET_III[3]));
    memcpy( &BUS_III[8],  &RADFET_III[4],  sizeof(RADFET_III[4]));
    memcpy(&BUS_III[10],  &RADFET_III[5],  sizeof(RADFET_III[5]));
    memcpy(&BUS_III[12],  &RADFET_III[6],  sizeof(RADFET_III[6]));
    memcpy(&BUS_III[14],  &RADFET_III[7],  sizeof(RADFET_III[7]));

    memcpy(&BUS_III[16],  &RADFET_III[8],  sizeof(RADFET_III[8]));
    memcpy(&BUS_III[18],  &RADFET_III[9],  sizeof(RADFET_III[9]));
    memcpy(&BUS_III[20], &RADFET_III[10], sizeof(RADFET_III[10]));
    memcpy(&BUS_III[22], &RADFET_III[11], sizeof(RADFET_III[11]));
    memcpy(&BUS_III[24], &RADFET_III[12], sizeof(RADFET_III[12]));
    memcpy(&BUS_III[26], &RADFET_III[13], sizeof(RADFET_III[13]));
    memcpy(&BUS_III[28], &RADFET_III[14], sizeof(RADFET_III[14]));
    memcpy(&BUS_III[30], &RADFET_III[15], sizeof(RADFET_III[15]));

    REQUEST_III = false ;
  }
}



void RUNNING_CMD_IV()
{
  while (REQUEST_IV == true)
  {
    if (STATE_REQUEST != 8)
    {
      REQUEST_IV = false ;
      break;
    }

    READ_RADFET(3, RADFET_IV);

    memcpy( &BUS_IV[0],  &RADFET_IV[0],  sizeof(RADFET_IV[0]));
    memcpy( &BUS_IV[2],  &RADFET_IV[1],  sizeof(RADFET_IV[1]));
    memcpy( &BUS_IV[4],  &RADFET_IV[2],  sizeof(RADFET_IV[2]));
    memcpy( &BUS_IV[6],  &RADFET_IV[3],  sizeof(RADFET_IV[3]));
    memcpy( &BUS_IV[8],  &RADFET_IV[4],  sizeof(RADFET_IV[4]));
    memcpy(&BUS_IV[10],  &RADFET_IV[5],  sizeof(RADFET_IV[5]));
    memcpy(&BUS_IV[12],  &RADFET_IV[6],  sizeof(RADFET_IV[6]));
    memcpy(&BUS_IV[14],  &RADFET_IV[7],  sizeof(RADFET_IV[7]));

    memcpy(&BUS_IV[16],  &RADFET_IV[8],  sizeof(RADFET_IV[8]));
    memcpy(&BUS_IV[18],  &RADFET_IV[9],  sizeof(RADFET_IV[9]));
    memcpy(&BUS_IV[20], &RADFET_IV[10], sizeof(RADFET_IV[10]));
    memcpy(&BUS_IV[22], &RADFET_IV[11], sizeof(RADFET_IV[11]));
    memcpy(&BUS_IV[24], &RADFET_IV[12], sizeof(RADFET_IV[12]));
    memcpy(&BUS_IV[26], &RADFET_IV[13], sizeof(RADFET_IV[13]));
    memcpy(&BUS_IV[28], &RADFET_IV[14], sizeof(RADFET_IV[14]));
    memcpy(&BUS_IV[30], &RADFET_IV[15], sizeof(RADFET_IV[15]));

    REQUEST_IV  = false ;
  }
}



void RUNNING_CMD_V()
{
  while (REQUEST_V == true)
  {
    if (STATE_REQUEST != 16)
    {
      REQUEST_V = false ;
      break;
    }

    READ_RADFET(4, RADFET_V);
    
    memcpy( &BUS_V[0],  &RADFET_V[0],  sizeof(RADFET_V[0]));
    memcpy( &BUS_V[2],  &RADFET_V[1],  sizeof(RADFET_V[1]));
    memcpy( &BUS_V[4],  &RADFET_V[2],  sizeof(RADFET_V[2]));
    memcpy( &BUS_V[6],  &RADFET_V[3],  sizeof(RADFET_V[3]));
    memcpy( &BUS_V[8],  &RADFET_V[4],  sizeof(RADFET_V[4]));
    memcpy(&BUS_V[10],  &RADFET_V[5],  sizeof(RADFET_V[5]));
    memcpy(&BUS_V[12],  &RADFET_V[6],  sizeof(RADFET_V[6]));
    memcpy(&BUS_V[14],  &RADFET_V[7],  sizeof(RADFET_V[7]));

    memcpy(&BUS_V[16],  &RADFET_V[8],  sizeof(RADFET_V[8]));
    memcpy(&BUS_V[18],  &RADFET_V[9],  sizeof(RADFET_V[9]));
    memcpy(&BUS_V[20], &RADFET_V[10], sizeof(RADFET_V[10]));
    memcpy(&BUS_V[22], &RADFET_V[11], sizeof(RADFET_V[11]));
    memcpy(&BUS_V[24], &RADFET_V[12], sizeof(RADFET_V[12]));
    memcpy(&BUS_V[26], &RADFET_V[13], sizeof(RADFET_V[13]));
    memcpy(&BUS_V[28], &RADFET_V[14], sizeof(RADFET_V[14]));
    memcpy(&BUS_V[30], &RADFET_V[15], sizeof(RADFET_V[15]));

    REQUEST_V   = false ;
  }
}



void RUNNING_CMD_VI()
{
  while (REQUEST_VI == true)
  {
    if (STATE_REQUEST != 32)
    {
      REQUEST_VI = false ;
      break;
    }

    READ_RADFET(5, RADFET_VI);

    memcpy( &BUS_VI[0],  &RADFET_VI[0],  sizeof(RADFET_VI[0]));
    memcpy( &BUS_VI[2],  &RADFET_VI[1],  sizeof(RADFET_VI[1]));
    memcpy( &BUS_VI[4],  &RADFET_VI[2],  sizeof(RADFET_VI[2]));
    memcpy( &BUS_VI[6],  &RADFET_VI[3],  sizeof(RADFET_VI[3]));
    memcpy( &BUS_VI[8],  &RADFET_VI[4],  sizeof(RADFET_VI[4]));
    memcpy(&BUS_VI[10],  &RADFET_VI[5],  sizeof(RADFET_VI[5]));
    memcpy(&BUS_VI[12],  &RADFET_VI[6],  sizeof(RADFET_VI[6]));
    memcpy(&BUS_VI[14],  &RADFET_VI[7],  sizeof(RADFET_VI[7]));

    memcpy(&BUS_VI[16],  &RADFET_VI[8],  sizeof(RADFET_VI[8]));
    memcpy(&BUS_VI[18],  &RADFET_VI[9],  sizeof(RADFET_VI[9]));
    memcpy(&BUS_VI[20], &RADFET_VI[10], sizeof(RADFET_VI[10]));
    memcpy(&BUS_VI[22], &RADFET_VI[11], sizeof(RADFET_VI[11]));
    memcpy(&BUS_VI[24], &RADFET_VI[12], sizeof(RADFET_VI[12]));
    memcpy(&BUS_VI[26], &RADFET_VI[13], sizeof(RADFET_VI[13]));
    memcpy(&BUS_VI[28], &RADFET_VI[14], sizeof(RADFET_VI[14]));
    memcpy(&BUS_VI[30], &RADFET_VI[15], sizeof(RADFET_VI[15]));

    REQUEST_VI  = false ;
  }
}



void RUNNING_CMD_VII()
{
  while (REQUEST_VII == true)
  {
    if (STATE_REQUEST != 64)
    {
      REQUEST_VII = false ;
      break;
    }

    READ_RADFET(6, RADFET_VII);

    memcpy( &BUS_VII[0],  &RADFET_VII[0],  sizeof(RADFET_VII[0]));
    memcpy( &BUS_VII[2],  &RADFET_VII[1],  sizeof(RADFET_VII[1]));
    memcpy( &BUS_VII[4],  &RADFET_VII[2],  sizeof(RADFET_VII[2]));
    memcpy( &BUS_VII[6],  &RADFET_VII[3],  sizeof(RADFET_VII[3]));
    memcpy( &BUS_VII[8],  &RADFET_VII[4],  sizeof(RADFET_VII[4]));
    memcpy(&BUS_VII[10],  &RADFET_VII[5],  sizeof(RADFET_VII[5]));
    memcpy(&BUS_VII[12],  &RADFET_VII[6],  sizeof(RADFET_VII[6]));
    memcpy(&BUS_VII[14],  &RADFET_VII[7],  sizeof(RADFET_VII[7]));

    memcpy(&BUS_VII[16],  &RADFET_VII[8],  sizeof(RADFET_VII[8]));
    memcpy(&BUS_VII[18],  &RADFET_VII[9],  sizeof(RADFET_VII[9]));
    memcpy(&BUS_VII[20], &RADFET_VII[10], sizeof(RADFET_VII[10]));
    memcpy(&BUS_VII[22], &RADFET_VII[11], sizeof(RADFET_VII[11]));
    memcpy(&BUS_VII[24], &RADFET_VII[12], sizeof(RADFET_VII[12]));
    memcpy(&BUS_VII[26], &RADFET_VII[13], sizeof(RADFET_VII[13]));
    memcpy(&BUS_VII[28], &RADFET_VII[14], sizeof(RADFET_VII[14]));
    memcpy(&BUS_VII[30], &RADFET_VII[15], sizeof(RADFET_VII[15]));

    REQUEST_VII = false ;
  }
}



void RUNNING_CMD_VIII()
{
  while (REQUEST_VIII == true)
  {
    if (STATE_REQUEST != 128)
    {
      REQUEST_VIII = false ;
      break;
    }

    READ_RADFET(7, RADFET_VIII);

    memcpy( &BUS_VIII[0],  &RADFET_VIII[0],  sizeof(RADFET_VIII[0]));
    memcpy( &BUS_VIII[2],  &RADFET_VIII[1],  sizeof(RADFET_VIII[1]));
    memcpy( &BUS_VIII[4],  &RADFET_VIII[2],  sizeof(RADFET_VIII[2]));
    memcpy( &BUS_VIII[6],  &RADFET_VIII[3],  sizeof(RADFET_VIII[3]));
    memcpy( &BUS_VIII[8],  &RADFET_VIII[4],  sizeof(RADFET_VIII[4]));
    memcpy(&BUS_VIII[10],  &RADFET_VIII[5],  sizeof(RADFET_VIII[5]));
    memcpy(&BUS_VIII[12],  &RADFET_VIII[6],  sizeof(RADFET_VIII[6]));
    memcpy(&BUS_VIII[14],  &RADFET_VIII[7],  sizeof(RADFET_VIII[7]));

    memcpy(&BUS_VIII[16],  &RADFET_VIII[8],  sizeof(RADFET_VIII[8]));
    memcpy(&BUS_VIII[18],  &RADFET_VIII[9],  sizeof(RADFET_VIII[9]));
    memcpy(&BUS_VIII[20], &RADFET_VIII[10], sizeof(RADFET_VIII[10]));
    memcpy(&BUS_VIII[22], &RADFET_VIII[11], sizeof(RADFET_VIII[11]));
    memcpy(&BUS_VIII[24], &RADFET_VIII[12], sizeof(RADFET_VIII[12]));
    memcpy(&BUS_VIII[26], &RADFET_VIII[13], sizeof(RADFET_VIII[13]));
    memcpy(&BUS_VIII[28], &RADFET_VIII[14], sizeof(RADFET_VIII[14]));
    memcpy(&BUS_VIII[30], &RADFET_VIII[15], sizeof(RADFET_VIII[15]));

    REQUEST_VIII = false ;
  }
}



void RUNNING_CMD_IX()
{
  while (REQUEST_IX == true)
  {
    if (STATE_REQUEST != 256)
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

    REQUEST_IX = false;
  }
}
