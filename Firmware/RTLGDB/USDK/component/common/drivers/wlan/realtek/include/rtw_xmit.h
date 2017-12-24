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
#ifndef _RTW_XMIT_H_
#define _RTW_XMIT_H_

/*---------------------------------------
  Define MAX_XMITBUF_SZ
---------------------------------------*/
#if defined(CONFIG_SDIO_HCI) || defined(CONFIG_GSPI_HCI) || defined(CONFIG_LX_HCI)

#ifdef CONFIG_TX_AGGREGATION	//effect only for SDIO and GSPI Interface
#define MAX_XMITBUF_SZ	(20480)	// 20k
#else
#if defined(PLATFORM_ECOS) || defined(PLATFORM_FREERTOS) || defined (PLATFORM_CMSIS_RTOS)

	#if defined(CONFIG_SDIO_HCI) || defined(CONFIG_GSPI_HCI)
		#define HAL_INTERFACE_OVERHEAD_XMIT_BUF 12	//HAL_INTERFACE_CMD (4) + HAL_INTERFACE_STATUS (8)
	#elif defined(CONFIG_LX_HCI)
		#define HAL_INTERFACE_OVERHEAD_XMIT_BUF 0
	#endif

// Consideration for MAX_XMITBUF_SZ size
// 	Check more detail information in MAX_SKB_BUF_SIZE	
//	Tx: [INTF_CMD][TX_DESC][WLAN_HDR][QoS][IV][SNAP][Data][MIC][ICV][INTF_STATUS]
//	HAL_INTERFACE_OVERHEAD: HAL_INTERFACE_CMD is 4/0 for SPI/PCIE, HAL_INTERFACE_STATUS is 8/0 for SPI/PCIE
//	WLAN_MAX_ETHFRM_LEN : May not be required because WLAN_HEADER +SNAP can totally 
//			cover ethernet header.Keep in only for safety.

#ifndef CONFIG_DONT_CARE_TP
#define MAX_XMITBUF_SZ		(HAL_INTERFACE_OVERHEAD_XMIT_BUF+\
							TXDESC_SIZE+\
							WLAN_MAX_PROTOCOL_OVERHEAD + WLAN_MAX_ETHFRM_LEN +\
							SKB_RESERVED_FOR_SAFETY)
#else
#define MAX_XMITBUF_SZ		(HAL_INTERFACE_OVERHEAD_XMIT_BUF+\
							TXDESC_SIZE+\
							WLAN_MAX_PROTOCOL_OVERHEAD + WLAN_MAX_TX_ETHFRM_LEN +\
							SKB_RESERVED_FOR_SAFETY)
#endif


#else // Other OS
#define MAX_XMITBUF_SZ (12288)  //12k 1536*8
#endif	//#ifdef PLATFORM_ECOS || defined(PLATFORM_FREERTOS)
#endif	//#ifdef CONFIG_TX_AGGREGATION

#elif defined(CONFIG_USB_HCI) || defined(CONFIG_PCI_HCI)
	#errof "Undefined bus interface for MAX_XMITBUF_SZ"
#endif	//interface define. SDIO/GSPI/LXbus/PCI/USB



/*--------------------------------------------------------------*/
/*  Define MAX_XMITBUF_SZ										*/
/*--------------------------------------------------------------*/
#if (defined CONFIG_GSPI_HCI || defined CONFIG_SDIO_HCI)

#if defined(PLATFORM_ECOS)
#define NR_XMITBUFF	(8)	
#elif defined(PLATFORM_FREERTOS) || defined (PLATFORM_CMSIS_RTOS)
#ifndef CONFIG_HIGH_TP
#define NR_XMITBUFF	(2)	//Decrease recv frame (8->2) due to memory limitation - YangJue
#else 
#define NR_XMITBUFF (128)
#endif
#else
#define NR_XMITBUFF	(128)
#endif	//#ifdef PLATFORM_ECOS

#elif defined(CONFIG_LX_HCI)
#define NR_XMITBUFF	(8)

#elif defined(CONFIG_USB_HCI) || defined(CONFIG_PCI_HCI)
	#errof "Undefined bus interface for MAX_XMITBUF_SZ"
#endif //interface define


