# ESP8266_Heweather

- [ESP8266_Heweather](#esp8266-heweather)
  * [基本介绍](#基本介绍)
  * [准备工作](#准备工作)
  * [使用说明](#使用说明)
    + [获取实时天气信息](#获取实时天气信息)
    + [获取天气预报信息](#获取天气预报信息)
    + [获取空气质量信息](#获取空气质量信息)

## 基本介绍

**Arduino**开发平台使用**ESP8266**获取**和风天气**的第三方库。



此库用于**ESP8266(NodeMCU)**物联网开发板通过**HTTPS协议**获取和风天气API所提供的免费天气信息。使用此库可以省去繁杂的HTTPS请求以及JSON解析部分，使用几行代码即可获取有效信息，大大简化了开发步骤。

> 注：
>
> - 由于信息的安全性要求不高，故HTTPS请求中设置了不进行身份校验；
> - 只涉及常人经常关注的信息如`温度`、`风力`、`降雨`等，其它一般人不关注的信息如`露点温度`等并未解析；



## 准备工作

1. 注册和风天气并获得key，详见 https://dev.heweather.com/docs/start/get-api-key；

2. 安装ESP8266扩展程序，详见 https://github.com/esp8266/Arduino；

3. 安装**ArduinoJson**库，详见 https://github.com/bblanchon/ArduinoJson；

	其他说明：

	- 私钥获取 https://dev.heweather.com/docs/start/get-api-key；

	- 城市代码 https://github.com/heweather/LocationList

		excel表 `Location_ID`，亦可通过[城市搜索](https://dev.heweather.com/docs/api/geo)获取 ；

	- 和风天气开发者**官方文档**：https://dev.heweather.com/；

## 使用说明

1. 安装本库

	1）下载压缩包或克隆；

	2）解压并复制到**项目文件夹**下的**libraries**目录下；

	3）重启Arduino IDE。

2. **example**目录中列出了使用的基本结构和所有函数示例，为主要参考文档；

### 获取实时天气信息

  ```c++
WeatherNow weatherNow;         // 建立weatherNow对象
weatherNow.config(UserKey, Location, Unit, Lang); // 配置请求信息
weatherNow.getServerCode();    // 获取API状态码   
weatherNow.getLastUpdate();    // 获取服务器更新天气信息时间
weatherNow.getTemp();          // 获取实况温度
weatherNow.getFeelLike();      // 获取实况体感温度
weatherNow.getIcon();          // 获取当前天气图标代码
weatherNow.getWeatherText();   // 获取实况天气状况的文字描述
weatherNow.getWindDir();       // 获取实况风向
weatherNow.getWindScale();     // 获取实况风力等级
weatherNow.getHumidity();      // 获取实况相对湿度百分比数值
weatherNow.getPrecip();        // 获取实况降水量,毫米
  ```



### 获取天气预报信息

```c++
WeatherForecast WeatherForecast;    // 建立WeatherForecast对象
WeatherForecast.config(UserKey, Location, Unit, Lang); // 配置请求信息
WeatherForecast.getServerCode();    // 获取API状态码
WeatherForecast.getLastUpdate();    // 获取服务器更新天气信息时间
// 以下i取值为 0,1,2，分别代表今天，明天和后天
WeatherForecast.getTempMax(i);      // 获取最高温度
WeatherForecast.getTempMin(i);      // 获取最低温度
WeatherForecast.getIconDay(i);      // 获取天气图标代码
WeatherForecast.getTextDay(i);      // 获取天气状况的文字描述
WeatherForecast.getWindDirDay(i);   // 获取风向
WeatherForecast.getwindScaleDay(i); // 获取风力等级
WeatherForecast.getHumidity(i);     // 获取相对湿度百分比数值
WeatherForecast.getPrecip(i);       // 获取降水量,毫米
WeatherForecast.getUvIndex(i);      // 获取紫外线强度指数
```



### 获取空气质量信息

```c++
AirQuality AirQuality;           // 建立AirQuality对象
AirQuality.config(UserKey, Location, Unit, Lang); // 配置请求信息
WeatherForecast.getServerCode(); // 获取API状态码
WeatherForecast.getLastUpdate(); // 获取服务器更新天气信息时间
AirQuality.getServerCode();      // 获取API状态码
AirQuality.getLastUpdate();      // 获取服务器更新天气信息时间
AirQuality.getAqi();             // 实时空气质量指数
AirQuality.getCategory();        // 实时空气质量指数级别
AirQuality.getPrimary();         // 实时空气质量的主要污染物，优时返回值为NA
```





















