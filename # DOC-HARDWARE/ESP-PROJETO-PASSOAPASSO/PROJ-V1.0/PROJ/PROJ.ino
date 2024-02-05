// C++ code
//
//SERVO - 13 D7
//ECHO - 14 D5
//TRIG - 12 D6
//LED VERDE - 4 D2
//LED VERMELHO - 5 D1
//LED SINAL - 0 D3
//SWITCH - 2 D4

//90 GRAUS É ABERTO
//0 GRAUS É FECHADO

#include <Servo.h>

int i = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

Servo servo_13;

void setup()
{
  pinMode(2, INPUT); //SWITCH
  pinMode(0, OUTPUT); //LED SINAL
  pinMode(5, OUTPUT); //LED VERMELHO
  pinMode(4, OUTPUT); //LED VERDE
  servo_13.attach(13, 500, 2500);

}

void loop()
{
  if (digitalRead(2) == HIGH) {
    digitalWrite(0, HIGH);
    if (0.01723 * readUltrasonicDistance(12, 14) <= 10) {
      delay(200);
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
      servo_13.write(50);
      delay(200);
    } else {
      delay(700);
      digitalWrite(5, HIGH);
      digitalWrite(4, LOW);
      servo_13.write(5);
    }
  } else {
    digitalWrite(5, HIGH);
    digitalWrite(0, LOW);
    digitalWrite(4, LOW);
    servo_13.write(5);
  }
  delay(10); // Delay a little bit to improve simulation performance
}
