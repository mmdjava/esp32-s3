#include <Wire.h>
#include <DS3231.h>

DS3231  rtc(SDA, SCL);
int buzzerPin = 2;  // پینی که بازر به آن وصل شده است

void setup() {
  Serial.begin(115200);
  rtc.begin();
  pinMode(buzzerPin, OUTPUT);  // تعریف پین بازر به عنوان خروجی
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readString();
    if (input.startsWith("setTime")) {
      int hour = input.substring(8, 10).toInt();
      int minute = input.substring(11, 13).toInt();
      int second = input.substring(14, 16).toInt();
      rtc.setTime(hour, minute, second);
    }
  }

  // اگر ساعت 3:30 بود
  if (rtc.getTimeStr().substring(0, 5) == "03:30") {
    digitalWrite(buzzerPin, HIGH);  // بازر را فعال می‌کنیم
    delay(10000);  // یک ثانیه صبر می‌کنیم
    digitalWrite(buzzerPin, LOW);  // بازر را خاموش می‌کنیم
  }

  delay(1000);
}
