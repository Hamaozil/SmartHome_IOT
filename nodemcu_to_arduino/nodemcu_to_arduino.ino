#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include <SoftwareSerial.h>
//-------------------------------------

#define wifi_ssid "....."
#define wifi_pass "........"
#define ip "broker.hivemq.com"
#define port 1883

//-------------------------------------

// subscribed topics
//leds
const char* officeLed = "home/officeLed" ;
const char* livingRoomLed = "home/livingRoomLed" ;
const char* bedRoomLed = "home/bedRoomLed" ;
//fans
const char* officeFan = "home/officeFan" ;
const char* livingRoomFan = "home/livingRoomFan" ;
const char* bedRoomFan = "home/bedRoomFan" ;
//door
const char* door = "home/door" ;
//-------------------------------------

// published topics
const char* gasTopic = "home/gas" ;
const char* temperatureTopic = "home/temperature" ;
//-------------------------------------

WiFiClient espclient;
PubSubClient client(espclient);
SoftwareSerial NodeMCU(D7, D8);

String doorState = "";

void on_message(char* topic , byte* message , unsigned int lenght)
{
  // topic --->home/bedRoomLed/  ---->message ---->on (0) /  off (1)
  // topic --->home/officeLed/ ---->message ---->on (0) / off (1)
  // topic --->home/livingRoomLed/  ---->message ---->on (0) / off (1)

  // topic --->home/bedRoomFan/  ---->message ---->on (0) / off (1)
  // topic --->home/officeFan/  ---->message ---->on (0) / off (1)
  // topic --->home/livingRoomFan/  ---->message ---->on (0) / off (1)

  String topic_msg = "";
  if (strcmp(topic, officeLed) == 0)
  {
    //Serial.print("office ");
    topic_msg = "home/officeLed/";
    for (int i = 0 ; i < lenght ; i++)
      topic_msg += char(message[i]) ; // on/off
  }
  else if (strcmp(topic, bedRoomLed) == 0)
  {
    topic_msg = "home/bedRoomLed/";
    for (int i = 0 ; i < lenght ; i++)
      topic_msg += char(message[i]) ; // on/off
  }
  else if (strcmp(topic, livingRoomLed) == 0)
  {
    topic_msg = "home/livingRoomLed/";
    for (int i = 0 ; i < lenght ; i++)
      topic_msg += char(message[i]) ; // on/off
  }
  //-------------------------------------------
  else if (strcmp(topic, officeFan) == 0)
  {
    //Serial.print("office ");
    topic_msg = "home/officeFan/";
    for (int i = 0 ; i < lenght ; i++)
      topic_msg += char(message[i]) ; // on/off
  }
  else if (strcmp(topic, bedRoomFan) == 0)
  {
    topic_msg = "home/bedRoomFan/";
    for (int i = 0 ; i < lenght ; i++)
      topic_msg += char(message[i]) ; // on/off
  }
  else if (strcmp(topic, livingRoomFan) == 0)
  {
    topic_msg = "home/livingRoomFan/";
    for (int i = 0 ; i < lenght ; i++)
      topic_msg += char(message[i]) ; // on/off
  }
  //---------------------------------------------
  else if (strcmp(topic, door) == 0)
  {
    topic_msg = "home/door/";
    for (int i = 0 ; i < lenght ; i++)
      topic_msg += char(message[i]) ; // open/close
  }
  //send topic message
  topic_msg.trim();
  Serial.print(topic_msg);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  WiFi.begin(wifi_ssid, wifi_pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("connecting to wifi....\n");
    delay(1000);
  }

  Serial.print("connected to wifi.\n");
  client.setServer(ip, port);
  Serial.print("connected to mqtt\n");
  client.setCallback(on_message);
  client.connect("NodeMCU Subscriber");

  client.subscribe(officeLed);
  client.subscribe(livingRoomLed);
  client.subscribe(bedRoomLed);

  client.subscribe(officeFan);
  client.subscribe(livingRoomFan);
  client.subscribe(bedRoomFan);

  client.subscribe(door);

  NodeMCU.begin(9600);
}

void loop() {
  if (!client.connected())
    reconnect();
  client.loop();
  if (NodeMCU.available() > 0)
  {
    String dataString = NodeMCU.readStringUntil('\n');
    int idx = dataString.indexOf(',');
    if (idx != -1) {
      String temperatureString = dataString.substring(2, idx);
      String gasLevelString = dataString.substring(idx + 3);
      const char* tempPtr = temperatureString.c_str();
      const char* gasPtr = gasLevelString.c_str();
      client.publish(temperatureTopic, tempPtr);
      client.publish(gasTopic, gasPtr);
    }
  }
}
