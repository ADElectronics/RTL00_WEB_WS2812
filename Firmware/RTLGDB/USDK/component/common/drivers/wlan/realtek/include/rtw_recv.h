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
#ifndef _RTW_RECV_H_
#define _RTW_RECV_H_
#include <hal_pg.h>

#if defined(PLATFORM_ECOS)
#define NR_RECVFRAME 16	//Decrease recv frame due to memory limitation - Alex Fang
#elif defined(PLATFORM_FREERTOS) || defined (PLATFORM_CMSIS_RTOS)
#ifdef CONFIG_RECV_REORDERING_CTRL
#define NR_RECVFRAME 16	//Increase recv frame due to rx reorder - Andy Sun
#else
#if WIFI_LOGO_CERTIFICATION
    #define NR_RECVFRAME 8	//Decrease recv frame due to memory limitation - Alex Fang
#else
#ifndef CONFIG_HIGH_TP
    #define NR_RECVFRAME 2	//Decrease recv frame due to memory limitation - YangJue
#else
    #define NR_RECVFRAME 256
#endif
#endif
#endif
#else
#define NR_RECVFRAME 256
#endif

#ifdef PLATFORM_OS_XP
	#define NR_RECVBUFF (16)
#elif defined(PLATFORM_OS_CE)
	#define NR_RECVBUFF (4)
#elif defined(PLATFORM_FREERTOS) || defined (PLATFORM_CMSIS_RTOS)
#ifndef CONFIG_HIGH_TP
//	#define NR_RECVBUFF (8)	//Decrease recv buffer due to memory limitation - Alex Fang
	#define NR_RECVBUFF (1)	//Decrease recv buffer due to memory limitation - YangJue
#else
	#define NR_RECVBUFF (32)
#endif
#else
	#if (defined CONFIG_GSPI_HCI || defined CONFIG_SDIO_HCI)
		#define NR_RECVBUFF (32)
	#else
		#define NR_RECVBUFF (4)
	#endif

	#define NR_PREALLOC_RECV_SKB (8)
#endif

#define RECV_BULK_IN_ADDR		0x80
#define RECV_INT_IN_ADDR		0x81

#define PHY_RSSI_SLID_WIN_MAX			100
#define PHY_LINKQUALITY_SLID_WIN_MAX		20

// Rx smooth factor
#define Rx_Smooth_Factor (20)

#define RXFRAME_ALIGN	8
#define RXFRAME_ALIGN_SZ	(1<<RXFRAME_ALIGN)

#define DRVINFO_SZ	4 // unit is 8bytes

#define MAX_RXFRAME_CNT	512
#define MAX_RX_NUMBLKS		(32)
#define RECVFRAME_HDR_ALIGN 128

#define SNAP_SIZE sizeof(struct ieee80211_snap_hdr)

#define RX_MPDU_QUEUE				0
#define RX_CMD_QUEUE				1
#define RX_MAX_QUEUE				2

#define MAX_SUBFRAME_COUNT	64

//for Rx reordering buffer control
struct recv_reorder_ctrl
{
	_adapter	*padapter;
	uint8_t enable;
	uint16_t indicate_seq;//=wstart_b, init_value=0xffff
	uint16_t wend_b;
	uint8_t wsize_b;
	_queue pending_recvframe_queue;
	_timer reordering_ctrl_timer;
};

struct	stainfo_rxcache	{
	uint16_t 	tid_rxseq[16];
/*
	unsigned short 	tid0_rxseq;
	unsigned short 	tid1_rxseq;
	unsigned short 	tid2_rxseq;
	unsigned short 	tid3_rxseq;
	unsigned short 	tid4_rxseq;
	unsigned short 	tid5_rxseq;
	unsigned short 	tid6_rxseq;
	unsigned short 	tid7_rxseq;
	unsigned short 	tid8_rxseq;
	unsigned short 	tid9_rxseq;
	unsigned short 	tid10_rxseq;
	unsigned short 	tid11_rxseq;
	unsigned short 	tid12_rxseq;
	unsigned short 	tid13_rxseq;
	unsigned short 	tid14_rxseq;
	unsigned short 	tid15_rxseq;
*/
};

