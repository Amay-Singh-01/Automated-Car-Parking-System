#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo1;

int IR1 = 4; // IR Sensor 1 (signal connected at pin no 4)
int IR2 = 7; // IR Sensor 2 (signal connected at pin no 7)
int Slot = 4; //Stores total number of parking Slots available
int flag1 = 0;
int flag2 = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  myservo1.attach(9); // Servo signal connected at pin 9
  myservo1.write(100); // Defaut position of Servo arm is at 10 degrees (passage blocked)
  lcd.setCursor(0, 0);
  lcd.print("      CAR      ");
  lcd.setCursor(0, 1);
  lcd.print(" PARKING SYSTEM ");
  delay(2000);
  lcd.clear();
}

void loop() {
  if (digitalRead(IR1) == LOW && flag1 == 0) {
    if (Slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo1.write(0);
        Slot = Slot - 1;
      }
    } else {
      lcd.setCursor(0, 0);
      lcd.print(" No Slots Left! ");
      lcd.setCursor(0, 1);
      lcd.print(" Parking Full ");
      delay(3000);
      lcd.clear();
    }
  }

  if (digitalRead(IR2) == LOW && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo1.write(0);
      Slot = Slot + 1;
    }
  }

  if (flag1 == 1 && flag2 == 1) {
    delay(1000);
    myservo1.write(100);
    flag1 = 0;
    flag2 = 0;
  }

  lcd.setCursor(0, 0);
  lcd.print("    WELCOME!    ");
  lcd.setCursor(0, 1);
  lcd.print("Slots Left: ");
  lcd.print(Slot);
}