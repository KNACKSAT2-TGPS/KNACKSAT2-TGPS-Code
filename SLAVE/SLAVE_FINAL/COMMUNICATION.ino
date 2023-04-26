//
//
//=========================<<<TGPS_REQUEST>>>=========================

// TGPS_REQUEST : REQUEST FROM MASTER.

void TGPS_REQUEST()
{
  // ======================<<<_I_>>>======================

  if (REGIS_DATA_I == true)
  {
    Wire.write(BUS_I, 32);
    memset(BUS_I, 0, sizeof(BUS_I));
    REGIS_CMD[0]    = 0xFF  ; // flash
    REGIS_DATA_I    = false ;
  }


  //======================<<<_II_>>>======================

  if (REGIS_DATA_II == true)
  {
    Wire.write(BUS_II, 32);
    memset(BUS_II, 0, sizeof(BUS_II));
    REGIS_CMD[0]    = 0xFF  ; // flash
    REGIS_DATA_II   = false ;
  }


  //======================<<<_III_>>>=====================

  if (REGIS_DATA_III == true)
  {
    Wire.write(BUS_III, 32);
    memset(BUS_III, 0, sizeof(BUS_III));
    REGIS_CMD[0]    = 0xFF  ; // flash
    REGIS_DATA_III  = false ;
  }


  //======================<<<_IV_>>>======================

  if (REGIS_DATA_IV == true)
  {
    Wire.write(BUS_IV, 32);
    memset(BUS_IV, 0, sizeof(BUS_IV));
    REGIS_CMD[0]    = 0xFF  ; // flash
    REGIS_DATA_IV   = false ;
  }


  //======================<<<_V_>>>=======================

  if (REGIS_DATA_V == true)
  {
    Wire.write(BUS_V, 32);
    memset(BUS_V, 0, sizeof(BUS_V));
    REGIS_CMD[0]    = 0xFF  ; // flash
    REGIS_DATA_V    = false ;
  }


  //======================<<<_VI_>>>======================

  if (REGIS_DATA_VI == true)
  {
    Wire.write(BUS_VI, 32);
    memset(BUS_VI, 0, sizeof(BUS_VI));
    REGIS_CMD[0]    = 0xFF  ; // flash
    REGIS_DATA_VI   = false ;
  }


  //======================<<<_VII_>>>=====================

  if (REGIS_DATA_VII == true)
  {
    Wire.write(BUS_VII, 32);
    memset(BUS_VII, 0, sizeof(BUS_VII));
    REGIS_CMD[0]    = 0xFF  ; // flash
    REGIS_DATA_VII  = false ;
  }


  //=====================<<<_VIII_>>>=====================

  if (REGIS_DATA_VIII == true)
  {
    Wire.write(BUS_VIII, 32);
    memset(BUS_VIII, 0, sizeof(BUS_VIII));
    REGIS_CMD[0]    = 0xFF  ; // flash
    REGIS_DATA_VIII = false ;
  }


  //======================<<<_IX_>>>======================

  if (REGIS_DATA_IX == true)
  {
    Wire.write(BUS_IX, 32);
    memset(BUS_IX   , 0, sizeof(BUS_IX));
    REGIS_CMD[0]   = 0xFF  ; // flash
    REGIS_DATA_IX  = false;
  }


  if (STATUS_ID == true)
  {
    Wire.write(FB_REGIS);
    STATUS_PAYLOAD    = 0xFF ;
    FB_REGIS          = 0xFF ;
    REGIS_CMD[0]      = 0xFF ; // flash
    STATUS_ID         = false;
  }

  if (CMD_TGPS == true)
  {
    Wire.write(FB_REGIS);
    Wire.write(FB_CMD);
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
  while (Wire.available()) //CHECK I2C DATA IS ON BUS
  {
    REGIS_CMD[j] = Wire.read();
    j++;
  }
  if (j != byte_in);
}