/*--------------------------------------------------------------*/
/*  Define XMITBUF_ALIGN_SZ										*/
/*--------------------------------------------------------------*/
#if defined(PLATFORM_OS_CE) || defined(PLATFORM_ECOS) || defined(PLATFORM_FREERTOS) || defined(PLATFORM_CMSIS_RTOS)
#define XMITBUF_ALIGN_SZ 4
#else
#if defined(CONFIG_PCI_HCI) || defined(CONFIG_LX_HCI)
#define XMITBUF_ALIGN_SZ 4
#else
#define XMITBUF_ALIGN_SZ 512
#endif
#endif

#define MAX_CMDBUF_SZ	(5120)	//(4096)
/*--------------------------------------------------------------*/
/*  Define xmit extension buff, size/numbers							*/
/*--------------------------------------------------------------*/
#define MAX_XMIT_EXTBUF_SZ	(1536)

#if defined(PLATFORM_ECOS)
#define NR_XMIT_EXTBUFF		(16)	//Decrease ext xmit buffer due to memory limitation - Alex Fang
#elif defined(PLATFORM_FREERTOS) || defined (PLATFORM_CMSIS_RTOS)
#define NR_XMIT_EXTBUFF		(8)	//Decrease ext xmit buffer due to memory limitation - Alex Fang
#else
#define NR_XMIT_EXTBUFF		(32)
#endif	//#ifdef	PLATFORM_ECOS

#define MAX_NUMBLKS		(1)

#define XMIT_VO_QUEUE (0)
#define XMIT_VI_QUEUE (1)
#define XMIT_BE_QUEUE (2)
#define XMIT_BK_QUEUE (3)

#define VO_QUEUE_INX		0
#define VI_QUEUE_INX		1
#define BE_QUEUE_INX		2
#define BK_QUEUE_INX		3
#define BCN_QUEUE_INX		4
#define MGT_QUEUE_INX		5
#define HIGH_QUEUE_INX		6
#define TXCMD_QUEUE_INX		7
#ifdef CONFIG_WLAN_HAL_TEST
#define HIGH1_QUEUE_INX		8
#define HIGH2_QUEUE_INX		9
#define HIGH3_QUEUE_INX		10
#define HIGH4_QUEUE_INX		11
#define HIGH5_QUEUE_INX		12
#define HIGH6_QUEUE_INX		13
#define HIGH7_QUEUE_INX		14
#define HW_QUEUE_ENTRY		15
#else
#define HW_QUEUE_ENTRY		8
#endif

#define WEP_IV(pattrib_iv, dot11txpn, keyidx)\
do{\
	pattrib_iv[0] = dot11txpn._byte_.TSC0;\
	pattrib_iv[1] = dot11txpn._byte_.TSC1;\
	pattrib_iv[2] = dot11txpn._byte_.TSC2;\
	pattrib_iv[3] = ((keyidx & 0x3)<<6);\
	dot11txpn.val = (dot11txpn.val == 0xffffff) ? 0: (dot11txpn.val+1);\
}while(0)


#define TKIP_IV(pattrib_iv, dot11txpn, keyidx)\
do{\
	pattrib_iv[0] = dot11txpn._byte_.TSC1;\
	pattrib_iv[1] = (dot11txpn._byte_.TSC1 | 0x20) & 0x7f;\
	pattrib_iv[2] = dot11txpn._byte_.TSC0;\
	pattrib_iv[3] = BIT(5) | ((keyidx & 0x3)<<6);\
	pattrib_iv[4] = dot11txpn._byte_.TSC2;\
	pattrib_iv[5] = dot11txpn._byte_.TSC3;\
	pattrib_iv[6] = dot11txpn._byte_.TSC4;\
	pattrib_iv[7] = dot11txpn._byte_.TSC5;\
	dot11txpn.val = dot11txpn.val == 0xffffffffffffULL ? 0: (dot11txpn.val+1);\
}while(0)

