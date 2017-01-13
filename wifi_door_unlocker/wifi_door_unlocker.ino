/* Wifi door unlocker
* Based off of the helloserver example sketch.
* Added servo functionality.
* 
* Servo is only powered when it receives a command to move.
* This allows a person to still manually lock/unlock using the knob/key.
* 
* Ip address and other information is sent over COM port during ESP8266 bootup.
* You may need to tweek SERVO_OPEN_ANGLE and SERVO_CLOSE_ANGLE
* 
* To open door: <ip address of 8266>/doorcontrol?door=open
* To close door: <ip address of 8266>/doorcontrol?door=close
* 
* Modified by Matthew From
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>
#define SERVO_OPEN_ANGLE 0
#define SERVO_CLOSE_ANGLE 180
#define SERVO_POWER_PIN 0

const char* ssid = "Your wifi SSID";
const char* password = "Your wifi pass";

ESP8266WebServer server(80);
Servo myservo;


void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void setDoor(bool open_close) {
  //Start to give the servo its signal
  if (open_close == 1) {
    myservo.write(SERVO_OPEN_ANGLE);
  } else {
    myservo.write(SERVO_CLOSE_ANGLE);
  }
  delay(5);
  //Only provide power to the servo when it has to move.
  digitalWrite(SERVO_POWER_PIN, HIGH);
  delay(500);
  digitalWrite(SERVO_POWER_PIN, LOW);
}

void handleNotFound(){
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
}

void handleDoor(){
  String message = "";
  if (server.argName(0) == "door" && server.arg(0) == "open"){
    setDoor(1);
    server.send(200, "text/plain", "Door Should Be Open");
    return;
  } else if (server.argName(0) == "door" && server.arg(0) == "close"){
    setDoor(0);
    server.send(200, "text/plain", "Door Should Be Closed");
    return;
  } else {
    message += "Invalid arguments:\n";
    for (uint8_t i=0; i<server.args(); i++){
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
  }
  return;
}

void setup(void){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  pinMode(SERVO_POWER_PIN, OUTPUT);
  digitalWrite(SERVO_POWER_PIN, LOW);
  setDoor(0);
  myservo.attach(2);
  myservo.write(10);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/doorcontrol", handleDoor);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
