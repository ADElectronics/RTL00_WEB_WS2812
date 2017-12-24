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
#ifndef __HAL_COM_PHYCFG_H__
#define __HAL_COM_PHYCFG_H__

#define		PathA                     			0x0	// Useless
#define		PathB                     			0x1
#define		PathC                     			0x2
#define		PathD                     			0x3

typedef enum _RATE_SECTION {
	CCK = 0,
	OFDM,
	HT_MCS0_MCS7,
	HT_MCS8_MCS15,
	HT_MCS16_MCS23,
	HT_MCS24_MCS31,
	VHT_1SSMCS0_1SSMCS9,
	VHT_2SSMCS0_2SSMCS9,
	VHT_3SSMCS0_3SSMCS9,
	VHT_4SSMCS0_4SSMCS9,
} RATE_SECTION;

typedef enum _RF_TX_NUM {
	RF_1TX = 0,
	RF_2TX,
	RF_3TX,
	RF_4TX,
	RF_MAX_TX_NUM,
	RF_TX_NUM_NONIMPLEMENT,
} RF_TX_NUM;

#define MAX_POWER_INDEX 		0x3F

typedef enum _REGULATION_TXPWR_LMT {
	TXPWR_LMT_FCC = 0,
	TXPWR_LMT_MKK = 1,
	TXPWR_LMT_ETSI = 2,
	TXPWR_LMT_WW = 3, // WW13, The mininum of ETSI,MKK
	TXPWR_LMT_GL = 4, // Global, The mininum of ETSI,MKK,FCC
	TXPWR_LMT_MAX_REGULATION_NUM = 5
} REGULATION_TXPWR_LMT;

/*------------------------------Define structure----------------------------*/ 
typedef struct _BB_REGISTER_DEFINITION{
	uint32_t rfintfs;			// set software control: 
						//		0x870~0x877[8 bytes]
							
	uint32_t rfintfo; 			// output data: 
						//		0x860~0x86f [16 bytes]
							
	uint32_t rfintfe; 			// output enable: 
						//		0x860~0x86f [16 bytes]
							
	uint32_t rf3wireOffset;	// LSSI data:
						//		0x840~0x84f [16 bytes]

	uint32_t rfHSSIPara2; 	// wire parameter control2 : 
						//		0x824~0x827,0x82c~0x82f, 0x834~0x837, 0x83c~0x83f [16 bytes]
								
	uint32_t rfLSSIReadBack; 	//LSSI RF readback data SI mode
						//		0x8a0~0x8af [16 bytes]

	uint32_t rfLSSIReadBackPi; 	//LSSI RF readback data PI mode 0x8b8-8bc for Path A and B

}BB_REGISTER_DEFINITION_T, *PBB_REGISTER_DEFINITION_T;


//----------------------------------------------------------------------
int32_t
phy_TxPwrIdxToDbm(
	IN	PADAPTER		Adapter,
	IN	WIRELESS_MODE	WirelessMode,
	IN	uint8_t				TxPwrIdx	
	);

uint8_t
PHY_GetTxPowerByRateBase(
	IN	PADAPTER		Adapter,
	IN	uint8_t				Band,
	IN	uint8_t				RfPath,
	IN	uint8_t				TxNum,
	IN	RATE_SECTION	RateSection
	);

uint8_t
PHY_GetRateSectionIndexOfTxPowerByRate(
	IN	PADAPTER	pAdapter,
	IN	uint32_t			RegAddr,
	IN	uint32_t			BitMask
	);

void
PHY_GetRateValuesOfTxPowerByRate(
	IN	PADAPTER	pAdapter,
	IN	uint32_t			RegAddr,
	IN	uint32_t			BitMask,
	IN	uint32_t			Value,
	OUT	uint8_t*			RateIndex,
	OUT	int8_t*			PwrByRateVal,
	OUT	uint8_t*			RateNum
	);

uint8_t
PHY_GetRateIndexOfTxPowerByRate(
	IN	uint8_t	Rate
	);

void 
PHY_SetTxPowerIndexByRateSection(
	IN	PADAPTER		pAdapter,
	IN	uint8_t				RFPath,	
	IN	uint8_t				Channel,
	IN	uint8_t				RateSection
	);

int8_t
PHY_GetTxPowerByRate( 
	IN	PADAPTER	pAdapter, 
	IN	uint8_t			Band, 
	IN	uint8_t			RFPath, 
	IN	uint8_t			TxNum, 
	IN	uint8_t			RateIndex
	);

void
PHY_SetTxPowerByRate( 
	IN	PADAPTER	pAdapter, 
	IN	uint8_t			Band, 
	IN	uint8_t			RFPath, 
	IN	uint8_t			TxNum, 
	IN	uint8_t			Rate,
	IN	int8_t			Value
	);

