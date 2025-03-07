#define BUZZER_PIN 5
#define RED_LED 4
#define YELLOW_LED 3
#define GREEN_LED 2
#define SERVO_PIN 6

//ultra sonic sensor
#define TRIGGERPIN 3 // this pin is the pin that sends out pulse 
#define ECHOPIN 2 //this pin reads the distance. 





void setup() {
   Serial.begin(9600); //so we can print if we want. 
 pinMode(TRIGGERPIN, OUTPUT); //send pulse 
 pinMode(ECHOPIN, INPUT); //reads pulse
 pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT); 
  pinMode(BUZZER_PIN, OUTPUT);
   Servo.attach(SERVO_PIN); //connecting servo object to pin  
  Servo.write(90); //set start of propeller to 90 degrees 

}

void loop() {
  // put your main code here, to run repeatedly:

delay(300);
 Servo.write (360);
delay(300); 
 Servo.write (390);
 delay(300); 
 Servo.write (450);
 delay(300); 
 Servo.write (480);
 delay(300); 
 Servo.write (520);
 delay(300); 

 digital.write(GREEN_LED, HIGH);
 digital.write(YELLOW_LED, HIGH);

   for (int i = 0; i < 7; i++) {
      digitalWrite(RED_LED, HIGH);
      delay(250);  // On for 0.25 seconds
      digitalWrite(GREEN_LED, LOW);
      delay(100);  // Off for 0.25 seconds
      digitalWrite(RED_LED, LOW);





}