#define AES_IV(pattrib_iv, dot11txpn, keyidx)\
do{\
	pattrib_iv[0] = dot11txpn._byte_.TSC0;\
	pattrib_iv[1] = dot11txpn._byte_.TSC1;\
	pattrib_iv[2] = 0;\
	pattrib_iv[3] = BIT(5) | ((keyidx & 0x3)<<6);\
	pattrib_iv[4] = dot11txpn._byte_.TSC2;\
	pattrib_iv[5] = dot11txpn._byte_.TSC3;\
	pattrib_iv[6] = dot11txpn._byte_.TSC4;\
	pattrib_iv[7] = dot11txpn._byte_.TSC5;\
	dot11txpn.val = dot11txpn.val == 0xffffffffffffULL ? 0: (dot11txpn.val+1);\
}while(0)


#define HWXMIT_ENTRY	4

#if  defined(CONFIG_RTL8812A) || defined(CONFIG_RTL8821A)|| defined(CONFIG_RTL8723B) || defined(CONFIG_RTL8195A) || defined(CONFIG_RTL8711B) ||defined(CONFIG_RTL8188F)
#define TXDESC_SIZE 40
#else
#define TXDESC_SIZE 32
#endif

#ifdef CONFIG_TX_EARLY_MODE
#define EARLY_MODE_INFO_SIZE	8
#endif

#if defined(CONFIG_SDIO_HCI) || defined(CONFIG_GSPI_HCI)
#define TXDESC_OFFSET TXDESC_SIZE

#endif

#ifdef CONFIG_USB_HCI
#define PACKET_OFFSET_SZ (8)
#define TXDESC_OFFSET (TXDESC_SIZE + PACKET_OFFSET_SZ)
#endif

#if defined(CONFIG_PCI_HCI) || defined(CONFIG_LX_HCI)
#if  defined(CONFIG_RTL8195A) || defined(CONFIG_RTL8711B)// buffer descriptor architecture
#define TXDESC_OFFSET TXDESC_SIZE
#else
#define TXDESC_OFFSET 0
#endif
#define TX_DESC_NEXT_DESC_OFFSET	40
#endif

#define TX_FRAGMENTATION_THRESHOLD 			2346

// Suppose (TX_DESC_MODE=1) ==> Segment number for each tx_buf_desc is 4. 2X4 = 8 (double words).
struct tx_buf_desc {	
	unsigned int txdw0;	
	unsigned int txdw1;	
	unsigned int txdw2;	
	unsigned int txdw3;	
	unsigned int txdw4;	
	unsigned int txdw5;	
	unsigned int txdw6;	
	unsigned int txdw7;
};

struct tx_desc{

	//DWORD 0
	unsigned int txdw0;

	unsigned int txdw1;

	unsigned int txdw2;

	unsigned int txdw3;

	unsigned int txdw4;

	unsigned int txdw5;

	unsigned int txdw6;

	unsigned int txdw7;
#ifdef CONFIG_PCI_HCI
	unsigned int txdw8;

	unsigned int txdw9;

	unsigned int txdw10;

	unsigned int txdw11;

	// 2008/05/15 MH Because PCIE HW memory R/W 4K limit. And now,  our descriptor
	// size is 40 bytes. If you use more than 102 descriptor( 103*40>4096), HW will execute
	// memoryR/W CRC error. And then all DMA fetch will fail. We must decrease descriptor
	// number or enlarge descriptor size as 64 bytes.
	unsigned int txdw12;

	unsigned int txdw13;

	unsigned int txdw14;

	unsigned int txdw15;
#endif
#if defined(CONFIG_LX_HCI)||defined(CONFIG_RTL8188F) 
    unsigned int txdw8;

    unsigned int txdw9;
#endif
};


union txdesc {
	struct tx_desc txdesc;
	unsigned int value[TXDESC_SIZE>>2];
};

#if defined(CONFIG_PCI_HCI) || defined(CONFIG_LX_HCI)
#ifdef CONFIG_WLAN_HAL_TEST    
#define PCI_MAX_TX_QUEUE_COUNT	 HW_QUEUE_ENTRY
#else
#define PCI_MAX_TX_QUEUE_COUNT	8
#endif

struct rtw_tx_ring {

#if ((RTL8195A_SUPPORT ==1) ||(RTL8711B_SUPPORT == 1))
	struct tx_buf_desc	*desc;
#else
	struct tx_desc	*desc;
#endif
	dma_addr_t		dma;
	unsigned int		idx;
	unsigned int		entries;
	_queue			queue;
	uint32_t				qlen;
};
#endif

