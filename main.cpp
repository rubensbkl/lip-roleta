#include <LiquidCrystal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//PINs
const byte PIN_BUTTON1 = 8;
const byte PIN_BUTTON2 = 9;
const byte PIN_GREEN = 10;
const byte PIN_RED = 11;
const byte PIN_YELLOW = 12;
const byte PIN_ANALOG_NOISE = A0; // Pino analógico para seed aleatório
LiquidCrystal lcd(2,3,4,5,6,7);

const int LEDS[] = {PIN_GREEN, PIN_RED, PIN_YELLOW};

//Game variables
int money;
int color;
int bet;
int buttonTime;
int win;

void setup() {
  //LCD setup
  lcd.begin(16,2);
  
  //pinModes
  pinMode(PIN_BUTTON1, INPUT_PULLUP);
  pinMode(PIN_BUTTON2, INPUT_PULLUP);
  for (int e : LEDS) {
    pinMode(e, OUTPUT);
  }
  
  //gameSetup
  money = 100;
  color = PIN_GREEN;

  // Seed aleatória
  int noiseSeed = analogRead(PIN_ANALOG_NOISE);
  srand(noiseSeed);
}

// Esperar mudança de estado do botão
void waitForButtonChange(byte button, byte state) {
  while (digitalRead(button) != state) {}
}
// Print on LCD
void printLCD(String str1, String str2) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(str1);
  lcd.setCursor(0,1);
  lcd.print(str2);
}
// Desligar todos os LEDs
void disableLed() {
  for(int e : LEDS) {
    digitalWrite(e, LOW);
  }
}

//Mostrar dinheiro
void dispMoney() {
  String moneyString = "R$" + String(money);
  if(moneyString.length() >= 15) {
    moneyString = moneyString.substring(0, 12) + "...$";
  }
  printLCD("Tiel Bet", moneyString);
  waitForButtonChange(PIN_BUTTON1, LOW);
  waitForButtonChange(PIN_BUTTON1, HIGH);
}

//Perguntar cor da aposta
void dispColor() {
  printLCD("Faca a sua", "aposta");
  waitForButtonChange(PIN_BUTTON1, HIGH);
  disableLed();
  digitalWrite(color, HIGH);
  buttonTime = 0;
  waitForButtonChange(PIN_BUTTON1, LOW);
  if(digitalRead(PIN_BUTTON1) == LOW) {
    while(digitalRead(PIN_BUTTON1) == LOW && buttonTime < 600) {
      buttonTime++;
      delay(1);
    }
    if(buttonTime < 600) {
      color = (color == PIN_GREEN) ? PIN_YELLOW : (color - 1);
    } else {
      disableLed();
      return;
    }
  }
  if(digitalRead(PIN_BUTTON2) == LOW) {
    color = (color == PIN_YELLOW) ? PIN_GREEN : (color + 1);
  }
  waitForButtonChange(PIN_BUTTON1, HIGH);
  dispColor();
}

//Perguntar valor da aposta
void dispBet() {
  printLCD("Apostar:", "R$" + String(bet));
  waitForButtonChange(PIN_BUTTON1, HIGH);
  buttonTime = 0;
  waitForButtonChange(PIN_BUTTON1, LOW);
  if(digitalRead(PIN_BUTTON1) == LOW) {
    while(digitalRead(PIN_BUTTON1) == LOW && buttonTime < 600) {
      buttonTime++;
      delay(1);
    }
    if(buttonTime < 600 && bet > 10) {
      bet -= 10;
    } else {
      return;
    }
  }
  if(digitalRead(PIN_BUTTON2) == LOW && bet < money) {
    bet += 10;
  }
  waitForButtonChange(PIN_BUTTON1, HIGH);
  dispBet();
}

// Sistema da Roleta
void dispGame() {
  money -= bet;
  int winColor = rand() % 37;
  Serial.println(winColor);
  win = 0;
  printLCD("Sorteando", String(winColor));
  waitForButtonChange(PIN_BUTTON1, HIGH);
  for(int i = 0; i <= 2; i++) {
    for(int j = 0; j <= 36; j++) {
      printLCD("Sorteando:" + String(winColor), "Current:" + String(j));
      disableLed();
      if(j == 0) {
        digitalWrite(PIN_YELLOW, HIGH);
      } else if(j % 2 == 0) {
        digitalWrite(PIN_GREEN, HIGH);
      } else {
        digitalWrite(PIN_RED, HIGH);
      }
      delay(i * 70);
      if(i == 2 && j == winColor) {
        delay(600);
        break;
      }
    }
  }
  if (color == PIN_YELLOW && winColor == 0) { 
    win = 2;
  } else if (color == PIN_RED && winColor % 2 == 1) {
    win = 1;
  } else if (color == PIN_GREEN && winColor % 2 == 0) {
    win = 1;
  } else {
    win = 0;
  }
}

// Mostrar Resultados
void dispResult() {
  if (win == 0) {
    printLCD("Voce perdeu", "R$" + String(bet));
  } else if (win == 1) {
    printLCD("Voce ganhou", "R$" + String(bet * 2));
    money += bet * 2;
  } else if (win == 2) {
    printLCD("Voce ganhou", "R$" + String(bet * 14));
    money += bet * 14;
  }
  delay(1500);
  disableLed();
}

//Game Loop
void loop() {
  if (money > 0) {
    dispMoney();
    dispColor();
    bet = 10;
    dispBet();
    dispGame();
    dispResult();
  } else {
    printLCD("Voce ripou", "Deposite mais :)");
  }
}