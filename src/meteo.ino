#include <DHT.h>
#include <ESP8266HTTPClient.h>

// Conectar D0-RST (deepsleep)

// Pin y tipo de sensor
int DHTPIN=D1;
int DHTTYPE=DHT22;

// Id para OTA
String app="meteo";
String ver="23";

// Autenticacion Corlysis
String dbName="meteo1";
String dbPass="013f827eb2c597cccb3fdbea31c46659";

extern String ser; // serial  (en wifota.ino)

void setup() { 
  Serial.begin(74880);
  if (wifota("app="+app+"&ver="+ver)) {
    DHT dht(DHTPIN,DHTTYPE);
    dht.begin();
    float temp=dht.readTemperature();
    float hum=dht.readHumidity();
    if ((temp!=NAN)&&(hum!=NAN))
      subeDatos((String)temp,(String)hum,
                (String)dht.computeHeatIndex(temp,hum,false));
  }
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


