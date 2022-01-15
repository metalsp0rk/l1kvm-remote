# Level1Techs KVM Remote

USB Remote for the Level1Techs KVM using Raspberry Pi Pico

# Hardware

## Bill of Materials

| Count | Device                        | Notes                                                                                                                    | Link                                  |
| ----  | -----                         | -----                                                                                                                    | ----                                  |
| 1     | Raspberry Pi Pico             |                                                                                                                          | https://www.adafruit.com/product/4864 |
| 5     | 12mm Round Tactile Switch     | These switches come with button caps.  If you don't like the colors, I've included a 3mf file so you can print your own. | https://www.adafruit.com/product/1009 |
| 2     | M3x20mm button head cap screw |                                                                                                                          | (https://www.mcmaster.com/92095A185/  |


## Enclosure

The enclosure is a 3 piece design, with optional mounting ears for screwing the remote onto a mounting surface.  The front component is designed so that the buttons are flush with the front of the enclosure.  The button mount is designed to hold the tactile switches with ~0.5mm of tolerance.  The pins should be exposed by ~1-2mm on the bottom of the mount, for ease of soldering when assembled.  The rear casing holds the Pi Pico and has ample room to hold wiring.  The Pico is located on the mount with conical pins and held in place with hot glue.  

Suggestions for improvements on the models are always welcome.


## Building

### Which parts to print

To build a complete unit, you'll need one of each of the following parts:

 - [Front Fascia](3MF/1-front_fascia.3mf)
 - One of: [Button Mount](3MF/2-button_mount.3mf) or [Button Mount with ears](3MF/2-button_mount_ears.3mf)
 - [Rear Casing](3MF/3-rear_casing.3mf)

If you want to mount the enclosure with screws, choose the button mount with ears.

The rear casing requires support or a printer that is _extremely good_ at bridging, so enable support.

Optionally, you can also print buttons for the switches.  You'll need 5 copies of [Switch Button](3MF/4-switch_button.3mf).

Switch buttons should be printed at a layer height of 0.12-0.16mm if possible, and all other components can be printed between 0.16-0.2mm layer height.  If you want, you can print all components on the same print, at a 0.16mm layer height.  This 8 piece print took approximately 10 hours on my Ender 3, so set the print and go out for a night on the town.


# Keymappings

We've got 5 buttons; 4 for directly changing inputs, one to act as a "modifier"

Here's the mapping table:
|  BTN  |  BASE  |  MOD         |
| ----- | ------ | ------------ |
|   1   |  MOD   |     NONE     |
| 2     | HEAD 1 | AUDIO FOLLOW |
| 3     | HEAD 2 | AUDIO LOCK   |
| 4     | HEAD 3 | USB FOLLOW   |
| 5     | HEAD 4 | USB LOCK     |

# Software

## Dependencies

Ubuntu:

```
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
```

### PicoProbe and PicoTool

If you want to use OpenOCD and a PicoProbe for development, you'll need to use the Raspberry Pi Foundation fork of OpenOCD until they upstream their changes.  This can be found at:

https://github.com/raspberrypi/openocd

Once you've installed OpenOCD, you'll need to build and flash a picoprobe:

https://github.com/raspberrypi/picoprobe

A more detailed guide can be found here: 

https://www.digikey.com/en/maker/projects/raspberry-pi-pico-and-rp2040-cc-part-2-debugging-with-vs-code/470abc7efb07432b82c95f6f67f184c0

## Building

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Debugging

Include Debug symbols.
```
cmake -DCMAKE_BUILD_TYPE=Debug ..
```
I've included a GDB sample for my macros, if you want to use GDB, go for it, otherwise, vscode has a good debugger, you just need to set up OpenOCD as your debugging target.

