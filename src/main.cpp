/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>
#include <Wire.h>
#include "SSD1306.h"
#include "WiFi.h"

SSD1306 display(0x3c, 5, 4);

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void loop()
{
  char buffer[128] = {0};
  // clear the display
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  int n = WiFi.scanNetworks();
  sprintf(buffer, "%d networks found", n);
  display.drawString(0, 0, buffer);
  for (int i = 0; i < n; ++i)
  {
    String ssid = WiFi.SSID(i);
    uint32_t rssi = WiFi.RSSI(i);
    char open[2];
    if(WiFi.encryptionType(i) == WIFI_AUTH_OPEN)
      strcpy(open, "Y");
    else strcpy(open, "N");
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "name: %s", ssid.c_str());
    display.drawString(0, (i + 1) * 10, buffer);

    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(WiFi.SSID(i));
    Serial.print(" (");
    Serial.print(WiFi.RSSI(i));
    Serial.print(")");
    Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
    delay(10);
  }
  display.display();
  delay(5000);
}