struct smooth_rssi_data {
	uint32_t	elements[100];	//array to store values
	uint32_t	index;			//index to current array to store
	uint32_t	total_num;		//num of valid elements
	uint32_t	total_val;		//sum of valid elements
};

struct signal_stat {
	uint8_t	update_req;		//used to indicate 
	uint8_t	avg_val;		//avg of valid elements
	uint32_t	total_num;		//num of valid elements
	uint32_t	total_val;		//sum of valid elements	
};


#if (RTL8195A_SUPPORT==1)
/* struct phy_info must be same with ODM ODM_PHY_INFO_T, see rtl8195a_query_rx_phy_status() */
struct phy_info
{
	uint8_t		RxPWDBAll;
	uint8_t		SignalQuality;	 						// in 0-100 index. 
	uint8_t		RxMIMOSignalStrength[MAX_RF_PATH];		// in 0~100 index
	int8_t		RecvSignalPower;						// Real power in dBm for this packet, no beautification and aggregation. Keep this raw info to be used for the other procedures.
	uint8_t		SignalStrength; 						// in 0-100 index.
	#if ((RTL8195A_SUPPORT == 0) && (RTL8711B_SUPPORT == 0))
		int8_t		RxMIMOSignalQuality[MAX_RF_PATH];	// per-path's EVM
		int8_t		RxPower;							// in dBm Translate from PWdB
		uint8_t		BTRxRSSIPercentage; 
		int8_t		RxPwr[MAX_RF_PATH];				// per-path's pwdb
		uint8_t		RxSNR[MAX_RF_PATH];				// per-path's SNR	
		uint8_t		btCoexPwrAdjust;
	#endif
	#if (ODM_IC_11AC_SERIES_SUPPORT)
		uint8_t		RxMIMOEVMdbm[MAX_RF_PATH];		// per-path's EVM dbm
		int16_t		Cfo_short[MAX_RF_PATH]; 		// per-path's Cfo_short
		int16_t		Cfo_tail[MAX_RF_PATH];			// per-path's Cfo_tail
		uint8_t		BandWidth;
	#endif
};
#elif(RTL8188F_SUPPORT == 1)
struct phy_info
{
	uint8_t		RxPWDBAll;

	uint8_t		SignalQuality;	 // in 0-100 index.
	int8_t		RxMIMOSignalQuality[MAX_RF_PATH];	//per-path's EVM
	uint8_t		RxMIMOEVMdbm[MAX_RF_PATH]; 		//per-path's EVM dbm
	uint8_t		RxMIMOSignalStrength[MAX_RF_PATH];// in 0~100 index
	uint16_t		Cfo_short[MAX_RF_PATH]; 			// per-path's Cfo_short
	uint16_t		Cfo_tail[MAX_RF_PATH];			// per-path's Cfo_tail

	int8_t		RxPower; // in dBm Translate from PWdB
	int8_t		RecvSignalPower;// Real power in dBm for this packet, no beautification and aggregation. Keep this raw info to be used for the other procedures.
	uint8_t		BTRxRSSIPercentage;
	uint8_t		SignalStrength; // in 0-100 index.
	int8_t		RxPwr[MAX_RF_PATH];				//per-path's pwdb
	uint8_t		RxSNR[MAX_RF_PATH];				//per-path's SNR
	uint8_t		BandWidth;
	uint8_t		btCoexPwrAdjust;
};
#elif(RTL8711B_SUPPORT == 1)
struct phy_info
{
	uint8_t		RxPWDBAll;
	
