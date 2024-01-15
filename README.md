# Mobiflight-A320-Efis-Fcu-Display-with-ESP32
A320 Efis/Fcu Display for Mobiflight using the new community device API.
Most is based of the work from Gagagu, see https://github.com/gagagu/Mobiflight-A320-Efis-Fcu-Display-with-ESP32
Only the integration into a community device is added.

## This project ist still in development!

The goal of this project is to create an A320 Efis and Fcu controlled by Mobiflight.

## The Idea
With the new Mobiflight feature for community devices a new one is set up to add all required functions to support OLED displays.

You will need nearly three Arduino Mega 2560 for all Efis and Fcu Buttons and LED's to control. Yes, you can use Portexpander to use one Arduino Mega, but why. The expander is not much cheaper than an additionally used Arduino Mega....

## Current State
The code is nearly finished and the displays are working. For easier testing i have used the Fly By Wire A320 with Mobiflight and i am using the Mobiflight 10

## Installation
Download the ZIP file from the Releases and copy the content into the community folder within your Mobiflight folder.


## Where are the stl's
Not released for now.

![alt_text](https://github.com/gagagu/Mobiflight-A320-Efis-Fcu-Display-with-ESP32/blob/main/Fritzing/Fritzing-Schematic.png)
In contrast to the shown schematic the I2C port expander is directly connected to a mega2560 or Raspberry Pico using there I2C pins.

## Used designs
https://www.printables.com/de/model/494654-airbus-a320-efis-baro-knob

https://cults3d.com/en/3d-model/game/rotary-switch-5-x-45

https://www.thingiverse.com/thing:5253832
