/*
  Based on WiFiSSLClient.ino in Wifi101 examples written by Arturo Guadalupi last revision November 2015
*/

void initializeWiFi() {
  WiFi.setPins(8, 7, 4, 2); // configure wifi pins
  delay(200);

  while (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    display.clearDisplay();display.setCursor(0, 0);
    display.print("WiFi shield not present");display.display();
    delay(500);
  }
  wStatus = WiFi.status();
  for (int i = 1; i < 4; i++) {
    if (wStatus != WL_CONNECTED) {
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
      if (password != "") // if no password
        wStatus = WiFi.begin(ssid, password);
      else
        wStatus = WiFi.begin(ssid);
    }
    else {
      Serial.print("Connected to WiFi -");
      Serial.println(i);
      break;
    }
    delay(1000);
  }

  if (wStatus != WL_CONNECTED)
    Serial.println("Continuing without WiFi");     // output some diagnostic info

  printWiFiStatus();
  WiFi.end(); // end wifi. will be restarted each upload.
//
//  display.print("SSID :");
//  display.println(ssid);
//  display.print("GSSID :");
//  display.println(GSSD_ID);
//  display.display(); // actually display all of the above
}

void printWiFiStatus() {
  if (wStatus == WL_CONNECTED) {
    display.println("Connected to Wifi");display.display();
    Serial.print("Connected to WiFi ");
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):"); Serial.print(rssi);
    Serial.println(" dBm");
  }
}
