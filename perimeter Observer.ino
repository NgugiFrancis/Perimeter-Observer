//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int trig = 22;  // pin  and variable definations
int echo = 23;
int pb = 52;
byte pushButtonState = 0;
long duration;
float distance;
float speed = 0.33;
// set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  pinMode(trig, OUTPUT);  // pins setup
  pinMode(echo, INPUT);
  pinMode(pb, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {

  pushButtonState = digitalRead(pb);
  digitalWrite(trig, 0);
  delayMicroseconds(2);
  digitalWrite(trig, 1);
  delayMicroseconds(10);
  digitalWrite(trig, 0);
  duration = pulseIn(echo, 1);
  distance = duration * speed / 2;
  Serial.print("the distance is in mm ");
  Serial.print(distance);
  Serial.print("the duration is in mm ");
  Serial.println(duration);
  delay(500);

  if ((distance > 140) && (pushButtonState == HIGH)) {  // diffenet messages in different scenarios
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("nobody is ");
    lcd.setCursor(2, 1);
    lcd.print("approaching");
    delay(100);
  } else if ((pushButtonState == LOW) && (distance > 140)) {

    lcd.setCursor(1, 0);
    lcd.print("that was fast");
    lcd.setCursor(5, 1);
    lcd.print("kudos");
    delay(500);
    lcd.clear();
  }

  else if ((distance < 140) && (pushButtonState == HIGH)) {
    lcd.setCursor(1, 0);
    lcd.print("someone is ...");
    lcd.setCursor(2, 1);
    lcd.print("approaching!");
    delay(1000);
    lcd.clear();
  } else if ((distance < 140) && (pushButtonState == LOW)) {
    lcd.setCursor(2, 0);
    lcd.print("Welcome ....");
    lcd.setCursor(2, 1);
    lcd.print("Human");
    delay(1000);
    lcd.clear();
  } else {

    lcd.setCursor(3, 0);
    lcd.print("perimeter ");
    lcd.setCursor(4, 1);
    lcd.print("is clear");
    delay(1000);
    lcd.clear();
  }
}
