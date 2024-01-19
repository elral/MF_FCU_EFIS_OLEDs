# Mobiflight-A320-Efis-Fcu-Display-with-ESP32
A320 Efis/Fcu Display for Mobiflight using the new community device API.
Most is based of the work from Gagagu, see https://github.com/gagagu/Mobiflight-A320-Efis-Fcu-Display-with-ESP32
Only the integration into a community device is added.

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
![alt_text](https://github.com/elral/MobiFlight-FCU_EFIS_OLEDs/blob/main/documents/folder_structure.png)

## Wiring
![alt_text](https://github.com/elral/MobiFlight-FCU_EFIS_OLEDs/blob/main/documents/FCU_EFIS.png)

