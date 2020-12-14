# EMF
Environmental monitoring and feedback

@[TOC](基于Arduino的智能环境监测与反馈系统)

# 一、项目背景

> 一个小巧轻便的环境监测系统，可以帮助人们更好地了解周围环境。

随着社会的发展，生产技术的更新，物联网理念如今已经深入人心，并随着传感器技术，通信技术和物联网技术的发展逐渐触及社会的每一个角落。

在当代社会信息化，智能化快速发展的背景下，设计了“基于Arduino的智能环境监测与反馈系统”。

近几年，工业化进程的日益发展导致环境污染问题日益突出，随着环境状况的不断变化，各地雾霾天气日益严重，已经影响到了人们的正常出行、生活以及健康，因此人们掌握了解自身所处周边环境状况信息的需求越来越迫切。

伴随着当前移动互联网技术的飞速发展，人们可以随时随地了解自己所处的环境状况信息，为出行和生活提供便捷服务，为寻求更加健康的环境提供依据。

本文主要利用现有的成熟传感技术和互联网技术实现实时获取环境状况信息，并对用户给予相应的反馈。


# 二、效果展示

<iframe src="//player.bilibili.com/player.html?aid=670685390&bvid=BV1ya4y1H7KH&cid=266770600&page=1" scrolling="no" border="0" frameborder="no" framespacing="0" allowfullscreen="true"> </iframe>


# 三、材料清单

## 1.Arduino开发板——YwRduino uno


市面上的开发板大同小异，一般都是使用Arduino UNO R3，新款开发板的性能可能要好一些，但是使用方法几乎一样

## 2.Arduino盾板——IO Sensor Shield传感器接口扩展板

因为该项目需要接的传感器较多，所以我买了一个扩展板。

如果平常使用的传感器不多，可以不使用扩展板。

## 3.8x7LED点阵显示模块

该模块用于显示表情，通过表情反映当前环境的状况


## 4.AM2302 DHT22温湿度传感器


温湿度传感器，顾名思义，就是用来检测环境温度和湿度的

## 5.火焰传感器——类似光敏传感器



火焰传感器只是对火焰最敏感，但是对普通光也有反应

## 6.声音传感器

声音传感器是用于检测声音信号大小的传感器




# 四、实现思路
在购买材料之前，我们计划把这个系统打造成一个“人”，赋予他感知环境并根据环境做出反馈的能力。

因此整体的思路是：

## 1.通过传感器获取环境信息
作为一个智能系统，当然是获取的信息越全面越好。因此这里指的传感器可以不止是上面提到的那些传感器，用户可以根据需要自行添加更多种类的传感器。

每个传感器的使用方法其实查查文档，基本都能找到使用方法，网上也有很多案例，基本都是可以拿来即用的。

> 这一步的工作量主要在代码整理上，将各种传感器的代码进行整合。

## 2.根据环境情况做出不同回应
有了所需要的环境信息后，便能利用环境信息做出一定的反馈，就跟人一样，当我们感到太热或太冷时，我们会通过表情及言语表达出来。

> 这一步主要的工作量在于如何设计系统的判断条件，即到底什么是热，它的具体数值是多少，这是我们需要确定的。

然后再写一些条件判断，当条件成立时，执行某些操作；条件不成立，再去执行其他操作。


# 五、具体步骤
## 1.获取环境温湿度

### 连接电路
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020121405363997.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3picF8xMjEzOA==,size_16,color_FFFFFF,t_70#pic_center)

### 引入必要的库和文件

```cpp
// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); 
  Serial.println("DHTxx test!");
 
  dht.begin();
}
```


### 主要函数编写

```cpp
// 读取湿度
void ReadH(){
  float humidity = dht.readHumidity();
  Serial.print("Humidity: "); 
  Serial.print(humidity);
  Serial.print(" %\t");
  return humidity;
}

// 读取温度
void ReadT(){
  float temperature = dht.readTemperature();
  Serial.print("Temperature: "); 
  Serial.print(temperature);
  Serial.println(" *C");
  return temperature;
}
```


### 效果展示及验证


![在这里插入图片描述](https://img-blog.csdnimg.cn/2020121500380359.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3picF8xMjEzOA==,size_16,color_FFFFFF,t_70)






## 2.获取环境声音大小

### 连接电路
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201215002839243.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3picF8xMjEzOA==,size_16,color_FFFFFF,t_70)
这里我将声音传感器的out引脚接到了模拟口0上


### 主要函数编写

```cpp
void ReadVoice(){
  int Voice = analogRead(0);   //传感器接于模拟口0
  Serial.print("Voice: "); 
  Serial.print(Voice);
  Serial.println();
  return Voice;
}
```

### 效果展示及验证
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201215003306618.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3picF8xMjEzOA==,size_16,color_FFFFFF,t_70)




## 3.获取环境亮度

### 连接电路
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201214054610323.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3picF8xMjEzOA==,size_16,color_FFFFFF,t_70#pic_center)



### 主要函数编写

```cpp
void ReadFire(){
  int Fire = analogRead(5);   //传感器接于模拟口5
  Serial.print("Fire: "); 
  Serial.print(Fire);
  Serial.println();
  return Fire;
}
```


### 效果展示及验证
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201215003401893.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3picF8xMjEzOA==,size_16,color_FFFFFF,t_70)
在没有光照或光照很弱时，火焰传感器的输出数值较大

