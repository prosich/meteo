#include <Espini.h>
#include <DHT.h>
#include "wifis.h"

// Conectar D0-RST (deepsleep)

// Pin y tipo de sensor
int DHTPIN=D1;
int DHTTYPE=DHT22;

// Id para OTA
char app[]="meteo";
char ver[]="24";

// Autenticacion Corlysis
String dbName="meteo1";
String dbPass="013f827eb2c597cccb3fdbea31c46659";

String ser;

void setup() { 
  Espini cosa(wifis(),app,ver,"ota.rosich.es","syslog.rosich.es");
  ser=cosa.getchipid();
  DHT dht(DHTPIN,DHTTYPE);
  dht.begin();
  float temp=dht.readTemperature();
  float hum=dht.readHumidity();
  if ((temp!=NAN)&&(hum!=NAN))
    subeDatos((String)temp,(String)hum,
              (String)dht.computeHeatIndex(temp,hum,false));
  ESP.deepSleep(300e6);
}

void loop() { // El bucle es deepsleep+reset.
}

void subeDatos(String temp, String hum, String sens) {
  Serial.println("Enviando T: "+temp+"C, H: "+hum+"%, S: "+sens+"C.");
    HTTPClient http;
    http.begin("http://corlysis.com:8087/write?db="+dbName+"&u=token&p="+dbPass);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");  
    int httpCode=http.POST(ser+" temp="+temp+",hum="+hum+",sens="+sens);
  Serial.println("Recibido HTTP "+(String)httpCode);
}


