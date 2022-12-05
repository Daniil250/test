#include <Arduino.h>
  #include <WiFi.h>
  #include <WebServer.h>
  #include <ESPAsyncWebServer.h>
  #include <SPIFFS.h>
  #include <AsyncTCP.h>
  #include <AsyncElegantOTA.h>
#define AP_SSID ""
#define AP_PASS ""

AsyncWebServer server(80);



String STM_Data = "m 20 0 100 5 200 10 300 15 400 20 500 25 600 30 490 30 350 29 320 28 300 27 200 22 100 20 20 19";

  
String data_from_stm;



int EXP;
int EXP1;
double in1;
double in2;
double in3;
double in4;
double in5;


void setup()
{
  
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
// /////////////////////////////////////////////
  Serial2.println("Serial 2 init success");

  if (!SPIFFS.begin())
  {
    Serial2.println("An Error has occurred while mounting SPIFFS");
    return;
  }
 // SPIFFS.begin();
////////////////////////////////////////////////////////////////////////////////////
//запуск WIFIточки 
  WiFi.mode(WIFI_AP);
  WiFi.softAP("My Portaltest1");
  
 
  
  server.on("/",HTTP_GET,[](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS,  "/men.html");
  });
 server.on("/gel",HTTP_GET,[](AsyncWebServerRequest *request)
            {
                request->send(SPIFFS, "/gel.html");
            });

   server.on("/m",HTTP_GET,[](AsyncWebServerRequest *request)
            {
                request->send(SPIFFS,  "/m.html");
            });
   server.on("/in", HTTP_GET, [](AsyncWebServerRequest * request) {
    
     in1 = request->arg("input1").toDouble();
     
  
     request->send(200, "text/plain", "" );
  
    Serial.println(in1);


        
  });  
  server.on("/in1", HTTP_GET, [](AsyncWebServerRequest * request) {
    
     
     in2=request->arg("input2").toDouble();
     
    request->send(200, "text/plain", "" );

    Serial.println(in2);
    
  });  
  server.on("/in2", HTTP_GET, [](AsyncWebServerRequest * request) {
    
     
     in3=request->arg("input3").toDouble();
     
    request->send(200, "text/plain", "" );

    Serial.println(in3);
    
  });  
  server.on("/in3", HTTP_GET, [](AsyncWebServerRequest * request) {
    
     
     in4=request->arg("input4").toDouble();
     
    request->send(200, "text/plain", "" );

    Serial.println(in4);
    
  });  
   server.on("/in4", HTTP_GET, [](AsyncWebServerRequest * request) {
    
     
     in5=request->arg("input5").toDouble();
     
    request->send(200, "text/plain", "" );

    Serial.println(in5);
    
  }); 
  server.on("/EXP", HTTP_GET, [](AsyncWebServerRequest * request) {
    
     EXP = request->arg("EXP").toInt();
    request->send(200, "text/plain", "" );
    Serial.println(EXP);
    
  }); 
    server.on("/EXP1", HTTP_GET, [](AsyncWebServerRequest * request) {
    
     EXP1 = request->arg("EXP1").toInt();
    request->send(200, "text/plain", "" );
    Serial.println(EXP1);
    
  }); 
  server.on("/index", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              request->send(SPIFFS, "/index.html");
            });
 

  server.on("/wotafak", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/plain", STM_Data.c_str()); });
            
 
 
  
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  //запуск сервера и OTA обновления 
  AsyncElegantOTA.begin(&server);
   server.begin();
  
  
  
  Serial2.println("Server started");
}

void loop() {


  if(Serial.available() > 0)
  {
    data_from_stm = Serial.readStringUntil('#');
    Serial2.println("Data from stm32 received:");
    Serial2.println(data_from_stm);
  }
  // put your main code here, to run repeatedly:
  
 
  
 

}


