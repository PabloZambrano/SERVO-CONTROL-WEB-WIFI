// Proyecto para Comunicaciones con Arduino - Elearning Total

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <Servo.h>

#include "index.h"; 
#define LEDonBoard 2 
#define ServoPort D1  

const char *ssid = "SSID";
const char *password = "PASSWORD_SSID";

Servo myservo;

ESP8266WebServer server(80);  
void handleRoot() {
 String s = MAIN_page; 
 server.send(200, "text/html", s); 
}



void handleServo(){
  String POS = server.arg("servoPOS");
  int pos = POS.toInt();
  myservo.write(pos);  
  delay(15);
  Serial.print("Angulo Servo:");
  Serial.println(pos);
  server.send(200, "text/plane","");
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  WiFi.begin(ssid, password); 
  Serial.println("");
    
  pinMode(LEDonBoard,OUTPUT); 
  digitalWrite(LEDonBoard, HIGH); 

  myservo.attach(ServoPort); 
  

  Serial.print("Tranca Palanca, conectando...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");

    digitalWrite(LEDonBoard, LOW);
    delay(250);
    digitalWrite(LEDonBoard, HIGH);
    delay(250);
  }

  digitalWrite(LEDonBoard, HIGH); 
  Serial.println("");
  Serial.print("Conectado : ");
  Serial.println(ssid);
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
  
  server.on("/",handleRoot);  
  server.on("/setPOS",handleServo); 
  server.begin();  
  Serial.println("Servidor Web OK");
}

void loop() {
 server.handleClient();
}

