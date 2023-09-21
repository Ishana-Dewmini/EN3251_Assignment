#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define LED_R D1
#define LED_Y D2
#define LED_G D3

WiFiClient espClient;
PubSubClient client(espClient);

const char* ssid = "GA20s";
const char* password = "anud1237";
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* subscribeTopic = "Group07";

void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_G, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.begin(ssid, password);  //Initialize WiFi Object

  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address : ");
  Serial.print(WiFi.localIP());

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT..");
    if (client.connect("Group07_Node_B")) {
      Serial.println("Connected to MQTT");
      client.subscribe(subscribeTopic);
    } else {
      Serial.println("MQTT Failed to connect");
      delay(5000);
    }
  }
}

void loop() {
  client.loop();
  delay(1000);
}



void callback(char* topic, byte* payload, unsigned int length) {
  // Handle incoming MQTT messages here
  DynamicJsonDocument doc(256); // Adjust the size based on your JSON message size
  deserializeJson(doc, payload, length);

  const char* pot = doc["POT"];
  const char* ldr = doc["LDR"]; 
  Serial.println(pot);
  if (pot != nullptr && ldr != nullptr) {    
    if (strcmp(pot, "Low") == 0 && strcmp(ldr, "Low") == 0){
      Serial.println("1");
      blynk();          
    }else if (strcmp(pot, "Low") == 0 && strcmp(ldr, "Medium") == 0){
      Serial.println("2");
      blynk();
    }else if (strcmp(pot, "Medium") == 0 && strcmp(ldr, "Low") == 0){
      Serial.println("3");
      blynk();
    }else if (strcmp(pot, "Medium") == 0 && strcmp(ldr, "Medium") == 0){
      Serial.println("4");
      state2();
    }else if (strcmp(pot, "High") == 0 && strcmp(ldr, "Low") == 0){
      Serial.println("5");
      state2();
    }else if (strcmp(pot, "Low") == 0 && strcmp(ldr, "High") == 0){
      Serial.println("6");
      state2();
    }else if (strcmp(pot, "High") == 0 && strcmp(ldr, "Medium") == 0){
      Serial.println("7");
      state3();
    }else if (strcmp(pot, "Medium") == 0 && strcmp(ldr, "High") == 0){
      Serial.println("8");
      state3();      
    }else if (strcmp(pot, "High") == 0 && strcmp(ldr, "High") == 0){
      Serial.println("9");
      state3();      
    }

  }
}

void blynk(){
  int t = 0;      
  while (t<4500){
    digitalWrite(LED_R,HIGH);
    digitalWrite(LED_Y,HIGH);
    digitalWrite(LED_G,HIGH);
    delay(400);
    digitalWrite(LED_R,LOW);
    digitalWrite(LED_Y,LOW);
    digitalWrite(LED_G,LOW);
    delay(100);
    t=t+500;     
  }
}

void state2(){
    digitalWrite(LED_R,LOW);
    digitalWrite(LED_Y,HIGH);
    digitalWrite(LED_G,HIGH);
    delay(4500);
    digitalWrite(LED_Y,LOW);
    digitalWrite(LED_G,LOW);
    
}

void state3(){
    digitalWrite(LED_R,HIGH);
    digitalWrite(LED_Y,HIGH);
    digitalWrite(LED_G,HIGH);
    delay(4500);
    digitalWrite(LED_R,LOW);    
    digitalWrite(LED_Y,LOW);
    digitalWrite(LED_G,LOW);
    
}