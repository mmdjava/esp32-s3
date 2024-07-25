#include <Wire.h>  // کتابخانه‌ای برای ارتباط I2C
#include <DS3231.h>  // کتابخانه‌ای برای کار با ماژول DS3231

DS3231  rtc(SDA, SCL);

void setup() {
  Serial.begin(115200);  // شروع ارتباط سریال با سرعت 115200
  rtc.begin();  // شروع کار با ماژول DS3231
}

void loop() {
  if (Serial.available()) {  // اگر داده‌ای در پورت سریال وجود داشت
    String input = Serial.readString();  // خواندن داده از پورت سریال
    if (input.startsWith("setTime")) {  // اگر داده ورودی با "setTime" شروع می‌شد
      int hour = input.substring(8, 10).toInt();  // استخراج ساعت از داده ورودی
      int minute = input.substring(11, 13).toInt();  // استخراج دقیقه از داده ورودی
      int second = input.substring(14, 16).toInt();  // استخراج ثانیه از داده ورودی
      rtc.setTime(hour, minute, second);  // تنظیم زمان بر روی ماژول DS3231
    }
  }

  // چاپ زمان فعلی بر روی پورت سریال
  Serial.print(rtc.getTimeStr());
  Serial.println();
  
  delay(1000);  // تاخیر یک ثانیه
}
