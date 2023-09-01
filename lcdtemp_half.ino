
#include <LiquidCrystal.h>
#include <DHT.h>


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
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
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  dht.begin();
  lcd.createChar(0, art);

}

void loop() {
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