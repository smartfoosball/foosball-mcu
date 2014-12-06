#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include <stdio.h>
#include <stm32f10x.h>
#include "hal_key.h"
#include "hal_rgb_led.h"
#include "hal_led.h"
#include "hal_motor.h"
#include "hal_temp_hum.h"

#define		REPORT_STATUS													0x00
#define 	REQUEST_STATUS												0x01

#define		ERROR_CHECKSUM												0x01
#define		ERROR_CMD															0x02
#define		ERROR_OTHER														0x03

#define		CMD_GET_MCU_INFO                      0x01
#define		CMD_GET_MCU_INFO_ACK                  0x02
#define		CMD_SEND_MCU_P0												0x03
#define		CMD_SEND_MCU_P0_ACK										0x04
#define		CMD_SEND_MODULE_P0										0x05
#define		CMD_SEND_MODULE_P0_ACK								0x06
#define		CMD_SEND_HEARTBEAT										0x07
#define		CMD_SEND_HEARTBEAT_ACK								0x08
#define		CMD_SET_MODULE_WORKMODE								0x09
#define		CMD_SET_MODULE_WORKMODE_ACK						0x0A
#define		CMD_RESET_MODULE											0x0B
#define		CMD_RESET_MODULE_ACK									0x0C
#define		CMD_REPORT_MODULE_STATUS							0x0D
#define		CMD_REPORT_MODULE_STATUS_ACK					0x0E
#define		CMD_REBOOT_MCU												0x0F
#define		CMD_REBOOT_MCU_ACK										0x10
#define		CMD_MODULE_CMD_ERROR_ACK							0x11
#define		CMD_MCU_CMD_ERROR_ACK									0x12

#define		SUB_CMD_CONTROL_MCU										0x01
#define		SUB_CMD_REQUIRE_STATUS								0x02
#define		SUB_CMD_REQUIRE_STATUS_ACK						0x03
#define		SUB_CMD_REPORT_MCU_STATUS							0x04

#define  	MAX_SEND_NUM                          3   
#define  	MAX_SEND_TIME                         20

#define		PRO_VER																"00000004"
#define		P0_VER																"00000004"
#define		HARD_VER															"00000001"
#define		SOFT_VER															"00000001"
#define		PRODUCT_KEY														"ef992d473159465ba9d70d4d1a14aa39"

typedef	struct	_status_writable								status_writable;
typedef	struct	_status_readonly								status_readonly;
typedef struct	_pro_headPart										pro_headPart;
typedef	struct	_pro_commonCmd									pro_commonCmd;
typedef struct	_m2w_returnMcuInfo							m2w_returnMcuInfo;
typedef	struct	_m2w_setModule									m2w_setModule;
typedef	struct	_w2m_controlMcu									w2m_controlMcu;
typedef	struct	_m2w_mcuStatus									m2w_mcuStatus;
typedef	struct	_w2m_reportModuleStatus					w2m_reportModuleStatus;
typedef struct	_pro_errorCmd										pro_errorCmd;
typedef struct _game														game;

#define MEMBER_DEFAULT 0
#define MEMBER_RED_VAN 1
#define MEMBER_RED_REAR 2
#define MEMBER_BLUE_VAN 3
#define MEMBER_BLUE_REAR 4

#define SIDE_UNKNOWN 0
#define SIDE_BLUE 2
#define SIDE_RED 1

#define GAME_STATUS_GOING 0
#define GAME_STATUS_START 1
#define GAME_STATUS_FINISH 2

#define CANCEL_BLUE_GOAL 3
#define CANCEL_RED_GOAL 2

__packed struct _game
{
/*	uint8_t			game_id;
	uint8_t			game_status;
	uint8_t			blue_goals;
	uint8_t			red_goals;
	uint8_t			blue_score;
	uint8_t			red_score;*/
	uint8_t			last_goal; // 0, unknown, 1, blue or 2, red
	uint8_t			last_goal_member; // 0-none,1-red_van,2-red_rear,3-blue_van,4-blue_rear
};

__packed	struct	_status_writable
{
	uint8_t							game_control; // bit 0=going,1=start,2=finish,3=cancel last ball
	uint8_t							game_id;
};

__packed	struct	_status_readonly
{
	uint8_t							actions; // exchange position=0, goal=1-2, goal_member=3-5, exchange_member=6-7
	uint8_t							blue_goals;
	uint8_t							red_goals;
	uint8_t							blue_score;
	uint8_t							red_score;
};

__packed	struct	_pro_headPart
{
	uint8_t							head[2];
	short								len;
	uint8_t							cmd;
	uint8_t							sn;
	uint8_t							flags[2];
};

__packed	struct	_pro_commonCmd
{
	pro_headPart 				head_part;
	uint8_t							sum;
};

__packed	struct	_pro_errorCmd
{
	pro_headPart 				head_part;
	uint8_t							error;
	uint8_t							sum;	
};

__packed	struct	_m2w_returnMcuInfo
{
	pro_headPart				head_part;
	uint8_t							pro_ver[8];
	uint8_t							p0_ver[8];
	uint8_t							hard_ver[8];
	uint8_t							soft_ver[8];
	uint8_t							product_key[32];
	short								binable_time;
	uint8_t							sum;
};

__packed	struct	_m2w_setModule
{
	pro_headPart				head_part;
	uint8_t							config_info;
	uint8_t							sum;
};

__packed	struct	_w2m_controlMcu
{
	pro_headPart				head_part;
	uint8_t							sub_cmd;
	uint8_t							cmd_tag;
	status_writable			status_w;
	uint8_t							sum;
};

__packed	struct	_m2w_mcuStatus
{
	pro_headPart				head_part;
	uint8_t							sub_cmd;
	status_writable			status_w;
	status_readonly			status_r;
	uint8_t							sum;
};

__packed	struct	_w2m_reportModuleStatus
{
	pro_headPart				head_part;
	uint8_t							status[2];
	uint8_t							sum;
};

short	exchangeBytes(short value);
void	MessageHandle(void);
void	SendToUart(uint8_t *buf, uint16_t packLen, uint8_t tag);
void	ReportStatus(uint8_t tag);
void	CheckStatus(void);
uint8_t CheckSum(  uint8_t *buf,int packLen );
void updateGameStatus(void);
void resetGame(uint8_t newGameId);

#endif /*_PROTOCOL_H*/


