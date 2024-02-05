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
Servo servo_13;

#include <Gwiot7941e.h>
#define GWIOT_7941E_RX_PIN 3
#define READ_LED_PIN 13
Gwiot7941e gwiot7941e;

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


void setup()
{
  pinMode(2, INPUT); //SWITCH
  pinMode(0, OUTPUT); //LED SINAL
  pinMode(5, OUTPUT); //LED VERMELHO
  pinMode(4, OUTPUT); //LED VERDE
  servo_13.attach(13, 500, 2500);
  servo_13.write(5);

    Serial.begin(115200);
    pinMode(READ_LED_PIN, OUTPUT);
    digitalWrite(READ_LED_PIN, LOW);
    gwiot7941e.begin(GWIOT_7941E_RX_PIN);
    Serial.println("\nPlace RFID tag near the 7941E...");
}

void loop()
{
    // if non-zero tag_id, update() returns true - a tag was read!
    if (gwiot7941e.update()) {
        Serial.println(gwiot7941e.getLastTagId(), HEX);
    }
  
  if (digitalRead(2) == HIGH) {
    digitalWrite(0, HIGH);
    if (0.01723 * readUltrasonicDistance(12, 14) <= 07) {
      delay(800);
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
      servo_13.write(50);
      //Serial.println("Cancela aberta.");
    } else {
      delay(270);
      digitalWrite(5, HIGH);
      digitalWrite(4, LOW);
      servo_13.write(5);
      //Serial.println("Cancela fechada.");
    }
  } else {
    digitalWrite(5, HIGH);
    digitalWrite(0, LOW);
    digitalWrite(4, LOW);
    servo_13.write(5);
    //Serial.println("Cancela travada.");
  }
  delay(10); // Delay a little bit to improve simulation performance
}
