#include "secrets.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include "WiFi.h"
#include <ArduinoJson.h>
#include <NewPing.h>
#define D1RA 13
#define D1RB 12
#define D1LA 14
#define D1LB 27

int mq6_sensor =34;
int LPG;
int US;
unsigned int obst_dist;
#define ESP32CAM_PUBLISH_TOPIC   "esp32/cam_2"
#define ESP32CAM_subscribe_TOPIC   "motor"
const int bufferSize = 1024 * 23; // 23552 bytes

const int TRIGGER_PIN_1 = 32; //ultrasonic sensor infront of boat
const int ECHO_PIN_1 = 35;
const int MAX_DISTANCE = 100;
NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(bufferSize);

void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("\n\n=====================");
  Serial.println("Connecting to Wi-Fi");
  Serial.println("=====================\n\n");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
 Serial.print("wifi_connected");
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, 8883, net);
  client.setCleanSession(true);
  client.onMessage(messageHandler);

  Serial.println("\n\n=====================");
  Serial.println("Connecting to AWS IOT");
  Serial.println("=====================\n\n");

  while (!client.connect("esp32")) {
    Serial.print(".");
    delay(1000);
  }

  if(!client.connected()){
    Serial.println("AWS IoT Timeout!");
    ESP.restart();
    return;
  }

  Serial.println("\n\n=====================");
  Serial.println("AWS IoT Connected!");
  Serial.println("=====================\n\n");
  
 client.subscribe(ESP32CAM_subscribe_TOPIC);
 Serial.println("subscribed");

}

void ultrasonic_sensor() {

  // Read distances from both ultrasonic sensors
  obst_dist = sonar1.ping_cm();
  // Print the distances
  Serial.print("obtacle distance: ");
  Serial.print(obst_dist);
  Serial.print(" cm\t");
}



void Forward() {
  digitalWrite(D1RA, HIGH);
  digitalWrite(D1RB, LOW);
  digitalWrite(D1LA, HIGH);
  digitalWrite(D1LB, LOW);
}
void Backward() {
  digitalWrite(D1RA, LOW);
  digitalWrite(D1RB, HIGH);
  digitalWrite(D1LA, LOW);
  digitalWrite(D1LB, HIGH);
}
void Left() {
  digitalWrite(D1RA, LOW);
  digitalWrite(D1RB, HIGH);
  digitalWrite(D1LA, HIGH);
  digitalWrite(D1LB, LOW);
}
void Right() {
  digitalWrite(D1RA, HIGH);
  digitalWrite(D1RB, LOW);
  digitalWrite(D1LA, LOW);
  digitalWrite(D1LB, HIGH);
}
void Stop() {
  digitalWrite(D1RA, LOW);
  digitalWrite(D1RB, LOW);
  digitalWrite(D1LA, LOW);
  digitalWrite(D1LB, LOW);
}
void messageHandler(String &topic, String &payload){
 
 Serial.print(payload);
String msg = payload; 
  if (msg == "F"){
    Forward();
    Serial.print("forward movement");
   delay(1000);
    }
    else if(msg == "B"){
    Backward();
    Serial.print("backward movement");
    delay(1000);
    }
    else if(msg == "R"){
    Right();
     
    Serial.print("right movement");
     delay(700);}
    else if (msg == "L"){
    Left();
    Serial.print("Left movement");
     delay(700);
    }else{
      Stop();
    }
    Stop();
}
  void publishMessage()
{
  StaticJsonDocument<500> doc;
  doc["sensor"] =  LPG;
  doc["u_sens"] = US;
  char jsonBuffer[700];
  serializeJson(doc, jsonBuffer); // print to client
  // Serial.println(jsonBuffer);
  client.publish(ESP32CAM_PUBLISH_TOPIC, jsonBuffer);
}
void setup() {
  pinMode(mq6_sensor, INPUT);
  pinMode(D1RA, OUTPUT);
  pinMode(D1RB, OUTPUT);
  pinMode(D1LA, OUTPUT);
  pinMode(D1LB, OUTPUT);
   Stop();
  Serial.begin(115200);
 connectAWS();
}

void loop() {
   int LPG_detected = analogRead(mq6_sensor);  
 Serial.println(LPG_detected); 
 delay(1000); 
 if (LPG_detected >=400)  
 {  
LPG = 1;
 Serial.println("LPG detected...");  
 
 }  
 else  
 {  
   LPG = 0;
 Serial.println("No LPG detected ");  
  
 } 
 ultrasonic_sensor();
 if (obst_dist ==0 || obst_dist>= 50){
  US =1;
 }
 else {
  US =0;
 }
 Serial.print("US =");
 Serial.println(US);
 Serial.print("lpg =");
 Serial.println(LPG);
 publishMessage();
 client.loop();
  
}
