#include <Servo.h>
#include <SPI.h>
#include <RFID.h>
#define SS_PIN 10
#define RST_PIN 9
RFID rfid(SS_PIN, RST_PIN);

Servo myservo;  

String rfidCard;
int pos = 0;    

void setup() {
  Serial.begin(9600);
  Serial.println("Starting the RFID Reader...");
  SPI.begin();
  rfid.init();
  myservo.attach(6); 
  myservo.write(180);
}

void loop() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
      Serial.println(rfidCard);
      if (rfidCard == "33 14 67 35" || rfidCard == "49 206 227 38") {
        for (pos = 180; pos >= 135; pos -= 1) { 
          myservo.write(pos);             
          delay(5);                      
        }
        myservo.write(180);
      }
      rfid.halt();
    }
  }
}
