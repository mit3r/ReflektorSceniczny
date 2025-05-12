#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

#ifndef NETWORK_H
#define NETWORK_H

class Network {
  static constexpr const char* ssid = "900729";
  static constexpr const char* password = "tyniafranek2020";

  public:
  static void setup();
  static void handle();

  // void connect(const char* ssid, const char* password);
  // void disconnect();
  // bool isConnected() const;
};

#endif