	uint8_t		SignalQuality;				/* in 0-100 index. */
	int8_t		RxMIMOSignalQuality[4];		/* per-path's EVM */
	uint8_t		RxMIMOEVMdbm[4];			/* per-path's EVM dbm */
	uint8_t		RxMIMOSignalStrength[4];	/* in 0~100 index */
	int16_t		Cfo_short[4];				/* per-path's Cfo_short */
	int16_t		Cfo_tail[4];					/* per-path's Cfo_tail */
	int8_t		RxPower;					/* in dBm Translate from PWdB */
	int8_t		RecvSignalPower;			/* Real power in dBm for this packet, no beautification and aggregation. Keep this raw info to be used for the other procedures. */
	uint8_t		BTRxRSSIPercentage;
	uint8_t		SignalStrength;				/* in 0-100 index. */
	int8_t		RxPwr[4];					/* per-path's pwdb */
	int8_t		RxSNR[4];					/* per-path's SNR	*/
	uint8_t		RxCount:2;					/* RX path counter---*/
	uint8_t		BandWidth:2;
	uint8_t		rxsc:4;						/* sub-channel---*/
	uint8_t		btCoexPwrAdjust;
	uint8_t		channel;						/* channel number---*/
	uint8_t		bMuPacket;					/* is MU packet or not---*/
	uint8_t		bBeamformed;				/* BF packet---*/
};
#else
#define MAX_PATH_NUM_92CS		2
struct phy_info //ODM_PHY_INFO_T
{	
	uint8_t		RxPWDBAll;	
	uint8_t		SignalQuality;	 // in 0-100 index. 
	uint8_t		RxMIMOSignalQuality[MAX_PATH_NUM_92CS]; //EVM
	uint8_t		RxMIMOSignalStrength[MAX_PATH_NUM_92CS];// in 0~100 index
	int8_t		RxPower; // in dBm Translate from PWdB
	int8_t		RecvSignalPower;// Real power in dBm for this packet, no beautification and aggregation. Keep this raw info to be used for the other procedures.
	uint8_t		BTRxRSSIPercentage;	
	uint8_t		SignalStrength; // in 0-100 index.
	uint8_t		RxPwr[MAX_PATH_NUM_92CS];//per-path's pwdb
	uint8_t		RxSNR[MAX_PATH_NUM_92CS];//per-path's SNR
};
#endif

struct rx_pkt_attrib	{
	uint16_t	pkt_len;
	uint8_t	physt;
	uint8_t	drvinfo_sz;
	uint8_t	shift_sz;
	uint8_t	hdrlen; //the WLAN Header Len
	uint8_t 	to_fr_ds;
	uint8_t 	amsdu;
	uint8_t	qos;
	uint8_t	priority;
	uint8_t	pw_save;
	uint8_t	mdata;
	uint16_t	seq_num;
	uint8_t	frag_num;
	uint8_t	mfrag;
	uint8_t	order;
	uint8_t	privacy; //in frame_ctrl field
	uint8_t	bdecrypted;
	uint8_t	encrypt; //when 0 indicate no encrypt. when non-zero, indicate the encrypt algorith
	uint8_t	iv_len;
	uint8_t	icv_len;
	uint8_t	crc_err;
	uint8_t	icv_err;

	uint16_t eth_type;

	uint8_t 	dst[ETH_ALEN];
	uint8_t 	src[ETH_ALEN];
	uint8_t 	ta[ETH_ALEN];
	uint8_t 	ra[ETH_ALEN];
	uint8_t 	bssid[ETH_ALEN];
	
	uint8_t ack_policy;
	
//#ifdef CONFIG_TCP_CSUM_OFFLOAD_RX
	uint8_t	tcpchk_valid; // 0: invalid, 1: valid
	uint8_t	ip_chkrpt; //0: incorrect, 1: correct
	uint8_t	tcp_chkrpt; //0: incorrect, 1: correct
//#endif
	uint8_t 	key_index;

	uint8_t	mcs_rate;
	uint8_t	rxht;
	uint8_t 	sgi;
	uint8_t 	pkt_rpt_type;
	uint32_t	MacIDValidEntry[2];	// 64 bits present 64 entry.


	uint8_t   data_rate;
/*
	uint8_t	signal_qual;
	int8_t	rx_mimo_signal_qual[2];
	uint8_t	signal_strength;
	uint32_t	RxPWDBAll;	
	int32_t	RecvSignalPower;
*/
	struct phy_info phy_info;	
};

