/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES 10  // Number of snowflakes in the animation example

#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16
static const unsigned char PROGMEM logo_bmp[] = { 0b00000000, 0b11000000,
                                                  0b00000001, 0b11000000,
                                                  0b00000001, 0b11000000,
                                                  0b00000011, 0b11100000,
                                                  0b11110011, 0b11100000,
                                                  0b11111110, 0b11111000,
                                                  0b01111110, 0b11111111,
                                                  0b00110011, 0b10011111,
                                                  0b00011111, 0b11111100,
                                                  0b00001101, 0b01110000,
                                                  0b00011011, 0b10100000,
                                                  0b00111111, 0b11100000,
                                                  0b00111111, 0b11110000,
                                                  0b01111100, 0b11110000,
                                                  0b01110000, 0b01110000,
                                                  0b00000000, 0b00110000 };

void setup() {
  Serial.begin(9600);


  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  analogReadResolution(12);
  analogReference(INTERNAL1V024);  // set internal referent// mean that it will read up to what is set
                                   // INTERNAL1V024
                                   // INTERNAL2V048
                                   // INTERNAL4V096
                                   // comment "analogReference()" out mean setting it to VCC 5v(max)
                                   // this is for lgt8f328p

  // https://docs.arduino.cc/language-reference/en/functions/analog-io/analogReference/
  // arduino board use different "analogReference(INTERNAL1V1)" name
  // also they dont use "analogReadResolution(12)" need to be commented out for arduino

  display.display();
  delay(250);
  display.clearDisplay();
}

//if your display is not working consider changing "#define SCREEN_ADDRESS 0x3D"(at line 35) to 0x3C or checking the connection, better yet testing with an example from adafruit
float watt;
float volt;
float miamp;
void loop() {


  display.clearDisplay();
  display.setTextColor(1);
  display.setTextSize(1);
  display.setTextWrap(0);

  miamp = currentreading() / 1000;
  volt = voltagereading();
  watt = miamp * volt;

  display.setCursor(0, (7 * 3 + 3) * 2);
  display.setTextSize(2);
  display.print(watt, 2);
  display.setTextSize(1);
  display.println("W");


  display.display();
}

float adcbit = 12;
float adc = pow(2, adcbit) - 1.0;

float internal_ref_volt = 1.024;

float avgcurrent = 0;
float current = 0;


float currentreading() {
  for (int i = 0; i < 1000; i++) {
    current = (analogRead(A0) * (internal_ref_volt / adc));
    //Serial.println(analogRead(A0));

    avgcurrent = avgcurrent + current;
  }

  avgcurrent = avgcurrent / 1000.0;
  display.setCursor(0, 0);
  display.setTextSize(3);
  display.print(avgcurrent * 1000, 2);
  display.setTextSize(2);
  display.println("mA");
  return avgcurrent * 1000;
}

float divide = 2.0 / (100.0 + 2.0);  // voltage divider, 2k and 100k from 50v to 0.98v fit for 1v internal ref
float avgvoltage = 0;
float voltage = 0;
float voltagereading() {
  for (int i = 0; i < 1000; i++) {
    voltage = float(analogRead(A1)) * (internal_ref_volt / adc) / divide;
   // Serial.println(voltage);

    avgvoltage = avgvoltage + voltage;
  }

  avgvoltage = avgvoltage / 1000.0;
  display.setCursor(0, 7 * 3 + 3);
  display.setTextSize(3);
  display.print(avgvoltage, 2);
  display.setTextSize(2);
  display.println("V");
  return avgvoltage;
}
