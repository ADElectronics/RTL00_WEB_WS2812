/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *                                        
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#ifndef __RTW_EFUSE_H__
#define __RTW_EFUSE_H__

#if (RTL8195A_SUPPORT == 1)
#include "rtl8195a.h"
#endif
#if (RTL8711B_SUPPORT == 1)
#include "ameba_soc.h"
#endif
/*--------------------------Define efuse Parameters-------------------------*/
#define	EFUSE_ERROE_HANDLE		1

#define	PG_STATE_HEADER 		0x01
#define	PG_STATE_WORD_0			0x02
#define	PG_STATE_WORD_1			0x04
#define	PG_STATE_WORD_2			0x08
#define	PG_STATE_WORD_3			0x10
#define	PG_STATE_DATA			0x20

#define	PG_SWBYTE_H				0x01
#define	PG_SWBYTE_L				0x02

#define	PGPKT_DATA_SIZE			8

#define	EFUSE_WIFI				0
#define	EFUSE_BT				1

enum _EFUSE_DEF_TYPE {
	TYPE_EFUSE_MAX_SECTION				= 0,
	TYPE_EFUSE_REAL_CONTENT_LEN			= 1,
	TYPE_AVAILABLE_EFUSE_BYTES_BANK		= 2,
	TYPE_AVAILABLE_EFUSE_BYTES_TOTAL	= 3,
	TYPE_EFUSE_MAP_LEN					= 4,
	TYPE_EFUSE_PROTECT_BYTES_BANK		= 5,
	TYPE_EFUSE_CONTENT_LEN_BANK			= 6,
};

#define EFUSE_MAP_SIZE			512
#define EFUSE_MAX_SIZE			256

#define	EFUSE_MAX_MAP_LEN		512
#define	EFUSE_MAX_HW_SIZE		256
#define	EFUSE_MAX_SECTION_BASE	16

#define EXT_HEADER(header) ((header & 0x1F ) == 0x0F)
#define ALL_WORDS_DISABLED(wde)	((wde & 0x0F) == 0x0F)
#define GET_HDR_OFFSET_2_0(header) ( (header & 0xE0) >> 5)

#define		EFUSE_REPEAT_THRESHOLD_		3
#define		EFUSE_MAX_WORD_UNIT			4

//=============================================
//	The following is for BT Efuse definition
//=============================================
#define		EFUSE_BT_MAX_MAP_LEN	1024
#define		EFUSE_MAX_BANK			4
#define		EFUSE_MAX_BT_BANK		(EFUSE_MAX_BANK-1)
//=============================================

/*--------------------------Define flash Parameters-------------------------*/
#if CONFIG_ADAPTOR_INFO_CACHING_FLASH
#if defined CONFIG_RTL8195A || defined(CONFIG_RTL8711B)
	#define FLASH_MAX_SIZE			FLASH_CAL_DATA_SIZE
	#define FLASH_MAGIC_NUMBER		0x8195 // magic number
	#define FLASH_HEADER_SIZE		4 // 2: address, 2: length
#endif
#endif // CONFIG_ADAPTOR_INFO_CACHING_FLASH
/*------------------------------Define structure----------------------------*/ 
typedef struct PG_PKT_STRUCT_A{
	uint8_t offset;
	uint8_t word_en;
	uint8_t data[8];	
	uint8_t word_cnts;
}PGPKT_STRUCT,*PPGPKT_STRUCT;

#ifdef HAL_EFUSE_MEMORY
typedef struct _EFUSE_HAL{
	uint8_t	fakeEfuseBank;
	uint32_t	fakeEfuseUsedBytes;
	uint8_t	fakeEfuseContent[EFUSE_MAX_HW_SIZE];
	uint8_t	fakeEfuseInitMap[EFUSE_MAX_MAP_LEN];
	uint8_t	fakeEfuseModifiedMap[EFUSE_MAX_MAP_LEN];
	
	uint16_t	BTEfuseUsedBytes;
	uint8_t	BTEfuseUsedPercentage;
	uint8_t	BTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
	uint8_t	BTEfuseInitMap[EFUSE_BT_MAX_MAP_LEN];
	uint8_t	BTEfuseModifiedMap[EFUSE_BT_MAX_MAP_LEN];

	uint16_t	fakeBTEfuseUsedBytes;
	uint8_t	fakeBTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
	uint8_t	fakeBTEfuseInitMap[EFUSE_BT_MAX_MAP_LEN];
	uint8_t	fakeBTEfuseModifiedMap[EFUSE_BT_MAX_MAP_LEN];
}EFUSE_HAL, *PEFUSE_HAL;
#endif // HAL_EFUSE_MEMORY