//These definition is used for Rx packet reordering.
#define SN_LESS(a, b)		(((a-b)&0x800)!=0)
#define SN_EQUAL(a, b)	(a == b)
//#define REORDER_WIN_SIZE	128
//#define REORDER_ENTRY_NUM	128
#define REORDER_WAIT_TIME	(30) // (ms)

#define RECVBUFF_ALIGN_SZ 8

#define RXDESC_SIZE	24
#define RXDESC_OFFSET RXDESC_SIZE

struct recv_stat
{
	unsigned int rxdw0;

	unsigned int rxdw1;

	unsigned int rxdw2;

	unsigned int rxdw3;

	unsigned int rxdw4;

	unsigned int rxdw5;

#ifdef CONFIG_PCI_HCI
	unsigned int rxdw6;

	unsigned int rxdw7;
#endif
};


struct recv_buf_stat {
	unsigned int rxdw0;

	unsigned int rxdw1;
};

#define EOR BIT(30)

#if defined(CONFIG_LX_HCI)
#define LX_MAX_RX_QUEUE		1// MSDU packet queue, Rx Command Queue
#define LX_MAX_RX_COUNT		4//RX_Q_DESC_NUM// 128

struct rtw_rx_ring {
#if ((RTL8195A_SUPPORT ==1) ||(RTL8711B_SUPPORT == 1))
	struct recv_buf_stat	*desc;
#else
	struct recv_stat	*desc;
#endif

	dma_addr_t		dma;
	unsigned int		idx;
	struct sk_buff	*rx_buf[LX_MAX_RX_COUNT];
};
#endif


/*
accesser of recv_priv: rtw_recv_entry(dispatch / passive level); recv_thread(passive) ; returnpkt(dispatch)
; halt(passive) ;

using enter_critical section to protect
*/
struct recv_priv
{
	_lock	lock;

	//_queue	blk_strms[MAX_RX_NUMBLKS];    // keeping the block ack frame until return ack
	_queue	free_recv_queue;
	_queue	recv_pending_queue;
	_queue	uc_swdec_pending_queue;


	uint8_t *pallocated_frame_buf;
	uint8_t *precv_frame_buf;

	uint free_recvframe_cnt;

	_adapter	*adapter;

#ifdef PLATFORM_WINDOWS
	_nic_hdl  RxPktPoolHdl;
	_nic_hdl  RxBufPoolHdl;

#ifdef PLATFORM_OS_XP
	PMDL	pbytecnt_mdl;
#endif
	uint	counter; //record the number that up-layer will return to drv; only when counter==0 can we  release recv_priv
	NDIS_EVENT 	recv_resource_evt ;
#endif

	uint32_t	bIsAnyNonBEPkts;
	uint64_t	rx_bytes;
	uint64_t	rx_pkts;
	uint64_t	rx_drop;
	uint64_t rx_overflow;
	uint64_t	last_rx_bytes;

	uint  rx_icv_err;
	uint  rx_largepacket_crcerr;
	uint  rx_smallpacket_crcerr;
	uint  rx_middlepacket_crcerr;

#ifdef CONFIG_USB_HCI
	//uint8_t *pallocated_urb_buf;
	_sema allrxreturnevt;
	uint	ff_hwaddr;
	uint8_t	rx_pending_cnt;

#ifdef CONFIG_USB_INTERRUPT_IN_PIPE
#ifdef PLATFORM_LINUX
	PURB	int_in_urb;
#endif

	uint8_t	*int_in_buf;
#endif //CONFIG_USB_INTERRUPT_IN_PIPE

#endif
#if defined(PLATFORM_LINUX) || defined(PLATFORM_FREEBSD)
#ifdef PLATFORM_FREEBSD
	struct task irq_prepare_beacon_tasklet;
	struct task recv_tasklet;
#else //PLATFORM_FREEBSD
	struct tasklet_struct irq_prepare_beacon_tasklet;
	struct tasklet_struct recv_tasklet;
#endif //PLATFORM_FREEBSD
	struct sk_buff_head free_recv_skb_queue;
	struct sk_buff_head rx_skb_queue;
#ifdef CONFIG_RX_INDICATE_QUEUE
	struct task rx_indicate_tasklet;
	struct ifqueue rx_indicate_queue;
#endif	// CONFIG_RX_INDICATE_QUEUE

#ifdef CONFIG_USE_USB_BUFFER_ALLOC_RX
	_queue	recv_buf_pending_queue;
#endif	// CONFIG_USE_USB_BUFFER_ALLOC_RX
#endif //defined(PLATFORM_LINUX) || defined(PLATFORM_FREEBSD)

