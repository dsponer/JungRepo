#include <Arduino.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WheelData.h>
#include <ESPAsyncWebServer.h>


volatile long temp_1, temp_2, counter_1, counter_2 = 0;

#define ENC_PIN_11 34
#define ENC_PIN_12 35
#define ENC_PIN_21 32
#define ENC_PIN_22 33

#define ENDER_PIN_1 12
#define ENDER_PIN_2 13
#define ENDER_PIN_3 23
#define ENDER_PIN_4 22

#define POT_PIN_1 25
#define POT_PIN_2 26
#define POT_PIN_3 27
#define POT_PIN_4 14

void ai1();
void ai2();
void ai3();
void ai4();

String write_control();

String data_send;

void InitServer(const char *ssid, const char *password);

unsigned int port = 1024;

const char * host_unity = "192.168.4.4";
const char * host_motor = "192.168.4.2";

AsyncWebServer  server(port);

WiFiClient client_unity;
WiFiClient client_motor;

WheelData recv_data;

const char *ssid = "JungAP";
const char *password = "12345678";

void setup()
{
  Serial.begin(9600);

  InitServer(ssid, password);

  pinMode(ENC_PIN_11, INPUT_PULLUP);
  pinMode(ENC_PIN_12, INPUT_PULLUP);
  pinMode(ENC_PIN_21, INPUT_PULLUP);
  pinMode(ENC_PIN_22, INPUT_PULLUP);
  pinMode(ENDER_PIN_1, INPUT_PULLUP);
  pinMode(ENDER_PIN_2, INPUT_PULLUP);
  pinMode(ENDER_PIN_3, INPUT_PULLUP);
  pinMode(ENDER_PIN_4, INPUT_PULLUP);
  pinMode(POT_PIN_1, INPUT);
  pinMode(POT_PIN_2, INPUT);
  pinMode(POT_PIN_3, INPUT);
  pinMode(POT_PIN_4, INPUT);

  attachInterrupt(digitalPinToInterrupt(ENC_PIN_11), ai1, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_PIN_21), ai3, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_PIN_12), ai2, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_PIN_22), ai4, RISING);
}

void loop()
{
  // WiFiClient client = server.available();

  // if (!client_unity.connect(host_unity, port))
  // {
  //   Serial.println("Jung's wheel connected");
  //   String incoming_data = "";
  //   // while (client.connected())
  //   // {
  //     if (client_unity.available())
  //     {
  //       incoming_data = client_unity.readStringUntil('}');
  //       incoming_data += '}';
  //       recv_data.get_data_from_string(incoming_data);
  //       incoming_data = "";
  //     }
    // }
    // client.stop();
    // Serial.println("Jung's wheel disconnected.");
  // }

  // if(!client_motor.connect(host_motor, port)){
  //   Serial.println("ESP Motor connected");
  //   if(client_motor.available()){
  //     client_motor.print("Hello esp");
  //     Serial.println("Connected to server successful!");


  //     Serial.println("Disconnecting...");
  //     client_motor.stop();
  //   }
  //   // client_motor.stop();
  // }



  
  /*
  Serial.println(" ");
  Serial.println(digitalRead(ENDER_PIN_1));
  Serial.println(digitalRead(ENDER_PIN_2));
  Serial.println(digitalRead(ENDER_PIN_3));
  Serial.println(digitalRead(ENDER_PIN_4));
  Serial.println(analogRead(POT_PIN_1));
  Serial.println(analogRead(POT_PIN_2));
  Serial.println(analogRead(POT_PIN_3));
  Serial.println(analogRead(POT_PIN_4));
  Serial.println(" ");
  delay(500);
  */

  if (counter_1 != temp_1)
  {
    Serial.println("Encoder 1");
    Serial.println(counter_1);
    temp_1 = counter_1;
  }

  if (counter_2 != temp_2)
  {
    Serial.println("Encoder 2");
    Serial.println(counter_2);
    temp_2 = counter_2;
  }
}

void ai1()
{
  if (digitalRead(ENC_PIN_12) == LOW)
  {
    counter_1++;
  }
  else
  {
    counter_1--;
  }
}

void ai2()
{
  if (digitalRead(ENC_PIN_11) == LOW)
  {
    counter_1--;
  }
  else
  {
    counter_1++;
  }
}

void ai3()
{
  if (digitalRead(ENC_PIN_22) == LOW)
  {
    counter_2++;
  }
  else
  {
    counter_2--;
  }
}

void ai4()
{
  if (digitalRead(ENC_PIN_21) == LOW)
  {
    counter_2--;
  }
  else
  {
    counter_2++;
  }
}

String write_control() {
  
  data_send = "hello test";
  
  return data_send;
  //return String(1.8 * bme.readTemperature() + 32);
}


void InitServer(const char *ssid, const char *password)
{
  Serial.println();
  Serial.println("Configuring access point...");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.print("Server port: ");
  Serial.println(port);
  server.on("/send_data", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", write_control().c_str());
  });

  server.begin();
  Serial.println("Server started");
}
