/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
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
#ifndef _RTW_MP_H_
#define _RTW_MP_H_

#ifndef PLATFORM_WINDOWS
//	00 - Success
//	11 - Error
#define STATUS_SUCCESS				(0x00000000L)
#define STATUS_PENDING				(0x00000103L)

#define STATUS_UNSUCCESSFUL			(0xC0000001L)
#define STATUS_INSUFFICIENT_RESOURCES		(0xC000009AL)
#define STATUS_NOT_SUPPORTED			(0xC00000BBL)

#define NDIS_STATUS_SUCCESS			((NDIS_STATUS)STATUS_SUCCESS)
#define NDIS_STATUS_PENDING			((NDIS_STATUS)STATUS_PENDING)
#define NDIS_STATUS_NOT_RECOGNIZED		((NDIS_STATUS)0x00010001L)
#define NDIS_STATUS_NOT_COPIED			((NDIS_STATUS)0x00010002L)
#define NDIS_STATUS_NOT_ACCEPTED		((NDIS_STATUS)0x00010003L)
#define NDIS_STATUS_CALL_ACTIVE			((NDIS_STATUS)0x00010007L)

#define NDIS_STATUS_FAILURE			((NDIS_STATUS)STATUS_UNSUCCESSFUL)
#define NDIS_STATUS_RESOURCES			((NDIS_STATUS)STATUS_INSUFFICIENT_RESOURCES)
#define NDIS_STATUS_CLOSING			((NDIS_STATUS)0xC0010002L)
#define NDIS_STATUS_BAD_VERSION			((NDIS_STATUS)0xC0010004L)
#define NDIS_STATUS_BAD_CHARACTERISTICS		((NDIS_STATUS)0xC0010005L)
#define NDIS_STATUS_ADAPTER_NOT_FOUND		((NDIS_STATUS)0xC0010006L)
#define NDIS_STATUS_OPEN_FAILED			((NDIS_STATUS)0xC0010007L)
#define NDIS_STATUS_DEVICE_FAILED		((NDIS_STATUS)0xC0010008L)
#define NDIS_STATUS_MULTICAST_FULL		((NDIS_STATUS)0xC0010009L)
#define NDIS_STATUS_MULTICAST_EXISTS		((NDIS_STATUS)0xC001000AL)
#define NDIS_STATUS_MULTICAST_NOT_FOUND		((NDIS_STATUS)0xC001000BL)
#define NDIS_STATUS_REQUEST_ABORTED		((NDIS_STATUS)0xC001000CL)
#define NDIS_STATUS_RESET_IN_PROGRESS		((NDIS_STATUS)0xC001000DL)
#define NDIS_STATUS_CLOSING_INDICATING		((NDIS_STATUS)0xC001000EL)
#define NDIS_STATUS_NOT_SUPPORTED		((NDIS_STATUS)STATUS_NOT_SUPPORTED)
#define NDIS_STATUS_INVALID_PACKET		((NDIS_STATUS)0xC001000FL)
#define NDIS_STATUS_OPEN_LIST_FULL		((NDIS_STATUS)0xC0010010L)
#define NDIS_STATUS_ADAPTER_NOT_READY		((NDIS_STATUS)0xC0010011L)
#define NDIS_STATUS_ADAPTER_NOT_OPEN		((NDIS_STATUS)0xC0010012L)
#define NDIS_STATUS_NOT_INDICATING		((NDIS_STATUS)0xC0010013L)
#define NDIS_STATUS_INVALID_LENGTH		((NDIS_STATUS)0xC0010014L)
#define NDIS_STATUS_INVALID_DATA		((NDIS_STATUS)0xC0010015L)
#define NDIS_STATUS_BUFFER_TOO_SHORT		((NDIS_STATUS)0xC0010016L)
#define NDIS_STATUS_INVALID_OID			((NDIS_STATUS)0xC0010017L)
#define NDIS_STATUS_ADAPTER_REMOVED		((NDIS_STATUS)0xC0010018L)
#define NDIS_STATUS_UNSUPPORTED_MEDIA		((NDIS_STATUS)0xC0010019L)
#define NDIS_STATUS_GROUP_ADDRESS_IN_USE	((NDIS_STATUS)0xC001001AL)
#define NDIS_STATUS_FILE_NOT_FOUND		((NDIS_STATUS)0xC001001BL)
#define NDIS_STATUS_ERROR_READING_FILE		((NDIS_STATUS)0xC001001CL)
#define NDIS_STATUS_ALREADY_MAPPED		((NDIS_STATUS)0xC001001DL)
#define NDIS_STATUS_RESOURCE_CONFLICT		((NDIS_STATUS)0xC001001EL)
#define NDIS_STATUS_NO_CABLE			((NDIS_STATUS)0xC001001FL)