	uint8_t *pallocated_recv_buf;
	uint8_t *precv_buf;    // 4 alignment
	_queue	free_recv_buf_queue;
	uint32_t	free_recv_buf_queue_cnt;

#if defined(CONFIG_SDIO_HCI) || defined(CONFIG_GSPI_HCI)
	_queue	recv_buf_pending_queue;
#endif

#if defined(CONFIG_PCI_HCI) || defined(CONFIG_LX_HCI)
	// Rx
	struct rtw_rx_ring	rx_ring[LX_MAX_RX_QUEUE];
	int 	rxringcount;
	uint16_t	rxbuffersize;
#endif

	//For display the phy informatiom
	uint8_t is_signal_dbg;	// for debug
	uint8_t signal_strength_dbg;	// for debug
	int8_t rssi;
	int8_t rxpwdb;
	uint8_t signal_strength;
	uint8_t signal_qual;
	uint8_t noise;
	int RxSNRdB[2];
	int8_t RxRssi[2];
	int FalseAlmCnt_all;

#ifdef CONFIG_NEW_SIGNAL_STAT_PROCESS
	_timer signal_stat_timer;
	uint32_t signal_stat_sampling_interval;
	//uint32_t signal_stat_converging_constant;
	struct signal_stat signal_qual_data;
	struct signal_stat signal_strength_data;
#else //CONFIG_NEW_SIGNAL_STAT_PROCESS
	struct smooth_rssi_data signal_qual_data;
	struct smooth_rssi_data signal_strength_data;
#endif //CONFIG_NEW_SIGNAL_STAT_PROCESS

#ifdef CONFIG_PROMISC
	uint8_t promisc_enabled;
	uint8_t promisc_len_used;
	_list promisc_list;
	_lock promisc_lock;
	uint32_t promisc_bk_rcr;
	uint16_t promisc_bk_rxfltmap2;
	uint8_t promisc_mgntframe_enabled;
#endif
};

#ifdef CONFIG_NEW_SIGNAL_STAT_PROCESS
#define rtw_set_signal_stat_timer(recvpriv) rtw_set_timer(&(recvpriv)->signal_stat_timer, (recvpriv)->signal_stat_sampling_interval)
#endif //CONFIG_NEW_SIGNAL_STAT_PROCESS

struct sta_recv_priv {

	_lock	lock;
	sint	option;

	//_queue	blk_strms[MAX_RX_NUMBLKS];
	_queue defrag_q;	 //keeping the fragment frame until defrag

	struct	stainfo_rxcache rxcache;

	//uint	sta_rx_bytes;
	//uint	sta_rx_pkts;
	//uint	sta_rx_fail;

};

struct recv_buf
{
	_list list;

//	_lock recvbuf_lock;

//	uint32_t	ref_cnt;

	PADAPTER adapter;

//	uint8_t	*pbuf;
//	uint8_t	*pallocated_buf;

	uint32_t	len;
	uint8_t	*phead;
	uint8_t	*pdata;
	uint8_t	*ptail;
	uint8_t	*pend;

#ifdef CONFIG_USB_HCI

	#if defined(PLATFORM_OS_XP)||defined(PLATFORM_LINUX)||defined(PLATFORM_FREEBSD)
	PURB	purb;
	dma_addr_t dma_transfer_addr;	/* (in) dma addr for transfer_buffer */
	uint32_t alloc_sz;
	#endif

	#ifdef PLATFORM_OS_XP
	PIRP		pirp;
	#endif

	#ifdef PLATFORM_OS_CE
	USB_TRANSFER	usb_transfer_read_port;
	#endif

