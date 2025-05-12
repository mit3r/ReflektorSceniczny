#include "api/network.h"

#include <api/states.h>

#include "LittleFS.h"
#include "api/sequence.h"
#include "config/scenes.h"

AsyncWebServer Network::server(80);
DNSServer Network::dnsServer;

void Network::setup() {
  WiFi.softAP(Network::ssid, Network::password);
  WiFi.softAPConfig(IPAddress(192, 168, 0, 1), IPAddress(192, 168, 0, 1), IPAddress(255, 255, 255, 0));
  Serial.println("Created access point");

  dnsServer.start(53, "*", WiFi.softAPIP());
  Serial.println("DNS server started");

  if (!LittleFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    File file = LittleFS.open("/index.html", "r");
    if (!file) {
      request->send(500, "text/plain", "Internal Server Error");
      return;
    }
    String content = file.readString();
    file.close();
    request->send(200, "text/html", content);
  });

  server.on("/set/position", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("ax") && request->hasParam("ay")) {
      int x = request->getParam("ax")->value().toInt();
      int y = request->getParam("ay")->value().toInt();
      if (StateManager::index() == 1)  // Monolith
        Movement::moveTo(x, y, true);

      request->send(200, "text/plain", "Position set wireless");
      Serial.printf("Position set wireless (%d, %d)\n", x, y);
    } else {
      request->send(400, "text/plain", "Missing parameters");
    }
  });

  server.on("/set/light", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("r") && request->hasParam("g") && request->hasParam("b")) {
      Color color;
      color.r = request->getParam("r")->value().toInt();
      color.g = request->getParam("g")->value().toInt();
      color.b = request->getParam("b")->value().toInt();
      if (StateManager::index() == 1)  // Monolith
        Lights::fadeTo(color);

      request->send(200, "text/plain", "Light set wireless");
      Serial.printf("Light set wireless (%d, %d, %d)\n", color.r, color.g, color.b);
    } else {
      request->send(400, "text/plain", "Missing parameters");
    }
  });

  server.begin();
  blinkWhite->run();
};