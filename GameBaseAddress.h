#pragma once

#define BASE_INVINCIBLE_CALL_ADDR		0x3BE70F0  			//�޵�CALL
#define BASE_ENCRYPT_ADDR				0x064683E8 			//���ܻ�ַ
#define BASE_DECTYPT_ADDR				0x06468448			//���ܻ�ַ
#define NOTICE_CALL_ADDR				0x02E1F260 			//���ȹ���
#define BASE_STORE_ADDR					0x062E04CC			//�̵��ַ-8=62E04C4
#define KEY_BOARD_ADDR					0x071B9460			//������ַ
#define BASE_TIME_ADDR					0x20A030			//ʱ���ַ
#define BASE_PASS_MAP_CALL_ADDR			0x1DECA50			//��ͼCALL
#define BASE_PASS_MAP_CHECKOUT_ADDR		0x40A150			//��ͼУ��
#define BASE_PERSON_SITE_ADDR			0x2A53FD0			//����CALL
#define Base_ScopeWriteInAddr			0x03A498B5 			//��Χд��
#define Base_AttackScopeddr				0x03A49887 			//������Χ
#define Base_DamageScopeAddr			0x03A498ED 			//�˺���Χ
#define Base_ScopeWriteOutAddr			0x03A4991C 			//��Χд��
#define BASE_FATIGUE_ADDR				0x0642B30C			//��ǰƣ��
#define BASE_MAX_FATIGUE_ADDR			0x0642B314			//���ƣ��
#define BASE_PERSON_ADDR				0x0642B240			//�����ַ
#define	BASE_PERSON_POWER_OFFSET		0x2980 				//����ƫ��
#define	BASE_PERSON_MENTALITY_OFFSET	0x29A0 				//����ƫ��
#define OFFSET_PERSON_X					0x1E4				//x����ƫ��
#define OFFSET_PERSON_Y					0x1E8 				//y����ƫ��
#define OFFSET_PERSON_Z					0x1EC 				//z����ƫ��
#define OFFSET_MAP						0xD4				//��ͼƫ��
#define OFFSET_ISOPEN					0x118				//�Ƿ���
#define OFFSET_CURRENT_ROOM_X			0xD30				//��ǰ����x
#define OFFSET_CURRENT_ROOM_Y			0xD34				//��ǰ����y
#define BASE_PERSON_X_ADDR				0x62E0E74			//�������
#define BASE_PERSON_Y_ADDR				0x62E0E78			//��������
#define BASE_PERSON_Z_ADDR				0x62E0E7C			//��������
#define BASE_NOTICE_ECX_ADDR			0x5E4940			//����_ECX
#define BASE_ROOM_NUMBER_ADDR			0x62E04C4			//������
#define OFFSET_DOOR_TYPE_ADDR			0xC8				//����ƫ��
#define OFFSET_BOSS_ROOM_X_ADDR			0xDE8				//boss����x
#define OFFSET_BOSS_ROOM_Y_ADDR			0xDE0				//boss����y
// 0ѡ���ɫ��1����2ѡͼ��3���
#define BASE_GAME_STATUS_ADDR			0x061FAF8C			//��Ϸ״̬
//������Ҫ�ĵ�ַ
#define BASE_DOUBLE_ATTACK_DET_ADDR_1	0x02C260E4			//��������ַ1
#define BASE_DOUBLE_ATTACK_DET_ADDR_2	0x02C26112			//��������ַ2
#define BASE_DOUBLE_ATTACK_ADDR			0x02C260C9			//������ַ
#define BASE_DOUBLE_ATTACK_REALIZE		0x00400700			//����ʵ�ֵ�ַ
#define BASE_AREA_CALL_ADDR				0x3B18D30			//����CALL
#define BASE_SEND_PACKET_ADDR			0x645DB9C			//������ַ
#define BASE_BUFFER_CALL_ADDR			0x3BCE7B0			//����CALL
#define BASE_ENCRYPT_PACKET_CALL_ADDR	0x3BCE8C0 			//���ܰ�CALL
#define BASE_SEND_PACKET_CALL_ADDR		0x3BD00B0			//����CALL
#define BASE_AREA_PARAM_ADDR			0x645CAD0			//�������
#define BASE_AREA_CALL_ADDR				0x3B18D30 			//����CALL
#define OFFSET_AREA_ADDR				0xE3B0  			//����ƫ��
#define BASEE_SKILL_COOLING_CALL_ADDR	0x2D42910 			//��ȴ�ж�CALL
#define OFFSET_START_ADDR				0xC0				//�׵�ַ
#define OFFSET_TAIL_ADDR				0xC4				//β��ַ


//������Ц�ж�
#define SKILL_COOLING_EMPTY_			0x400800
#
// 0642B240  6F4 


// 868  0642B240

/*
��������꣬x�ᣬy�ᣬz��(�������Ż�仯����ȻΪ0)
.���� �������,103681652,  62E0E74 7��_��ȡ			
.���� ��������,103681656,  62E0E78 7��_��ȡ
.���� ��������,103681660,  62E0E7C 7��_��ȡ
y1132888064
x1147289600


����ƫ��,1108,  454

�����ַ+��ͼƫ��+�׵�ַ--����ַaddr
��һ��ѭ��
addr+0 == ��һ��ͼ����Ʒ��ַ
ͼ����Ʒ��ַ+ƫ�ƾ��ܵõ���Ҫ��
addr+4 == �ڶ���ͼ����Ʒ��ַ


����������
33 C5 89 45 F0 53 56 57 50 8D 45 F4 64 A3 
00 00 00 00 8B 5D 14 8B 45 08 8B F9
+ 4D  ----����ַ��
������ת
02C260C9  E9 32 A6 7D FD 90
���챶��
00400700    
C7 45 10 03 00 00 00 89 B5 68 FE FF FF E9 BC 59 82 02 90 90         
���
02C260E4  90 90 90 90 90
02C26112  90 90 90 90 90




˳;����
048BA3E7   E9 D9580100     jmp 048CFCC5                             ; �����Ǽ��

*/


