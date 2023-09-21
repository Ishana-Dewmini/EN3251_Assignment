#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Wire.h>

#define POT_PIN     34
#define LDR_PIN     35
#define PERIOD  5000

const char  *SSID = "GA20s";    // SSID of WiFi
const char  *PASSWORD = "anud1237";    // Password of WiFi
const char  *mqttBroker = "broker.hivemq.com"; // alternate hosts: test.mosquitto.or, broker.hivemq.com
const int   mqttPort = 1883;
const char  *mqttClientID = "Esp32_group07";
const char  *Topic = "Group07"; // Topic to publish

WiFiClient   espClient;
PubSubClient  client(espClient);

unsigned long   Time;
StaticJsonDocument<200> doc;//creating doc
JsonObject object = doc.to<JsonObject>();//convertion

//setup wifi network
void WIFIsetup() {
    client.setServer(mqttBroker, mqttPort);
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

//initialized pin and calculate time
void pinInit() {
    
    pinMode(POT_PIN, INPUT);
    pinMode(LDR_PIN, INPUT);
    Time = millis();
}

//publishing values 5s to 5s
void sendValues() {
    int potValue = analogRead(POT_PIN);
    int LDRValue = analogRead(LDR_PIN);
    
    json_object(potValue, LDRValue);//crating json object
    String jsonString;
    serializeJson(doc, jsonString);

    client.publish(Topic, jsonString.c_str());//publishing
    Time = millis();
        
    Serial.print("POT: ");
    Serial.println(potValue);
    Serial.print("LDR: ");
    Serial.println(LDRValue);
}

void json_object(int potValue, int LDRValue){
  
    //adding values for node-red dashboard customization
    object["POTvalue"] = potValue;
    object["LDRvalue"] = LDRValue;
    
    //setting status 
    //POT       
    if(potValue <= 4095/3){
      object["POT"] = "Low";
    }
    else if(potValue <= 2*4095/3){
      object["POT"] = "Medium";
    }
    else{
      object["POT"] = "High";
    }

    //LDR
    if(LDRValue <= 4095/3){
      object["LDR"] = "Low";
    }
    else if(LDRValue <= 2*4095/3){
      object["LDR"] = "Medium";
    }
    else{
      object["LDR"] = "High";
    }
    
}

//connection establishment with broker
void reconnect() {

  while (!client.connected()) {

    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.println("Not connected to MQTT broker");
      delay(5000);
    }
  }
}

void setup() {
  
  Serial.begin(115200);
  WIFIsetup();
  pinInit();
  reconnect();
  
}

void loop() {

  if(!client.connected()){
    reconnect();
  }  
  if (millis() - Time >= PERIOD) {
    sendValues();
  }
  client.loop();

}