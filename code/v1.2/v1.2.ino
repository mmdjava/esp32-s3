#include <Wire.h>
#include <DS3231.h>

DS3231  rtc(SDA, SCL);
int buzzerPin = 2;
String alarmTime = "03:30";  // ساعت فعال شدن بازر به صورت پیش‌فرض

void setup() {
  Serial.begin(115200);
  rtc.begin();
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readString();
    if (input.startsWith("setTime")) {
      int hour = input.substring(8, 10).toInt();
      int minute = input.substring(11, 13).toInt();
      int second = input.substring(14, 16).toInt();
      rtc.setTime(hour, minute, second);
    } else if (input.startsWith("setAlarm")) {  // اگر داده ورودی با "setAlarm" شروع می‌شد
      alarmTime = input.substring(8, 13);  // استخراج ساعت از داده ورودی
    }
  }

  // اگر ساعت فعلی با ساعت تنظیم شده برای بازر برابر بود
  if (rtc.getTimeStr().substring(0, 5) == alarmTime) {
    digitalWrite(buzzerPin, HIGH);
    delay(1000);
    digitalWrite(buzzerPin, LOW);
  }

  delay(1000);
}
