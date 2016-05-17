ARCHITECTURE  = avr
BOARD_TAG     = mega
BOARD_SUB     = atmega2560
MONITOR_PORT  = /dev/ttyACM0

USER_LIB_PATH = ./libraries
ARDUINO_LIBS  = SPI Adafruit_DotStar

# uncomment these lines if needed to fit system configuration
#ARDUINO_DIR   = 
#ARDMK_DIR     = 
#AVR_TOOLS_DIR = 

#CFLAGS_STD = -g
#CXXFLAGS_STD = -g

#windows stuff below
#MONITOR_PORT  = com3
#ARDUINO_DIR   = ../../../Program\ Files\ \(x86\)/Arduino
#ARDMK_DIR     = ./arduino-mk
#AVR_TOOLS_DIR = ../../../Program\ Files\ \(x86\)/Arduino/hardware/tools/avr
#MONITOR_CMD   = putty
#MONITOR_PARMS = 8,1,n,N

include ./arduino-mk/Arduino.mk