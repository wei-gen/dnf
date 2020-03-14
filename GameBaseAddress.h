#pragma once

#define BASE_INVINCIBLE_CALL_ADDR		0x3BE70F0  			//无敌CALL
#define BASE_ENCRYPT_ADDR				0x064683E8 			//解密基址
#define BASE_DECTYPT_ADDR				0x06468448			//加密基址
#define NOTICE_CALL_ADDR				0x02E1F260 			//喇叭公告
#define BASE_STORE_ADDR					0x062E04CC			//商店基址-8=62E04C4
#define KEY_BOARD_ADDR					0x071B9460			//按键基址
#define BASE_TIME_ADDR					0x20A030			//时间基址
#define BASE_PASS_MAP_CALL_ADDR			0x1DECA50			//过图CALL
#define BASE_PASS_MAP_CHECKOUT_ADDR		0x40A150			//过图校验
#define BASE_PERSON_SITE_ADDR			0x2A53FD0			//坐标CALL
#define Base_ScopeWriteInAddr			0x03A498B5 			//范围写入
#define Base_AttackScopeddr				0x03A49887 			//攻击范围
#define Base_DamageScopeAddr			0x03A498ED 			//伤害范围
#define Base_ScopeWriteOutAddr			0x03A4991C 			//范围写出
#define BASE_FATIGUE_ADDR				0x0642B30C			//当前疲劳
#define BASE_MAX_FATIGUE_ADDR			0x0642B314			//最大疲劳
#define BASE_PERSON_ADDR				0x0642B240			//人物基址
#define	BASE_PERSON_POWER_OFFSET		0x2980 				//力量偏移
#define	BASE_PERSON_MENTALITY_OFFSET	0x29A0 				//智力偏移
#define OFFSET_PERSON_X					0x1E4				//x坐标偏移
#define OFFSET_PERSON_Y					0x1E8 				//y坐标偏移
#define OFFSET_PERSON_Z					0x1EC 				//z坐标偏移
#define OFFSET_MAP						0xD4				//地图偏移
#define OFFSET_ISOPEN					0x118				//是否开门
#define OFFSET_CURRENT_ROOM_X			0xD30				//当前房间x
#define OFFSET_CURRENT_ROOM_Y			0xD34				//当前房间y
#define BASE_PERSON_X_ADDR				0x62E0E74			//人物横轴
#define BASE_PERSON_Y_ADDR				0x62E0E78			//人物纵轴
#define BASE_PERSON_Z_ADDR				0x62E0E7C			//人物竖轴
#define BASE_NOTICE_ECX_ADDR			0x5E4940			//公告_ECX
#define BASE_ROOM_NUMBER_ADDR			0x62E04C4			//房间编号
#define OFFSET_DOOR_TYPE_ADDR			0xC8				//门型偏移
#define OFFSET_BOSS_ROOM_X_ADDR			0xDE8				//boss房间x
#define OFFSET_BOSS_ROOM_Y_ADDR			0xDE0				//boss房间y
// 0选择角色，1城镇，2选图，3打怪
#define BASE_GAME_STATUS_ADDR			0x061FAF8C			//游戏状态
//倍功需要的地址
#define BASE_DOUBLE_ATTACK_DET_ADDR_1	0x02C260E4			//倍功检测地址1
#define BASE_DOUBLE_ATTACK_DET_ADDR_2	0x02C26112			//倍功检测地址2
#define BASE_DOUBLE_ATTACK_ADDR			0x02C260C9			//倍功地址
#define BASE_DOUBLE_ATTACK_REALIZE		0x00400700			//倍功实现地址
#define BASE_AREA_CALL_ADDR				0x3B18D30			//区域CALL
#define BASE_SEND_PACKET_ADDR			0x645DB9C			//发包基址
#define BASE_BUFFER_CALL_ADDR			0x3BCE7B0			//缓冲CALL
#define BASE_ENCRYPT_PACKET_CALL_ADDR	0x3BCE8C0 			//加密包CALL
#define BASE_SEND_PACKET_CALL_ADDR		0x3BD00B0			//发包CALL
#define BASE_AREA_PARAM_ADDR			0x645CAD0			//区域参数
#define BASE_AREA_CALL_ADDR				0x3B18D30 			//区域CALL
#define OFFSET_AREA_ADDR				0xE3B0  			//区域偏移
#define BASEE_SKILL_COOLING_CALL_ADDR	0x2D42910 			//冷却判断CALL
#define OFFSET_START_ADDR				0xC0				//首地址
#define OFFSET_TAIL_ADDR				0xC4				//尾地址


//技能冷笑判断
#define SKILL_COOLING_EMPTY_			0x400800
#
// 0642B240  6F4 


// 868  0642B240

/*
人物的坐标，x轴，y轴，z轴(跳起来才会变化，不然为0)
.常量 人物横轴,103681652,  62E0E74 7度_获取			
.常量 人物纵轴,103681656,  62E0E78 7度_获取
.常量 人物竖轴,103681660,  62E0E7C 7度_获取
y1132888064
x1147289600


名称偏移,1108,  454

人物基址+地图偏移+首地址--》地址addr
第一次循环
addr+0 == 第一个图内物品地址
图内物品地址+偏移就能得到想要的
addr+4 == 第二个图内物品地址


倍功特侦码
33 C5 89 45 F0 53 56 57 50 8D 45 F4 64 A3 
00 00 00 00 8B 5D 14 8B 45 08 8B F9
+ 4D  ----》地址处
制造跳转
02C260C9  E9 32 A6 7D FD 90
制造倍功
00400700    
C7 45 10 03 00 00 00 89 B5 68 FE FF FF E9 BC 59 82 02 90 90         
检测
02C260E4  90 90 90 90 90
02C26112  90 90 90 90 90




顺途检测点
048BA3E7   E9 D9580100     jmp 048CFCC5                             ; 这里是检测

*/