	uint8_t  irp_pending;
	int  transfer_len;

#endif

#if defined(PLATFORM_LINUX) || defined(PLATFORM_ECOS) || defined(PLATFORM_FREERTOS) || defined (PLATFORM_CMSIS_RTOS)
	_pkt	*pskb;
//	uint8_t	reuse;
#endif
#ifdef PLATFORM_FREEBSD //skb solution
	struct sk_buff *pskb;
	uint8_t	reuse;
#endif //PLATFORM_FREEBSD //skb solution
};

/*
	head  ----->

		data  ----->

			payload

		tail  ----->


	end   ----->

	len = (unsigned int )(tail - data);

*/
struct recv_frame_hdr
{
	_list	list;
#ifndef CONFIG_BSD_RX_USE_MBUF
	struct sk_buff	 *pkt;
	struct sk_buff	 *pkt_newalloc;
#else // CONFIG_BSD_RX_USE_MBUF
	_pkt	*pkt;
	_pkt *pkt_newalloc;
#endif // CONFIG_BSD_RX_USE_MBUF

	_adapter  *adapter;

	uint8_t fragcnt;

	int frame_tag;

	struct rx_pkt_attrib attrib;

	uint  len;
	uint8_t *rx_head;
	uint8_t *rx_data;
	uint8_t *rx_tail;
	uint8_t *rx_end;

	void *precvbuf;


	//
	struct sta_info *psta;
#ifdef CONFIG_RECV_REORDERING_CTRL
	//for A-MPDU Rx reordering buffer control
	struct recv_reorder_ctrl *preorder_ctrl;
#endif
#ifdef CONFIG_WAPI_SUPPORT
	uint8_t UserPriority;
	uint8_t WapiTempPN[16];
	uint8_t WapiSrcAddr[6];
	uint8_t bWapiCheckPNInDecrypt;
	uint8_t bIsWaiPacket;
#endif

};

union recv_frame{

	union{
		_list list;
		struct recv_frame_hdr hdr;
		uint mem[RECVFRAME_HDR_ALIGN>>2];
	}u;

	//uint mem[MAX_RXSZ>>2];

};

typedef enum _RX_PACKET_TYPE{
	NORMAL_RX,//Normal rx packet
	TX_REPORT1,//CCX
	TX_REPORT2,//TX RPT
	HIS_REPORT,// USB HISR RPT
	C2H_PACKET
}RX_PACKET_TYPE, *PRX_PACKET_TYPE;

extern union recv_frame *_rtw_alloc_recvframe (_queue *pfree_recv_queue);  //get a free recv_frame from pfree_recv_queue
extern void rtw_init_recvframe(union recv_frame *precvframe ,struct recv_priv *precvpriv);
extern int	 rtw_free_recvframe(union recv_frame *precvframe, _queue *pfree_recv_queue);

#define rtw_dequeue_recvframe(queue) rtw_alloc_recvframe(queue)
extern int _rtw_enqueue_recvframe(union recv_frame *precvframe, _queue *queue);

#ifdef CONFIG_TRACE_SKB
int __rtw_enqueue_recvframe(union recv_frame *precvframe, _queue *queue);
union recv_frame *__rtw_alloc_recvframe (_queue *pfree_recv_queue);  //get a free recv_frame from pfree_recv_queue

