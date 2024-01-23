#include "LCD.h"

LCD::LCD() : lcd(0x27, 20, 4) {
	isAvailable = false;
}

void LCD::init() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
	isAvailable = true;
  Serial.println("init lcd");
  return;
}

void LCD::displayLine(String message, int line) {
  clearLCDLine(line);
  lcd.setCursor(0, line);
  lcd.print(message);
}


void LCD::clearLCDLine(int line){
  for(int n = 0; n < 20; n++) { // 20 indicates symbols in line. For 2x16 LCD write - 16
    lcd.setCursor(n,line);
    lcd.print(" ");
  }
}

void LCD::clear() {
  lcd.clear();
}