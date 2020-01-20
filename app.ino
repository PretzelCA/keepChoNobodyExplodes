#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 6, A5, A4, A3, A2);

void setup() {
  pinMode(A5, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);

  lcd.begin(16, 2);

  lcd.print("Keep Cho");
  lcd.setCursor(0, 1);
  lcd.print("Nobody Explodes");
  
  delay(10000);
}

void loop()
{
    clearScreen();
    lcd.setCursor(0, 0);
    lcd.print("Starting Game   ");
    lcd.setCursor(0, 1);
    lcd.print("Timer: 5:00     ");

    int time = 300;
    int strikes = 0;

    for (int i = time; i >= 0; --i) {
        for (int t = 0; t < 100; t++) {
            clearScreen();
            lcd.print("Time:" + String(((i - (i%60))/60)%60) + ":" + String(i % 60) + "  " + "Xs:" + String(strikes));
            lcd.setCursor(0 ,1);
            lcd.print("Tick: " + String(t));
            delay(10);
        }
    }

}

void clearScreen() {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");  
    lcd.setCursor(0, 0);
}