#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int i;
int j;
const int irReceiver = 9;                // 紅外線接收器


const int irLed  = 10;                    // 紅外線發射器
const unsigned int frequency = 38000;    // 發射頻率(單位: Hz)
int sensorPin = A0;
int sensorValue = 0;
boolean button = 0;
int points = 0;
int highest = 0;
int count = 60;
int ir_status;
int stage = 0;
int LED2=11;
int LED3=12;
const byte LEDs[10] = {
  B01111110,
  B00110000,
  B01101101,
  B01111001,
  B00110011,
  B01011011,
  B01011111,
  B01110000,
  B01111111,
  B01111011
};
void setup() {
  Serial.begin(9600);  // 開啟 Serial port, 通訊速率為 9600 bps
  pinMode(2, OUTPUT); //2 3 4 5 6 7 七段式顯示器
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);//button
  pinMode(irReceiver, INPUT);     // 把 irReceiver 接腳設置為 INPUT
  pinMode(irLed, OUTPUT);        // 把 irLed 接腳設置為 INPUT
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  tone(irLed, frequency);       // 產生指定頻率的脈波 (Pulses)
  lcd.begin(16, 2);
}
int high = 0;
void loop() {
  if (!button) //按下按鈕時
  {
    button = digitalRead(8);
    points = 0;
    highest = high;
    count = 41;
    stage = 1;
  }
  if (button)//按鈕鬆開時
  {
    lcd.clear();
    if (count >= 1)
    {
      //Serial.println(points);
      count -= 1;//倒數
      i = count / 10;
      j = count % 10;
     // Serial.print(i);
     // Serial.println(j);
      digitalWrite(3, LOW);
      shiftOut(2, 4, LSBFIRST, LEDs[i]);
      digitalWrite(3, HIGH);
      digitalWrite(6, LOW);
      shiftOut(5, 7, LSBFIRST, LEDs[j]);
      digitalWrite(6, HIGH);
      if (i != 0 && j == 0)//正常時間倒數
      {
        i--;
        j = j + 9;
      }
      else
      {
        j--;
      }
      lcd.setCursor(0, 0); // 設定游標位置在第一行行首
      lcd.print("Points:");
      lcd.setCursor(0, 1); // 設定游標位置在第二行行首
      lcd.print(points);
      lcd.setCursor(8, 0); // 設定游標位置
      lcd.print("Highest:");
      lcd.setCursor(8, 1); // 設定游標位置
      lcd.print(highest);
      boolean a = false;
      boolean b = false;
      boolean big = false;
      int score1 = 30;
      int score2 = 70;
      Serial.println(points);
      for (int i = 0; i < 1000; i = i + 40)
      {
        ir_status = digitalRead(irReceiver);
        Serial.println(sensorValue);
        Serial.println(ir_status);
        if (big == false)
        {
          sensorValue = analogRead(sensorPin);
        }
        if (sensorValue > 1000)
        {
          big = true;
          if (ir_status == 0 && a == false)
          {
            a = true;
            points += 2;
            digitalWrite(LED2,HIGH);
            delay(40);
            digitalWrite(LED2,LOW);
          }
          else 
          {
            delay(40);
          }
        }
        else
        {
          if (ir_status == 0 && b == false)
          {            
            points += 3; 
            b = true;
            digitalWrite(LED3,HIGH);
            delay(40);
            digitalWrite(LED3,LOW);    
          }
          else 
          {
            delay(40);
          }
        }
        
        
      }
      if (count == 0 && points < score1 && stage == 1)
      {
        lcd.clear();
        lcd.setCursor(0, 0); // 設定游標位置在第一行行首
        lcd.print("Game over QQ");
        delay(1500);
        if (points > highest)
        {
          high = points;
        }
        button = false;
      }
      if (count == 0 && points >= score1 && stage == 1)
      {
        stage = 2;
        lcd.clear();
        delay(1500);
        lcd.setCursor(0, 0); // 設定游標位置在第一行行首
        lcd.print("Stage 2 wow");
        delay(1500);
        lcd.clear();
        lcd.setCursor(0, 0); // 設定游標位置在第一行行首
        lcd.print("Wait..");
        lcd.setCursor(0, 8); // 設定游標位置在第一行行首
        lcd.print("3");
        delay(1000);
        lcd.setCursor(0, 8); // 設定游標位置在第一行行首
        lcd.print("2");
        delay(1000);
        lcd.setCursor(0, 8); // 設定游標位置在第一行行首
        lcd.print("1");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0); // 設定游標位置在第一行行首
        lcd.print("Ready");
        delay(1000);
        lcd.setCursor(0, 7); // 設定游標位置在第一行行首
        lcd.print("Go");
        delay(500);
        lcd.clear();
        count = 41;
      }

      if (count == 0 && points >= score2 && stage == 2)
      {
        stage = 3;
        lcd.clear();
        delay(1500);
        lcd.setCursor(0, 0); // 設定游標位置在第一行行首
        lcd.print("Final Stage >=<");
        delay(1500);
        lcd.clear();
        lcd.setCursor(0, 0); // 設定游標位置在第一行行首
        lcd.print("Wait..");
        lcd.setCursor(0, 8); // 設定游標位置在第一行行首
        lcd.print("3");
        delay(1000);
        lcd.setCursor(0, 8); // 設定游標位置在第一行行首
        lcd.print("2");
        delay(1000);
        lcd.setCursor(0, 8); // 設定游標位置在第一行行首
        lcd.print("1");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0); // 設定游標位置在第一行行首
        lcd.print("Ready");
        delay(500);
        lcd.setCursor(0, 7); // 設定游標位置在第一行行首
        lcd.print("Go");
        delay(500);
        lcd.clear();
        count = 21;
      }
      if (count == 0 && points < score2 && stage == 2)
      {
        lcd.clear();
        delay(1500);
        lcd.setCursor(0, 0); // 設定游標位置在第一行行首
        lcd.print("Game over TwT");
        delay(1500);
        if (points > highest)
        {
          high = points;
        }
        button = false;
      }
      if (count == 0 && stage == 3)
      {
        lcd.clear();
        delay(1500);
        lcd.setCursor(0, 0); // 設定游標位置在第一行行首
        lcd.print("Congratulations!!");
        delay(1500);
        if (points > highest)
        {
          high = points;
        }
        button = false;
      }
    }
  }
}
