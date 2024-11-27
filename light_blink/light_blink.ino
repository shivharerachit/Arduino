#include "NewPing.h"
#define TRIGGER_PIN 33
#define ECHO_PIN 25
#define MAX_DISTANCE 400
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
#define in1 12
#define in2 14
#define in3 27
#define in4 26
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
char ch;
void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("ABCD"); //Bluetooth device name - You can give any name
  Serial.println("The device started, now you can pair it with bluetooth!");
}
void loop() {
  if (SerialBT.available()) {
    ch =(char)SerialBT.read();
    if(ch == 'f'){
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      if(sonar.ping_cm()!=0 && sonar.ping_cm()<=30){
        digitalWrite(in1,LOW);
        digitalWrite(in2,LOW);
        digitalWrite(in3,LOW);
        digitalWrite(in4,LOW);
        delay(500);
      }  
    } else if(ch == 'b'){
      digitalWrite(in2,HIGH);
      digitalWrite(in1,LOW);
      digitalWrite(in4,HIGH);
      digitalWrite(in3,LOW);
    } else if(ch == 's'){
      digitalWrite(in2,LOW);
      digitalWrite(in1,LOW);
      digitalWrite(in4,LOW);
      digitalWrite(in3,LOW);
    } else if(ch == 'l'){
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
    }else if(ch == 'r'){
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
    }
  }
  delay(20);
  
}