当受到光照或有火焰时：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201215003604772.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3picF8xMjEzOA==,size_16,color_FFFFFF,t_70)
传感器输出数值变小：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201215003626286.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3picF8xMjEzOA==,size_16,color_FFFFFF,t_70)




## 4.确定反馈逻辑
> 根据传感器接收到的环境数据做出相应动作，此处参数可自行修改

### 代码实现

```cpp
  if (humidity < 25){
    DrawEmoji(broken_emoji);
    Serial.println("broken");
  }
  else if (Fire > 1000){
    DrawEmoji(blush_emoji);
    Serial.println("blush");
  }
  else if (temperature < 15){
    DrawEmoji(sad_emoji);
    Serial.println("sad");
  }
  else if (Voice > 100){
    DrawEmoji(angry_emoji);
    Serial.println("angry");
  }
  else{
    DrawEmoji(smeil_emoji);
    Serial.println("smeil");
    }
```


## 5.根据反馈逻辑输出表情

### 连接电路
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201215004235805.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3picF8xMjEzOA==,size_16,color_FFFFFF,t_70#pic_center)


### 引入必要的库和文件并编写表情

```cpp
// 7*8点阵屏
#include <SparkFun_LED_8x7.h>
#include <Chaplex.h>

byte led_pins[] = {4, 5, 6, 7, 8, 9, 10, 11}; // Pins for LEDs
byte i;
byte x;
byte y;
byte radius;
// smeil
const byte smeil_emoji[] = { 
                             0,0,0,0,0,0,0,0,
                             0,0,0,1,1,0,0,0,
                             0,0,1,0,0,1,0,0,
                             0,0,0,0,0,0,0,0,
                             0,0,0,0,0,0,0,0,
                             1,0,1,0,0,1,0,1,
                             0,1,0,0,0,0,1,0};

// sad
const byte sad_emoji[] = { 
                             0,0,0,0,0,0,0,0,
                             0,0,1,0,0,1,0,0,
                             0,0,0,1,1,0,0,0,
                             0,0,0,0,0,0,0,0,
                             0,0,0,0,0,0,0,0,
                             1,0,1,0,0,1,0,1,
                             0,1,0,0,0,0,1,0};

// shy
const byte shy_emoji[] = { 
                             0,0,0,0,0,0,0,0,
                             0,0,0,1,1,0,0,0,
                             0,0,1,0,0,1,0,0,
                             0,1,0,0,0,0,1,0,
                             0,0,0,0,0,0,0,0,
                             0,1,1,0,0,1,1,0,
                             1,0,0,1,1,0,0,1};

// blush
const byte blush_emoji[] = { 
                             0,0,0,0,0,0,0,0,
                             0,0,1,1,1,1,0,0,
                             0,0,0,0,0,0,0,0,
                             0,1,0,0,0,0,1,0,
                             1,0,1,0,0,1,0,1,
                             1,0,1,0,0,1,0,1,
                             0,1,0,0,0,0,1,0};

// angry
const byte angry_emoji[] = { 
                             0,0,0,0,0,0,0,0,
                             0,1,0,0,0,1,0,0,
                             0,0,1,1,1,0,0,0,
                             0,0,0,0,0,0,0,0,
                             0,1,1,0,0,1,1,0,
                             1,0,1,0,0,1,0,1,
                             1,0,0,0,1,0,0,1};

// broken
const byte broken_emoji[] = { 
                             0,0,0,0,0,0,0,0,
                             0,1,0,0,0,0,1,0,
                             0,0,1,1,1,1,0,0,
                             0,0,0,0,0,0,0,0,
                             1,0,1,0,0,1,0,1,
                             0,1,0,0,0,0,1,0,
                             1,0,1,0,0,1,0,1};
```

### 主要函数编写

```cpp
void DrawEmoji(const byte emojy[]){
  Plex.clear();
  Plex.drawBitmap(emojy);
  Plex.display();
}
```

### 效果展示及验证
- 输出笑脸：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201215004708818.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3picF8xMjEzOA==,size_16,color_FFFFFF,t_70)
- 蒙圈表情：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201215004826243.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3picF8xMjEzOA==,size_16,color_FFFFFF,t_70)
- 难受表情：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201215004848729.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3picF8xMjEzOA==,size_16,color_FFFFFF,t_70)



## 6.根据反馈逻辑合成语音并输出

### 通过Python获取Arduino串口数据
这里需要一个serial库，用于和Arduino通信，使用以下命令进行安装：

```bash
pip install pyserial
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201215005041400.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3picF8xMjEzOA==,size_16,color_FFFFFF,t_70)

> pyserial的官方文档：[https://pypi.org/project/pyserial/](https://pypi.org/project/pyserial/)

这里简单带大家过一下pyserial库的使用方法。

#### 打开串口
插入Arduino后，可以看到对应的串口，一般是COM3
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201215005722680.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3picF8xMjEzOA==,size_16,color_FFFFFF,t_70)
下面通过serial库打开COM3：

```python
import serial

Sensor = serial.Serial('COM3', 9600, timeout=0.2)
```


#### 读取串口输出

```python
strs = Sensor.readline().decode('utf-8')
if strs.strip()!='':
	print(strs)
```

### 通过win32com库语音合成

```python
import win32com.client

speaker = win32com.client.Dispatch("SAPI.SpVoice")
text = "输入要语音合成的内容"
speaker.Speak(text)
```


# 六、代码汇总
本项目使用的代码已上传至GitHub：
[https://github.com/zbp-xxxp/EMF](https://github.com/zbp-xxxp/EMF)