/*------------------------Export global variable----------------------------*/
#if CONFIG_FAKE_EFUSE
extern uint8_t fakeEfuseBank;
extern uint32_t fakeEfuseUsedBytes;
extern uint8_t fakeEfuseContent[];
extern uint8_t fakeEfuseInitMap[];
extern uint8_t fakeEfuseModifiedMap[];
#endif

#ifdef CONFIG_BT_COEXIST
extern uint32_t BTEfuseUsedBytes;
extern uint8_t BTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
extern uint8_t BTEfuseInitMap[];
extern uint8_t BTEfuseModifiedMap[];
#if CONFIG_FAKE_EFUSE
extern uint32_t fakeBTEfuseUsedBytes;
extern uint8_t fakeBTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
extern uint8_t fakeBTEfuseInitMap[];
extern uint8_t fakeBTEfuseModifiedMap[];
#endif
#endif

/*------------------------Export global variable----------------------------*/

uint8_t	efuse_GetCurrentSize(_adapter * padapter, uint16_t *size);
uint8_t	rtw_efuse_access(_adapter * padapter, uint8_t bRead, uint16_t start_addr, uint16_t cnts, uint8_t *data);
uint8_t	rtw_efuse_map_read(_adapter * padapter, uint16_t addr, uint16_t cnts, uint8_t *data);
uint8_t	rtw_efuse_map_write(_adapter * padapter, uint16_t addr, uint16_t cnts, uint8_t *data);
uint8_t	rtw_BT_efuse_map_read(_adapter * padapter, uint16_t addr, uint16_t cnts, uint8_t *data);
uint8_t 	rtw_BT_efuse_map_write(_adapter * padapter, uint16_t addr, uint16_t cnts, uint8_t *data);

uint16_t	Efuse_GetCurrentSize(_adapter * pAdapter, uint8_t efuseType, BOOLEAN bPseudoTest);
uint8_t	Efuse_CalculateWordCnts(uint8_t word_en);
void	EFUSE_GetEfuseDefinition(_adapter * pAdapter, uint8_t efuseType, uint8_t type, void *pOut, BOOLEAN bPseudoTest);
uint8_t	efuse_OneByteRead(_adapter * pAdapter, uint16_t addr, uint8_t *data, BOOLEAN	 bPseudoTest);
uint8_t	efuse_OneByteWrite(_adapter * pAdapter, uint16_t addr, uint8_t data, BOOLEAN	 bPseudoTest);

void	Efuse_PowerSwitch(_adapter * pAdapter,uint8_t	bWrite,uint8_t	 PwrState);
//int 	Efuse_PgPacketRead(_adapter * pAdapter, uint8_t offset, uint8_t *data, BOOLEAN bPseudoTest);
int 	Efuse_PgPacketWrite(_adapter * pAdapter, uint8_t offset, uint8_t word_en, uint8_t *data, BOOLEAN bPseudoTest);
void	efuse_WordEnableDataRead(uint8_t word_en, uint8_t *sourdata, uint8_t *targetdata);
uint8_t	Efuse_WordEnableDataWrite(_adapter * pAdapter, uint16_t efuse_addr, uint8_t word_en, uint8_t *data, BOOLEAN bPseudoTest);

void	EFUSE_ShadowMapUpdate(_adapter * pAdapter, uint8_t efuseType, BOOLEAN bPseudoTest);
void	EFUSE_ShadowRead(_adapter * pAdapter, uint8_t Type, uint16_t Offset, uint32_t *Value);

#endif

