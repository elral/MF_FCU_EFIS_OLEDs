#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SH110X.h>

enum OLEDType {
    SSD1306,
    SH1106
};

class OLEDInterface {
public:
    virtual void begin() = 0;
    virtual void displayText(const char* text) = 0;
    // Weitere Funktionen für den Zugriff auf das Display können hier hinzugefügt werden.
};

class SSD1306Implementation : public OLEDInterface {
public:
    SSD1306Implementation(int width, int height, int reset) {
        oled = new Adafruit_SSD1306(width, height, &Wire, reset);
    }

    void begin() override {
        oled->begin(SSD1306_I2C_ADDRESS, OLED_RESET);
    }

    void displayText(const char* text) override {
        oled->clearDisplay();
        oled->setTextSize(1);
        oled->setTextColor(SSD1306_WHITE);
        oled->setCursor(0, 0);
        oled->print(text);
        oled->display();
    }

private:
    Adafruit_SSD1306* oled;
    static const int OLED_RESET = -1; // Reset-Pin, -1, wenn nicht verwendet
    static const int SSD1306_I2C_ADDRESS = 0x3C; // Je nach Adresse des Displays
};

class SH1106Implementation : public OLEDInterface {
public:
    SH1106Implementation(int width, int height, int reset) {
        oled = new Adafruit_SH1106G(width, height, &Wire, reset);
    }

    void begin() override {
        oled->begin();
    }

    void displayText(const char* text) override {
        // SH1106 hat keine separate clearDisplay-Methode, stattdessen kann
        // der Bildschirm direkt überschrieben werden.
        oled->setTextSize(1);
        oled->setTextColor(SH110X_WHITE);
        oled->setCursor(0, 0);
        oled->print(text);
        oled->display();
    }

private:
    Adafruit_SH1106G* oled;
};

class OLEDController {
public:
    OLEDController(OLEDType type) {
        if (type == SSD1306) {
            implementation = new SSD1306Implementation(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_RESET);
        } else {
            implementation = new SH1106Implementation(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_RESET);
        }
    }

    void begin() {
        implementation->begin();
    }

    void displayText(const char* text) {
        implementation->displayText(text);
    }

private:
    OLEDInterface* implementation;

    static const int SCREEN_WIDTH = 128;
    static const int SCREEN_HEIGHT = 64;
    static const int OLED_RESET = -1; // Reset-Pin, -1, wenn nicht verwendet
};
