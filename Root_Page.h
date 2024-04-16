#ifndef _ROOT_PAGE
#define _ROOT_PAGE

#define DINOSAUR_POS_X      78
#define DINOSAUR_POS_Y      52
#define DINOSAUR_WIDTH      43
#define DINOSAUR_HEIGH      47

#define PAGE_TEXT_PARTIAL_POS_X         0
#define PAGE_TEXT_PARTIAL_POS_Y         120
#define PAGE_TEXT_PARTIAL_WIDTH         200
#define PAGE_TEXT_PARTIAL_HEIGHT        20

extern const unsigned char pic_dinosaur_1[];
extern const unsigned char pic_dinosaur_2[];

void DrawDinosaurGIF( void );
void DrawTestText( void );
void DrawSelectPage( void );
void DrawSelectPage( void );
void DrawSelectPageLoop( uint8_t mode_now );
void DrawWebserverPage( void );
void DrawDinosaurGIF( uint8_t counter, uint16_t x, uint16_t y );

#endif