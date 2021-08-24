#include "WeatherForecast.h"

WeatherForecast::WeatherForecast() {
}

void WeatherForecast::config(String userKey, String location, String unit, String lang) {
  _requserKey = userKey;
  _reqLocation = location;
  _reqUnit = unit;
  _reqLang = lang;
}

bool WeatherForecast::get() {
  // https请求
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure(); // 不进行服务器身份认证
  HTTPClient https;
  #ifdef DEBUG
  Serial.print("[HTTPS] begin...\n");
  #endif DEBUG
  String url = "https://devapi.heweather.net/v7/weather/3d?location=" + _reqLocation +
              "&key=" + _requserKey + "&unit=" + _reqUnit + "&lang=" + _reqLang + "&gzip=n";
  if (https.begin(*client, url)) {  // HTTPS连接成功
    #ifdef DEBUG
    Serial.print("[HTTPS] GET...\n");
    #endif DEBUG
    int httpCode = https.GET(); // 请求

    if (httpCode > 0) { // 错误返回负值
      #ifdef DEBUG
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      #endif DEBUG
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) { // 服务器响应
        String payload = https.getString();
        #ifdef DEBUG
        Serial.println(payload);
        #endif DEBUG
        _parseNowJson(payload);
        return true;
      }
    } else { // 错误返回负值
      #ifdef DEBUG
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      #endif DEBUG
      return false;
    }
    https.end();
  } else { // HTTPS连接失败
    #ifdef DEBUG
    Serial.printf("[HTTPS] Unable to connect\n");
    #endif DEBUG
    return false;
  }
}

void WeatherForecast::_parseNowJson(String payload) {
  const size_t capacity = 2*JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(2) +
                          JSON_OBJECT_SIZE(5) + 3*JSON_OBJECT_SIZE(26) + 1320;
  DynamicJsonDocument doc(capacity);

  deserializeJson(doc, payload);

  const char* code = doc["code"];
  const char* updateTime = doc["updateTime"];
  JsonArray daily = doc["daily"];
  JsonObject daily_0 = daily[0];
  JsonObject daily_1 = daily[1];
  JsonObject daily_2 = daily[2];

  _response_code = doc["code"].as<String>();
  _last_update_str = doc["updateTime"].as<String>();
  _daily_fxDate_str[0] = daily_0["fxDate"].as<String>();
  _daily_fxDate_str[1] = daily_1["fxDate"].as<String>();
  _daily_fxDate_str[2] = daily_2["fxDate"].as<String>();
  _daily_sunrise_str[0] = daily_0["sunrise"].as<String>();
  _daily_sunrise_str[1] = daily_1["sunrise"].as<String>();
  _daily_sunrise_str[2] = daily_2["sunrise"].as<String>();
  _daily_tempMax_int[0] = daily_0["tempMax"].as<int>();
  _daily_tempMax_int[1] = daily_1["tempMax"].as<int>();
  _daily_tempMax_int[2] = daily_2["tempMax"].as<int>();
  _daily_tempMin_int[0] = daily_0["tempMin"].as<int>();
  _daily_tempMin_int[1] = daily_1["tempMin"].as<int>();
  _daily_tempMin_int[2] = daily_2["tempMin"].as<int>();
  _daily_iconDay_int[0] = daily_0["iconDay"].as<int>();
  _daily_iconDay_int[1] = daily_1["iconDay"].as<int>();
  _daily_iconDay_int[2] = daily_2["iconDay"].as<int>();
  _daily_textDay_str[0] = daily_0["textDay"].as<String>();
  _daily_textDay_str[1] = daily_1["textDay"].as<String>();
  _daily_textDay_str[2] = daily_2["textDay"].as<String>();
  _daily_windDirDay_str[0] = daily_0["windDirDay"].as<String>();
  _daily_windDirDay_str[1] = daily_1["windDirDay"].as<String>();
  _daily_windDirDay_str[2] = daily_2["windDirDay"].as<String>();
  _daily_windScaleDay_str[0] = daily_0["windScaleDay"].as<String>();
  _daily_windScaleDay_str[1] = daily_1["windScaleDay"].as<String>();
  _daily_windScaleDay_str[2] = daily_2["windScaleDay"].as<String>();
  _daily_humidity_int[0] = daily_0["humidity"].as<int>();
  _daily_humidity_int[1] = daily_1["humidity"].as<int>();
  _daily_humidity_int[2] = daily_2["humidity"].as<int>();
  _daily_precip_float[0] = daily_0["precip"].as<float>();
  _daily_precip_float[1] = daily_1["precip"].as<float>();
  _daily_precip_float[2] = daily_2["precip"].as<float>();
  _daily_uvIndex_int[0] = daily_0["uvIndex"].as<int>();
  _daily_uvIndex_int[1] = daily_1["uvIndex"].as<int>();
  _daily_uvIndex_int[2] = daily_2["uvIndex"].as<int>();
}

// 返回API状态码
String WeatherForecast::getServerCode() {
  return _response_code;
}

// 返回当前API最近更新时间
String WeatherForecast::getLastUpdate() {
  return _last_update_str;
}

// 返回日期
String WeatherForecast::getFxDate(int index) {
  return _daily_fxDate_str[index];
}
// 返回日出时间
String WeatherForecast::getSunRise(int index) {
  return _daily_sunrise_str[index];
}

// 返回最高气温
int WeatherForecast::getTempMax(int index) {
  return _daily_tempMax_int[index];
}

// 返回最低气温
int WeatherForecast::getTempMin(int index) {
  return _daily_tempMin_int[index];
}

// 返回白天天气状况的图标代码
int WeatherForecast::getIconDay(int index) {
  return _daily_iconDay_int[index];
}

// 返回天气状况的文字描述
String WeatherForecast::getTextDay(int index) {
  return _daily_textDay_str[index];
}

// 返回白天风向
String WeatherForecast::getWindDirDay(int index) {
  return _daily_windDirDay_str[index];
}

// 返回白天风力等级
String WeatherForecast::getwindScaleDay(int index) {
  return _daily_windScaleDay_str[index];
}

// 返回当天相对湿度百分比数值
int WeatherForecast::getHumidity(int index) {
  return _daily_humidity_int[index];
}

// 返回当天降水量，毫米
float WeatherForecast::getPrecip(int index) {
  return _daily_precip_float[index];
}

// 返回当天紫外线强度指数
int WeatherForecast::getUvIndex(int index) {
  return _daily_uvIndex_int[index];
}

