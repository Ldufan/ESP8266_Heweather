#ifndef _WEATHER_FORECAST_H_
#define _WEATHER_FORECAST_H_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

#define DEBUG   // 调试用

class WeatherForecast {
  public:
    WeatherForecast();

  private:
    const char* _host = " ";     // 服务器地址
};
#endif
