# fx1-arduino-parser

This is an Arduino library for communicating with ROBO Pro software over USB.

[![ROBOPro with Arduino demo](http://img.youtube.com/vi/otV3sn2Q770/0.jpg)](http://www.youtube.com/watch?v=otV3sn2Q770)

The fx1-arduino-parser is a component that may be useful for a variety of projects, including educational tools. I want developers to be able to play with fx1-arduino-parser, give feedback, and think of novel uses for it. All the code is free and open source. Enjoy!

##How to use it
1. Download latest fx1-arduino-parser release.
2. Open in Arduino IDE and Upload fx1-arduino-parser to board.
3. Find which serial port used by Arduino.
4. Start ROBO Pro.
5. Setup Connection and Controller model: USB and ROBO TX.
6. Choose Bluetooth connection type and then select COM port from STEP 3.
7. Design flow-chart.
8. Run it in Online mode.

##Pin mapping

Inputs

| RP pin        | Arduino pin | RP pin mode |
|:------------- |:-----------:|:-----------:|
| I1            | 2           | Digital     |
| I2            | 3           | Digital     |
| I3            | 4           | Digital     |
| I4            | A0          | Analog      |
| I5            | A1          | Analog      |
| I6            | A2          | Analog      |
| I7            | A3          | Analog      |
| I8            | A4          | Analog      |


Оutputs

| RP pin        | Arduino pin | RP pin mode  |
|:------------- |:-----------:|:------------:|
| O1            | 6           | Digital      |
| O2            | 7           | Digital      |
| O3            | 8           | Digital      |
| O4            | 9           | Analog (0-8) |
| O5            | 10          | Analog (0-8) |
| O6            | 11          | Analog (0-8) |
| O7            | 12          | Digital      |
| O8            | 13          | Digital      |

##Links
1. [Original discussion at the ftcommunity.de forum](http://forum.ftcommunity.de/viewtopic.php?f=8&t=1655).

##Version history:
V0.2 - 03.09.2015. Changed output pins map. Now Arduino's pins 6-13 coresponds to ROBO TX pins O1-O8.
                   Changed input pins map. Now Arduino's pins A3-A4 coresponds to ROBO TX pins I7 and I8.
                   This version tested with ROBO Pro 4.1.8, Arduino IDE 1.0.6 and ARUDINO UNO R3 board.
				   
V0.1 - 03.01.2013. This version tested with ROBO Pro 3.2.0, Arduino IDE 1.0.3 and ARUDINO UNO R3 board.

##License:
All contents of this repository are released under [Creative Commons Share-alike 3.0](http://creativecommons.org/licenses/by-sa/3.0/).