struct	hw_xmit	{
	//_lock xmit_lock;
	//_list	pending;
	_queue *sta_queue;
	//struct hw_txqueue *phwtxqueue;
	//sint	txcmdcnt;
	int	accnt;
};

#if 0
struct pkt_attrib
{
	uint8_t	type;
	uint8_t	subtype;
	uint8_t	bswenc;
	uint8_t	dhcp_pkt;
	uint16_t	ether_type;
	int	pktlen;		//the original 802.3 pkt raw_data len (not include ether_hdr data)
	int	pkt_hdrlen;	//the original 802.3 pkt header len
	int	hdrlen;		//the WLAN Header Len
	int	nr_frags;
	int	last_txcmdsz;
	int	encrypt;	//when 0 indicate no encrypt. when non-zero, indicate the encrypt algorith
	uint8_t	iv[8];
	int	iv_len;
	uint8_t	icv[8];
	int	icv_len;
	int	priority;
	int	ack_policy;
	int	mac_id;
	int	vcs_mode;	//virtual carrier sense method

	uint8_t 	dst[ETH_ALEN];
	uint8_t	src[ETH_ALEN];
	uint8_t	ta[ETH_ALEN];
	uint8_t 	ra[ETH_ALEN];

	uint8_t	key_idx;

	uint8_t	qos_en;
	uint8_t	ht_en;
	uint8_t	raid;//rate adpative id
	uint8_t	bwmode;
	uint8_t	ch_offset;//PRIME_CHNL_OFFSET
	uint8_t	sgi;//short GI
	uint8_t	ampdu_en;//tx ampdu enable
	uint8_t	mdata;//more data bit
	uint8_t	eosp;

	uint8_t	pctrl;//per packet txdesc control enable
	uint8_t	triggered;//for ap mode handling Power Saving sta

	uint32_t	qsel;
	uint16_t	seqnum;

	struct sta_info * psta;
#ifdef CONFIG_TCP_CSUM_OFFLOAD_TX
	uint8_t	hw_tcp_csum;
#endif
};
#else
//reduce size
struct pkt_attrib
{
	uint8_t	type;
	uint8_t	subtype;
	uint8_t	bswenc;
	uint8_t	dhcp_pkt;
	uint16_t	ether_type;
	uint16_t	seqnum;
	uint16_t	pkt_hdrlen;	//the original 802.3 pkt header len
	uint16_t	hdrlen;		//the WLAN Header Len
	uint32_t	pktlen;		//the original 802.3 pkt raw_data len (not include ether_hdr data)
	uint32_t	last_txcmdsz;
	uint8_t	encrypt;	//when 0 indicate no encrypt. when non-zero, indicate the encrypt algorith
	uint8_t	iv_len;
	uint8_t	icv_len;
	uint8_t	iv[18];
	uint8_t	icv[16];
	uint8_t	priority;
	uint8_t	ack_policy;
	uint8_t	mac_id;
	uint8_t	vcs_mode;	//virtual carrier sense method
	uint8_t 	dst[ETH_ALEN];
	uint8_t	src[ETH_ALEN];
	uint8_t	ta[ETH_ALEN];
	uint8_t 	ra[ETH_ALEN];
	uint8_t	key_idx;
	uint8_t	qos_en;
	uint8_t	ht_en;
	uint8_t	raid;//rate adpative id
	uint8_t	bwmode;
	uint8_t	ch_offset;//PRIME_CHNL_OFFSET
	uint8_t	sgi;//short GI
	uint8_t	ampdu_en;//tx ampdu enable
	uint8_t	mdata;//more data bit
	uint8_t	pctrl;//per packet txdesc control enable
	uint8_t	triggered;//for ap mode handling Power Saving sta
	uint8_t	qsel;
	uint8_t	eosp;
	uint8_t	rate;
	uint8_t	intel_proxim;
	uint8_t 	retry_ctrl;
	struct sta_info * psta;
#ifdef CONFIG_TCP_CSUM_OFFLOAD_TX
	uint8_t	hw_tcp_csum;
#endif
};
#endif

