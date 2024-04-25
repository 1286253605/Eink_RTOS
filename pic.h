#ifndef _PIC_H_
#define _PIC_H_

#define PIC_MAX_NUM 3
enum PIC_ALL_INDEX{
    PIC_ALL_CAT = 0,
    PIC_ALL_PIKA,
    PIC_ALL_PANDA
};
// extern char* pic_all[];

extern const unsigned char pic_dinosaur_1[];
extern const unsigned char pic_dinosaur_2[];

// 172 x 200 猫
extern const unsigned char gImage_IMG_0001[];
// 93*200 皮卡丘
extern const unsigned char gImage_IMG_0003[];
// 200*200 熊猫
extern const unsigned char gImage_IMG_0005[];


void PicShowInPage( uint8_t pic_num );


#endif