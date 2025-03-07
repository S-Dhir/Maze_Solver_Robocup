void beginWire()
{
  Wire.setSCL(1);
  Wire.setSDA(0);
  Wire.begin();
  Wire.setClock(400000);
}

void TCA9548A(uint8_t bus)
{
  Wire.beginTransmission(0x70); // TCA9548A address is 0x70
  Wire.write(1 << bus);         // send byte to select bus
  Wire.endTransmission();
}

void writeRegister(uint8_t reg, uint8_t value)
{
  Wire.beginTransmission(APDS9960_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t *readRegister(uint8_t reg, uint8_t len)
{
  static uint8_t data[5]; // Assuming len is always <= 3
  Wire.beginTransmission(APDS9960_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(APDS9960_ADDRESS, len);
  while (Wire.available() < len)
    ;

  for (uint8_t i = 0; i < len; i++)
    data[i] = Wire.read();
  return data;
}

int readProximity(uint8_t channel)
{
  TCA9548A(channel);
  uint8_t *proximityData = readRegister(APDS9960_REG_PDATA, 2);
  int proximity = (proximityData[1] << 8) | proximityData[0];
  return proximity;
}
void initAPDS(uint8_t channel)
{
  TCA9548A(channel);
  delay(20);
  writeRegister(APDS9960_REG_ENABLE, (0 << 6) | (1 << 5) | (0 << 4) | (0 << 3) | (1 << 2) | (0 << 1) | 1); 
  // Bit 6 to 0 Disable Gesture
  // Bit 5 to 1 Enable Proximity Interrupt
  // Bit 4 to 0 Disable ALS Interrupt
  // Bit 3 to 0 Disable Wait Enable
  // Bit 2 to 1 Enable Proximity
  // Bit 1 to 0 Disable ALS Power 
  // Bit 0 to 1 Enable Proximity Power
  writeRegister(APDS9960_REG_CONFIG2, (0 << 7) | (0 << 6) | (0x03 << 4) | 1);
  // Bit 7 to 0 Disable Proximity Saturation Interrupt
  // Bit 6 to 0 Disable Diode Saturation Interrupt
  // Bit 4 to 0x03 Sets Proximity LED Boost to 300%
  // Bit 0 to 1 Reserved must be set to 1
  // writeRegister(APDS9960_REG_CONFIG3, (0 << 5) | (0 << 3) | (0 << 2) | (0 << 1) | (0 << 0));
  writeRegister(APDS9960_REG_CONTROL, (0x00 << 6) | (0x03 << 2) | 0x01);
  // writeRegister(APDS9960_REG_COUNTR, (0x00 << 6));
  // Bit 6 to 0x00 Sets LED Current to 100 Mah
  // Bit 2 to 0x03 Sets Proximity Gain to 8x
  // Bit 0 to 0x01 Sets ALS Gain to 44x
  delay(50);
}
int detectTurn(bool currDL, bool currDR)
{
  if (currDL != prevWallLeft)
  {
    prevWallLeft = currDL;
    if (!currDL)
      return LEFT;
  }
  else if (currDR != prevWallRight)
  {
    prevWallRight = currDR;
    if (!currDR)
      return RIGHT;
  }
  return 0;
}

void updateWalls(bool _delay)
{
  for (int i = 0; i < 5; i++)
  {
    updateProximitySensors();
    if (_delay)
      delay(5);
    else
      delay(2);
  }
  prevWallLeft = (dl_filtered > leftTurnSense);
  prevWallRight = (dr_filtered > rightTurnSense);
}

void updateProximitySensors()
{
  fl = readProximity(FL);
  fr = readProximity(FR);
  dl = readProximity(DL);
  dr = readProximity(DR);

  dl_filtered = alpha * dl_filtered + (1 - alpha) * dl;
  dr_filtered = alpha * dr_filtered + (1 - alpha) * dr;
  fl_filtered = alpha * fl_filtered + (1 - alpha) * fl;
  fr_filtered = alpha * fr_filtered + (1 - alpha) * fr;
}

void delayWithSensorUpdate(int ms)
{ // only in multiples of 5
  long _curr = millis();
  delay(1);
  while ((millis() - _curr) < ms)
  {
    updateProximitySensors();
    mpu.update();
  }
}

void waitForUserInput1()
{
  while (1)
  {
    updateProximitySensors();
    mpu.update();
    if (dl > 200)
      break;
    alterLEDstate();
    SerialDebug.println("waiting1..");
    delay(50);
  }
  // _beep();
  state = HIGH;
  alterLEDstate();
}

void waitForUserInput2()
{
  while (1)
  {
    updateProximitySensors();
    mpu.update();
    if (dr > 200)
      break;
    alterLEDstate();
    SerialDebug.println("waiting2..");
    delay(100);
  }
  _beep();
  state = HIGH;
  alterLEDstate();
}

void printWalldata()
{
  SerialDebug.print("fl:");
  SerialDebug.print(fl);
  SerialDebug.print(",fr:");
  SerialDebug.print(fr);
  SerialDebug.print(",dl:");
  SerialDebug.print(dl);
  SerialDebug.print(",dr:");
  SerialDebug.println(dr);
}