#ifdef PLATFORM_FREEBSD
#define ETH_ALEN	6		/* Octets in one ethernet addr	 */
#define ETH_HLEN	14		/* Total octets in header.	 */
#define ETH_P_IP	0x0800		/* Internet Protocol packet	*/

/*struct rtw_ieee80211_hdr {
	uint16_t frame_control;
	uint16_t duration_id;
	uint8_t addr1[6];
	uint8_t addr2[6];
	uint8_t addr3[6];
	uint16_t seq_ctrl;
	uint8_t addr4[6];
} ;*/
#endif //PLATFORM_FREEBSD

#define WLANHDR_OFFSET	64

#define NULL_FRAMETAG		(0x0)
#define DATA_FRAMETAG		0x01
#define L2_FRAMETAG		0x02
#define MGNT_FRAMETAG		0x03
#define AMSDU_FRAMETAG		0x04

#define EII_FRAMETAG		0x05
#define IEEE8023_FRAMETAG  	0x06

#define MP_FRAMETAG		0x07

#define TXAGG_FRAMETAG 		0x08

enum {
	XMITBUF_DATA = 0,
	XMITBUF_MGNT = 1,
	XMITBUF_CMD = 2,
};

struct  submit_ctx{
	uint32_t submit_time; /* */
	uint32_t timeout_ms; /* <0: not synchronous, 0: wait forever, >0: up to ms waiting */
	int status; /* status for operation */
#ifdef PLATFORM_LINUX
	struct completion done;
#endif
};

enum {
	RTW_SCTX_DONE_SUCCESS = 0,
	RTW_SCTX_DONE_UNKNOWN,
	RTW_SCTX_DONE_BUF_ALLOC,
	RTW_SCTX_DONE_BUF_FREE,
	RTW_SCTX_DONE_WRITE_PORT_ERR,
	RTW_SCTX_DONE_TX_DESC_NA,
	RTW_SCTX_DONE_TX_DENY,
};


void rtw_sctx_init(struct submit_ctx *sctx, int timeout_ms);
int rtw_sctx_wait(struct submit_ctx *sctx);
void rtw_sctx_done_err(struct submit_ctx **sctx, int status);
void rtw_sctx_done(struct submit_ctx **sctx);

typedef struct _XIMT_BUF_ {    
	uint32_t     AllocatBufAddr;    
	uint32_t     BufAddr;    
	uint32_t     BufLen;
}XIMT_BUF, *PXIMT_BUF;

struct xmit_buf
{
	_list	list;

	_adapter *padapter;

#if USE_SKB_AS_XMITBUF
	_pkt *pkt;
#else
	uint8_t *pallocated_buf;
#endif
	uint8_t *pbuf;

	void *priv_data;

	uint16_t buf_tag; // 0: Normal xmitbuf, 1: extension xmitbuf, 2:cmd xmitbuf
	uint16_t flags;
	uint32_t alloc_sz;

	uint32_t  len;

	struct submit_ctx *sctx;

#ifdef CONFIG_USB_HCI

	//uint32_t sz[8];
	uint32_t	ff_hwaddr;

#if defined(PLATFORM_OS_XP)||defined(PLATFORM_LINUX) || defined(PLATFORM_FREEBSD)
	PURB	pxmit_urb[8];
	dma_addr_t dma_transfer_addr;	/* (in) dma addr for transfer_buffer */
#endif

#ifdef PLATFORM_OS_XP
	PIRP		pxmit_irp[8];
#endif

#ifdef PLATFORM_OS_CE
	USB_TRANSFER	usb_transfer_write_port;
#endif

	uint8_t bpending[8];

	sint last[8];

#endif

#if defined(CONFIG_SDIO_HCI) || defined(CONFIG_GSPI_HCI)
	uint8_t *phead;
	uint8_t *pdata;
	uint8_t *ptail;
	uint8_t *pend;
	uint32_t ff_hwaddr;
	uint8_t	pg_num;	
	uint8_t	agg_num;
#ifdef PLATFORM_OS_XP
	PMDL pxmitbuf_mdl;
	PIRP  pxmitbuf_irp;
	PSDBUS_REQUEST_PACKET pxmitbuf_sdrp;
#endif
#endif

#if defined(DBG_XMIT_BUF )|| defined(DBG_XMIT_BUF_EXT)
	uint8_t no;
#endif

#if defined(CONFIG_PCI_HCI) || defined(CONFIG_LX_HCI)
#if ((RTL8195A_SUPPORT ==1) ||(RTL8711B_SUPPORT == 1))
	XIMT_BUF BufInfo[4];    
	uint32_t BlockNum;
#endif
#endif
};