#define NDIS_STATUS_INVALID_SAP			((NDIS_STATUS)0xC0010020L)
#define NDIS_STATUS_SAP_IN_USE			((NDIS_STATUS)0xC0010021L)
#define NDIS_STATUS_INVALID_ADDRESS		((NDIS_STATUS)0xC0010022L)
#define NDIS_STATUS_VC_NOT_ACTIVATED		((NDIS_STATUS)0xC0010023L)
#define NDIS_STATUS_DEST_OUT_OF_ORDER		((NDIS_STATUS)0xC0010024L)  // cause 27
#define NDIS_STATUS_VC_NOT_AVAILABLE		((NDIS_STATUS)0xC0010025L)  // cause 35,45
#define NDIS_STATUS_CELLRATE_NOT_AVAILABLE	((NDIS_STATUS)0xC0010026L)  // cause 37
#define NDIS_STATUS_INCOMPATABLE_QOS		((NDIS_STATUS)0xC0010027L)  // cause 49
#define NDIS_STATUS_AAL_PARAMS_UNSUPPORTED	((NDIS_STATUS)0xC0010028L)  // cause 93
#define NDIS_STATUS_NO_ROUTE_TO_DESTINATION	((NDIS_STATUS)0xC0010029L)  // cause 3
#endif /* #ifndef PLATFORM_WINDOWS */

#if 0
#define MPT_NOOP			0
#define MPT_READ_MAC_1BYTE		1
#define MPT_READ_MAC_2BYTE		2
#define MPT_READ_MAC_4BYTE		3
#define MPT_WRITE_MAC_1BYTE		4
#define MPT_WRITE_MAC_2BYTE		5
#define MPT_WRITE_MAC_4BYTE		6
#define MPT_READ_BB_CCK			7
#define MPT_WRITE_BB_CCK		8
#define MPT_READ_BB_OFDM		9
#define MPT_WRITE_BB_OFDM		10
#define MPT_READ_RF			11
#define MPT_WRITE_RF			12
#define MPT_READ_EEPROM_1BYTE		13
#define MPT_WRITE_EEPROM_1BYTE		14
#define MPT_READ_EEPROM_2BYTE		15
#define MPT_WRITE_EEPROM_2BYTE		16
#define MPT_SET_CSTHRESHOLD		21
#define MPT_SET_INITGAIN		22
#define MPT_SWITCH_BAND			23
#define MPT_SWITCH_CHANNEL		24
#define MPT_SET_DATARATE		25
#define MPT_SWITCH_ANTENNA		26
#define MPT_SET_TX_POWER		27
#define MPT_SET_CONT_TX			28
#define MPT_SET_SINGLE_CARRIER		29
#define MPT_SET_CARRIER_SUPPRESSION	30
#define MPT_GET_RATE_TABLE		31
#define MPT_READ_TSSI			32
#define MPT_GET_THERMAL_METER		33
#endif

