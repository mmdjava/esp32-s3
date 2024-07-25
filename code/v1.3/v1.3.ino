#include <Wire.h>
#include <DS3231.h>

DS3231  rtc(SDA, SCL);
int buzzerPin = 2;
int led1 = 4;  // پینی که LED دوم به آن وصل شده است
String alarmTime = "03:30";

void setup() {
  Serial.begin(115200);
  rtc.begin();
  pinMode(buzzerPin, OUTPUT);
  pinMode(led1, OUTPUT);  // تعریف پین LED دوم به عنوان خروجی
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readString();
    if (input.startsWith("setTime")) {
      int hour = input.substring(8, 10).toInt();
      int minute = input.substring(11, 13).toInt();
      int second = input.substring(14, 16).toInt();
      rtc.setTime(hour, minute, second);
    } else if (input.startsWith("setAlarm")) {
      alarmTime = input.substring(8, 13);
    }
  }

  if (rtc.getTimeStr().substring(0, 5) == alarmTime) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(led1, HIGH);  // روشن کردن LED دوم
    delay(10000);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(led1, LOW);  // خاموش کردن LED دوم
  }

  delay(1000);
}
