#include <Servo.h>.

const int trigPin = 22;  // Ultrasonic Sensor pin definations
const int echoPin = 23;
long duration;  // duration and distance Variables
int distance;

Servo myServo;  // servo object for controlling the servo motor

void setup() {
  pinMode(trigPin, OUTPUT);  // Distance sensor pinmode definations
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myServo.attach(9);  // Servo pin defination
}
void loop() {                        // rotatethe servo motor from 15 to 165 degrees
  for (int i = 15; i <= 165; i++) {  // runs the instructions in an increasing motor angle
    myServo.write(i);
    delay(30);
    distance = calculateDistance();  //gets the distance for each degree

    Serial.print(i);         // prints the current degree
    Serial.print(".");       // Separates the outputs for the Processing IDE indexing
    Serial.print(distance);  // Prints the distance
    Serial.print(".");
  }    

    for (int i = 165; i > 15; i--) {  // Run the instructions in a the opposite motor direction
      myServo.write(i);
      delay(30);
      distance = calculateDistance();
      Serial.print(i);
      Serial.print(",");
      Serial.print(distance);
      Serial.print(".");
    }
  }

  int calculateDistance() {
/* Function for getting the distance measured by the Ultrasonic sensor 
 * Alternate;y ypu can use the new ping lib**/
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);  // Set the trigPin to HIGH state for 10 microSeconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);  // Reads the echoPin, returns the sound wave travel time in microseconds
    distance = duration * 0.034 / 2;    //compute the distance using the ship equation
    return distance;
  }