typedef enum _ANTENNA_PATH{
		ANTENNA_NONE	= 0x00,
		ANTENNA_D		,
		ANTENNA_C		,
		ANTENNA_CD		,
		ANTENNA_B		,
		ANTENNA_BD		,
		ANTENNA_BC		,
		ANTENNA_BCD 	,
		ANTENNA_A		,
		ANTENNA_AD		,
		ANTENNA_AC		,
		ANTENNA_ACD 	,
		ANTENNA_AB		,
		ANTENNA_ABD 	,
		ANTENNA_ABC 	,
		ANTENNA_ABCD
} ANTENNA_PATH;


#define MAX_MP_XMITBUF_SZ 	2048
#define NR_MP_XMITFRAME		8

struct mp_xmit_frame
{
	_list	list;

	struct pkt_attrib attrib;

	_pkt *pkt;

	int frame_tag;

	_adapter *padapter;

#ifdef CONFIG_USB_HCI

	//insert urb, irp, and irpcnt info below...
	//max frag_cnt = 8

	uint8_t *mem_addr;
	uint32_t sz[8];

#if defined(PLATFORM_OS_XP) || defined(PLATFORM_LINUX)
	PURB pxmit_urb[8];
#endif

#ifdef PLATFORM_OS_XP
	PIRP pxmit_irp[8];
#endif

	uint8_t bpending[8];
	int32_t ac_tag[8];
	int32_t last[8];
	uint irpcnt;
	uint fragcnt;
#endif /* CONFIG_USB_HCI */

	uint mem[(MAX_MP_XMITBUF_SZ >> 2)];
};

struct mp_wiparam
{
	uint32_t bcompleted;
	uint32_t act_type;
	uint32_t io_offset;
	uint32_t io_value;
};

typedef void(*wi_act_func)(void* padapter);

#ifdef PLATFORM_WINDOWS
struct mp_wi_cntx
{
	uint8_t bmpdrv_unload;

	// Work Item
	NDIS_WORK_ITEM mp_wi;
	NDIS_EVENT mp_wi_evt;
	_lock mp_wi_lock;
	uint8_t bmp_wi_progress;
	wi_act_func curractfunc;
	// Variable needed in each implementation of CurrActFunc.
	struct mp_wiparam param;
};
#endif

struct mp_tx
{
	uint8_t stop;
	uint32_t count, sended;
	uint8_t payload;
	struct pkt_attrib attrib;
	struct tx_desc desc;
	uint8_t *pallocated_buf;
	uint8_t *buf;
	uint32_t buf_size, write_size;
	//_thread_hdl_	PktTxThread;
	struct task_struct	MpXmitThread;
};

#define MP_MAX_LINES		1000
#define MP_MAX_LINES_BYTES	256