void
PHY_SetTxPowerLevelByPath(
	IN	PADAPTER	Adapter,
	IN	uint8_t			channel,
	IN	uint8_t			path
	);

void 
PHY_SetTxPowerIndexByRateArray(
	IN	PADAPTER		pAdapter,
	IN	uint8_t				RFPath,
	IN	CHANNEL_WIDTH	BandWidth,	
	IN	uint8_t				Channel,
	IN	uint8_t*				Rates,
	IN	uint8_t				RateArraySize
	);

void
PHY_InitTxPowerByRate(
	IN	PADAPTER	pAdapter
	);

void
PHY_StoreTxPowerByRate(
	IN	PADAPTER	pAdapter,
	IN	uint32_t			Band,
	IN	uint32_t			RfPath,
	IN	uint32_t			TxNum,
	IN	uint32_t			RegAddr,
	IN	uint32_t			BitMask,
	IN	uint32_t			Data
	);

void
PHY_TxPowerByRateConfiguration(
	IN  PADAPTER			pAdapter
	);

uint8_t
PHY_GetTxPowerIndexBase(
	IN	PADAPTER		pAdapter,
	IN	uint8_t				RFPath,
	IN	uint8_t				Rate,	
	IN	CHANNEL_WIDTH	BandWidth,	
	IN	uint8_t				Channel,
	OUT PBOOLEAN		bIn24G
	);

int8_t
PHY_GetTxPowerLimit(
	IN	PADAPTER		Adapter,
	IN	uint32_t				RegPwrTblSel,
	IN	BAND_TYPE		Band,
	IN	CHANNEL_WIDTH	Bandwidth,
	IN	uint8_t				RfPath,
	IN	uint8_t				DataRate,
	IN	uint8_t				Channel
	);

void
PHY_SetTxPowerLimit(
	IN	PADAPTER			Adapter,
	IN	uint8_t					Regulation,
	IN	uint8_t					Band,
	IN	uint8_t					Bandwidth,
	IN	uint8_t					RateSection,
	IN	uint8_t					RfPath,
	IN	uint8_t					Channel,
	IN	uint8_t					PowerLimit
	);

void 
PHY_ConvertTxPowerLimitToPowerIndex(
	IN	PADAPTER			Adapter
	);

void
PHY_InitTxPowerLimit(
	IN	PADAPTER			Adapter
	);

int8_t
PHY_GetTxPowerTrackingOffset( 
	PADAPTER	pAdapter,
	uint8_t			Rate,
	uint8_t			RFPath
	);

uint8_t
PHY_GetTxPowerIndex(
	IN	PADAPTER			pAdapter,
	IN	uint8_t					RFPath,
	IN	uint8_t					Rate,	
	IN	CHANNEL_WIDTH		BandWidth,	
	IN	uint8_t					Channel
	);

void
PHY_SetTxPowerIndex(
	IN	PADAPTER		pAdapter,
	IN	uint32_t				PowerIndex,
	IN	uint8_t				RFPath,	
	IN	uint8_t				Rate
	);

#ifdef CONFIG_LOAD_PHY_PARA_FROM_FILE
#define MAX_PARA_FILE_BUF_LEN	25600

#define LOAD_MAC_PARA_FILE				BIT0
#define LOAD_BB_PARA_FILE					BIT1
#define LOAD_BB_PG_PARA_FILE				BIT2
#define LOAD_BB_MP_PARA_FILE				BIT3
#define LOAD_RF_PARA_FILE					BIT4
#define LOAD_RF_TXPWR_TRACK_PARA_FILE	BIT5
#define LOAD_RF_TXPWR_LMT_PARA_FILE		BIT6

int phy_ConfigMACWithParaFile(IN PADAPTER	Adapter, IN char*	pFileName);

int phy_ConfigBBWithParaFile(IN PADAPTER	Adapter, IN char*	pFileName, IN uint32_t	ConfigType);

int phy_ConfigBBWithPgParaFile(IN PADAPTER	Adapter, IN char*	pFileName);

int phy_ConfigBBWithMpParaFile(IN PADAPTER	Adapter, IN char*	pFileName);

int PHY_ConfigRFWithParaFile(IN	PADAPTER	Adapter, IN char*	pFileName, IN uint8_t	eRFPath);

int PHY_ConfigRFWithTxPwrTrackParaFile(IN PADAPTER	Adapter, IN char*	pFileName);

int PHY_ConfigRFWithPowerLimitTableParaFile(IN PADAPTER	Adapter, IN char*	pFileName);

void phy_free_filebuf(_adapter *padapter);
#endif //CONFIG_LOAD_PHY_PARA_FROM_FILE


#endif //__HAL_COMMON_H__

