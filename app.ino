#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 6, A5, A4, A3, A2);

void setup() {
  pinMode(A5, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);

  lcd.begin(16, 2);

  lcd.print("Keep Cho and");
  lcd.setCursor(0, 1);
  lcd.print("Nobody Explodes");
  
  Serial.begin(9600);

  //delay(5000);
}

void loop()
{
    clearScreen();
    lcd.setCursor(0, 0);
    lcd.print("Starting Game   ");
    lcd.setCursor(0, 1);
    lcd.print("Timer: 5:00     ");

    String avaliableModules[4] = {"3F", "5A", "1C", "6E"};

    int infrared = 7;
    int tiltLeft = 11;
    int tiltRight = 12;
    int water = 9;

    int time = 300;
    int lives = 3;

    int death = 0;
    int deathTime;

    int win = 0;
    int winTime;

    int amountOfPatterns = 10;
    int amountOfModulesInPatterns = 6;

    int currentPattern = 0;
    int currentModule = 0;

    int timeSinceDefuse = 0;

    String modulePatterns[amountOfPatterns][amountOfModulesInPatterns];

    Serial.println("Creating module matrix:");

    for (int i = 0; i < amountOfPatterns; i++) {
        for (int t = 0; t < amountOfModulesInPatterns; t++) {
            int randInt = (random(0, 4));
            modulePatterns[i][t] = avaliableModules[randInt];
            Serial.println(String(randInt));
            Serial.println(String(i) + ":" + String(t) + " " + modulePatterns[i][t]);
        }
    }

    Serial.println("Displaying module matrix");
    while (death != 1 || win != 1) {
        for (int i = time; i >= 0; --i) {
            tone(13, 1000);
            delay(50);
            noTone(13);
            for (int t = 0; t < 50; t++) {
                if (lives <= 0 || i == 0) {
                    if (death != 1) {
                        deathTime = i;
                    }
                    death = 1;
                    loseGame(deathTime);
                    break;
                    break;
                }
                clearScreen();
                lcd.print("Time:" + String(((i - (i%60))/60)%60) + ":" + String(i % 60));
                lcd.setCursor(0 ,1);
                for (int y = 0; y < amountOfModulesInPatterns; y++) {
                    lcd.print(modulePatterns[currentPattern][y]);
                }
                lcd.print(" " + String(currentPattern) + ":" + String(currentModule));
                delay(10);

                if (modulePatterns[currentPattern][currentModule] == "3F") {
                    Serial.println(digitalRead(infrared));
                    if (digitalRead(tiltLeft) == 0 || digitalRead(tiltRight) == 0 || digitalRead(water) == 0) {
                        if (timeSinceDefuse > 99999) {
                            lives--;
                        } else {
                            timeSinceDefuse++;
                        }
                    } else if (digitalRead(infrared) == 0) {
                        timeSinceDefuse = 0;
                        currentModule++;
                        tone(13, 1500);
                        delay(100);
                        noTone(13);
                    }
                }

                if (modulePatterns[currentPattern][currentModule] == "5A") {
                    if (digitalRead(infrared) == 0 || digitalRead(tiltRight) == 0 || digitalRead(water) == 0) {
                        if (timeSinceDefuse > 99999) {
                            lives--;
                        } else {
                            timeSinceDefuse++;
                        }
                    } else if (digitalRead(tiltLeft) == 0) {
                        timeSinceDefuse = 0;
                        currentModule++;
                        tone(13, 1500);
                        delay(100);
                        noTone(13);
                    }
                }

                if (modulePatterns[currentPattern][currentModule] == "1C") {
                    if (digitalRead(infrared) == 0 || digitalRead(tiltLeft) == 0 || digitalRead(water) == 0) {
                        if (timeSinceDefuse > 99999) {
                            lives--;
                        } else {
                            timeSinceDefuse++;
                        }
                    } else if (digitalRead(tiltRight) == 0) {
                        timeSinceDefuse = 0;
                        currentModule++;
                        tone(13, 1500);
                        delay(100);
                        noTone(13);
                    }
                }

                if (modulePatterns[currentPattern][currentModule] == "6E") {
                    if (digitalRead(infrared) == 0 || digitalRead(tiltLeft) == 0 || digitalRead(tiltRight) == 0) {
                        if (timeSinceDefuse > 99999) {
                            lives--;
                        } else {
                            timeSinceDefuse++;
                        }
                    } else if (digitalRead(water) == 0) {
                        timeSinceDefuse = 0;
                        currentModule++;
                        tone(13, 1500);
                        delay(100);
                        noTone(13);
                    }
                }

                if (currentModule >= (amountOfModulesInPatterns)) {
                    currentModule = 0;
                    currentPattern++;
                }

                if(currentPattern >= (amountOfPatterns)) {
                    if (win != 1) {
                        winTime = i;
                    }
                    win = 1;
                    winGame(winTime);
                    break;
                    break;
                }
            }
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

void loseGame(int time) {
    clearScreen();
    lcd.print("THE CHO BLEW UP!");
    lcd.setCursor(0, 1);
    if (time == 0) {
        lcd.print("You ran out!");
    } else {
        lcd.print(String(((time - (time%60))/60)%60) + ":" + String(time%60) + " left!");
    }
                            tone(13, 500);
                        delay(500);
                        noTone(13);
    for (;;) {
        Serial.println("LOSE");
    }
}

void winGame(int time) {
    clearScreen();
    lcd.print("YOU DEFUSED CHO!");
    lcd.setCursor(0, 1);
    lcd.print(String(((time - (time%60))/60)%60) + ":" + String(time%60) + " left!");
                            tone(13, 3000);
                        delay(500);
                        noTone(13);
    for (;;) {
       Serial.println("WIN");
    }
}