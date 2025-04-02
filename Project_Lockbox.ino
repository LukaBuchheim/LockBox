#define BUZZER_PIN 5
#define RED_LED 4
#define YELLOW_LED 3
#define GREEN_LED 2
#define SERVO_PIN 6

 #include <Servo.h>
Servo TheServo; 

#include <MFRC522.h>

#include <MFRC522Extended.h>

#include <deprecated.h>

#include <require_cpp11.h>


#include <SPI.h>

#include <MFRC522.h>



#define RST_PIN 9 // Configurable, see typical pin layout above

#define SS_PIN 10 // Configurable, see typical pin layout above



MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance


void setup() {
   Serial.begin(9600); //so we can print if we want. 
 pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT); 
  pinMode(BUZZER_PIN, OUTPUT);
   TheServo.attach(SERVO_PIN); //connecting servo object to pin  
  TheServo.write(90); //set start of propeller to 90 degrees 

  while (!Serial); // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

SPI.begin(); // Init SPI bus

mfrc522.PCD_Init(); // Init MFRC522

delay(4); // Optional delay. Some board do need more time after init to be ready, see Readme

mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details

Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:

delay(300);
  TheServo.write (360);
delay(300); 
 TheServo.write (390);
 delay(300); 
 TheServo.write (450);
 delay(300); 
 TheServo.write (480);
 delay(300); 
 TheServo.write (520);
 delay(300); 

//LED FLASHING 

for (int i = 0; i < 10; i++) {
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(YELLOW_LED, HIGH);
        delay(250);
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(YELLOW_LED, LOW);
        delay(250);
        digitalWrite(GREEN_LED, LOW);  
    delay(250);                   
    }

    //LED FLASHING
    for (int i = 0; i < 7; i++) {
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(YELLOW_LED, HIGH);
        delay(250);
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(YELLOW_LED, LOW);
        delay(250);
    }

  //LED FLASHING
    for (int i = 0; i < 7; i++) {
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(YELLOW_LED, HIGH);
        delay(100);
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(YELLOW_LED, LOW);
        delay(100);
    }

  for (int i = 0; i < 10; i++) {
        digitalWrite(RED_LED, HIGH);
        delay(100);
        digitalWrite(RED_LED, LOW); // Turn RED LED OFF
        delay(100);
    }

   
  
if ( ! mfrc522.PICC_IsNewCardPresent()) {

return;

}



 // Select one of the cards

if ( ! mfrc522.PICC_ReadCardSerial()) {

return;

}




MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);



Serial.print(F("RFID Tag UID:"));

printHex(mfrc522.uid.uidByte, mfrc522.uid.size);

Serial.println("");



mfrc522.PICC_HaltA(); // Halt PICC

}

void printHex(byte *buffer, byte bufferSize) {



 //Serial.begin("reading?");

for (byte i = 0; i < bufferSize; i++) {

Serial.print(buffer[i] < 0x10 ? " 0" : " ");

Serial.print(buffer[i], HEX);

}


if()


}







