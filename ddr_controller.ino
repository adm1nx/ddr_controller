#include <HID-Project.h>
#include <HID-Settings.h>

/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  Gamepad example
  Press a button and demonstrate Gamepad actions

  You can also use Gamepad1,2,3 and 4 as single report.
  This will use 1 endpoint for each gamepad.

  See HID Project documentation for more infos
  https://github.com/NicoHood/HID/wiki/Gamepad-API
*/


const int pinLed = LED_BUILTIN;
const int p1_ctl_up = 2;
const int p1_ctl_down = 3; 
const int p1_ctl_left = 4;
const int p1_ctl_right = 5;
const int p1_ctl_enter = 6;

const int p1_dnc_up = 7;
const int p1_dnc_down = 8;
const int p1_dnc_left = 9;
const int p1_dnc_right = 10;

const int p2_ctl_up = 11;
const int p2_ctl_down = 12; 
const int p2_ctl_left = 13;
const int p2_ctl_right = 14;
const int p2_ctl_enter = 15;

const int p2_dnc_up = 16;
const int p2_dnc_down = 17;
const int p2_dnc_left = 18;
const int p2_dnc_right = 19;


void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  pinMode(p1_ctl_up, INPUT_PULLUP);
  pinMode(p1_ctl_down, INPUT_PULLUP); 
  pinMode(p1_ctl_left, INPUT_PULLUP);
  pinMode(p1_ctl_right, INPUT_PULLUP);
  pinMode(p1_ctl_enter, INPUT_PULLUP);

  pinMode(p1_dnc_up, INPUT_PULLUP);
  pinMode(p1_dnc_down, INPUT_PULLUP);
  pinMode(p1_dnc_left, INPUT_PULLUP);
  pinMode(p1_dnc_right, INPUT_PULLUP);

  pinMode(p2_ctl_up, INPUT_PULLUP);
  pinMode(p2_ctl_down, INPUT_PULLUP); 
  pinMode(p2_ctl_left, INPUT_PULLUP);
  pinMode(p2_ctl_right, INPUT_PULLUP);
  pinMode(p2_ctl_enter, INPUT_PULLUP);

  pinMode(p2_dnc_up, INPUT_PULLUP);
  pinMode(p2_dnc_down, INPUT_PULLUP);
  pinMode(p2_dnc_left, INPUT_PULLUP);
  pinMode(p2_dnc_right, INPUT_PULLUP);



  // Sends a clean report to the host. This is important on any Arduino type.
  Gamepad1.begin();
  Gamepad2.begin();
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // Press button 1-32
    static uint8_t count = 0;
    count++;
    if (count == 33) {
      Gamepad1.releaseAll();
      Gamepad2.releaseAll();
      count = 0;
    }
    else
      Gamepad1.press(count);
      Gamepad2.press(count);

    // Move x/y Axis to a new position (16bit)
    Gamepad.xAxis(random(0xFFFF));
    Gamepad.yAxis(random(0xFFFF));

    // Go through all dPad positions
    // values: 0-8 (0==centered)
    static uint8_t dpad1 = GAMEPAD_DPAD_CENTERED;
    Gamepad.dPad1(dpad1++);
    if (dpad1 > GAMEPAD_DPAD_UP_LEFT)
      dpad1 = GAMEPAD_DPAD_CENTERED;

    static int8_t dpad2 = GAMEPAD_DPAD_CENTERED;
    Gamepad.dPad2(dpad2--);
    if (dpad2 < GAMEPAD_DPAD_CENTERED)
      dpad2 = GAMEPAD_DPAD_UP_LEFT;

    // Functions above only set the values.
    // This writes the report to the host.
    Gamepad.write();

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
