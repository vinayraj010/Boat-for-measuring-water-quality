#include <SoftwareSerial.h>
#include<A7Client.h>
A7Client a7Client (1, 2);

const char server[] = "";
char msg[200] = ""; 
// char time[] = "";
char temperature[7] = "";
char pH[6] = "";
char DO[7] = ""; 
char lat[9] = "";
char lng[9] = "";

const uint8_t pinRST = 5;
const uint8_t pinTurbidity    = A0;
const uint8_t pinDO           = A2;
const uint8_t pinTemperature  = A3;

struct Data{
  float temperature;
  int turbidity;
} data;

unsigned long previousMillis = 0;
long timeInterval = 10000;

void setup() {
  Serial.begin(9600);
  Serial.println(freeRam());


  pinMode(pinRST, OUTPUT);
  pinMode(pinPWR, OUTPUT);
  digitalWrite(pinRST, HIGH);
  delay(1000);
  digitalWrite(pinRST, LOW);

  Serial.println(freeRam());
  Serial.println(F("Response okay! :) Module is alive!"));
  delay(10000);

  while(!a7Client.startGPS()){
  Serial.println(F("Try activating GPS again."));
  }
  printData(&data);
    
  while(!a7Client.readGPS());   
  if(a7Client.parse(a7Client.lastNMEA())){
     Serial.print(F("Location: "));
     Serial.print(a7Client.latitude, 4); Serial.print(a7Client.lat);
     Serial.print(F(", ")); 
     Serial.print(a7Client.longitude, 4); Serial.println(a7Client.lon);
     Serial.print(F("Location (in degrees, works with Google Maps): "));
     Serial.print(a7Client.latitudeDegrees, 4);
     Serial.print(F(", ")); 
     Serial.println(a7Client.longitudeDegrees, 4);    
  }


  convertToChar(&data, a7Client);
    if (lat[0] == '0'){
    lat[0] = '2';
    lat[1] = '8';
    lat[2] = '.';
    lat[3] = '5';
    lat[4] = '4';
    lat[5] = '4';
    lat[6] = '1';
    lat[7] = '4';
    lat[8] = '2';
    lat[9] = '1';

    lng[0] = '7';
    lng[1] = '7';
    lng[2] = '.';
    lng[3] = '2';
    lng[4] = '7';
    lng[5] = '2';
    lng[6] = '0';
    lng[7] = '6';
    lng[8] = '1';
    lng[9] = '7';
    }    
  constructHTTPRequest(msg);  
  a7Client.connect(server,80);
  sendHTTPRequest(msg);  
}


void loop() {  
  // Serial.println(F("I am down here"));
  
  // if (a7Client.available())
  // Serial.write(a7Client.read());

  // if (Serial.available())
  // a7Client.writeSerial(Serial.read());


  unsigned long currentMillis = millis();
     
  printData(&data);
  
  if((currentMillis - previousMillis >= timeInterval)){
    previousMillis = currentMillis;
    printData(&data);

    while(!a7Client.readGPS());      
    if(a7Client.parse(a7Client.lastNMEA())){
      Serial.println(F("parsed completed"));    
    }
    convertToChar(&data, a7Client);  
    printCharData();
    constructHTTPRequest(msg);    
    if (a7Client.connect(server, 80)){
      
    }
    sendHTTPRequest(msg);
  }  
}
