#include "SevSeg.h"

#define BUZZER A0
#define ALARM_BUTTON A1
#define HOUR_BUTTON A2
#define MINUTE_BUTTON A3
#define LED_PIN A4
#define ALARM_SWITCH A5

SevSeg sevseg;

int offsetHours = 2;
int offsetMinutes = 46;
int offsetSeconds = 0;

int alarmHours = 2;
int alarmMinutes = 47;
bool alarmStatus = false;

int alarm = 262; // C4

void setup(){

  pinMode(BUZZER, OUTPUT);
  pinMode(ALARM_BUTTON, INPUT_PULLUP);
  pinMode(HOUR_BUTTON, INPUT_PULLUP);
  pinMode(MINUTE_BUTTON, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(ALARM_SWITCH, INPUT_PULLUP);
  
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};

  bool resistorsOnSegments = true;
  
  sevseg.begin(COMMON_CATHODE, 4, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(100);

  Serial.begin(9600);
  Serial.println("WELCOME");
}

void displayCurrentTime() {
  // turn time into a single number
  int currentTime = getHours() * 100 + getMinutes();
  sevseg.setNumber(currentTime);
}

void displayAlarmTime() {
  // turn alarm time into a single number
  int alarmTime = alarmHours * 100 + alarmMinutes;
  sevseg.setNumber(alarmTime);
}

void loop(){
  
  // check if alarm is on and alarm time is met
  if(alarmStatus) {
    if(getHours()==alarmHours && getMinutes()==alarmMinutes) {
      tone(BUZZER, alarm, 10);
      noTone(BUZZER);
    }
  }

  // check if alarm button is pressed, toggle alarm on/off
  if(digitalRead(ALARM_SWITCH)==0) {
    alarmStatus = !alarmStatus;
    noTone(BUZZER);
    delay(500);
  }

  // check if time matches with alarm time
  if(digitalRead(ALARM_BUTTON)==0) {
    // display alarm time
    displayAlarmTime();
    
    if(digitalRead(HOUR_BUTTON)==0) {
      // hour button and alarm button are pressed
      alarmHours = alarmHours + 1;
      delay(500);
    }

    if(digitalRead(MINUTE_BUTTON)==0) {
      // minute button and alarm button are pressed
      alarmMinutes = alarmMinutes + 1;
      delay(500);
    }
  } else {

    // display current time
    displayCurrentTime();

    // increase hour by 1 if hour button is pressed and alarm button is not pressed
    if(digitalRead(HOUR_BUTTON)==0) {
      offsetHours = offsetHours + 1;
      Serial.println(offsetHours);
      if(offsetHours > 23) {
        offsetHours = 0;
      }
      delay(500);
    }

    // increase minute by 1 if alarm button is not pressed and minute button is pressed
    if(digitalRead(MINUTE_BUTTON)==0) {
      offsetMinutes = offsetMinutes + 1;
      if(offsetMinutes > 59) {
        offsetMinutes = 0;
      }
      delay(500);
    }
  }

  // alarm status
  if(alarmStatus) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  sevseg.refreshDisplay();
}

int timeElapsed() {
  return (offsetHours * 3600) + (offsetMinutes * 60) + offsetSeconds + (millis()/1000);
}

int getHours() {
  return (timeElapsed() / 3600) % 24;
}

int getMinutes() {
  return (timeElapsed() / 60) % 60;
}
 
int getSeconds() {
  return timeElapsed() % 60;
}
