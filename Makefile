MCU = atmega328p
F_CPU = 16000000UL
BAUD = 115200
PORT = /dev/ttyUSB0

CXX = avr-g++

TARGET = main

ARDUINO_CORE = /usr/share/arduino/hardware/arduino/avr/cores/arduino
ARDUINO_VARIANTS = /usr/share/arduino/hardware/arduino/avr/variants/standard

BUILD = build

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall \
         -I$(ARDUINO_CORE) \
         -I$(ARDUINO_VARIANTS) \
         -I.

SRCS = main.cpp motors.cpp encoders.cpp
OBJS = $(SRCS:%.cpp=$(BUILD)/%.o)

CORE_SRC = $(wildcard $(ARDUINO_CORE)/*.c) $(wildcard $(ARDUINO_CORE)/*.cpp)
CORE_OBJS = $(CORE_SRC:$(ARDUINO_CORE)/%.c=$(BUILD)/core_%.o)
CORE_OBJS := $(CORE_OBJS:$(ARDUINO_CORE)/%.cpp=$(BUILD)/core_%.o)

all: $(TARGET).hex

# create build dir
$(BUILD):
	mkdir -p $(BUILD)

# compile your code
$(BUILD)/%.o: %.cpp | $(BUILD)
	$(CXX) $(CFLAGS) -c $< -o $@

# compile Arduino core INTO BUILD folder (IMPORTANT FIX)
$(BUILD)/core_%.o: $(ARDUINO_CORE)/%.c | $(BUILD)
	$(CXX) $(CFLAGS) -c $< -o $@

$(BUILD)/core_%.o: $(ARDUINO_CORE)/%.cpp | $(BUILD)
	$(CXX) $(CFLAGS) -c $< -o $@

# link everything
$(TARGET).elf: $(OBJS) $(CORE_OBJS)
	$(CXX) $(CFLAGS) $^ -o $@

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex -R .eeprom $< $@

upload: $(TARGET).hex
	avrdude -c arduino -p $(MCU) -P $(PORT) -b $(BAUD) \
	-U flash:w:$(TARGET).hex

clean:
	rm -rf $(BUILD) *.elf *.hex