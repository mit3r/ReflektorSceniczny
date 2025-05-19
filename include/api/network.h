#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

#ifndef NETWORK_H
#define NETWORK_H

class Network {
  static constexpr const char* ssid = "@the.miter";
  static constexpr const char* password = "zestresowany";

  static AsyncWebServer server;
  static DNSServer dnsServer;
  static constexpr const char* host = "esp8266";
  static constexpr const char* domain = "esp8266.local";

  public:
  static void setup();
  static void begin();
};

#endif