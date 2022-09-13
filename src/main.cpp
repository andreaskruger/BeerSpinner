#include <Arduino.h>
#include <TB6612FNG.h>
#include<TalkyBoi.h>

#define AIN1 25
#define AIN2 26
#define PWMA 33
#define STBY 32
#define potPin 15
#define ADC_MAX 4096

int potValue = 0;
int potMap = 0;

Tb6612fng motor(STBY, AIN1, AIN2, PWMA);

void setup() {
  Serial.begin(115200);
  motor.begin();
  WIFI_init();
  pinMode(potPin,INPUT);
}

void loop() {
  int time = millis();
  potValue = analogRead(potPin);
  potMap = map(potValue, 0,ADC_MAX,0,255);
  motor.drive(potMap, 100);
  int currentTime = time - millis();
  //Serial.print(currentTime);
}