typedef void (*MPT_WORK_ITEM_HANDLER)(IN void *Adapter);
typedef struct _MPT_CONTEXT
{
	// Indicate if we have started Mass Production Test.
	BOOLEAN			bMassProdTest;

	// Indicate if the driver is unloading or unloaded.
	BOOLEAN			bMptDrvUnload;

	_sema			MPh2c_Sema;
	_timer			MPh2c_timeout_timer;
// Event used to sync H2c for BT control

	BOOLEAN		MptH2cRspEvent;
	BOOLEAN		MptBtC2hEvent;
	BOOLEAN		bMPh2c_timeout;

	/* 8190 PCI does not support NDIS_WORK_ITEM. */
	// Work Item for Mass Production Test.
	//NDIS_WORK_ITEM	MptWorkItem;
//	RT_WORK_ITEM		MptWorkItem;
	// Event used to sync the case unloading driver and MptWorkItem is still in progress.
//	NDIS_EVENT		MptWorkItemEvent;
	// To protect the following variables.
//	NDIS_SPIN_LOCK		MptWorkItemSpinLock;
	// Indicate a MptWorkItem is scheduled and not yet finished.
	BOOLEAN			bMptWorkItemInProgress;
	// An instance which implements function and context of MptWorkItem.
	MPT_WORK_ITEM_HANDLER	CurrMptAct;

	// 1=Start, 0=Stop from UI.
	uint32_t			MptTestStart;
	// _TEST_MODE, defined in MPT_Req2.h
	uint32_t			MptTestItem;
	// Variable needed in each implementation of CurrMptAct.
	uint32_t			MptActType; 	// Type of action performed in CurrMptAct.
	// The Offset of IO operation is depend of MptActType.
	uint32_t			MptIoOffset;
	// The Value of IO operation is depend of MptActType.
	uint32_t			MptIoValue;
	// The RfPath of IO operation is depend of MptActType.
	uint32_t			MptRfPath;

	WIRELESS_MODE		MptWirelessModeToSw;	// Wireless mode to switch.
	uint8_t			MptChannelToSw; 	// Channel to switch.
	uint8_t			MptInitGainToSet; 	// Initial gain to set.
	//uint32_t			bMptAntennaA; 		// TRUE if we want to use antenna A.
	uint32_t			MptBandWidth;		// bandwidth to switch.
	uint32_t			MptRateIndex;		// rate index.
	// Register value kept for Single Carrier Tx test.
	uint8_t			btMpCckTxPower;
	// Register value kept for Single Carrier Tx test.
	uint8_t			btMpOfdmTxPower;
	// For MP Tx Power index
	uint8_t			TxPwrLevel[2];	// rf-A, rf-B

	// Content of RCR Regsiter for Mass Production Test.
	uint32_t			MptRCR;
	// TRUE if we only receive packets with specific pattern.
	BOOLEAN			bMptFilterPattern;
 	// Rx OK count, statistics used in Mass Production Test.
 	uint32_t			MptRxOkCnt;
 	// Rx CRC32 error count, statistics used in Mass Production Test.
 	uint32_t			MptRxCrcErrCnt;

	BOOLEAN			bCckContTx;	// TRUE if we are in CCK Continuous Tx test.
 	BOOLEAN			bOfdmContTx;	// TRUE if we are in OFDM Continuous Tx test.
	BOOLEAN			bStartContTx; 	// TRUE if we have start Continuous Tx test.
	// TRUE if we are in Single Carrier Tx test.
	BOOLEAN			bSingleCarrier;
	// TRUE if we are in Carrier Suppression Tx Test.
	BOOLEAN			bCarrierSuppression;
	//TRUE if we are in Single Tone Tx test.
	BOOLEAN			bSingleTone;

	// ACK counter asked by K.Y..
	BOOLEAN			bMptEnableAckCounter;
	uint32_t			MptAckCounter;

	// SD3 Willis For 8192S to save 1T/2T RF table for ACUT	Only fro ACUT delete later ~~~!
	//int8_t		BufOfLines[2][MAX_LINES_HWCONFIG_TXT][MAX_BYTES_LINE_HWCONFIG_TXT];
	//int8_t			BufOfLines[2][MP_MAX_LINES][MP_MAX_LINES_BYTES];
	//int32_t			RfReadLine[2];

	uint8_t		APK_bound[2];	//for APK	path A/path B
	BOOLEAN		bMptIndexEven;

	uint8_t		backup0xc50;
	uint8_t		backup0xc58;
	uint8_t		backup0xc30;
	uint8_t 		backup0x52_RF_A;
	uint8_t 		backup0x52_RF_B;

	uint8_t			h2cReqNum;
	uint8_t			c2hBuf[20];

	uint8_t          btInBuf[100];
	uint32_t			mptOutLen;
	uint8_t          mptOutBuf[100];

}MPT_CONTEXT, *PMPT_CONTEXT;
//#endif

//#define RTPRIV_IOCTL_MP 					( SIOCIWFIRSTPRIV + 0x17)
enum {
	WRITE_REG = 1,
	READ_REG,
	WRITE_RF,
	READ_RF,
	MP_START,
	MP_STOP,
	MP_RATE,
	MP_CHANNEL,
	MP_BANDWIDTH,
	MP_TXPOWER,
	MP_ANT_TX,
	MP_ANT_RX,
	MP_CTX,
	MP_QUERY,
	MP_ARX,
	MP_PSD,
	MP_PWRTRK,
	MP_THER,
	MP_IOCTL,
	EFUSE_GET,
	EFUSE_SET,
	CONFIG_GET,
	CONFIG_SET,
	MP_RESET_STATS,
	MP_DUMP,
	MP_PHYPARA,
	MP_SetRFPathSwh,
	MP_QueryDrvStats,
	MP_SetBT,
	TEST_CFG,
	MP_NULL,
	MP_GET_TXPOWER_INX,
	MP_SET_PREAMBLE,
	MP_DISABLE_BT_COEXIST,
	MP_PwrCtlDM,
	MP_IQK,
	MP_LCK,
	MP_DRV_ABILITY
};

