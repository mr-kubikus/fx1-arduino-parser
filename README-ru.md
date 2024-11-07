[English](README.md) ∙ [Русский](README-ru.md)
# fx1-arduino-parser
Подключаем Arduino к ROBO Pro через USB

[![Демонстрация ROBOPro и Arduino](http://img.youtube.com/vi/otV3sn2Q770/0.jpg)](http://www.youtube.com/watch?v=otV3sn2Q770)

После загрузки скетча fx1-arduino-parser.ino плата Arduino ведет себя как контроллер ROBO TX в режиме "Online". Вы составляете алгоритм в виде блок-схемы в ROBO Pro, а Arduino берет на себя взаимодействие с объектом управления. Таким образом fx1-arduino-parser можно использовать для изучения алгоритмического программирования в образовательных проектах.

Если у вас появятся новые идеи насчет использования этого проекта - буду рад получить ваш отзыв. Весь исходный код проекта открыт для свободного использования. Мир! Упчк!

## Содержание
* [Системные требования](#requirements)
* [Использование по назначению](#how-to-use)
* [Привязка портов Arduino к ROBO Pro](#pin-mapping)
* [Решение проблемы с автоматической перезагрузкой Arduino](#solution-for-reboot)
* [Ссылки](#ссылки)
* [История проекта](#история-проекта)
* [Лицензия](#лицензия)

## <a name="requirements">Системные требования
* ROBO Pro версия 4.6.6
* Интрефейс USB

## <a name="how-to-use">Использование по назначению
1. Загрузите [свежий релиз](https://github.com/mr-kubikus/fx1-arduino-parser/releases) проекта на свой компьютер.
2. Распакуйте архив fx1-arduino-parser.zip в папку с проектами для Arduino.
3. Откройте проект fx1-arduino-parser.ino в Arduino IDE и скомпилируйте и загрузите в Arduino.
4. Определите - какой последовательный порт использует плата Arduino.
5. Запустите ROBO Pro.
6. Укажите настройки подключения к контроллеру: порт - USB, тип контроллера - ROBO TX.
7. Укажите тип подключения - Bluetooth и выберите порт, к которому подкулючена плата Arduino (см. шаг 4).
8. Составьте блок схему алгоритма.
9. Запустите проект в режиме "Онлайн".

## <a name="pin-mapping">Привязка портов Arduino к ROBO Pro
### Входы
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


### Выходы
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

## <a name="solution-for-reboot">Решение проблемы с автоматической перезагрузкой Arduino
Если вы используете плату Arduino UNO или клон, то возможна следующая проблема. Когда ROBO Pro открывает порт - Arduino перезагружается. Это может приводить к появленияю сообщения "Timeout" в ROBO Pro. Для устранения этой проблемы надо отключить автоматическу перезагрузку Arduino UNO согласно рекомендациям с сайта [playground.arduino.cc](https://playground.arduino.cc/Main/DisablingAutoResetOnSerialConnection/).

## <a name="links">Ссылки
1. [Исходное обсуждение на форуме ftcommunity.de forum](https://forum.ftcommunity.de/viewtopic.php?f=8&t=1655).
2. [Загрузка ROBO Pro с сайта fischertechnik.de](https://www.fischertechnik.de/de-de/apps-und-software/software-archiv).

## <a name="history">История проекта
V0.3 - 11.08.2016. Changed version.firmware.part.b by one to make it compatible with ROBO Pro 4.2.3.

V0.2 - 03.09.2015. Changed output pins map. Now Arduino's pins 6-13 coresponds to ROBO TX pins O1-O8.
                   Changed input pins map. Now Arduino's pins A3-A4 coresponds to ROBO TX pins I7 and I8.
                   This version tested with ROBO Pro 4.1.8, Arduino IDE 1.0.6 and ARUDINO UNO R3 board.
				   
V0.1 - 03.01.2013. This version tested with ROBO Pro 3.2.0, Arduino IDE 1.0.3 and ARUDINO UNO R3 board.

## <a name="license">Лицензия
Все содержание данного репозитория распространяется под лицензией [Creative Commons Share-alike 3.0](http://creativecommons.org/licenses/by-sa/3.0/).
