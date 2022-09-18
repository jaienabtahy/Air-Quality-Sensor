# Air-Quality-Sensor
The Air Quaity Sensor (AQS) is a low-cost, low-power DIY device with sensors for CO2, temp-pressure-relativehumidity, and PM2.5 (dust or smoke). It has an on-board logger and WiFi connectivity to Google Sheets for (almost) real time data reporting.

V3 has code for the SPS30 PM2.5 and HSC differential pressure (Met Museum) sensors. If these are not pesent the code keeps going and reports 'no sensor' to SD log and google sheet. Additionally, keeps the start-stop for Wifi and sleeps all for ~25mA operation.

This project is under CUNY ASRC Community Sensor Lab.
