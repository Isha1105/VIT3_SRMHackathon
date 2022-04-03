 #include<LiquidCrystal.h>
#define tank_pump1 13
#define tank_pump2 12
#define SensorPin A0 
#define SensorPin1 A1
#define DHTTYPE DHT11
#include "DHT.h"
#define DHTPIN 2 
DHT dht(DHTPIN, DHTTYPE);
float sensorValue1 = 0; 
float sensorValue2 = 0; 
int moist_percent1;
int moisture_value1;
int moist_percent2;
int moisture_value2;

LiquidCrystal lcd(7, 6, 8, 9, 10, 11); 
void setup() { 
  lcd.begin(16, 2);
 Serial.begin(9600); 
 pinMode(tank_pump1,OUTPUT);
 pinMode(tank_pump2,OUTPUT);
 digitalWrite(tank_pump1,LOW);
digitalWrite(tank_pump2,LOW);
dht.begin();
} 
void loop() { 
  lcd.begin(0,0);
 for (int i = 0; i <= 100; i++) 
 { 
   sensorValue1 = sensorValue1 + analogRead(SensorPin); 
   delay(1);
   sensorValue2 = sensorValue2 + analogRead(SensorPin1); 
   delay(1); 
 } 
 sensorValue1 = sensorValue1/100.0; 
 sensorValue2 = sensorValue2/100.0; 
 
 delay(30); 

moisture_value1= analogRead(SensorPin);
moist_percent1=map(moisture_value1,0,1023,0,100);
Serial.println("Soil moisture sensor1"); 
Serial.println(sensorValue1);
Serial.println(moist_percent1); 
Serial.println();

moisture_value2= analogRead(SensorPin1);
moist_percent2=map(moisture_value2,0,1023,0,100);
Serial.println("Soil moisture sensor2"); 
Serial.println(sensorValue2);
Serial.println(moist_percent2); 
Serial.println();

float h = dht.readHumidity();
float t = dht.readTemperature();
float f = dht.readTemperature(true);


 Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("C "));
  Serial.print(f);
  Serial. println();
 tank();
} 


void tank(){
  if (moist_percent1<50 && moist_percent2<50){
    digitalWrite(tank_pump1,HIGH);
    digitalWrite(tank_pump2,HIGH);
    lcd.print("pump 1,2 on");
    delay(500);
   
  }
  else if (moist_percent1>50 && moist_percent2<50){
    digitalWrite(tank_pump1,LOW);
    digitalWrite(tank_pump2,HIGH);
    lcd.print("pump 2 on");
    delay(500);
 
  }
   else if (moist_percent1<50 && moist_percent2>50){
    digitalWrite(tank_pump1,HIGH);
    digitalWrite(tank_pump2,LOW);
    lcd.print("pump 1 on");
    delay(500);
 
  }
  else if (moist_percent1>50 && moist_percent2>50){
    digitalWrite(tank_pump1,LOW);
    digitalWrite(tank_pump2,LOW);
    lcd.print("no irrigation");
    delay(500);
 
  }


  
  
}
