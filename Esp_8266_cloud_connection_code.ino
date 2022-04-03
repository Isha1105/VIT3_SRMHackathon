#include <ESP8266WiFi.h>

#include <ThingSpeak.h>

WiFiClient client;

long myChannelNumber = 1679537;

const char myWriteAPIKey[] = "HQC65JEMMFHE7FSL";



const int sensor=A0; 

float tempc; 
float tempf; 

float vout; 



void setup() {



Serial.begin(9600);

WiFi.begin("Chetan","12345678");

while(WiFi.status() !=WL_CONNECTED)

{delay(100);

Serial.print("wifi not connected\n");

}

Serial.println();

Serial.println("NodeMCU is Connected");

Serial.println(WiFi.localIP());

ThingSpeak.begin(client);

pinMode(sensor,INPUT);

}

void loop() {

//  main code 
vout=analogRead(sensor);

vout=((vout)/1024)*3300+20;

tempc=vout; 
tempf=(vout*1.8)+32; 

Serial.println("Temperature in C: " + (String) tempc);

Serial.println("Temperature in F: " + (String) tempf);

ThingSpeak.writeField(myChannelNumber, 1, tempc, myWriteAPIKey);
ThingSpeak.writeField(myChannelNumber, 2, tempf, myWriteAPIKey);

delay(2000);

}
