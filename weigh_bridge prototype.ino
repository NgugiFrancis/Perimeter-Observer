// tlanslating the weight measured in a weight bridge into an easily legible analogue meter
#include <Servo.h>

#include <NewPing.h>

int btnPin = 7;  // defination of variables
int ServoPin = 8;
int TriggerPin = 22;
int EchoPin = 23;
bool btn_prev;
int k = 250;
int force;
// 200 = maxDistance
NewPing sonar(TriggerPin, EchoPin, 100);
Servo servo;

void setup() {
  btn_prev = digitalRead(btnPin);  // variable initialization
  pinMode(btnPin, INPUT_PULLUP);
  delay(50);

  servo.attach(ServoPin);
  Serial.begin(9600);
}

void loop() {

  int btn = digitalRead(btnPin);  //button state detection

  if ((btn == LOW) && (btn_prev == HIGH)) {
    btn_prev = digitalRead(btnPin);
    int cm = sonar.ping_cm();
    int angle = map(cm, 2, 15, 15, 100);  // mapping the the distance to the analogous angle
    servo.write(angle);

    delay(50);                         // distance acquisation
    Serial.print("The distance is ");  // parameter display
    Serial.print(cm);
    Serial.print(" , the button is ");
    Serial.print(btn);

    Serial.print(" and the force is ");
    Serial.println(cm * k);  // Force calculation and display
    delay(500);
  }
  btn_prev = digitalRead(btnPin);  // updating the previous button state
}