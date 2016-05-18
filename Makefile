ARCHITECTURE  = avr
BOARD_TAG     = mega
BOARD_SUB     = atmega2560

ifeq ($(OS),Windows_NT)
	MONITOR_PORT  = com3
	# To work on Windows, create a symlink with mklink /d "C:\Arduino" "C:\Program Files (x86)\Arduino"
	ARDUINO_DIR   = ../../../Arduino
	AVR_TOOLS_DIR = ../../../Arduino/hardware/tools/avr
	MONITOR_CMD   = putty
	MONITOR_PARMS = 8,1,n,N
else
	MONITOR_PORT  = /dev/ttyACM0
endif

USER_LIB_PATH = ./libraries
ARDUINO_LIBS  = SPI Adafruit_DotStar

# uncomment these lines if needed to fit system configuration
#ARDUINO_DIR   = 
#ARDMK_DIR     = 
#AVR_TOOLS_DIR = 

#CFLAGS_STD = -g
#CXXFLAGS_STD = -g

include ./arduino-mk/Arduino.mk