#include <Wire.h>
#include <RTClib.h>
#include <DHT.h>
#include <LiquidCrystal.h>

// DHT11 Setup
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// MQ-7 Setup
const int mq7Pin = A0;

// RTC Setup
RTC_DS1307 rtc;

// LCD Setup (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(7, OUTPUT);

  if (!rtc.begin()) {
    Serial.println("RTC nicht gefunden!");
    while (1);
  }

  // Uncomment to set the time on first upload:
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  DateTime now = rtc.now();

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  int sensorValue = analogRead(mq7Pin);
  float voltage = sensorValue * (5.0 / 1023.0);

  // Approximate CO ppm based on voltage
  float co_ppm = (voltage - 0.1) * 1000;
  if (co_ppm < 0) co_ppm = 0;

  lcd.clear();

  // Line 1: Time + Temp
  lcd.setCursor(0, 0);
  if (now.hour() < 10) lcd.print('0');
  lcd.print(now.hour());
  lcd.print(':');
  if (now.minute() < 10) lcd.print('0');
  lcd.print(now.minute());
  lcd.print(':');
  if (now.second() < 10) lcd.print('0');
  lcd.print(now.second());
  lcd.print(' ');

  if (!isnan(temperature)) {
    lcd.print(temperature, 1);
    lcd.print((char)223);
    lcd.print("C");
  } else {
    lcd.print("Temp Err");
  }

  // Line 2: Humidity + CO ppm
  lcd.setCursor(0, 1);
  if (!isnan(humidity)) {
    lcd.print(humidity, 0);
    lcd.print("% ");
  } else {
    lcd.print("Hum Err ");
  }

  lcd.print("CO:");
  lcd.print(co_ppm, 0); 
  lcd.print("ppm");

  Serial.print("Zeit: ");
  if (now.hour() < 10) Serial.print('0');
  Serial.print(now.hour());
  Serial.print(':');
  if (now.minute() < 10) Serial.print('0');
  Serial.print(now.minute());
  Serial.print(':');
  if (now.second() < 10) Serial.print('0');
  Serial.print(now.second());
  Serial.print(" | ");

  if (!isnan(temperature)) {
    Serial.print("Temp: ");
    Serial.print(temperature, 1);
    Serial.print(" °C, ");
  } else {
    Serial.print("Temp Error, ");
  }

  if (!isnan(humidity)) {
    Serial.print("Humidity: ");
    Serial.print(humidity, 1);
    Serial.print(" %, ");
  } else {
    Serial.print("Humidity Error, ");
  }

  Serial.print("CO: ");
  Serial.print(co_ppm, 0);
  Serial.println(" ppm");

  delay(2000);
}