struct mp_priv
{
	_adapter *papdater;

	//Testing Flag
	uint32_t mode;//0 for normal type packet, 1 for loopback packet (16bytes TXCMD)

	uint32_t prev_fw_state;

	//OID cmd handler
	struct mp_wiparam workparam;
//	uint8_t act_in_progress;

	//Tx Section
	uint8_t TID;
	uint32_t tx_pktcount;
	struct mp_tx tx;

	//Rx Section
	uint8_t rx_pkt_by_mac;
	uint32_t rx_pktcount;
	uint32_t rx_crcerrpktcount;
	uint32_t rx_macpktcount;
	uint32_t rx_pktloss;
	
	struct recv_stat rxstat;

	//RF/BB relative
	uint8_t channel;
	uint8_t bandwidth;
	uint8_t prime_channel_offset;
	uint8_t txpoweridx;
	uint8_t txpoweridx_b;
	uint8_t rateidx;
	uint32_t preamble;
//	uint8_t modem;
	uint32_t CrystalCap;
//	uint32_t curr_crystalcap;

	uint16_t antenna_tx;
	uint16_t antenna_rx;
//	uint8_t curr_rfpath;

	uint8_t check_mp_pkt;

	uint8_t bSetTxPower;
	uint8_t bCCKTxPowerAdjust;
	uint8_t bFAStatistics;
//	uint ForcedDataRate;
	uint8_t mp_dm;
	struct wlan_network mp_network;
	NDIS_802_11_MAC_ADDRESS network_macaddr;

#ifdef PLATFORM_WINDOWS
	uint32_t rx_testcnt;
	uint32_t rx_testcnt1;
	uint32_t rx_testcnt2;
	uint32_t tx_testcnt;
	uint32_t tx_testcnt1;

	struct mp_wi_cntx wi_cntx;

	uint8_t h2c_result;
	uint8_t h2c_seqnum;
	uint16_t h2c_cmdcode;
	uint8_t h2c_resp_parambuf[512];
	_lock h2c_lock;
	_lock wkitm_lock;
	uint32_t h2c_cmdcnt;
	NDIS_EVENT h2c_cmd_evt;
	NDIS_EVENT c2h_set;
	NDIS_EVENT h2c_clr;
	NDIS_EVENT cpwm_int;

	NDIS_EVENT scsir_full_evt;
	NDIS_EVENT scsiw_empty_evt;
#endif

	uint8_t *pallocated_mp_xmitframe_buf;
	uint8_t *pmp_xmtframe_buf;
	_queue free_mp_xmitqueue;
	uint32_t free_mp_xmitframe_cnt;

	MPT_CONTEXT MptCtx;
};

typedef struct _IOCMD_STRUCT_ {
	uint8_t	cmdclass;
	uint16_t	value;
	uint8_t	index;
}IOCMD_STRUCT;

struct rf_reg_param {
	uint32_t path;
	uint32_t offset;
	uint32_t value;
};

struct bb_reg_param {
	uint32_t offset;
	uint32_t value;
};
//=======================================================================

#define LOWER 	_TRUE
#define RAISE	_FALSE

/* Hardware Registers */
#if 0
#if 0
#define IOCMD_CTRL_REG			0x102502C0
#define IOCMD_DATA_REG			0x102502C4
#else
#define IOCMD_CTRL_REG			0x10250370
#define IOCMD_DATA_REG			0x10250374
#endif

