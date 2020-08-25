#include "AirQuality.h"

AirQuality::AirQuality() {
}

// 配置请求信息，私钥、位置、单位、语言
void AirQuality::config(String userKey, String location, String unit, String lang) {
  _requserKey = userKey;
  _reqLocation = location;
  _reqUnit = unit;
  _reqLang = lang;
}

// 尝试获取信息，成功返回true，失败返回false
bool AirQuality::get() {
  // https请求
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure(); //不进行服务器身份认证
  HTTPClient https;
  #ifdef DEBUG
  Serial.print("[HTTPS] begin...\n");
  #endif DEBUG
  String url = "https://devapi.heweather.net/v7/air/now?location=" + _reqLocation +
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

// 解析Json信息
void AirQuality::_parseNowJson(String payload) {
  const size_t capacity = 2*JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(10) + 250;
  DynamicJsonDocument doc(capacity);

  deserializeJson(doc, payload);

  const char* code = doc["code"];
  const char* updateTime = doc["updateTime"];
  JsonObject now = doc["now"];

  _response_code = doc["code"].as<String>();         // API状态码
  _last_update_str = doc["updateTime"].as<String>(); // 当前API最近更新时间
  _now_aqi_int = now["aqi"].as<int>();               // 实时空气质量指数
  _now_category_str = now["category"].as<String>();  // 实时空气质量指数级别
  _now_primary_str = now["primary"].as<String>();    // 实时空气质量的主要污染物，优时返回 NA

}

// API状态码
String AirQuality::getServerCode() {
  return _response_code;
}

// 当前API最近更新时间
String AirQuality::getLastUpdate() {
  return _last_update_str;
}

// 实时空气质量指数
int AirQuality::getAqi() {
  return _now_aqi_int;
}

// 实时空气质量指数级别
String AirQuality::getCategory() {
  return _now_category_str;
}

// 实时空气质量的主要污染物，空气质量为优时，返回值为NA
String AirQuality::getPrimary() {
  return _now_primary_str;
}
