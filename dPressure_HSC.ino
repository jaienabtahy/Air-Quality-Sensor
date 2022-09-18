// Honeywell TruStability HSC differential pressure sensor
// model no. HSC-D-RR-N-100MD-S-A-3

void initializeHSC() {
  Serial.print("starting HSC... ");
  int hscStatus;
  SPI.begin(); // start SPI communication
  diffPresSens.begin(); // run sensor initialization
  for (int i = 1; i < 5; i++) {
    hscStatus = diffPresSens.readSensor();
    if (!hscStatus) // return 0 is ok condition
      break;
    delay(100);
  }
  if (hscStatus == 0) {
    Serial.print("Differential Pressure Sensor Connected");
    stat &= 0xBF; // clear bit 6
    display.println("HSC Connected");display.display();
  }
  else {
    Serial.print("Differential Pressure Sensor Not Detected");
    display.println("HSC Not Connected");display.display();
    stat |= 0x40; // set bit 6
    
  }
  Serial.println(hscStatus);
}

String readHSC() {
  if (!(stat & 0X40)) { // check bit 6. if clear sensor is present
    int HSCstatus = diffPresSens.readSensor();
    int i = 0;
    while (HSCstatus) {
      HSCstatus = diffPresSens.readSensor(); //
      Serial.print('.');
      i++;
      if (i > 10)
        break; // timeout
      delay(50);
    };
    if (i > 10) 
      return (String("lost HSC")); // timeout condition
    else 
      return (String(diffPresSens.temperature()) + String(", ") + String(diffPresSens.pressure()) + String(", "));
  }
  else // bit 6 set, no sensor
    return (String("no HSC,.,"));
}
