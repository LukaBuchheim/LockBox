#define BUZZER_PIN 5
#define RED_LED 4
#define YELLOW_LED 3
#define GREEN_LED 2
#define SERVO_PIN 6

 #include <Servo.h>
Servo TheServo; 



void setup() {
   Serial.begin(9600); //so we can print if we want. 
 pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT); 
  pinMode(BUZZER_PIN, OUTPUT);
   TheServo.attach(SERVO_PIN); //connecting servo object to pin  
  TheServo.write(90); //set start of propeller to 90 degrees 

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

   
  


}







