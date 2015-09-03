//
// Sample sketch for the Fish.X1 protocol parser
// For more information please visit:
// https://github.com/mr-kubikus/fx1-arduino-parser
// http://forum.ftcommunity.de/viewtopic.php?f=8&t=1655
//
// Thanks to Ad2 for helpful information 
// Thanks to https://www.facebook.com/fischertechnik.ru for support
//

#include "fx1.h"

void setup()
{
  // Initialize parser
  fx1ParserInit();
  
  // Initialize UART
  // ROBO TX works at 38400,8,n,1  
  while(!Serial);
  Serial.begin(38400); 
  
}

void loop()
{
  unsigned char  symbol = 0;

  // Check UART and read one symbol
  if (Serial.available() > 0 ) {
    symbol = Serial.read();
  } else {
    return;
  }
  
  // Parse FishX1 protocol
  fx1ParserParse(symbol);
}
