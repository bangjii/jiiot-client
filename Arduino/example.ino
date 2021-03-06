/*
 JiIOT client
 modified 31 March 2018
 by Hudzaifah.
*/

#include "SPI.h"
#include "Ethernet.h"
#include <ArduinoJson.h>   //you have to download this library first

char server[] = "iotcampus.net";
String apikey = "yourAPIkey";
String kirim = "/jiiot/api/kirim.php?key=" + apikey;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };	//your MAC address
IPAddress ip(192, 168, xxx, xxx);   //your ip address
EthernetClient client;

//config for timer checking connection
const unsigned int updateChannelsInterval = 15 * 1000;
long lastConnectionTimeChannels = 0;
boolean lastConnectedChannels = false;
int failedCounterChannels = 0;
long lastConnectionTimeTalkBack = 0;
boolean lastConnectedTalkBack = false;
int failedCounterTalkBack = 0;

String respKirim;
int trigPin = 3;
int echoPin = 4;
int pir = 5;

void setup(){
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);	// Sets the echoPin as an Input
  pinMode(pir, INPUT); 		// Sets the pir as an Input
  startEthernet();
}

void loop(){
  //reading and calculate distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance= int(duration*0.034/2);		//or int distance= (duration*0.034/2).toInt();
  //pir sensor status
  int motion = digitalRead(pir);
  
  updateChannels("Distance", distance);		//send sensor value and sensor name
  updateChannels("Motion", motion);			//send sensor value and sensor name
  delay(60000);   //delay one minutes
}

void updateChannels(String senName, String senValue){
  String param = kirim + "&sensor=" + senName + "&nilai=" + senValue;
  if(!client.connected() && (millis() - lastConnectionTimeChannels > updateChannelsInterval)){
    if (client.connect(server, 80)){
      client.println("GET " + param +" HTTP/1.1");
      client.println("Host: " + String(server));
      client.println("Connection: close");
      client.println();
      lastConnectionTimeChannels = millis();
      if (client.connected()){
        failedCounterChannels = 0;
        while(client.connected() && !client.available()) delay(1);
        while (client.connected() || client.available()){
          char charIn = client.read();
          respKirim += charIn;
        }
        int sResp = respKirim.indexOf('{');
        int eResp = respKirim.indexOf('}');
        String jResp = respKirim.substring(sResp,eResp+1);
        Serial.println(jResp);
      }
      else{
        failedCounterChannels++;
        Serial.println("Connection to JiIOT failed ("+String(failedCounterChannels, DEC)+")");
        Serial.println();
        lastConnectionTimeChannels = millis();
      }
    }
    else{
      failedCounterChannels++;
      Serial.println("Connection to JiIOT Failed ("+String(failedCounterChannels, DEC)+")");
      Serial.println();
      lastConnectionTimeChannels = millis();
    }
  }
  if (failedCounterChannels > 3 ){
    startEthernet();
  }
    client.stop();
    Serial.flush();
}
void startEthernet(){
  client.stop();
  Serial.println("Connecting Arduino to JiIOT...");
  delay(1000);
  if (Ethernet.begin(mac) == 0){
    Ethernet.begin(mac, ip);
  }
  delay(1000);
}
