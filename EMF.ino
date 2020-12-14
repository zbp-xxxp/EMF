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

// DHT humidity/temperature sensors
#include "DHT.h"

#define DHTPIN 2   // what pin we're connected to

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
  Serial.println(F("------------Start-----------"));

  // Initialize and clear display
  Plex.init(led_pins);
  Plex.clear();
  Plex.display();
  DrawEmoji(smeil_emoji); //默认启动时为笑脸
  
  // Seed our random number generator with an analog voltage read
  randomSeed(analogRead(0));
  dht.begin(); //温湿度传感器
}

float humidity = 0;
float temperature = 0;
int Voice = 0;
int Fire = 0;

void DrawEmoji(const byte emojy[]){
  Plex.clear();
  Plex.drawBitmap(emojy);
  Plex.display();
}

// 读取湿度
void ReadH(){
  humidity = dht.readHumidity();
  Serial.print("Humidity: "); 
  Serial.print(humidity);
  Serial.print(" %\t");
}

// 读取温度
void ReadT(){
  temperature = dht.readTemperature();
  Serial.print("Temperature: "); 
  Serial.print(temperature);
  Serial.println(" *C");
}

void ReadVoice(){
  Voice = analogRead(0);   //传感器接于模拟口0
  Serial.print("Voice: "); 
  Serial.print(Voice);
  Serial.println();
}

void ReadFire(){
  Fire = analogRead(5);   //传感器接于模拟口5
  Serial.print("Fire: "); 
  Serial.print(Fire);
  Serial.println();
}


void loop() {
  ReadH();
  ReadT();
  ReadVoice();
  ReadFire();  
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
  delay(5000);
}
