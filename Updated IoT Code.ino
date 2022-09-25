#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "iot-work-3fb2e-default-rtdb.firebaseio.com"  //Database link
#define FIREBASE_AUTH "hWhes26LFnakkxeLPDneclih58N9iVLYekMOhzXC"  //Database secrate

#define WIFI_SSID "PAPPURAJ"      //Router name
#define WIFI_PASSWORD "00000000"  //Router password

-------------------------------------------------------


FirebaseData firebaseData,loadData;
FirebaseJson json;



void senW(String field,float value){
 Firebase.setString(firebaseData, "/AnalogOutput/"+field,String(value) );
  
}

String senR(String field){
if (Firebase.getString(loadData, "/AnalogInput/"+field)){
    return loadData.stringData();
  }
}

//Sending data
void loadW(String field,int value){
 Firebase.setString(firebaseData, "/Load/"+field,String(value) );
  
}

//Receiving data
String loadR(String field){
if (Firebase.getString(loadData, "/Load/"+field)){
    return loadData.stringData();
  }
}



void initFire(){
  pinMode(D4,OUTPUT);
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(D4,0);
    Serial.print(".");
    delay(200);
    digitalWrite(D4,1);
    Serial.print(".");
    delay(200);
    
  }
  
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}














void setup() {

  pinMode(D5,INPUT);
  Serial.begin(9600);
  initFire();

  delay(500);

  Firebase.setString(firebaseData, "/Hello","World" );

  
   

}




void loop() {

  Serial.println("Sen: "+senR("Light"));

  delay(500);

}
