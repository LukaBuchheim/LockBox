#define BUZZER_PIN 5
#define RED_LED 4
#define YELLOW_LED 3
#define GREEN_LED 2
#define SERVO_PIN 6

#define TRIGGERPIN 7 // this pin is the pin that sends out pulse 
#define ECHOPIN 8 //this pin reads the distance. 

int const RX_PIN = A2; //not using define because bluetooth doesn't like it. This is RX Pin  //receiving signal
int const TX_PIN = A4; //sends signal 
#include <SoftwareSerial.h> 
// My bluetooth ends in AB24C5

#include <Servo.h>
#define MICHAEL_PIN 9

#include <SPI.h>

#include <MFRC522.h>

Servo TheServo; 

#define RST_PIN 9 // Configurable, see typical pin layout above

#define SS_PIN 10 // Configurable, see typical pin layout above



MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

SoftwareSerial tooth(TX_PIN, RX_PIN); //make a bluetooth object 
//set tx and rx pins 
//tx goes first, then rx 
char davis; 


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

pinMode(TRIGGERPIN, OUTPUT); //send pulse 
 pinMode(ECHOPIN, INPUT); //reads pulse

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

Serial.print("Distance: "); 
Serial.println(distance);
delay(100); 

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
tone(BUZZER_PIN, 1000); 
delay(1000); 
noTone(BUZZER_PIN);
delay(500);   

  } 

   if ((0 < distance < 6) {
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

      if (davis == "Platypus") {
        Serial.println("Access Granted!"); 
        delay(300);
        TheServo.write(360);
        delay(300); 
        TheServo.write(390);
        delay(300); 
        TheServo.write(450);
        delay(300); 
        TheServo.write(480);
        delay(300); 
        TheServo.write(520);
        delay(1000); 
        TheServo.write(450);
        delay(300);
        TheServo.write(420);
        delay(300); 
        TheServo.write(390);
        delay(300); 
      } 
    } 
  }





















