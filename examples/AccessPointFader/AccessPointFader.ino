#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Tiny.h>
#include <Wire.h>
 
MDNSResponder mdns;
ESP8266WebServer server(80);

const char *ssid = "FreeWiFi";
const char *password = "thereisnospoon";

void handleRoot() {
  digitalWrite(LED_BUILTIN, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(LED_BUILTIN, 0);
}

void handleNotFound(){
  digitalWrite(LED_BUILTIN, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(LED_BUILTIN, 0);
}
 
void setup(void){
  Tiny.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);
  Serial.begin(115200);
  
  WiFi.softAP(ssid, password);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", handleRoot);
  
  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}

int16_t b = 0;
void loop(void){
  server.handleClient();
  Tiny.analogWrite(8, abs(b++));
  if (b >= 254) b = -255;
  delay(5);
} 
