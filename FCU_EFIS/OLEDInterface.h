#include <Arduino.h>
#include "allocateMem.h"
#include "commandmessenger.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH   128  // OLED display width, in pixels
#define SCREEN_HEIGHT  64   // OLED display height, in pixels
#define OLED_RESET     -1   // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3c // address of the displays. All displays uses the same address

enum OLEDType {
    SSD1306,
    SH1106
};

class OLEDInterface
{
public:
    OLEDInterface(OLEDType type)
    {
        _type = type;
        if (_type == SSD1306) {
            if (!FitInMemory(sizeof(Adafruit_SSD1306))) {
                // Error Message to Connector
                cmdMessenger.sendCmd(kStatus, F("Custom Device does not fit in Memory"));
                return;
            }
            oled_1306 = new (allocateMemory(sizeof(Adafruit_SSD1306))) Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
        } else {
            if (!FitInMemory(sizeof(Adafruit_SH1106G))) {
                // Error Message to Connector
                cmdMessenger.sendCmd(kStatus, F("Custom Device does not fit in Memory"));
                return;
            }
            oled_1106 = new (allocateMemory(sizeof(Adafruit_SH1106G))) Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
        }
    }
    void begin(uint8_t I2Caddress, bool status)
    {
        if (_type == SSD1306)
            oled_1306->begin(SSD1306_SWITCHCAPVCC, I2Caddress, status);
        else
            oled_1106->begin(I2Caddress, status);
    }
    void display()
    {
        if (_type == SSD1306)
            oled_1306->display();
        else
            oled_1106->display();
    }
    void clearDisplay()
    {
        if (_type == SSD1306)
            oled_1306->clearDisplay();
        else
            oled_1106->clearDisplay();
    }
    void setTextColor(uint16_t color)
    {
        if (_type == SSD1306)
            oled_1306->setTextColor(color);
        else
            oled_1106->setTextColor(color);
    }
    void setFont(const GFXfont *f = NULL)
    {
        if (_type == SSD1306)
            oled_1306->setFont(f);
        else
            oled_1106->setFont(f);
    }
    void setCursor(int16_t x, int16_t y)
    {
        if (_type == SSD1306)
            oled_1306->setCursor(x, y);
        else
            oled_1106->setCursor(x, y);
    }
    void setTextSize(uint8_t s)
    {
        if (_type == SSD1306)
            oled_1306->setTextSize(s);
        else
            oled_1106->setTextSize(s);
    }
    void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
    {
        if (_type == SSD1306)
            oled_1306->fillCircle(x0, y0, r, color);
        else
            oled_1106->fillCircle(x0, y0, r, color);
    }
    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
    {
        if (_type == SSD1306)
            oled_1306->drawFastVLine(x, y, h, color);
        else
            oled_1106->drawFastVLine(x, y, h, color);
    }
    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
    {
        if (_type == SSD1306)
            oled_1306->drawFastHLine(x, y, w, color);
        else
            oled_1106->drawFastHLine(x, y, w, color);
    }
    void println(const char *t)
    {
        if (_type == SSD1306)
            oled_1306->println(t);
        else
            oled_1106->println(t);
    }
    void println(String t)
    {
        if (_type == SSD1306)
            oled_1306->println(t);
        else
            oled_1106->println(t);
    }
    void print(const char *t)
    {
        if (_type == SSD1306)
            oled_1306->print(t);
        else
            oled_1106->print(t);
    }
    void print(String t)
    {
        if (_type == SSD1306)
            oled_1306->print(t);
        else
            oled_1106->print(t);
    }

private:
    OLEDType          _type;
    Adafruit_SSD1306 *oled_1306;
    Adafruit_SH1106G *oled_1106;
};
