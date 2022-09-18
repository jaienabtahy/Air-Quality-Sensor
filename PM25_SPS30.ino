/*  Sensirion SPS20 PM sensor.
      functions:
      - void initializeSPS30()
      - String readSPS30
      Retuns String with 10 data fields: mass (ug/m3) for 1um, 2.5um, 4um, 10um;
     concentration for 0.5um, 1um, 2.5um, 10um (#/cm3) and average particle size (um)
*/

String readSPS30()
{ static bool pmheader = true;
  uint8_t ret, error_cnt, i = 0;
  String outString;
  struct sps_values val;

  if (!(stat & 0x20)) {
    // loop to get data up to 2 times
    for (i = 1; i < 3; i++) {
      ret = sps30.GetValues(&val);
      if (ret == SPS30_ERR_DATALENGTH )
        Serial.println("SPS30 err reading values");
      else if (ret != SPS30_ERR_OK)
        Serial.println("SPS30 err reading values");
      else
        break;
    }

    // only print header first time
    if (pmheader) {
      Serial.println("PM data from Sensirion SPS30 is in the following order...");
      Serial.println("-------------Mass -----------    ------------- Number --------------   -Average-");
      Serial.println("     Concentration [μg/m3]             Concentration [#/cm3]             [μm]");
      Serial.println("mP1.0,\tmP2.5,\tmP4.0,\tmP10,\tnP0.5,\tnP1.0,\tnP2.5,\tnP4.0,\tnP10,\tPartSize");
      pmheader = false;
    }

    if (i < 3) { // we got valid data
      outString = String(val.MassPM1) + String(", ") + String(val.MassPM2) + String(", ") + String(val.MassPM4) + String(", ") + String(val.MassPM10) + String(", ") +
                  String(val.NumPM0) + String(", ") + String(val.NumPM1) + String(", ") + String(val.NumPM2) + String(", ") + String(val.NumPM4) + String(", ") +
                  String(val.NumPM10) + String(", ") + String(val.PartSize) + String(", ");
      PM25 = val.NumPM2; // for oled display
    }
    else
      outString = String("PM err,-,-,-,-,-,-,-,-,-,");
  }
  else // not valid data
    outString = String("no SPS30,.,.,.,.,.,.,.,.,.,");
  return (outString);
}

void initializeSPS30() {
  Serial.print("starting SPS30... ");
  pinMode(11, OUTPUT);

  int i = 0;
  for (i = 1; i < 3; i++) {
    digitalWrite(11, LOW); // turn off the power to the Adafruit Miniboost 3.7V->5V converter for SPS30
    delay(10000); // wait for voltage to drop so that SPS30 is off
    digitalWrite(11, HIGH); // turn on. If this power cycle isn't done the UART Serial1 won't connect
    Serial1.begin(115200);
    if (!Serial1)
      Serial.println("Serial1 NOT ok");
    delay(1000);
    if (!sps30.begin(&Serial1))
      Serial.println("Serial1 communication channel NOT ok");
    else if (!sps30.probe()){    // check for SPS30 connection
      Serial.println("probe / connect with SPS30 NOT ok");
      display.clearDisplay();display.setCursor(0, 0);
      display.println("SPS30 Not Detected");display.display();}
    else if (!sps30.reset())
      Serial.println("reset SPS30 NOT ok");
    else if (!sps30.start())     // start measurement
      Serial.println("SPS30 start NOT ok");
    else {
      Serial.println("SPS30 Connected");
      display.clearDisplay();display.setCursor(0, 0);
      display.println("SPS30 Connected");display.display();
      break;
    }
//    Serial.print("Trying 2 times: ");
//    Serial.println(i);
  }
  if (i >= 3)
    stat |= 0x20; // error so set bit 5
  else
    stat &= 0xDF; // no error clear bit 5
  //Serial.println(String("stat: ") + String(stat));
}
