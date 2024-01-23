#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

class LCD {
public:
  LCD();
  void init();
  void displayLine(String message, int line);
  void clear();
	bool isAvailable;
private:
	LiquidCrystal_I2C lcd;
  void clearLCDLine(int line);
};

#endif
