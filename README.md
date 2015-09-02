# fx1-arduino-parser

This is an Arduino library for communicating with ROBO Pro software over USB.

[![ROBOPro with Arduino demo](http://img.youtube.com/vi/otV3sn2Q770/0.jpg)](http://www.youtube.com/watch?v=otV3sn2Q770)

The fx1-arduino-parser is a component that may be useful for a variety of projects, including educational tools. I want developers to be able to play with fx1-arduino-parser, give feedback, and think of novel uses for it. All the code is free and open source. Enjoy!

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
| I7            | -           | -           |
| I8            | -           | -           |


Оutputs

| RP pin        | Arduino pin | RP pin mode  |
|:------------- |:-----------:|:------------:|
| O1            | 8           | Digital      |
| O2            | 9           | Analog (0-8) |
| O3            | 10          | Analog (0-8) |
| O4            | 11          | Analog (0-8) |
| O5            | 12          | Digital      |
| O6            | 13          | Digital      |
| O7            | -           | -            |
| O8            | -           | -            |

##Version history:
V0.1 - 03.01.2013. This version tested with ROBO Pro 3.2.0, Arduino IDE 1.0.3 and ARUDINO UNO R3 board.

##License:
All contents of this repository are released under [Creative Commons Share-alike 3.0](http://creativecommons.org/licenses/by-sa/3.0/).
