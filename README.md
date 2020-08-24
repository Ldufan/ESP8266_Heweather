# ESP8266_Heweather

## 基本介绍

**Arduino**开发平台使用**ESP8266**获取**和风天气**的第三方库。



此库用于ESP8266(NodeMCU)开发板通过HTTPS协议获取和风天气API所提供的免费天气信息。使用此库可以省去繁杂的HTTPS请求以及JSON解析部分，使用几行代码即可获取有效信息，大大简化了开发步骤。

和风天气开发者官方文档：https://dev.heweather.com/

## 准备工作

1. 注册和风天气并获得key，详见 https://dev.heweather.com/docs/start/get-api-key；
2. 安装ESP8266扩展程序，详见 https://github.com/esp8266/Arduino；
3. 安装**ArduinoJson**库，详见 https://github.com/bblanchon/ArduinoJson；

## 使用说明

1. 安装本库

	1）下载压缩包或克隆；

	2）解压并复制到**项目文件夹**下的**libraries**目录下；

	3）重启Arduino IDE。

2. **esample**目录中列出了使用的基本结构和所有函数示例，为主要参考文档；

### 获取实时天气信息

  ```
  WeatherNow weatherNow;                            //建立weatherNow对象
  weatherNow.config(UserKey, Location, Unit, Lang); // 配置请求信息
  // 部分函数示例
  weatherNow.getLastUpdate();        //获取服务器更新天气信息时间
  weatherNow.getTemp();              //获取实况温度
  weatherNow.getIcon();              //获取当前天气图标代码
  weatherNow.getWindScale();         //获取实况风力等级
  ```

### 获取天气预报信息

开发中。。。

### 获取空气质量信息

开发中。。。

















