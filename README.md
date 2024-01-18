# Arduino Heater Controler

## What's the purpose of the project?

The idea for this project came from noticing the hight temperature of the
metal door ont south side of the house during sunny winter days. Its purpose is
to raise temperature of the room using water heated by the sunlight.

## How does it work?

On the south side of the house, that catches a lot of sunlight, there's
special pad filled with water that is being heated up by the sun. If the
temperature of said water rises above the temperature inside of a room,
the Arduino Controler turns on the pump, which pushes heated water to
the heater inside of the room.

## Hardware used in the project:

- Arduino Uno
- LCD Display board with buttons
- 4x DS18B20 - temperature sensors
- OptotriacMOC 3041 - Pump on/off

## Libraries used in the project:

- EEPROM.h used to be able to set desired temperatures
- LiquidCrystal.h used to control LCD display
- DallasTemperatures.h used to easliy read temperatures from DS18B20 sensors
- OneWire.h dependencies of DallasTemperatures to read temperatures from
  multiple sensors connected to one pin on the Arduino Board

## Possible problems.

- Outside temperatures falling belowe 0*C. This could lead to water freeze and
  burst the pipes. Possible fix would be some sort of system that drains the
  water in case of temperatures falling below 0*C.

- System efficiency might not be as hight as expected. In the northern parts
  of Poland during spring, autumn and winter winter sky is often cloudy which
  could result in low heating capabilities of this Heating System.