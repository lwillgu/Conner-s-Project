/*
 * This is a basic example on how to use Espalexa and its device declaration methods.
 */ 
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>

// prototypes
boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);

// Change this!!
const char* ssid = "Wifi Name";
const char* password = "Passsword";

boolean wifiConnected = false;

Espalexa espalexa;

EspalexaDevice* device3; //this is optional

int relay = 4;

void setup()
{
  Serial.begin(115200);
    pinMode(relay, OUTPUT); //Set relay as output


  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    
    // Define your devices here. 
    espalexa.addDevice("Water Pump", waterPumpChange, 0); //simplest definition, default state off
    
    espalexa.begin();
    
  } else
  {
    while (1) {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}
 
void loop()
{
   espalexa.loop();
   delay(1);
}

//our callback functions
void waterPumpChange(uint8_t brightness) {

    //EXAMPLE
    if (brightness) {
      Serial.print("ON, brightness ");
      Serial.println(brightness);
      digitalWrite(relay, LOW); //Turn lamp off

    }
    else  {
      Serial.println("OFF");
      digitalWrite(relay, HIGH); //Turn lamp on

    }
}





// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state){
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
