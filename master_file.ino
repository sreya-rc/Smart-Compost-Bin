#include <LiquidCrystal.h>
#include <DHT.h>
#include <Servo.h>

Servo servo;     
int trigPin = 6;    
int echoPin = 7;   
int servoPin = 9;
int led= 10;
long duration, dist, average;   
long aver[3];   //array for average

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
DHT dht(8, DHT22);
int temp;
int humidity;
int dt = 2000;

byte art[8] = {
  0b01110,
  0b00000,
  0b11111,
  0b01110,
  0b01110,
  0b01110,
  0b11011,
  0b00000
};


void setup() {

  //for servo     
    Serial.begin(9600);
    servo.attach(servoPin);  
    pinMode(trigPin, OUTPUT);  
    pinMode(echoPin, INPUT);  
    servo.write(0);         //close cap on power on
    delay(100);
    servo.detach();

  //for display
    lcd.begin(16, 2);
    dht.begin();
    lcd.createChar(0, art);
} 

void measure() {  
digitalWrite(10,HIGH);
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(15);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
dist = (duration/2) / 29.1;    //obtain distance
}
void loop() { 
Serial.print(dist);

//for servo
  for (int i=0;i<=2;i++) {   //average distance
    measure();               
   aver[i]=dist;            
    delay(10);              //delay between measurements
  }
 dist=(aver[0]+aver[1]+aver[2])/3;    
Serial.print(dist);

if ( dist<40 ) {
//Change distance as per your need
 servo.attach(servoPin);
  delay(1);
 servo.write(0);  
 delay(3000);       
 servo.write(170);    
 delay(1000);
 servo.detach();

}
Serial.print(dist);

//for disp
// set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  temp = dht.readTemperature();
  humidity = dht.readHumidity();
  lcd.setCursor(0, 0);
  lcd.print("Temp:     ");
  lcd.print(temp);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");
  lcd.setCursor(15, 1);
  lcd.write(byte(0));
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
}