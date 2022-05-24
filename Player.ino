
#include <SD.h>
#include <SoftwareSerial.h>
#include "DFPlayer_Mini_Mp3.h"
#define Pot1 A0
#define Pot2 A1
SoftwareSerial mySerial(2, 3); // RX, TX

#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
#include <avr/power.h>
#endif
#define NUMPIXELS      6
Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3 = Adafruit_NeoPixel(NUMPIXELS, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels4 = Adafruit_NeoPixel(NUMPIXELS, 7, NEO_GRB + NEO_KHZ800);

const int chipSelect = 10;  //设定CS接口
//

#define KEY1 A0
#define KEY2 A1
#define KEY3 8
#define KEY4 9


#define TrigPin A3
#define EchoPin A2

float Value_cm;
void setup () {
  pinMode(KEY1, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
  pinMode(KEY3, INPUT_PULLUP);
  pinMode(KEY4, INPUT_PULLUP);

  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  Serial.begin (9600);
  mySerial.begin (9600);
  delay(100);
  mp3_set_serial (mySerial);	//set softwareSerial for DFPlayer-mini mp3 module
  delay(1);  //wait 1ms for mp3 module to set volume
  mp3_set_volume (30);
  delay(100);
  //mp3_play (2);
  //mp3_single_play (1);//单一循环
  delay (100);

#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels1.begin();
  pixels2.begin();
  pixels3.begin();
  pixels4.begin();

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels1.setPixelColor(i, pixels1.Color(0, 50, 0)); // Moderately bright green color.
    pixels2.setPixelColor(i, pixels1.Color(0, 50, 0));
    pixels3.setPixelColor(i, pixels1.Color(0, 50, 0));
    pixels4.setPixelColor(i, pixels1.Color(0, 50, 0));
  }
  pixels1.show(); // This sends the updated pixel color to the hardware.
  pixels2.show();
  pixels3.show();
  pixels4.show();
  delay(1000);
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels1.setPixelColor(i, pixels1.Color(0, 0, 0)); // Moderately bright green color.
    pixels2.setPixelColor(i, pixels1.Color(0, 0, 0));
    pixels3.setPixelColor(i, pixels1.Color(0, 0, 0));
    pixels4.setPixelColor(i, pixels1.Color(0, 0, 0));
  }
  pixels1.show(); // This sends the updated pixel color to the hardware.
  pixels2.show();
  pixels3.show();
  pixels4.show();

  Serial.print("Initializing SD card...");  //串口输出数据Initializing SD card...
  pinMode(chipSelect, OUTPUT);


  if (!SD.begin(chipSelect)) {  //如果从CS口与SD卡通信失败，串口输出信息Card failed, or not present
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");  //与SD卡通信成功，串口输出信息card initialized.
  //xinjianwenjian("datalog.csv");
}
long timer1 = 0;
String dataString = "";
int recordxiangmu = 0;
long recordtimer1 = 0;
bool ganyin = 0;
int onoff = 0;
int modeval = 0;
int js = 0;
void loop () {

  if (millis() - timer1 > 1000)
  {
    timer1 = millis();
    if (modeval == 0)
    {
      Value_cm = getddistance(TrigPin, EchoPin);
      Serial.println(Value_cm);

      if (Value_cm < 10 && ganyin == 0)
      {
        if (onoff == 1) //录制模式
        {
          Serial.println("录制模式 开始");
          js = 0;
          xinjianwenjian("datalog.csv");
          modeval = 1;
          for (int i = 0; i < 5; i++)
          {
            ledshan("1", "1","1", "1", 50, 0, 0);
          }
          mp3_play (1);
        }
        if (onoff == 2)//2//播放模式
        {
          Serial.println("播放模式 开始");
          js = 0;
          modeval = 2;
          for (int i = 0; i < 5; i++)
          {
            ledshan("1", "1","1", "1", 0, 0, 50);
          }
          mp3_play (1);
        }
      }
      else if (Value_cm < 30 && ganyin == 0)
      {
        ganyin = 1;
        onoff++;
        if (onoff > 2) // 0 off  1 //录制模式 2//播放模式
          onoff = 0;
        if (onoff == 0)
        {
          Serial.println("0 off");
          modeval = 0;
          mp3_stop ();
          for (int i = 0; i < NUMPIXELS; i++) {
            pixels1.setPixelColor(i, pixels1.Color(0, 0, 0)); // Moderately bright green color.
            pixels2.setPixelColor(i, pixels1.Color(0, 0, 0));
            pixels3.setPixelColor(i, pixels1.Color(0, 0, 0));
            pixels4.setPixelColor(i, pixels1.Color(0, 0, 0));
          }
          pixels1.show(); // This sends the updated pixel color to the hardware.
          pixels2.show();
          pixels3.show();
          pixels4.show();
        }
        if (onoff == 1)
        {
          Serial.println("1 //录制模式");
          mp3_play (3);
          for (int i = 0; i < NUMPIXELS; i++) {
            pixels1.setPixelColor(i, pixels1.Color(50, 0, 0)); // Moderately bright green color.
            pixels2.setPixelColor(i, pixels1.Color(50, 0, 0));
            pixels3.setPixelColor(i, pixels1.Color(50, 0, 0));
            pixels4.setPixelColor(i, pixels1.Color(50, 0, 0));
          }
          pixels1.show(); // This sends the updated pixel color to the hardware.
          pixels2.show();
          pixels3.show();
          pixels4.show();
        }
        if (onoff == 2)
        {
          Serial.println("2//播放模式");
          mp3_play (2);
          for (int i = 0; i < NUMPIXELS; i++) {
            pixels1.setPixelColor(i, pixels1.Color(0, 0, 50)); // Moderately bright green color.
            pixels2.setPixelColor(i, pixels1.Color(0, 0, 50));
            pixels3.setPixelColor(i, pixels1.Color(0, 0, 50));
            pixels4.setPixelColor(i, pixels1.Color(0, 0, 50));
          }
          pixels1.show(); // This sends the updated pixel color to the hardware.
          pixels2.show();
          pixels3.show();
          pixels4.show();
        }

      }
      if (Value_cm > 50 )
      {
        ganyin = 0;
      }
    }
  }
  if (modeval == 1) //录制模式
  {
    recordMode();//录制模式

  }
  if (modeval == 2) //播放模式
  {
    palyMode();//播放模式
  }
}
void recordMode()//录制模式
{
  String num1 = "0";
  String num2 = "0";
  String num3 = "0";
  String num4 = "0";
  if (recordxiangmu == 0) //等待检测
  {
    if (digitalRead(KEY1) == 0)
    {
      delay(10);
      if (digitalRead(KEY1) == 0)
      {
        Serial.println("key1");
        num1 = "1";
        recordxiangmu = 1;
        //recordtimer1=millis();
      }
    }
    if (digitalRead(KEY2) == 0)
    {
      delay(10);
      if (digitalRead(KEY2) == 0)
      {
        Serial.println("key2");
        num2 = "1";
        recordxiangmu = 1;
        //recordtimer1=millis();
      }
    }
    if (digitalRead(KEY3) == 0)
    {
      delay(10);
      if (digitalRead(KEY3) == 0)
      {
        Serial.println("key3");
        num3 =  "1";
        recordxiangmu = 1;
        ///recordtimer1=millis();
      }
    }
    if (digitalRead(KEY4) == 0)
    {
      delay(10);
      if (digitalRead(KEY4) == 0)
      {
        Serial.println("key4");
        num4 =  "1";
        recordxiangmu = 1;
        //recordtimer1=millis();
      }
    }
    if (millis() - recordtimer1 > 1000) //超时 没检测到 记录为空动作
    {
      recordxiangmu = 1;
    }
  }
  if (recordxiangmu == 1) //记录到SD 蓝牙发送结果
  {
    String recordStr = "";
    ledliushui(num1, num2, num3, num4, 50, 0, 0);
    recordStr = num1 + "," + num2 + "," + num3 + "," + num4;
    Serial.println("send=" + recordStr);

    //dao SD
    File dataFile = SD.open("datalog.csv", FILE_WRITE);
    // 打开datalog.txt文件，读写状态，位置在文件末尾。
    if (dataFile)
    {
      dataFile.println(recordStr);
      // 数组dataString输出到串口
      Serial.println(recordStr);
    }
    // 如果无法打开文件，串口输出错误信息error opening datalog.txt
    else
    {
      Serial.println("error opening datalog.txt");
    }
    dataFile.close();

    recordxiangmu = 2;

    js++;
    Value_cm = getddistance(TrigPin, EchoPin);
    Serial.println(Value_cm);
    Serial.println("js=" + String(js));
    if (Value_cm < 30 || js > 90)
    {
      Serial.println("录制模式 结束");
      modeval = 0;
      onoff = 0;
      mp3_stop ();
      for (int i = 0; i < 5; i++)
      {
        ledshan("1", "1","1", "1", 50, 0, 0);
      }
    }
  }
  if (recordxiangmu == 2)//控制记录节拍
  {
    if (millis() - recordtimer1 > 1000) //超时 没检测到 记录为空动作
    {
      recordxiangmu = 0;
      recordtimer1 = millis();
    }
  }
}
void palyMode()//播放模式
{
  String str;
  unsigned long index = 0;
  String num1 = "0";
  String num2 = "0";
  String num3 = "0";
  String num4 = "0";
  String leddo1 = "0";
  String leddo2 = "0";
  String leddo3 = "0";
  String leddo4 = "0";
  File dataFile = SD.open("datalog.csv");
  if (dataFile)
  {
    while (dataFile.available())
    { //检查是否dataFile是否有数据
      char inChar = (char)dataFile.read(); //如果有数据则把数据发送到串口
      str += inChar;
      if (inChar == '\n')//
      {
        Serial.println(str);
        num1 = str.substring(0, 1);
        num2 = str.substring(2, 3);
        num3 = str.substring(4, 5);
        num4 = str.substring(6, 7);
        String recordStr = num1 + "," + num2 + "," + num3 + "," + num4;
        Serial.println("read csv=" + recordStr);
        ledliushui(num1, num2, num3, num4, 0, 0, 50);
        long timerd = 0;
        timerd = millis();
        while (millis() - timerd < 1000)
        {
          leddo1 = "0";
          leddo2 = "0";
          leddo3 = "0";
          leddo4 = "0";
          if (digitalRead(KEY1) == 0 && num1 == "1")
          {
            Serial.println("key1");
            leddo1 = "1";
          }
          if (digitalRead(KEY2) == 0 && num2 == "1")
          {
            Serial.println("key2");
            leddo2 = "1";
          }
          if (digitalRead(KEY3) == 0 && num3 == "1")
          {
            Serial.println("key3");
            leddo3 = "1";
          }
          if (digitalRead(KEY4) == 0 && num4 == "1")
          {
            Serial.println("key4");
            leddo4 = "1";
          }
          ledshan(leddo1, leddo2, leddo3, leddo4, 0, 50, 0);
        }
        js++;
        Value_cm = getddistance(TrigPin, EchoPin);
        Serial.println(Value_cm);
        Serial.println("js=" + String(js));
        if (Value_cm < 30 || js > 90)
        {
          Serial.println("播放模式 结束");
          onoff = 0;
          modeval = 0;
          mp3_stop ();
          for (int i = 0; i < 5; i++)
          {
            ledshan("1", "1","1", "1", 0, 0, 50);
          }
          dataFile.close();
          delay(1000);
          break;
        }

        str = ""; //清除
      }
    }
    Serial.println("播放模式 结束");
    onoff = 0;
    modeval = 0;
    mp3_stop ();
  }
  else
  {
    Serial.println("datalog.csv no find");
  }
  dataFile.close();
}
float getddistance(int Trig, int Echo)
{
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  digitalWrite(Trig, LOW); //低高低电平发一个短时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  //读取一个引脚的脉冲（HIGH或LOW）。例如，如果value是HIGH，pulseIn()会等待引脚变为HIGH，开始计时，再等待引脚变为LOW并停止计时。
  //返回脉冲的长度，单位微秒。如果在指定的时间内无脉冲函数返回。
  //此函数的计时功能由经验决定，长时间的脉冲计时可能会出错。计时范围从10微秒至3分钟。（1秒=1000毫秒=1000000微秒）
  //接收到的高电平的时间（us）* 340m/s / 2 = 接收到高电平的时间（us） * 17000 cm / 1000000 us = 接收到高电平的时间 * 17 / 1000  (cm)
  return float( pulseIn(Echo, HIGH) * 17 ) / 1000; //将回波时间换算成cm

}