#define rtw_enqueue_recvframe(precvframe, queue, Q) \
	do{\
		set_skb_list_flag(precvframe->u.hdr.pkt, SKBLIST_RECVFRAME_##Q);\
		__rtw_enqueue_recvframe(precvframe, queue);\
	}while (0)
#define rtw_alloc_recvframe(queue, precvframe, Q) \
	(\
		precvframe = __rtw_alloc_recvframe(queue),\
		precvframe ? clear_skb_list_flag(precvframe->u.hdr.pkt, SKBLIST_RECVFRAME_##Q):0,\
		precvframe\
	)
#else
extern int rtw_enqueue_recvframe(union recv_frame *precvframe, _queue *queue);
extern union recv_frame *rtw_alloc_recvframe (_queue *pfree_recv_queue);  //get a free recv_frame from pfree_recv_queue
#endif

extern void rtw_free_recvframe_queue(_queue *pframequeue,  _queue *pfree_recv_queue);
uint32_t rtw_free_uc_swdec_pending_queue(_adapter *adapter);

#ifdef CONFIG_TRACE_SKB
sint _rtw_enqueue_recvbuf_to_head(struct recv_buf *precvbuf, _queue *queue);
sint _rtw_enqueue_recvbuf(struct recv_buf *precvbuf, _queue *queue);
struct recv_buf *_rtw_dequeue_recvbuf (_queue *queue);

#define rtw_enqueue_recvbuf_to_head(precvbuf, queue, Q) \
	do{\
		set_skb_list_flag(precvbuf->pskb, SKBLIST_RECVBUF_##Q);\
		_rtw_enqueue_recvbuf_to_head(precvbuf, queue);\
	}while (0)
#define rtw_enqueue_recvbuf(precvbuf, queue, Q) \
	do{\
		set_skb_list_flag(precvbuf->pskb, SKBLIST_RECVBUF_##Q);\
		_rtw_enqueue_recvbuf(precvbuf, queue);\
	}while (0)
#define rtw_dequeue_recvbuf(queue, precvbuf, Q) \
	(\
		precvbuf = _rtw_dequeue_recvbuf(queue),\
		precvbuf ? clear_skb_list_flag(precvbuf->pskb, SKBLIST_RECVBUF_##Q):0,\
		precvbuf\
	)

#else
sint rtw_enqueue_recvbuf_to_head(struct recv_buf *precvbuf, _queue *queue);
sint rtw_enqueue_recvbuf(struct recv_buf *precvbuf, _queue *queue);
struct recv_buf *rtw_dequeue_recvbuf (_queue *queue);
#endif

void rtw_reordering_ctrl_timeout_handler(void *pcontext);


__inline static uint8_t *get_rxmem(union recv_frame *precvframe)
{
	//always return rx_head...
	if(precvframe==NULL)
		return NULL;

	return precvframe->u.hdr.rx_head;
}

__inline static uint8_t *get_rx_status(union recv_frame *precvframe)
{

	return get_rxmem(precvframe);

}



__inline static uint8_t *get_recvframe_data(union recv_frame *precvframe)
{

	//alwasy return rx_data
	if(precvframe==NULL)
		return NULL;

	return precvframe->u.hdr.rx_data;

}

//TODO
#if 0

__inline static uint8_t *recvframe_push(union recv_frame *precvframe, sint sz)
{
	// append data before rx_data

	/* add data to the start of recv_frame
 *
 *      This function extends the used data area of the recv_frame at the buffer
 *      start. rx_data must be still larger than rx_head, after pushing.
 */

	if(precvframe==NULL)
		return NULL;


	precvframe->u.hdr.rx_data -= sz ;
	if( precvframe->u.hdr.rx_data < precvframe->u.hdr.rx_head )
	{
		precvframe->u.hdr.rx_data += sz ;
		return NULL;
	}

	precvframe->u.hdr.len +=sz;

	return precvframe->u.hdr.rx_data;

}

#endif	//#if 0

__inline static uint8_t *recvframe_pull(union recv_frame *precvframe, sint sz)
{
	// rx_data += sz; move rx_data sz bytes  hereafter

	//used for extract sz bytes from rx_data, update rx_data and return the updated rx_data to the caller


	if(precvframe==NULL)
		return NULL;


	precvframe->u.hdr.rx_data += sz;

	if(precvframe->u.hdr.rx_data > precvframe->u.hdr.rx_tail)
	{
		precvframe->u.hdr.rx_data -= sz;
		return NULL;
	}

	precvframe->u.hdr.len -=sz;

	return precvframe->u.hdr.rx_data;

}

__inline static uint8_t *recvframe_put(union recv_frame *precvframe, sint sz)
{
	// rx_tai += sz; move rx_tail sz bytes  hereafter

	//used for append sz bytes from ptr to rx_tail, update rx_tail and return the updated rx_tail to the caller
	//after putting, rx_tail must be still larger than rx_end. 	

	if(precvframe==NULL)
		return NULL;

	precvframe->u.hdr.rx_tail += sz;

	if(precvframe->u.hdr.rx_tail > precvframe->u.hdr.rx_end)
	{
		precvframe->u.hdr.rx_tail -= sz;
		return NULL;
	}

	precvframe->u.hdr.len +=sz;

	return precvframe->u.hdr.rx_tail;

}



__inline static uint8_t *recvframe_pull_tail(union recv_frame *precvframe, sint sz)
{
	// rmv data from rx_tail (by yitsen)

	//used for extract sz bytes from rx_end, update rx_end and return the updated rx_end to the caller
	//after pulling, rx_end must be still larger than rx_data.

	if(precvframe==NULL)
		return NULL;

	precvframe->u.hdr.rx_tail -= sz;

	if(precvframe->u.hdr.rx_tail < precvframe->u.hdr.rx_data)
	{
		precvframe->u.hdr.rx_tail += sz;
		return NULL;
	}

	precvframe->u.hdr.len -=sz;

	return precvframe->u.hdr.rx_tail;

}

__inline static _buffer * get_rxbuf_desc(union recv_frame *precvframe)
{
	_buffer * buf_desc = NULL;

	if(precvframe==NULL)
		return NULL;
#ifdef PLATFORM_WINDOWS
	NdisQueryPacket(precvframe->u.hdr.pkt, NULL, NULL, &buf_desc, NULL);
#endif

	return buf_desc;
}


__inline static union recv_frame *rxmem_to_recvframe(uint8_t *rxmem)
{
	//due to the design of 2048 bytes alignment of recv_frame, we can reference the union recv_frame
	//from any given member of recv_frame.
	// rxmem indicates the any member/address in recv_frame

	return (union recv_frame*)(((SIZE_PTR)rxmem >> RXFRAME_ALIGN) << RXFRAME_ALIGN);

}

__inline static union recv_frame *pkt_to_recvframe(_pkt *pkt)
{
	(void) pkt;
	uint8_t * buf_star = NULL;
	union recv_frame * precv_frame = NULL;
#ifdef PLATFORM_WINDOWS
	_buffer * buf_desc;
	uint len;

	NdisQueryPacket(pkt, NULL, NULL, &buf_desc, &len);
	NdisQueryBufferSafe(buf_desc, &buf_star, &len, HighPagePriority);
#endif
	precv_frame = rxmem_to_recvframe((unsigned char*)buf_star);

	return precv_frame;
}

__inline static uint8_t *pkt_to_recvmem(_pkt *pkt)
{
	// return the rx_head

	union recv_frame * precv_frame = pkt_to_recvframe(pkt);

	return 	precv_frame->u.hdr.rx_head;

}

__inline static uint8_t *pkt_to_recvdata(_pkt *pkt)
{
	// return the rx_data

	union recv_frame * precv_frame =pkt_to_recvframe(pkt);

	return 	precv_frame->u.hdr.rx_data;

}


__inline static sint get_recvframe_len(union recv_frame *precvframe)
{
	return precvframe->u.hdr.len;
}


__inline static int32_t translate_percentage_to_dbm(uint32_t SignalStrengthIndex)
{
	int32_t	SignalPower; // in dBm.

#ifndef CONFIG_SKIP_SIGNAL_SCALE_MAPPING
	// Translate to dBm (x=0.9y-95).
	SignalPower = (int32_t)((SignalStrengthIndex *18) /20); 
	SignalPower -= 95; 
#else
	/* Translate to dBm (x=y-100) */
	SignalPower = SignalStrengthIndex - 100;
#endif

	return SignalPower;
}


struct sta_info;

extern void _rtw_init_sta_recv_priv(struct sta_recv_priv *psta_recvpriv);
extern void  mgt_dispatcher(_adapter *padapter, union recv_frame *precv_frame);
int process_recv_indicatepkts(_adapter *padapter, union recv_frame *prframe);

void rtw_rxhandler(_adapter * padapter, struct recv_buf *precvbuf);
uint32_t rtw_free_buf_pending_queue(_adapter *adapter);

#endif