struct xmit_frame
{
	_list	list;

	struct pkt_attrib attrib;

	_pkt *pkt;

	int	frame_tag;

	_adapter *padapter;

	uint8_t	*buf_addr;

	struct xmit_buf *pxmitbuf;

#if defined(CONFIG_SDIO_HCI) || defined(CONFIG_GSPI_HCI)
	uint8_t	pg_num;
	uint8_t	agg_num;
#endif

#ifdef CONFIG_USB_HCI
#ifdef CONFIG_USB_TX_AGGREGATION
	uint8_t	agg_num;
#endif
	int8_t	pkt_offset;
#ifdef CONFIG_RTL8192D
	uint8_t	EMPktNum;
	uint16_t	EMPktLen[5];//The max value by HW
#endif
#endif

#if defined(CONFIG_PCI_HCI) || defined(CONFIG_LX_HCI)
#if ((RTL8195A_SUPPORT ==1) ||(RTL8711B_SUPPORT == 1))
	uint32_t TxDexAddr;    
	uint32_t HdrLen;    
	uint32_t PayLoadAddr;    
	uint32_t PayLoadLen;    
	uint32_t TotalLen;    
	uint32_t BlockNum;    
	XIMT_BUF BufInfo[4];    
	BOOLEAN NoCoalesce;
#endif
#endif
};

struct tx_servq {
	_list	tx_pending;
	_queue	sta_pending;
	int qcnt;
};

struct sta_xmit_priv
{
	_lock	lock;
	sint	option;
	sint	apsd_setting;	//When bit mask is on, the associated edca queue supports APSD.


	//struct tx_servq blk_q[MAX_NUMBLKS];
	struct tx_servq	be_q;			//priority == 0,3
	struct tx_servq	bk_q;			//priority == 1,2
	struct tx_servq	vi_q;			//priority == 4,5
	struct tx_servq	vo_q;			//priority == 6,7
	_list 	legacy_dz;
	_list  apsd;

	uint16_t txseq_tid[16];

	//uint	sta_tx_bytes;
	//uint64_t	sta_tx_pkts;
	//uint	sta_tx_fail;


};


struct	hw_txqueue	{
	volatile sint	head;
	volatile sint	tail;
	volatile sint 	free_sz;	//in units of 64 bytes
	volatile sint      free_cmdsz;
	volatile sint	 txsz[8];
	uint	ff_hwaddr;
	uint	cmd_hwaddr;
	sint	ac_tag;
};

struct agg_pkt_info{
	uint16_t offset;
	uint16_t pkt_len;
};


struct	xmit_priv	{

	_lock	lock;

	//_queue	blk_strms[MAX_NUMBLKS];
	_queue	be_pending;
	_queue	bk_pending;
	_queue	vi_pending;
	_queue	vo_pending;
	_queue	bm_pending;

	//_queue	legacy_dz_queue;
	//_queue	apsd_queue;

	uint8_t *pallocated_frame_buf;
	uint8_t *pxmit_frame_buf;
	uint free_xmitframe_cnt;

	//uint mapping_addr;
	//uint pkt_sz;

	_queue	free_xmit_queue;

	//struct	hw_txqueue	be_txqueue;
	//struct	hw_txqueue	bk_txqueue;
	//struct	hw_txqueue	vi_txqueue;
	//struct	hw_txqueue	vo_txqueue;
	//struct	hw_txqueue	bmc_txqueue;

	_adapter	*adapter;

	uint8_t   	vcs_setting;
	uint8_t	vcs;
	uint8_t	vcs_type;
	//uint16_t  rts_thresh;

	uint64_t	tx_bytes;
	uint64_t	tx_pkts;
	uint64_t	tx_drop;
	uint64_t	last_tx_bytes;
	uint64_t	last_tx_pkts;