#define IOCMD_GET_THERMAL_METER		0xFD000028

#define IOCMD_CLASS_BB_RF		0xF0
#define IOCMD_BB_READ_IDX		0x00
#define IOCMD_BB_WRITE_IDX		0x01
#define IOCMD_RF_READ_IDX		0x02
#define IOCMD_RF_WRIT_IDX		0x03
#endif
#define BB_REG_BASE_ADDR		0x800

/* MP variables */
#if 0
#define _2MAC_MODE_	0
#define _LOOPBOOK_MODE_	1
#endif
typedef enum _MP_MODE_ {
	MP_OFF,
	MP_ON,
	MP_ERR,
	MP_CONTINUOUS_TX,
	MP_SINGLE_CARRIER_TX,
	MP_CARRIER_SUPPRISSION_TX,
	MP_SINGLE_TONE_TX,
	MP_PACKET_TX,
	MP_PACKET_RX
} MP_MODE;


#define MAX_RF_PATH_NUMS	MAX_RF_PATH


extern uint8_t mpdatarate[NumRates];

/* MP set force data rate base on the definition. */
typedef enum _MPT_RATE_INDEX
{
	/* CCK rate. */
	MPT_RATE_1M,	/* 0 */
	MPT_RATE_2M,
	MPT_RATE_55M,
	MPT_RATE_11M,	/* 3 */

	/* OFDM rate. */
	MPT_RATE_6M,	/* 4 */
	MPT_RATE_9M,
	MPT_RATE_12M,
	MPT_RATE_18M,
	MPT_RATE_24M,
	MPT_RATE_36M,
	MPT_RATE_48M,
	MPT_RATE_54M,	/* 11 */

	/* HT rate. */
	MPT_RATE_MCS0,	/* 12 */
	MPT_RATE_MCS1,
	MPT_RATE_MCS2,
	MPT_RATE_MCS3,
	MPT_RATE_MCS4,
	MPT_RATE_MCS5,
	MPT_RATE_MCS6,
	MPT_RATE_MCS7,	/* 19 */
	MPT_RATE_MCS8,
	MPT_RATE_MCS9,
	MPT_RATE_MCS10,
	MPT_RATE_MCS11,
	MPT_RATE_MCS12,
	MPT_RATE_MCS13,
	MPT_RATE_MCS14,
	MPT_RATE_MCS15,	/* 27 */
	MPT_RATE_LAST
}MPT_RATE_E, *PMPT_RATE_E;

#define MAX_TX_PWR_INDEX_N_MODE 64	// 0x3F

typedef enum _POWER_MODE_ {
	POWER_LOW = 0,
	POWER_NORMAL
}POWER_MODE;


#define RX_PKT_BROADCAST	1
#define RX_PKT_DEST_ADDR	2
#define RX_PKT_PHY_MATCH	3

#if 0
#define RPTMaxCount 0x000FFFFF;

// parameter 1 : BitMask
// 	bit 0  : OFDM PPDU
//	bit 1  : OFDM False Alarm
//	bit 2  : OFDM MPDU OK
//	bit 3  : OFDM MPDU Fail
//	bit 4  : CCK PPDU
//	bit 5  : CCK False Alarm
//	bit 6  : CCK MPDU ok
//	bit 7  : CCK MPDU fail
//	bit 8  : HT PPDU counter
//	bit 9  : HT false alarm
//	bit 10 : HT MPDU total
//	bit 11 : HT MPDU OK
//	bit 12 : HT MPDU fail
//	bit 15 : RX full drop
typedef enum _RXPHY_BITMASK_
{
	OFDM_PPDU_BIT = 0,
	OFDM_FALSE_BIT,
	OFDM_MPDU_OK_BIT,
	OFDM_MPDU_FAIL_BIT,
	CCK_PPDU_BIT,
	CCK_FALSE_BIT,
	CCK_MPDU_OK_BIT,
	CCK_MPDU_FAIL_BIT,
	HT_PPDU_BIT,
	HT_FALSE_BIT,
	HT_MPDU_BIT,
	HT_MPDU_OK_BIT,
	HT_MPDU_FAIL_BIT,
} RXPHY_BITMASK;
#endif

