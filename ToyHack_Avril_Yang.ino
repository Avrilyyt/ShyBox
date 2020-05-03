#include <Servo.h>

Servo coverServo;
Servo eyeServo;

const int ledPin = 13;
const int trigPin = 11;      //Trig pin (OUTPUT) of the Ultrasonic Sensor HC-SR04
const int echoPin = 12;      //Echo pin (INPUT) of the Ultrasonic Sensor HC-SR04

int action;                  //

long duration;
float distance;

void setup() {
  Serial.begin(9600);        //start serial communication
  
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  coverServo.attach(4);      //set pin for servo
  eyeServo.attach(2);       
  coverServo.write(0);        //reset servo position
  eyeServo.write(0);           
}

void loop() {
  distance = getDistance();

  if (distance < 5){
    coverServo.write(80);
    eyeServo.write(60);
    delay(500);
    coverServo.write(10);
    eyeServo.write(0);
  }
  else if (distance < 40){
    coverServo.write(90-distance*2);
    eyeServo.write(60-distance);
  }
  else{
    coverServo.write(10);
    eyeServo.write(0);
  }

  if (distance < 15){
    digitalWrite(ledPin, HIGH);
  }
  else{
    digitalWrite(ledPin,LOW);
  }
}

float getDistance(){
  digitalWrite(trigPin, LOW);          //provide LOW pulse beforehand to ensure a clean HIGH pulse:
  delay(2);
  digitalWrite(trigPin, HIGH);         //Sensor is triggered by a HIGH pulse of 10 or more microseconds.
  delay(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  float dist = (duration/2)*0.034;       //Time convertion to cm
  //distance = (duration/2)*0.0135;    //Time convertion to inches

  Serial.print("distance:");
  Serial.println(distance);

  return dist;

}
