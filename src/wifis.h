
ESP8266WiFiMulti wifis() {
  ESP8266WiFiMulti wm;

  wm.addAP("RM24","aabbccddee");
  wm.addAP("LGG3","password");
  wm.addAP("METEO","password");

  return(wm);
  }

