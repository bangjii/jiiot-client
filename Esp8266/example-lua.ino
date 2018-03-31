/*
 JiIOT client
 modified 31 March 2018
 by Hudzaifah.
*/

#include <SoftwareSerial.h>
SoftwareSerial espSerial(7, 6);    // RX, TX

void setup(){  
  Serial.begin(9600);
  espSerial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);	// Sets the echoPin as an Input
  pinMode(pir, INPUT); 		// Sets the pir as an Input
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
  espSerial.println("post('Distance'," + String(distance) + ")");
  espSerial.println("post('Motion'," + String(motion) + ")");
  delay(60000);								//delay one minutes
}