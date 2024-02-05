#ifndef _MAIN_H
#define _MAIN_H


#define PIN_BOOT_9      9
#define PIN_MODE        8
#define PIN_KEEP        1
#define PIN_LED         12
#define IDLE_PRIORITY   0

#define digitalToggle(x) digitalWrite( (x), !digitalRead( (x) ) )

#include "GB2312.h"

#endif