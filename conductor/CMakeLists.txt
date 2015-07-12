# CMake Configuration for an Arduino project
#
set(ARDUINO_SDK_PATH /opt/homebrew-cask/Caskroom/arduino/1.6.5/Arduino.app/Contents/Java/)
set(CMAKE_TOOLCHAIN_FILE /Users/tmallen/development/arduino-cmake/cmake/ArduinoToolchain.cmake) # Arduino Toolchain
set(CMAKE_C_COMPILER /usr/local/CrossPack-AVR/bin/avr-gcc)
set(CMAKE_CXX_COMPILER /usr/local/CrossPack-AVR/bin/avr-g++)
set(ARDUINO_1_5 true)

cmake_minimum_required(VERSION 2.8)

project(RobotBand C CXX)

#print_board_list()
#print_programmer_list()

# The Arduino variant
set(ARDUINO_DEFAULT_BOARD uno)
# The ttyport for writing to the Arduino
set(ARDUINO_DEFAULT_PORT /dev/tty.usbmodem1411)

# Add library paths or alternatively in the CODE_SRCS variable
set(LIBRARY_SRCS
#    ../libraries/DHT22/DHT22.cpp
#    ../libraries/RFM69/RFM69.cpp
#    ../libraries/SPIFlash/SPIFlash.cpp
)

# Additional Headers
set(LIBRARY_HDRS
    ${ARDUINO_SDK_PATH}/libraries/Servo/src/
)

# Search paths for the headers
include_directories(
    src/
    ${ARDUINO_SDK_PATH}/libraries/Servo/src/
#    ../libraries/DHT22/
#    ../libraries/RFM69/
#    ../libraries/SPIFlash
#    ../communication/)
)

# Source code running my code
set(CODE_SRCS
    src/Conductor.cpp
    src/PianoRoll.cpp
    src/Musician.cpp
    src/AxeMan.cpp
    src/LightMan.cpp
    ${LIBRARY_SRCS}
)

generate_arduino_firmware(MyArduinoSoftware
      SRCS  ${CODE_SRCS}
      HDRS  ${LIBRARY_HDRS}
      )