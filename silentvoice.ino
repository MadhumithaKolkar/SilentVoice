#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Flex Sensor Pins
const int thumbPin  = A0;
const int indexPin  = A1;
const int middlePin = A2;
const int ringPin   = A3;
const int littlePin = A6;

// Thresholds (adjust if required)
const int THUMB_THRESHOLD  = 985;
const int INDEX_THRESHOLD  = 900;
const int MIDDLE_THRESHOLD = 900;
const int RING_THRESHOLD   = 900;
const int LITTLE_THRESHOLD = 900;

String lastWord = "";

void displayWord(String word)
{
  if(word != lastWord)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(word);
    lastWord = word;
  }
}

void setup()
{
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sign Glove");
  lcd.setCursor(0,1);
  lcd.print("Ready");
  delay(2000);

  lcd.clear();
}

void loop()
{
  int thumb  = analogRead(thumbPin);
  int index  = analogRead(indexPin);
  int middle = analogRead(middlePin);
  int ring   = analogRead(ringPin);
  int little = analogRead(littlePin);

  Serial.print("T:");
  Serial.print(thumb);
  Serial.print(" I:");
  Serial.print(index);
  Serial.print(" M:");
  Serial.print(middle);
  Serial.print(" R:");
  Serial.print(ring);
  Serial.print(" L:");
  Serial.println(little);

  bool T = thumb  > THUMB_THRESHOLD;
  bool I = index  > INDEX_THRESHOLD;
  bool M = middle > MIDDLE_THRESHOLD;
  bool R = ring   > RING_THRESHOLD;
  bool L = little > LITTLE_THRESHOLD;

  // All fingers
  if(T && I && M && R && L)
  {
    displayWord("EMERGENCY");
  }

  // Thumb + Index
  else if(T && I && !M && !R && !L)
  {
    displayWord("YES");
  }

  // Thumb + Middle
  else if(T && !I && M && !R && !L)
  {
    displayWord("NO");
  }

  // Thumb + Ring
  else if(T && !I && !M && R && !L)
  {
    displayWord("PLEASE");
  }

  // Thumb + Little
  else if(T && !I && !M && !R && L)
  {
    displayWord("FOOD");
  }

  // Single Fingers
  else if(T && !I && !M && !R && !L)
  {
    displayWord("HELLO");
  }

  else if(!T && I && !M && !R && !L)
  {
    displayWord("FOOD");
  }

  else if(!T && !I && M && !R && !L)
  {
    displayWord("WATER");
  }

  else if(!T && !I && !M && R && !L)
  {
    displayWord("HELP");
  }

  else if(!T && !I && !M && !R && L)
  {
    displayWord("THANK YOU");
  }

  else
  {
    displayWord("READY");
  }

  delay(200);
}