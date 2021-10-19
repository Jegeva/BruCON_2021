#! /bin/bash

# erases the storage
# resets the usb device
# flashes the firmware
# resets the usb device
# opens minicom to the device
#$IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 2000000 erase_flash 

sudo ./reset_usb.py cp210x 
make flash  && sudo ./reset_usb.py cp210x && sleep 0.2 && minicom -w -z -D /dev/ttyUSB0 -b 115200
