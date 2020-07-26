#include <M5Stack.h>
#include <BBQ10Keyboard.h>
#include "Free_Fonts.h"

BBQ10Keyboard keyboard;

void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.lcd.setRotation(3);
  M5.Lcd.setTextColor(TFT_BLACK, TFT_WHITE);
  M5.Lcd.fillScreen(TFT_WHITE);
  M5.Lcd.setFreeFont(FF24); // FreeSansBold24pt7b
  M5.Lcd.drawString(F("M5 Begin"), 0, 0, 1);
  keyboard.begin();
  keyboard.setBacklight(0.5f);
  M5.Lcd.setFreeFont(FSS9); // FreeSans9pt7b
  M5.Lcd.setCursor(0, 50);
  M5.Lcd.print("> ");
}

void loop() {
  const int keyCount = keyboard.keyCount();
  if (keyCount == 0) return;
  const BBQ10Keyboard::KeyEvent key = keyboard.keyEvent();
  String state = "pressed";
  if (key.state == BBQ10Keyboard::StateLongPress) state = "held down";
  else if (key.state == BBQ10Keyboard::StateRelease) {
    state = "released";
    M5.Lcd.print(key.key);
  }
  Serial.printf("key: '%c' (dec %d, hex %02x) %s\r\n", key.key, key.key, key.key, state.c_str());
  // pressing 'b' turns off the backlight and pressing Shift+b turns it on
  if (key.state == BBQ10Keyboard::StatePress) {
    if (key.key == 'b') {
      keyboard.setBacklight(0);
    } else if (key.key == 'B') {
      keyboard.setBacklight(1.0);
    }
  }
}
