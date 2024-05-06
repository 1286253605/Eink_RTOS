#ifndef _WEATHERRES_H_
#define _WEATHERRES_H_
/* 有的组件位置是动态的 根据之前的组件文本长度变化而变化 比如温度后的C */

/* 当前城市 LOGO位置 */
#define POS_X_DESTINATION_LOGO      4
#define POS_Y_DESTINATION_LOGO      55
/* 当前城市文本 */
#define POS_Y_DESTINATION_TEXT      ( POS_X_DESTINATION_LOGO + 32 )
#define POS_X_DESTINATION_TEXT      ( POS_Y_DESTINATION_LOGO + 22 )
/* 温度数值位置 */
#define POS_X_TEMP_TEXT             4
#define POS_Y_TEMP_TEXT             10


//width:24  height:24   
extern const unsigned char degree[];
//width:12  height:12 
extern const unsigned char degree_12[];
//width:38  height:12 
extern const unsigned char yiyanp[];
//width:64  height:64  
extern const unsigned char baoxue[];
extern const unsigned char baoyu[];
extern const unsigned char dabaoyu[];
extern const unsigned char daxue[];
extern const unsigned char dayu[];
extern const unsigned char dongyu[];
extern const unsigned char duoyun[];
extern const unsigned char fuchen[];
extern const unsigned char leiyubingbao[];
extern const unsigned char leizhenyu[];
extern const unsigned char mai[];
extern const unsigned char qiangshachenbao[];
extern const unsigned char qing[];
extern const unsigned char shachenbao[];
extern const unsigned char tedabaoyu[];
extern const unsigned char weizhi[];
extern const unsigned char dawu[];
extern const unsigned char xiaoxue[];
extern const unsigned char xiaoyu[];
extern const unsigned char yangsha[];
extern const unsigned char ying[];
extern const unsigned char yujiaxue[];
extern const unsigned char zhenxue[];
extern const unsigned char zhenyu[];
extern const unsigned char zhongxue[];
extern const unsigned char zhongyu[];


//width:16  height:16
extern const unsigned char shidu[];
extern const unsigned char fengli[];

//width:32  height:28
extern const unsigned char dingwei[];
#endif