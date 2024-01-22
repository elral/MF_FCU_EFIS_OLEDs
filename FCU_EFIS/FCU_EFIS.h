#pragma once

#include "Arduino.h"
#include "OLEDInterface.h"

// address of the multiplexer to change the channels
#define TCA9548A_I2C_ADDRESS  0x70
#define TCA9548A_CHANNEL_EFIS_LEFT  0
#define TCA9548A_CHANNEL_EFIS_RIGHT 1
#define TCA9548A_CHANNEL_FCU_SPD    6
#define TCA9548A_CHANNEL_FCU_HDG    5
#define TCA9548A_CHANNEL_FCU_FPA    4
#define TCA9548A_CHANNEL_FCU_ALT    3
#define TCA9548A_CHANNEL_FCU_VS     2
#define TCA9548A_CHANNEL_UNUSED     7


class FCU_EFIS
{
public:
    FCU_EFIS();
    void begin();
    void attach(uint8_t addrI2C);
    void detach();
    void set(int16_t messageID, char *message);
    void update();

private:
    bool          _initialised;
    uint8_t       _addrI2C;
    OLEDInterface *oled;

    void setTCAChannel(byte i);
    void updateDisplayEfisLeft(void);
    void updateDisplayEfisRight(void);
    void updateDisplayFcuSpd(void);
    void updateDisplayFcuHdg(void);
    void updateDisplayFcuFpa(void);
    void updateDisplayFcuAlt(void);
    void updateDisplayFcuVs(void);

};
