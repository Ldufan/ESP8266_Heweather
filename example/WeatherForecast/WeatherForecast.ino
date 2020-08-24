#include <ESP8266_Heweather.h>

const char* ssid     = "SSID";   // WiFi名称
const char* password = "PASSWORD"; // WiFi密码

String UserKey = "YOUR-KEY";   // 私钥 https://dev.heweather.com/docs/start/get-api-key
String Location = "101010100"; // 城市代码 https://github.com/heweather/LocationList,表中的 Location_ID
String Unit = "m";             // 公制-m/英制-i
String Lang = "zh";            // 语言 英文-en/中文-zh
float ROUND = 0.5;             // 更新间隔<小时>,天气预报API 1小时更新一次

WeatherForecast WeatherForecast;

void setup(){
  Serial.begin(9600);
  Serial.println("");

  ConnectWiFi(); // 连接WiFi
  WeatherForecast.config(UserKey, Location, Unit, Lang); // 配置请求信息
}

void loop(){
  if(WeatherForecast.get()){ // 获取天气更新
    for (int i = 0; i < 3; i++) {
      Serial.print(F("==========Day "));
      Serial.print(i);
      Serial.println(F("=========="));
      Serial.print("Server Response: ");
      Serial.println(WeatherForecast.getServerCode());    // 获取API状态码
      Serial.print(F("Last Update: "));
      Serial.println(WeatherForecast.getLastUpdate());    // 获取服务器更新天气信息时间
      Serial.print(F("TempMax: "));
      Serial.println(WeatherForecast.getTempMax(i));      // 获取最高温度
      Serial.print(F("TempMin: "));
      Serial.println(WeatherForecast.getTempMin(i));      // 获取最低温度
      Serial.print(F("Icon: "));
      Serial.println(WeatherForecast.getIconDay(i));      // 获取天气图标代码
      Serial.print(F("Weather Direction: "));
      Serial.println(WeatherForecast.getTextDay(i));      // 获取天气状况的文字描述
      Serial.print(F("WindDir: "));
      Serial.println(WeatherForecast.getWindDirDay(i));   // 获取风向
      Serial.print(F("WindScale: "));
      Serial.println(WeatherForecast.getwindScaleDay(i)); // 获取风力等级
      Serial.print(F("Humidity: "));
      Serial.println(WeatherForecast.getHumidity(i));     // 获取相对湿度百分比数值
      Serial.print(F("Precip: "));
      Serial.println(WeatherForecast.getPrecip(i));       // 获取降水量,毫米
      Serial.print(F("UvIndex: "));
      Serial.println(WeatherForecast.getUvIndex(i));      // 获取紫外线强度指数
      Serial.println(F("========================="));
    }
  } else {    // 更新失败
    Serial.println("Update Failed...");
    Serial.print("Server Response: ");
    Serial.println(WeatherForecast.getServerCode()); // 参考 https://dev.heweather.com/docs/start/status-code
  }
  delay(ROUND * 3600000);
}

// 连接WiFi
void ConnectWiFi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);

  int i = 0;
  while (WiFi.status() != WL_CONNECTED && (i < 10)) {
    delay(1000);
    Serial.print('.');
    i++;
  }
  if (i == 10) { // 10s失败
    Serial.println("WiFi Connection Failed");
  } else { // 成功
    Serial.println("");
    Serial.println("WiFi Connection Successful!");
    Serial.print("IP address:    ");
    Serial.println(WiFi.localIP());
  }
}
