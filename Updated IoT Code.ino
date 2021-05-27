#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>



#define FIREBASE_HOST "iotdemo-c0d3f-default-rtdb.firebaseio.com"  //Database link
#define FIREBASE_AUTH "fZgTbsoG2t6tevpagt9HDxf1c4P7pias3Yspsovb"  //Database secrate

#define WIFI_SSID "Roboment"      //Router name
#define WIFI_PASSWORD "roboment2018"  //Router password




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
  pinSet();
 
  Serial.begin(9600);
  initFire();

  loadW("Test",1);

  Serial.println("Load: "+loadR("Test"));
  Serial.println("Sen: "+senR("Test"));
   

}



void pinSet(){
  pinMode(D1,INPUT);
  pinMode(D5,INPUT);
  pinMode(D6,OUTPUT);
  
}




void loop() {


    int LDR=analogRead(D1);


    if(LDR==0){
      Serial.println("LDR is on");
      loadW("LDR",1);
      digitalWrite(D6,1);
    }else{
        loadW("LDR",0);
       Serial.println("LDR is off");
       digitalWrite(D6,0);
    }



    


 // String val=loadR("Test");
//  
//    if(val=="1"){
//      
//      Serial.println("Light is on");
//      digitalWrite(D6,1);
//      
//    }else{
//      
//      Serial.println("Light is off");
//      digitalWrite(D6,0);
//      
//    }
//   
  
}



