#include <LiquidCrystal.h>
// Connections:
// rs (LCD pin 4) to Arduino pin 12
// rw (LCD pin 5) to Arduino pin 11
// enable (LCD pin 6) to Arduino pin 10
// LCD pin 15 to Arduino pin 13
// LCD pins d4, d5, d6, d7 to Arduino pins 7, 6, 5, 4
LiquidCrystal lcd(12, 11, 10, 7, 6, 5, 4);
// Pin used by the Relay
// pin 13 will control the backlight
int relayPin = 2, backLight = 13;  

// This array holds the inputs that will be used by the moisture senor(s)
int inputs[] = {A12};

void setup(){
  Serial.begin(9600);
  // Set the pin for outputing.
  pinMode(relayPin, OUTPUT);
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
  lcd.begin(16,4);              // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd.clear();                  // start with a blank screen
}

void loop(){
  int ct = (sizeof(inputs)/sizeof(*inputs));
  double value = 0.0, avg = 0.0;
  // Air = sensorValue of 674
  // Straight, filtered water = sensorValue of 324
  for(int i = 0; i < ct; i++){
    value += analogRead(inputs[i]);
  }
  avg = value / ct;
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(value);
  lcd.setCursor(10,1);
  lcd.print(avg);
  delay(2000);
  if(avg < 500.0 && avg >= 400.0){
    lcd.clear();
    lcd.setCursor(0,2);         // set cursor to column 0, row 2
    lcd.print("All is fine");
    delay(2000);
  }
  else{
    lcd.clear();
    lcd.setCursor(0,2);         // set cursor to column 0, row 2
    lcd.print("Still waiting");
    delay(1000); // Wait 100 micro seconds before continuing
  }
}