	struct hw_xmit *hwxmits;
	uint8_t	hwxmit_entry;

#ifdef CONFIG_USB_HCI
	_sema	tx_retevt;//all tx return event;
	uint8_t		txirp_cnt;//

#ifdef PLATFORM_OS_CE
	USB_TRANSFER	usb_transfer_write_port;
//	USB_TRANSFER	usb_transfer_write_mem;
#endif
#ifdef PLATFORM_LINUX
	struct tasklet_struct xmit_tasklet;
#endif
#ifdef PLATFORM_FREEBSD
	struct task xmit_tasklet;
#endif
	//per AC pending irp
	int beq_cnt;
	int bkq_cnt;
	int viq_cnt;
	int voq_cnt;

#endif

#if defined(CONFIG_PCI_HCI)  || defined(CONFIG_LX_HCI)
	// Tx
	struct rtw_tx_ring	tx_ring[PCI_MAX_TX_QUEUE_COUNT];
	int	txringcount[PCI_MAX_TX_QUEUE_COUNT];
	uint8_t 	beaconDMAing;		//flag of indicating beacon is transmiting to HW by DMA
#ifdef PLATFORM_LINUX
	struct tasklet_struct xmit_tasklet;
#endif
#endif

	_queue free_xmitbuf_queue;
	_queue pending_xmitbuf_queue;
	uint8_t *pallocated_xmitbuf;
	uint8_t *pxmitbuf;
	uint free_xmitbuf_cnt;
#if USE_XMIT_EXTBUFF
	_queue free_xmit_extbuf_queue;
	uint8_t *pallocated_xmit_extbuf;
	uint8_t *pxmit_extbuf;
	uint free_xmit_extbuf_cnt;
#endif
	uint16_t	nqos_ssn;
	#ifdef CONFIG_TX_EARLY_MODE

	#define MAX_AGG_PKT_NUM 256 //Max tx ampdu coounts		
	
	struct agg_pkt_info agg_pkt[MAX_AGG_PKT_NUM];
	#endif
};

#ifdef CONFIG_TRACE_SKB
extern struct xmit_buf *_rtw_alloc_xmitbuf_ext(struct xmit_priv *pxmitpriv, uint32_t size);

//extern struct xmit_frame *_rtw_alloc_xmitframe(struct xmit_priv *pxmitpriv);
//extern int32_t _rtw_free_xmitframe(struct xmit_priv *pxmitpriv, struct xmit_frame *pxmitframe);
//extern void _rtw_free_xmitframe_queue(struct xmit_priv *pxmitpriv, _queue *pframequeue);

#define rtw_alloc_xmitbuf_ext(pxmitpriv, pxmitbuf, size) \
	(\
		pxmitbuf = _rtw_alloc_xmitbuf_ext(pxmitpriv, size),\
		pxmitbuf ? set_skb_list_flag(pxmitbuf->pkt, SKBLIST_XMITEXTBUF):0,\
		pxmitbuf\
	)
#else
extern struct xmit_buf *rtw_alloc_xmitbuf_ext(struct xmit_priv *pxmitpriv, uint32_t size);
#endif
extern int32_t rtw_free_xmitbuf_ext(struct xmit_priv *pxmitpriv, struct xmit_buf *pxmitbuf);

extern struct xmit_buf *rtw_alloc_xmitbuf(struct xmit_priv *pxmitpriv);
extern int32_t rtw_free_xmitbuf(struct xmit_priv *pxmitpriv, struct xmit_buf *pxmitbuf);

extern struct xmit_frame *rtw_alloc_xmitframe(struct xmit_priv *pxmitpriv);
extern int32_t rtw_free_xmitframe(struct xmit_priv *pxmitpriv, struct xmit_frame *pxmitframe);
extern void rtw_free_xmitframe_queue(struct xmit_priv *pxmitpriv, _queue *pframequeue);
struct tx_servq *rtw_get_sta_pending(_adapter *padapter, struct sta_info *psta, sint up, uint8_t *ac);
extern int32_t rtw_xmitframe_enqueue(_adapter *padapter, struct xmit_frame *pxmitframe);
extern struct xmit_frame* rtw_dequeue_xframe(struct xmit_priv *pxmitpriv, struct hw_xmit *phwxmit_i, sint entry);

