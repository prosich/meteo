#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>

WifiAPEntry wifis[] = {
    {"LGG3","password"},
    {"METEO","password"},    
    {"RM24S","eb0ub011"}, 
    {"RMUP","aabbccddee"} 
};

String ser; // hw#

bool wifota(String id) {
  ESP8266WiFiMulti wifiMulti;
  ser=(String)ESP.getChipId();
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress()+" conectando a wifi");
  for(WifiAPEntry wifi:wifis) 
    wifiMulti.addAP(wifi.ssid,wifi.passphrase);
  for (int segs=1; segs<=15; segs++) {
    delay(1000);
    if (wifiMulti.run() == WL_CONNECTED) {
      Serial.println(WiFi.localIP()); 
      ESPhttpUpdate.update("ota.rosich.es",80,"/cgi/ota?ser="+ser+"&"+id);
      return(true);
    }
  }
  Serial.println("Fallo de conexion"); 
  return(false);
}


