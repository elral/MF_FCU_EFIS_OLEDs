> [!NOTE]  
> This article is for developers who would like to create their own community device implementation. If you are interested in simply using community devices, check out [this page](https://github.com/MobiFlight/MobiFlight-Connector/wiki/Using-a-pre-build-custom-device)

## Prerequisites
* MobiFlight firmware development is done with [VSCode](https://code.visualstudio.com/) and the [PlatformIO](https://platformio.org) extension. 
Make sure to install both.
* **Create** a new reposority by using the [Community Template repository](https://github.com/MobiFlight/CommunityDevice_Template)*

Follow the next steps carefully!

## Preparing the firmware
1. Rename the folder `/Template`, the name should reflect your device
2. Do **not** rename `MFCustomDevice.cpp/.h` as these filenames are required from the existing code.
4. Rename `MyCustomClass.cpp` and `MyCustomClass.h` to a name which fits to your community device.
5. Rename `MyCustomDevice_platformio.ini` to a name which fits to your community device (see step 1) but keep `_platformio.ini`, e.g. `YourChangedName_platformio.ini`
6. Rename the include path's from `MyCustomClass.cpp` and `MFCustomDevice.h` from `#include MyCustomClass.h` to `#include YourChangedName.h`
7. Adapt the `YourChangedName_platformio.ini`:
   1. Decide which board should be supported. The template is set up for the Mega and Pico. Is one of them is not needed, delete this part which is called in the following _environment_.
   2. Rename `[env_template]` to your community device and change `-I./Template` to the path where your sources are located (see 1.).
   3. Define which core firmware version should be used, e.g. `custom_core_firmware_version = 2.5.1` for the latest release as for now.
   4. Rename `Template` from `custom_device_folder` to the folder of your sources (see 1.) It's required again for copying the firmware files and creating the ZIP file (see below).
   5. Rename `Your_Project` from `custom_community_project`, this name will be the name of the generated ZIP file.
   6. rename each required environment from `[env:mobiflight_template_xyz]` to your community device. It should be like `[env:YourCommunityDevice_board]`
   7. Rename `-I./Template` under `build_flags` to your choosed folder name.
   8. Rename `+<../Template>` under `build_src_filter` to your choosed folder name.
   9. Rename `'-DMOBIFLIGHT_TYPE="Mobiflight Template Mega"'` to your needs. It should be like `'-DMOBIFLIGHT_TYPE="YourDevice_board Mega"'`. This is important and this must match with "MobiFlightType" within the .json files (see below).
   10. Rename `'-DMOBIFLIGHT_NAME="Mobiflight Template Mega"'` to your needs. It should be like `'-DMOBIFLIGHT_TYPE="YourDevice_board Mega"'`. This name will show up as name for this board and can be changed within the connector.
   11. If the Raspberry Pico should  be supported, follow the next steps. Otherwise delete the section `[env:mobiflight_template_raspberrypico]`
   12. Rename `'-DMOBIFLIGHT_TYPE="Mobiflight Template RaspiPico"'` to your needs. It should be like `'-DMOBIFLIGHT_TYPE="YourDevice_board RaspiPico"'`. This is important and this must match with "MobiFlightType" within the .json files (see below)
   13. Rename `'-DMOBIFLIGHT_NAME="Mobiflight Template RaspiPico"'` to your needs. It should be like `'-DMOBIFLIGHT_TYPE="YourDevice_board Mega"'`. This name will show up as name for this board and can be changed within the connector.
   14. Rename all `env_template` in each environment to the name you have choosen under topic 7.II
8. Nothing has to be changed within the `platformio.ini`:

If you are done, it should look like this:

![image](https://github.com/MobiFlight/MobiFlight-Connector/assets/3263285/58bf29c7-11df-47e9-a045-99ca731d917c)

Now it's time to test all these settings. Open a teminal window in PlatformIO and type `pio run`. This will compile all environments defined in `platformio.ini` including your newly defined environments. If everything is setup correct, no failure should be reported.
The FW files gets generated and will be copied to the `firmware` folder within `/Community`. Addiotionaly a folder `/zip` and a ZIP file gets generated which contains the complete `Community` folder
If you want only to compile your new environment, type `pio run -e YourName_YourCustomDevice_board` (see 7.VI).

## Setting up the connector files

### community.board.json files

To get your new defined board recognized from the connector, for each supported board a board.json file has to be set up. Within the copied folder is a sub folder named `connector_files`. Rename both board.json files to your needs. It should be like `YourName_YourDevice_board.board.json`. Both files (or just one if only one board should be supported) must be modified:
* Rename `"FirmwareBaseName": "mobiflight_template_raspberrypico"` to your defined environment, see point 6.
* Rename `"FriendlyName": "Mobiflight Template Mega"` to your needs. This will show up as name of the board in the Mobiflight Modules. This can be get overwritten within this dialog.
* Rename `"MobiFlightType": "Mobiflight Template Mega"` to the type you have defined in the `YourChangedName_platformio.ini` under 7.IX. and 7.XII. This **must** match the Type you have defined under 7.IX/7.XII. Otherwise the connector will not find your community board!
* Rename `"CustomDeviceType": ["MOBIFLIGHT_TEMPLATE","MOBIFLIGHT_TEMPLATE"]` to your community device type(s). If only one type is supported, delete the second entry. These definitions are used to filter the list of community devices which are under `/devices` are available, so only community devices can be added which fit to the community firmware. This/these entry(ies) must match `"Type": "MOBIFLIGHT_TEMPLATE"` within the `.device.json` file.
(* delete/adapt the list of pins if required. E.g. if you have setup an OLED with hardware SPI connection, the pins are predefined by the processor. So these pins would be deleted in this board.json file and would not be in the list of required pins in your device.json file (see below).) -> TBD

### custom.device.json files
The json files are in different folders under `/Community`. The boad.json files are under `boards` and the device.json files are under `devices`.
For each community device which will be supported a device.json file has to be setup. For the first one rename `mobiflight.template.device.json` to e.g. `YourName.YourDevice.device.json` and rename the entries to your needs:
1. `"Type": "MOBIFLIGHT_TEMPLATE"` must match one of the definitions from `"CustomDeviceType": ["MOBIFLIGHT_TEMPLATE","MOBIFLIGHT_TEMPLATE"]` (only two ore more entires if you support two or more community devices) within the board.json file you have set up. This information is part of of the complete definition of the community device which is strored in the EEPROM. Additionally check this in your code within `MFCustomDevice.cpp` to prevent that a wrong community device gets loaded which is not supported from your software. See the example in `MFCustomDevice.cpp` which got copied in the steps before.
Within `MFCustomDevice.cpp` is an example, how to read this information from the EEPROM.
2. Define all pins you require for your device. These pins with the hints will show up in the dialog from the UI if you add a community device to your configuration. Within `MFCustomDevice.cpp` the pins will be read from the EEPROM for your further use. There is an example in this file how to do this.
3. Define all messages you need for your community device. These messages can be choosen within the output ConfigWizard under the display tab to choose which value will be sent to which message type. The description entry will also show up to give additional hints what the user should choose.
4. Rename "Label": "Mobiflight's template", to your needs. This label will show up if you add a community device within the connector

### All .json files
Copy the complete `/Community` folder into the `/Community` folder which is in your Mobiflight installation folder.


### Testing
Now it's a good point to test everything you have set up.

The existing firmware itself will do nothing, but you can check if your new community board will show up under the Mobiflight Modules dialog if flashing the firmware to your new board. Additionally you can check if your community device could be choosed and gets uploaded to your board.
A new Mega w/o firmware is connected:

![image](https://github.com/MobiFlight/MobiFlight-Connector/assets/3263285/7167ecb9-c254-400c-88be-fc5ef5b103b3)

In the list of firmwares there should be an entry which matches `'-DMOBIFLIGHT_TYPE="YourDevice_board"'` from `YourChangedName_platformio.ini`.
Choose this entry and your firmware gets uploaded.
After this step you should be able to add a community device.

![image](https://github.com/MobiFlight/MobiFlight-Connector/assets/3263285/59f292f7-cbb1-4570-b0be-c5a933958e9e)

For each `YourName.YourDevice.device.json` a list item with `"Type": "YourName_YourDevice"` should show up. Choose one of them and check if all pins will show up. If you have more than one community device defined test this with all of them.

![image](https://github.com/MobiFlight/MobiFlight-Connector/assets/3263285/55d15e50-39ee-4474-a251-61da51754320)


## Implement your community firmware
See all hints in the files. It is also a good idea to check how the examples are set up. The basic GNC255 community device supports an 256x128 OLED, so just one community class is supported. The community device for the FCU and EFIS display from KAV simulation supports five different classes, so it's a good example how to set up two ore more supported devices.

## Further information

### Special message
There are some special messages with their respective IDs defined:
* Stop message (`-1`) - The device should turn off on receiving this message. The message is sent by the Connector any time the MobiFlight execution stops (Stop-button) or the application is shutdown.
* PowerSavingMode message (`-2`) - The device should go into a power saving mode (value=1) or wake up from it again (value=0).

### Overview how the json files are related
![image](https://github.com/MobiFlight/MobiFlight-Connector/assets/3263285/0123829b-27c1-49ad-96d2-30a751da6e25)

