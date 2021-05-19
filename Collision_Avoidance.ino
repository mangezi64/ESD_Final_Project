/* Arduino example sketch to control a JSN-SR04T ultrasonic distance sensor with Arduino. No library needed. More info: https://www.makerguides.com */
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Define Trig and Echo pin:
#define trigPin 2
#define echoPin 3
#define redLED 4
#define buzzer 5
#define buzz_freq 1000
int set = 0;

// Define variables:
long duration;
int distance;

void setup() {
  // Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(redLED, OUTPUT);

  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("System Starting");
  lcd.setCursor(0,1);
  lcd.print("System Active");
  

}

void loop() {

  
  collision_system();
  delay(100);
}

void collision_system()
{
  
   float distance = get_distance();
   while (distance < 100){
      //digitalWrite(buzzer, 1);
      tone(buzzer, buzz_freq);
      digitalWrite(redLED, 1);
      if (distance < 30){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Collision ");
        lcd.setCursor(0,1);
        lcd.print("Emrgncy Alerted");
        if (set == 0){
          //send emergerncy
          
          delay(5000);
        }
        distance = get_distance(); 
        break;
      }
        else{
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Collision Alert");
          lcd.setCursor(0,1);
          lcd.print("Evade Danger");
        }
        distance = get_distance();  
   
   }
    //digitalWrite(buzzer, 0);
    noTone(buzzer);
    digitalWrite(redLED, 0); 
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Drive ");
    lcd.setCursor(4,1);
    lcd.print("Safely");
  
  
}

float get_distance()
{
  // Clear the trigPin by setting it LOW:
  digitalWrite(trigPin, LOW);
  
  delayMicroseconds(5);

 // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance:
  distance = duration*0.034/2;
  if (distance>160 ){
    distance = 160;
  }
  
  return distance;
}
/*// Include the library:
#include <NewPing.h>

// Define Trig and Echo pin:
#define trigPin 2
#define echoPin 3
#define redLED 4
#define buzzer 5

// Define maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500 cm:
#define MAX_DISTANCE 400

// NewPing setup of pins and maximum distance.
NewPing sonar = NewPing(trigPin, echoPin, MAX_DISTANCE);

void setup() {
  // Open the Serial Monitor at 9600 baudrate to see ping results:
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(redLED, OUTPUT);
  
}

void loop() {
  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings:
  delay(500);
  getDist();
  
  
}


void getDist(){
   Serial.print(sonar.ping_cm());
   Serial.println(" cm");/*
  while (sonar.ping_cm() < 150){
    
    
      digitalWrite(buzzer, 1);
      digitalWrite(redLED, 1);
      Serial.println("Collision Alert");
      if (sonar.ping_cm() < 4){
      Serial.println("Collision \n Emergency Alerted");
      break;
    }
    
  }
    digitalWrite(buzzer, 0);
    digitalWrite(redLED, 0);  
  
  }*/