typedef enum _ENCRY_CTRL_STATE_ {
	HW_CONTROL,		//hw encryption& decryption
	SW_CONTROL,		//sw encryption& decryption
	HW_ENCRY_SW_DECRY,	//hw encryption & sw decryption
	SW_ENCRY_HW_DECRY	//sw encryption & hw decryption
}ENCRY_CTRL_STATE;

typedef enum _PREAMBLE {
		Long_Preamble	= 0x01,
		Short_Preamble		  ,
		Long_GI 			  ,
		Short_GI
} PREAMBLE;



//=======================================================================
//extern struct mp_xmit_frame *alloc_mp_xmitframe(struct mp_priv *pmp_priv);
//extern int free_mp_xmitframe(struct xmit_priv *pxmitpriv, struct mp_xmit_frame *pmp_xmitframe);

extern int32_t init_mp_priv(_adapter * padapter);
extern void free_mp_priv(struct mp_priv *pmp_priv);
extern int32_t MPT_InitializeAdapter(_adapter * padapter, uint8_t Channel);
extern void MPT_DeInitAdapter(_adapter * padapter);
extern int32_t mp_start_test(_adapter * padapter);
extern void mp_stop_test(_adapter * padapter);

//=======================================================================
//extern void	IQCalibrateBcut(_adapter * pAdapter);

//extern uint32_t	bb_reg_read(_adapter * Adapter, uint16_t offset);
//extern uint8_t	bb_reg_write(_adapter * Adapter, uint16_t offset, uint32_t value);
//extern uint32_t	rf_reg_read(_adapter * Adapter, uint8_t path, uint8_t offset);
//extern uint8_t	rf_reg_write(_adapter * Adapter, uint8_t path, uint8_t offset, uint32_t value);

//extern uint32_t	get_bb_reg(_adapter * Adapter, uint16_t offset, uint32_t bitmask);
//extern uint8_t	set_bb_reg(_adapter * Adapter, uint16_t offset, uint32_t bitmask, uint32_t value);
//extern uint32_t	get_rf_reg(_adapter * Adapter, uint8_t path, uint8_t offset, uint32_t bitmask);
//extern uint8_t	set_rf_reg(_adapter * Adapter, uint8_t path, uint8_t offset, uint32_t bitmask, uint32_t value);

extern uint32_t _read_rfreg(_adapter * padapter, uint8_t rfpath, uint32_t addr, uint32_t bitmask);
extern void _write_rfreg(_adapter * padapter, uint8_t rfpath, uint32_t addr, uint32_t bitmask, uint32_t val);

extern uint32_t read_macreg(_adapter *padapter, uint32_t addr, uint32_t sz);
extern void write_macreg(_adapter *padapter, uint32_t addr, uint32_t val, uint32_t sz);
extern uint32_t read_bbreg(_adapter *padapter, uint32_t addr, uint32_t bitmask);
extern void write_bbreg(_adapter *padapter, uint32_t addr, uint32_t bitmask, uint32_t val);
extern uint32_t read_rfreg(_adapter * padapter, uint8_t rfpath, uint32_t addr);
extern void write_rfreg(_adapter * padapter, uint8_t rfpath, uint32_t addr, uint32_t val);

extern void	SetChannel(_adapter * pAdapter);
extern void	SetBandwidth(_adapter * pAdapter);
extern void	SetTxPower(_adapter * pAdapter);
extern void	SetAntennaPathPower(_adapter * pAdapter);
//extern void	SetTxAGCOffset(_adapter * pAdapter, uint32_t ulTxAGCOffset);
extern void	SetDataRate(_adapter * pAdapter);

extern void	SetAntenna(_adapter * pAdapter);

//extern void	SetCrystalCap(_adapter * pAdapter);