void rtw_count_tx_stats(_adapter *padapter, struct xmit_frame *pxmitframe, int sz);
extern void rtw_update_protection(_adapter *padapter, uint8_t *ie, uint ie_len);
extern int32_t rtw_make_wlanhdr(_adapter *padapter, uint8_t *hdr, struct pkt_attrib *pattrib);
extern int32_t rtw_put_snap(uint8_t *data, uint16_t h_proto);

extern int32_t rtw_xmit_classifier(_adapter *padapter, struct xmit_frame *pxmitframe);
extern uint32_t rtw_calculate_wlan_pkt_size_by_attribue(struct pkt_attrib *pattrib);
#define rtw_wlan_pkt_size(f) rtw_calculate_wlan_pkt_size_by_attribue(&f->attrib)
extern int32_t rtw_xmitframe_coalesce(_adapter *padapter, _pkt *pkt, struct xmit_frame *pxmitframe);
#ifdef CONFIG_TDLS
int32_t rtw_xmit_tdls_coalesce(_adapter *padapter, struct xmit_frame *pxmitframe, uint8_t action);
#endif
int32_t _rtw_init_hw_txqueue(struct hw_txqueue* phw_txqueue, uint8_t ac_tag);
void _rtw_init_sta_xmit_priv(struct sta_xmit_priv *psta_xmitpriv);


int32_t rtw_txframes_pending(_adapter *padapter);
int32_t rtw_txframes_sta_ac_pending(_adapter *padapter, struct pkt_attrib *pattrib);
void rtw_txframes_update_attrib_vcs_info(_adapter *padapter, struct xmit_frame *pxmitframe);
void rtw_init_hwxmits(struct hw_xmit *phwxmit, sint entry);


int32_t _rtw_init_xmit_priv(struct xmit_priv *pxmitpriv, _adapter *padapter);
void _rtw_free_xmit_priv (struct xmit_priv *pxmitpriv);


void rtw_alloc_hwxmits(_adapter *padapter);
void rtw_free_hwxmits(_adapter *padapter);


int32_t rtw_xmit(_adapter *padapter, _pkt **pkt);

#if defined(CONFIG_AP_MODE) || defined(CONFIG_TDLS)
sint xmitframe_enqueue_for_sleeping_sta(_adapter *padapter, struct xmit_frame *pxmitframe);
void stop_sta_xmit(_adapter *padapter, struct sta_info *psta);
void wakeup_sta_to_xmit(_adapter *padapter, struct sta_info *psta);
void xmit_delivery_enabled_frames(_adapter *padapter, struct sta_info *psta);
#endif

uint8_t	qos_acm(uint8_t acm_mask, uint8_t priority);

int32_t xmitframe_addmic(_adapter *padapter, struct xmit_frame *pxmitframe);
int32_t xmitframe_swencrypt(_adapter *padapter, struct xmit_frame *pxmitframe);

#ifdef CONFIG_XMIT_THREAD_MODE
void	enqueue_pending_xmitbuf(struct xmit_priv *pxmitpriv, struct xmit_buf *pxmitbuf);
struct xmit_buf*	dequeue_pending_xmitbuf(struct xmit_priv *pxmitpriv);
struct xmit_buf*	dequeue_pending_xmitbuf_under_survey(struct xmit_priv *pxmitpriv);
sint	check_pending_xmitbuf(struct xmit_priv *pxmitpriv);
thread_return	rtw_xmit_thread(thread_context context);
#endif

uint32_t	rtw_get_ff_hwaddr(struct xmit_frame	*pxmitframe);

extern int32_t rtw_xmit_mgnt(_adapter * padapter, struct xmit_frame *pmgntframe);
extern int32_t rtw_xmit_data(PADAPTER padapter, struct xmit_frame *pxmitframe);
extern int32_t rtw_xmit_xmitbuf(_adapter * padapter, struct xmit_buf *pxmitbuf);
extern uint32_t ffaddr2deviceId(struct dvobj_priv *pdvobj, uint32_t addr);
extern unsigned int nr_xmitframe;
extern unsigned int nr_xmitbuff;
#endif	//_RTL871X_XMIT_H_

