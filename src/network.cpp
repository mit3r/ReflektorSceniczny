#include "api/network.h"

#include "LittleFS.h"
#include "api/states.h"
#include "api/theater.h"
#include "config/scenes.h"
#include "interfaces/lights.h"
#include "interfaces/movement.h"

AsyncWebServer Network::server(80);
DNSServer Network::dnsServer;

void Network::setup() {
  WiFi.softAP(Network::ssid, Network::password);
  WiFi.softAPConfig(IPAddress(192, 168, 0, 1), IPAddress(192, 168, 0, 1), IPAddress(255, 255, 255, 0));
  Serial.println("Created access point");

  if (!LittleFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }

  // Handle position changing
  server.on("/position", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("x") && request->hasParam("y")) {
      short x = request->getParam("x")->value().toInt();
      short y = request->getParam("y")->value().toInt();
      if (StateManager::index() == 1) {
        Controls::lockAnalog();
        Movement::stop();
        Movement::moveToAngle({x, y});
        Serial.printf("Position set wireless (%d, %d)\n", x, y);
        request->send(200);
      } else
        request->send(400, "text/plain", "Invalid state");
    } else
      request->send(400, "text/plain", "Missing parameters");
  });

  // Handle lights color changing
  server.on("/color", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("r") && request->hasParam("g") && request->hasParam("b")) {
      Color color;
      color.r = request->getParam("r")->value().toInt();
      color.g = request->getParam("g")->value().toInt();
      color.b = request->getParam("b")->value().toInt();
      if (StateManager::index() == 1) {
        Controls::lockAnalog();
        Lights::stop();
        Lights::fadeColorTo(color);
        Serial.printf("Color set wireless (%d, %d, %d)\n", color.r, color.g, color.b);
        request->send(200);
      } else
        request->send(400, "text/plain", "Invalid state");
    } else
      request->send(400, "text/plain", "Missing parameters");
  });

  // Handle static files serving
  server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
  server.onNotFound([](AsyncWebServerRequest *request) {
    if (request->method() == HTTP_OPTIONS)
      request->send(200);
    else
      request->send(404, "text/plain", "Not Found");
  });
};

void Network::begin() {
  server.begin();
  Serial.println("Server started");

  dnsServer.start(53, "*", WiFi.softAPIP());
  Serial.println("DNS server started");
}