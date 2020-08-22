#ifndef _WEATHERNOW_H_
#define _WEATHERNOW_H_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

#define DEBUG   // 调试用


class WeatherNow {
  public:
    WeatherNow();

  private:
    const char* _host = " ";     // 服务器地址

};
#endif
