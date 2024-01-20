#include <Arduino.h>
#include "TestMultipleOLED.h"

// Beispiel für die Verwendung:
int testOLED() {
    OLEDController oledController(SSD1306);
    oledController.begin();
    oledController.displayText("Hello, OLED!");

    // Hier können Sie auf andere Funktionen der OLEDController-Klasse zugreifen.

    return 0;
}