# Mobiflight-A320-Efis-Fcu-Display
A320 Efis/Fcu Display for Mobiflight using the new community device API.
Most is based of the work from Gagagu, see https://github.com/gagagu/Mobiflight-A320-Efis-Fcu-Display-with-ESP32
Only the integration into a community device is added.

5 OLED's are used for the FCU, and two OLED's are used for left and right EFIS.
The FW is setup for 1.3" OLED's with 128x64 pixel using the SH1106 chipset.

## This project ist still in development!
The goal of this project is to create an A320 Efis and Fcu controlled by Mobiflight.

## The Idea
With the new Mobiflight feature for community devices a new one is set up to add all required functions to support OLED displays.

You will need nearly three Arduino Mega 2560 for all Efis and Fcu Buttons and LED's to control. Or you can use Portexpander to use one Arduino Mega or Raspberry Pico. 

## Current State
The code is nearly finished and the displays are working. For the latest status regarding the connector config file see Gagagu's github page.
I will try to keep the FW functions on track with Gagagu, but I can not promise it.

## Installation
Download the ZIP file from the Releases and extract it into the community folder within your Mobiflight folder.
It should look like this:

![alt_text](https://github.com/elral/MobiFlight-FCU_EFIS_OLEDs/blob/main/documents/folder_structure_new.png)

** IMPORTANT **
Until version 0.9.2 the folder name within the zip file was `Elral_FCU_EFIS`, now the folder name is `Elral`.
If you have already installed version 0.9.2 or below, please delete the folder `Elral_FCU_EFIS`.

Connect your Mega or Pico board and start Mobiflight. Flash the firmware and add one custom device. Set the I2C adress to 0x70/0x71 or to the adress you have choosen on the portexpander.
Even I2C addresses support OLED's with SH1106G driver, odd I2C addresses support OLED's with SSD1306 driver.

## Wiring
![alt_text](https://github.com/elral/MobiFlight-FCU_EFIS_OLEDs/blob/main/documents/FCU_EFIS.png)

### Important note:
If you set the I2C address to 0x71 then you need to change the Multiplexer's address too. 
This is done by connecting the A0 PIN to the 3V3 on the Arduino board. 
There is no need to change anything if you are using the 0x70 address though, since this is the default address of the TCA9548A board.
