#include <ESP8266_Heweather.h>

const char* ssid     = "SSID";     // WiFi名称
const char* password = "PASSWORD"; // WiFi密码

String UserKey = "YOUR-KEY";   // 私钥 https://dev.heweather.com/docs/start/get-api-key
String Location = "101010100"; // 城市代码 https://github.com/heweather/LocationList,表中的 Location_ID
String Unit = "m";             // 公制-m/英制-i
String Lang = "zh";            // 语言 英文-en/中文-zh
float ROUND = 0.5;             // 更新间隔<小时>实时天气API 1小时更新一次

AirQuality AirQuality;

void setup(){
  Serial.begin(9600);
  Serial.println("");

  ConnectWiFi(); // 连接WiFi

  AirQuality.config(UserKey, Location, Unit, Lang); // 配置请求信息
}

void loop(){
  if(AirQuality.get()){ // 获取更新
    Serial.println(F("======AirQuality Info======"));
    Serial.print("Server Response: ");
    Serial.println(AirQuality.getServerCode()); // 获取API状态码
    Serial.print(F("Last Update: "));
    Serial.println(AirQuality.getLastUpdate()); // 获取服务器更新天气信息时间
    Serial.print(F("AirQuality Aqi: "));
    Serial.println(AirQuality.getAqi());        // 实时空气质量指数
    Serial.print(F("Category: "));
    Serial.println(AirQuality.getCategory());   // 实时空气质量指数级别
    Serial.print(F("Primary: "));
    Serial.println(AirQuality.getPrimary());    // 实时空气质量的主要污染物，空气质量为优时，返回值为NA
    Serial.println(F("========================"));
  } else {  // 更新失败
    Serial.println("Update Failed...");
    Serial.print("Server Response: ");
    Serial.println(AirQuality.getServerCode()); // 参考 https://dev.heweather.com/docs/start/status-code
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