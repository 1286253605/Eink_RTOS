#ifndef _SYSTEM_INIT_H
#define _SYSTEM_INIT_H

#include "U8g2_for_Adafruit_GFX.h"
#include "u8g2_fonts.h"
#include "GxEPD2_BW.h"
#include "GxEPD2_3C.h"

/* U8G2字体设置 */
extern U8G2_FOR_ADAFRUIT_GFX my_u8g2_fonts;
/* 显示屏驱动 */
extern GxEPD2_BW<GxEPD2_154, GxEPD2_154::HEIGHT> my_display;

void SystemHardwareInit( void );
void SystemSoftwareInit( void );

void _GPIOInit( void );
void _DisplayInit( void );

#endif