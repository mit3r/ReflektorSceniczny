#include "network.h"

#include "sequence.h"

AsyncWebServer server(80);

void Network::setup() {
  // WiFi.mode(WIFI_STA);
  // WiFi.begin(Network::ssid, Network::password);
  // Serial.println("Connecting to WiFi...");

  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.print(".");
  // }
  // Serial.println();
  // Serial.println("Connected to WiFi: ");
  // Serial.print("SSID: ");
  // Serial.println(WiFi.SSID());
  // Serial.print("IP address: ");
  // Serial.println(WiFi.localIP());
  // Serial.print("Signal strength: ");
  // Serial.println(WiFi.RSSI());

  // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
  //   request->send(200, "text/plain", "Hello from ESP8266!");
  // });

  // server.on("/set/position", HTTP_GET, [](AsyncWebServerRequest *request) {
  //   String x = request->getParam("x")->value();
  //   String y = request->getParam("y")->value();
  //   Serial.printf("Setting position: x=%s, y=%s\n", x.c_str(), y.c_str());
  //   request->send(200, "text/plain", "Position set");
  // });

  // server.begin();
  Sequence *seq = new Sequence(std::vector<Frame>{
      {Color{100, 0, 0}, Point{0, 0}, 600},
      {Color{100, 0, 0}, Point{0, 0}, 0},
      {Color{0, 0, 0}, Point{0, 0}, 200},
      {Color{0, 0, 0}, Point{0, 0}, 0},
      {Color{0, 100, 0}, Point{0, 0}, 600},
      {Color{0, 100, 0}, Point{0, 0}, 0},
      {Color{0, 0, 0}, Point{0, 0}, 200},
      {Color{0, 0, 0}, Point{0, 0}, 0},
      {Color{0, 0, 100}, Point{0, 0}, 600},
      {Color{0, 0, 100}, Point{0, 0}, 0},
      {Color{0, 0, 0}, Point{0, 0}, 0},

  });

  seq->run();
}

void Network::handle() {
  // delay(10);  // Avoid blocking
}