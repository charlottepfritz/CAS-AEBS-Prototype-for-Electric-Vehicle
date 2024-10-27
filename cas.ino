// Date: 10/27
// This code performs the following functions:
// 1. Prints distance (in cm) to LCD screen from Arduino UNO
// 2. Displays on LCD screen the current 'zone'
// zone 1 -- no warning (object detected > 50 cm from vehicle)
// zone 2 -- visual warning (object detected < 50 cm from the vehicle, requires driver attention)
// zone 3 -- visual and audio warning (object detected VERY close to the vehicle, requires driver intervention)

//Adapted from: https://www.youtube.com/watch?v=ontlwqrzfxo

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // Format -> (Address,Width,Height )

const int trigPin = 7;
const int echoPin = 4;

int buzz = 10;
int distance;

long duration;

void setup() {

	lcd.init();
	lcd.backlight();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(13, OUTPUT);
  pinMode(2, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  // clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance= duration*0.034/2;

  // Prints the distance on the Serial Monitor after each reading
    Serial.println(distance);
    lcd.setCursor(0, 0); // Sets the location at which subsequent text written to the LCD will be displayed
    lcd.print("Distance: "); // Prints string "Distance" on the LCD
    lcd.print(distance); // Prints the distance value from the sensor
    lcd.print(" cm");
    delay(10);

  // ZONE 3 -- VISUAL AND AUDIO WARNING
  if(distance < 20)
  {
      lcd.setCursor(0, 1);
      lcd.print("3 - CAUTION!!");
      delay(10);

      // VISUAL
      digitalWrite(13, HIGH);
      digitalWrite(2, HIGH);

      // AUDIO
      tone(buzz, 2000);
      delay(100);
      noTone(buzz);
      delay(100);
      tone(buzz, 2000);
      delay(100);
      noTone(buzz);
      delay(100);
      tone(buzz, 2000);
      delay(100);
      noTone(buzz);
      tone(buzz, 2000);
      delay(100);
      noTone(buzz);
      delay(100);
  }

  // ZONE 2 -- VISUAL WARNING
  else if(distance <= 50 && distance >= 20)
  {
      lcd.setCursor(0, 1);
      lcd.print("2 - ALERT     ");
      delay(10);
      digitalWrite(2, HIGH);
      digitalWrite(13, LOW);
  }

  // ZONE 1 -- NO WARNING
  else
  {
      lcd.setCursor(0, 1);
      lcd.print("1 - SAFE     ");
      delay(10);

      digitalWrite(2, LOW); // turn the LED off by making the voltage LOW
      digitalWrite(13, LOW); // turn the LED off by making the voltage LOW
  }
}