#define BUZZER_PIN 5
#define RED_LED 4
#define YELLOW_LED 3
#define GREEN_LED 2
#define SERVO_PIN 6

#define TRIGGERPIN 7 // this pin is the pin that sends out pulse 
#define ECHOPIN 8 //this pin reads the distance. 

int const RX_PIN = A2; //not using define because bluetooth doesn't like it. This is RX Pin  //receiving signal
int const TX_PIN = A1; //sends signal 
#include <SoftwareSerial.h> 
// My bluetooth ends in AB24C5

//Servo 
#include <Servo.h>
Servo TheServo; 

//RFID set up/libary set up 
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN 9 // Configurable, see typical pin layout above
#define SS_PIN 10 // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
byte SpecialCard[4] = {0xB5, 0x30, 0x24, 0x03}; // This is so it knows which UID to look for, i set it to B5 30 24 03 which is my RFID card, this is also for later
// Compare's scanned card to the "Special card" (for later)
bool Luka_Card(byte scannedCard[], byte SpecialCard[]) { 
  for (int i = 0; i < 4; i++) {
    if (scannedCard[i] != SpecialCard[i]) {
      return false;
    }
  }
  return true;
}
//bluetooth set up 
SoftwareSerial tooth(TX_PIN, RX_PIN); //make a bluetooth object 

char davis; 


void setup() {
   
  Serial.begin(9600); //so we can print if we want. 
 
 //LED set up 
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT); 
  pinMode(BUZZER_PIN, OUTPUT);
   TheServo.attach(SERVO_PIN); //connecting servo object to pin  
  TheServo.write(200); //set start of propeller to 90 degrees 

while (!Serial); // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

//RFID set up 
SPI.begin(); // Init SPI 
mfrc522.PCD_Init(); // Init MFRC522

//ultra sonic sensor set up 
pinMode(TRIGGERPIN, OUTPUT); //send pulse 
 pinMode(ECHOPIN, INPUT); //reads pulse

//bluetooth set up 
 tooth.begin(9600); //starts my bluetooth

}

void loop() {
  // put your main code here, to run repeatedly:


for (int i = 0; i < 3; i++) {
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(YELLOW_LED, LOW);
        delay(250);
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(YELLOW_LED, LOW);
        delay(250);
        digitalWrite(GREEN_LED, LOW);  
    delay(250);                   
    }

digitalWrite(TRIGGERPIN, LOW); //turning off first because we want a fresh start
delayMicroseconds(2); //really fast turn it off then turn it on 
digitalWrite(TRIGGERPIN, HIGH);
delayMicroseconds(10); //needs to be 10 because of our sensor

float duration = pulseIn(ECHOPIN, HIGH); //tell us the time from pulse sent to pulse recived. 
Serial.println(duration); 

// distance = speed*durration 

float speed = 0.034;  //measured in cm/microseconds 
float distance = speed * duration/2; // distance meaured in cm 

Serial.println("Distance: "); 
Serial.print(distance);
delay(100); 

//LED sequence

  if (distance > 6) {
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
        delay(300); 



    }
tone(BUZZER_PIN, 10); 
delay(1000); 
noTone(BUZZER_PIN);
tone(BUZZER_PIN, 10); 
delay(1000); 
noTone(BUZZER_PIN);
tone(BUZZER_PIN, 10); 
delay(1000); 
noTone(BUZZER_PIN);
delay(500); 
Serial.println("BOOM");

  } 

   if (0 < distance < 6) {
     for (int i = 0; i < 8; i++) {
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(RED_LED, LOW); 
      delay(100);

  if (tooth.available() > 0) {
        davis = tooth.read();
        tooth.print("Input: ");
        tooth.println(davis);
      }

      if (davis == 'd') {
        Serial.println("Hmmmmm i guess thats correct...."); 
        while (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) { // the || acts as an "or" so it's gonna wait until it reads a card. 
        delay(100); // Slight delay, just give it some time 
       } 
       
        //if the card matches Luka's card it's the special card, Access granted
        if (Luka_Card(mfrc522.uid.uidByte, SpecialCard)) {
        Serial.println("Access Granted");
        TheServo.write(110);
        delay(100);
        TheServo.write(80);
        delay(10000);
         TheServo.write(360);
         }
         else {Serial.println("Access Denied!");
         TheServo.write(360);
  
         }
         
         mfrc522.PICC_HaltA();   // Halt PICC
         delay(1000); // Pause before scanning again
         davis = '/0'; // clears bluetooth stuff, so basically clears the char 
        return; //restarts loop 
        } 
      } 
    }
  }





