extern int32_t	SetThermalMeter(_adapter * pAdapter, uint8_t target_ther);
extern void	GetThermalMeter(_adapter * pAdapter, uint8_t *value);

extern void	SetContinuousTx(_adapter * pAdapter, uint8_t bStart);
extern void	SetSingleCarrierTx(_adapter * pAdapter, uint8_t bStart);
extern void	SetSingleToneTx(_adapter * pAdapter, uint8_t bStart);
extern void	SetCarrierSuppressionTx(_adapter * pAdapter, uint8_t bStart);
extern void PhySetTxPowerLevel(_adapter * pAdapter);

extern void	fill_txdesc_for_mp(_adapter * padapter, struct tx_desc *ptxdesc);
extern void	SetPacketTx(_adapter * padapter);
extern void	SetPacketRx(_adapter * pAdapter, uint8_t bStartRx);

extern void	ResetPhyRxPktCount(_adapter * pAdapter);
extern uint32_t	GetPhyRxPktReceived(_adapter * pAdapter);
extern uint32_t	GetPhyRxPktCRC32Error(_adapter * pAdapter);

extern int32_t	SetPowerTracking(_adapter * padapter, uint8_t enable);
extern void	GetPowerTracking(_adapter * padapter, uint8_t *enable);

extern uint32_t	mp_query_psd(_adapter * pAdapter, uint8_t *data);


extern void Hal_SetAntenna(_adapter * pAdapter);
extern void Hal_SetBandwidth(_adapter * pAdapter);

extern void Hal_SetTxPower(_adapter * pAdapter);
extern void Hal_SetCarrierSuppressionTx(_adapter * pAdapter, uint8_t bStart);
extern void Hal_SetSingleToneTx ( _adapter * pAdapter , uint8_t bStart );
extern void Hal_SetSingleCarrierTx (_adapter * pAdapter, uint8_t bStart);
extern void Hal_SetContinuousTx (_adapter * pAdapter, uint8_t bStart);
extern void Hal_SetBandwidth(_adapter * pAdapter);

extern void Hal_SetDataRate(_adapter * pAdapter);
extern void Hal_SetChannel(_adapter * pAdapter);
extern void Hal_SetAntennaPathPower(_adapter * pAdapter);
extern int32_t Hal_SetThermalMeter(_adapter * pAdapter, uint8_t target_ther);
extern int32_t Hal_SetPowerTracking(_adapter * padapter, uint8_t enable);
extern void Hal_GetPowerTracking(_adapter * padapter, uint8_t * enable);
extern void Hal_GetThermalMeter(_adapter * pAdapter, uint8_t *value);
extern void Hal_mpt_SwitchRfSetting(_adapter * pAdapter);
extern void Hal_MPT_CCKTxPowerAdjust(_adapter * Adapter);
extern void Hal_MPT_CCKTxPowerAdjustbyIndex(_adapter * pAdapter, BOOLEAN beven);
extern void Hal_SetCCKTxPower(_adapter * pAdapter, uint8_t * TxPower);
extern void Hal_SetOFDMTxPower(_adapter * pAdapter, uint8_t * TxPower);
extern void Hal_TriggerRFThermalMeter(_adapter * pAdapter);
extern uint8_t Hal_ReadRFThermalMeter(_adapter * pAdapter);
extern void Hal_SetCCKContinuousTx(_adapter * pAdapter, uint8_t bStart);
extern void Hal_SetOFDMContinuousTx(_adapter * pAdapter, uint8_t bStart);
extern void Hal_ProSetCrystalCap (_adapter * pAdapter , uint32_t CrystalCapVal);
extern void _rtw_mp_xmit_priv(struct xmit_priv *pxmitpriv);
extern void MP_PHY_SetRFPathSwitch(_adapter * pAdapter ,BOOLEAN bMain);
extern uint32_t mpt_ProQueryCalTxPower(_adapter * pAdapter, uint8_t RfPath);
extern void MPT_PwrCtlDM(PADAPTER padapter, uint32_t bstart);

#endif //_RTW_MP_H_

