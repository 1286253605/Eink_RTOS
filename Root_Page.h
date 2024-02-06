#ifndef _ROOT_PAGE
#define _ROOT_PAGE

#define DINOSAUR_POS_X      78
#define DINOSAUR_POS_Y      52
#define DINOSAUR_WIDTH      43
#define DINOSAUR_HEIGH      47

#define PAGE_TEXT_PARTIAL_POS_X         0
#define PAGE_TEXT_PARTIAL_POS_Y         130
#define PAGE_TEXT_PARTIAL_WIDTH         200
#define PAGE_TEXT_PARTIAL_HEIGHT        70

extern const unsigned char pic_dinosaur_1[];
extern const unsigned char pic_dinosaur_2[];

void DrawDinosaurGIF( void );
void DrawTestText( void );
#endif