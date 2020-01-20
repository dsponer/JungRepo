/*
 Name:		JungWiFi.ino
 Author:	FrankEinstein
 Version:   0.1A
*/

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

// Stepper motor_1(200, 21, 19);
// Stepper motor_2(200, 18, 5);
// Stepper motor_3(200, 4, 2);
// Stepper motor_4(200, 23, 22);

const char *ssid = "JungAP";
const char *password = "12345678";

void test(int dir_pin, int step_pin, int direction, int steps)
{

  if (direction == 1)
  {
    digitalWrite(dir_pin, HIGH);
  }
  else
  {
    digitalWrite(dir_pin, LOW);
  }

  for (int i = 0; i < steps; i++)
  {
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(1000);
  }
}

void setup()
{
  Serial.begin(9600);

  //setting up pins
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connect Done");

  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  // test(21, 19, 1, 100);
  // delay(1000);

  // // test(18, 5, 1, 100);
  // // delay(1000);

  // // test(4, 2, 1, 100);
  // // delay(1000);

  // // test(13, 12, 1, 100);
  // // delay(1000);

  // // test(13, 12, 0, 100);
  // // delay(1000);

  // // test(4, 2, 0, 100);
  // // delay(1000);

  // // test(18, 5, 0, 100);
  // // delay(1000);

  // test(21, 19, 0, 100);
  // delay(1000);

  // if (top_sensor == true && trig_statement != top_sensor) {
  // 	while (top_sensor != 0) {
  // 		motor_1.step(-1);
  //     Serial.println(top_sensor);
  // 		top_sensor = digitalRead(SENSOR_TOP);
  // 	}
  // }
  // trig_statement = top_sensor;
}
