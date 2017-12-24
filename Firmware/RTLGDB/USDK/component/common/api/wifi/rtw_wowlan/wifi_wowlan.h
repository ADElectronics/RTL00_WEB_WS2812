#ifndef _WIFI_WOWLAN_H_
#define _WIFI_WOWLAN_H_

#include <platform_stdlib.h>
#include <osdep_service.h>
#include <FreeRTOS.h>
#include <timers.h>

#define WOWLAN_DBG 1

enum{
	WOWLAN_DBG_OFF = 0,
	WOWLAN_DBG_ALWAYS,
	WOWLAN_DBG_ERROR,
	WOWLAN_DBG_WARNING,
	WOWLAN_DBG_INFO
};

#if WOWLAN_DBG
	//#define WOWLAN_DUMP_MSG
	#define WOWLAN_DUMP_MSG_1 //dump packet when setting
	static unsigned char  gWowlanDbgLevel = WOWLAN_DBG_ERROR;
	#define WOWLAN_PRINTK(fmt, args...)		printf(fmt"\r\n",## args)
	#define _WOWLAN_PRINTK(fmt, args...)	printf(fmt,## args)
	#define WOWLAN_DBG_MSG(level, fmt, args...)					\
			do{														\
				if(level <= gWowlanDbgLevel){	\
					WOWLAN_PRINTK(fmt,## args);							\
				}													\
			}while(0)
#else
	#define WOWLAN_PRINTK(fmt, args...)
	#define WOWLAN_DBG_MSG(level, fmt, args...)	
#endif

#ifndef uint8_t
typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned int		uint32_t;
#endif

#ifndef BIT
#define BIT(x)	((uint32_t)1 << (x))
#endif

#ifndef le16_to_cpu //need a general definition for the whole system
#define cpu_to_le32(x) ((uint32_t)(x))
#define le32_to_cpu(x) ((uint32_t)(x))
#define cpu_to_le16(x) ((uint16_t)(x))
#define le16_to_cpu(x) ((uint16_t)(x))
#endif

#ifndef IP_FMT
#define IP_FMT "%d.%d.%d.%d"
#endif

#ifndef IP_ARG
#define IP_ARG(x) ((uint8_t*)(x))[0],((uint8_t*)(x))[1],((uint8_t*)(x))[2],((uint8_t*)(x))[3]
#endif

#ifndef MAC_FMT
#define MAC_FMT "%02x:%02x:%02x:%02x:%02x:%02x"
#endif

#ifndef MAC_ARG
#define MAC_ARG(x) ((uint8_t*)(x))[0],((uint8_t*)(x))[1],((uint8_t*)(x))[2],((uint8_t*)(x))[3],((uint8_t*)(x))[4],((uint8_t*)(x))[5]
#endif

#ifndef ETH_ALEN
#define ETH_ALEN 6
#endif

#ifndef ethhdr
struct ethhdr 
{
	unsigned char	h_dest[ETH_ALEN];	/* destination eth addr	*/
	unsigned char	h_source[ETH_ALEN];	/* source ether addr	*/
	unsigned short	h_proto;		/* packet type ID field	*/
};
#endif

#ifndef wowlan_memcpy
	#define wowlan_memcpy(d, s, n)	rtw_memcpy((void*)(d), ((void*)(s)), (n))
#endif

#ifndef wowlan_malloc
	#define wowlan_malloc(sz)	rtw_malloc(sz)
#endif

#ifndef wowlan_zmalloc
	#define wowlan_zmalloc(sz)	rtw_zmalloc(sz)
#endif

#ifndef wowlan_memset
	#define wowlan_memset(pbuf, c, sz)	rtw_memset(pbuf, c, sz)
#endif

#ifndef wowlan_mfree
	#define wowlan_mfree(p, sz)	rtw_mfree(((uint8_t*)(p)), (sz))
#endif

#ifndef wowlan_memcmp
	#define wowlan_memcmp(s1, s2, n) rtw_memcmp(((void*)(s1)), ((void*)(s2)), (n))
#endif

#ifndef wowlan_mdelay_os
	#define wowlan_mdelay_os(ms) rtw_mdelay_os(ms)
#endif

/*Mutex services*/
typedef _mutex _wowlock;

__inline static void _init_wowlock(_wowlock *plock)
{
	rtw_mutex_init(plock);
}

__inline static void _free_wowlock(_wowlock *plock)
{
	rtw_mutex_free(plock);
}

__inline static void _enter_wowlock(_wowlock *plock)
{
	rtw_mutex_get(plock);
}

__inline static void _exit_wowlock(_wowlock *plock)
{
	rtw_mutex_put(plock);
}

/*Timer services*/
typedef TimerHandle_t _wowTimer;
#define TMR_AUTO_RELOAD_EN	_TRUE
#define TMR_AUTO_RELOAD_DIS	_FALSE

__inline static void
_wowlan_init_timer(_wowTimer *ptimer, void *adapter, TIMER_FUN pfunc,void* cntx, const char *name, uint32_t auto_reload)
{
	*ptimer = rtw_timerCreate(
				(signed const char *)name, 		// Just a text name, not used by the RTOS kernel. 
				TIMER_MAX_DELAY,		// Timer Period, not 0
				auto_reload,		// Whether timer will auto-load themselves when expires
				cntx,		// Uniq id used to identify which timer expire.. 
				pfunc		// Timer callback							
			);
}

__inline static void 
_wowlan_set_timer(_wowTimer *ptimer, uint32_t delay_time_ms)
{
	if(rtw_timerChangePeriod(*ptimer, rtw_ms_to_systime(delay_time_ms), TIMER_MAX_DELAY) == _FAIL)
		WOWLAN_PRINTK("Fail to set timer period");
}

__inline static void 
_wowlan_cancel_timer(_wowTimer *ptimer)
{
	rtw_timerStop(*ptimer, TIMER_MAX_DELAY);
}

__inline static void 
_wowlan_del_timer(_wowTimer *ptimer)
{
	rtw_timerDelete(*ptimer, TIMER_MAX_DELAY);
}

__inline static void *
_wowlan_get_timer_cntx(_wowTimer timer)
{
	return pvTimerGetTimerID(timer);
}

enum rtw_wowlan_wakeup_reason {
	RTW_WOWLAN_WAKEUP_BY_PATTERN				= BIT(0),
	RTW_WOWLAN_WAKEUP_BY_DISCONNECTION			= BIT(1),
	RTW_WOWLAN_WAKEUP_MAX 						= 0x7FFFFFFF
}; 

enum rtw_wowlan_cmd_id{
	RTW_WOWLAN_CMD_ENABLE = 0x01, // enable wowlan service
	RTW_WOWLAN_CMD_PATTERNS = 0x02, // wowlan pattern setting
	RTW_WOWLAN_CMD_PROT_OFFLOAD_CONFIG = 0x03, //ARP offload setting
	RTW_WOWLAN_CMD_GET_STATUS = 0x04, // get rtw_wowlan_status
	RTW_WOWLAN_CMD_CLEAR_ALL = 0x05, //clear wowlan content
	RTW_WOWLAN_CMD_KEEPALIVE = 0x06, //for keep alive packet setting
	RTW_WOWLAN_CMD_MAX = 0xff
};

#define RTW_WOWLAN_MAX_RX_FILTERS			(5)
#define RTW_WOWLAN_RX_FILTER_MAX_FIELDS	(8)
#define RTW_WOWLAN_ID_OFFSET				(100) //to match some application, ID starts from 100
#define RTW_WOWLAN_MIN_FILTERS_ID			(RTW_WOWLAN_ID_OFFSET)
#define RTW_WOWLAN_MAX_FILTERS_ID			(RTW_WOWLAN_ID_OFFSET+RTW_WOWLAN_MAX_RX_FILTERS-1)

struct rtw_wowlan_rx_filter_field {
	uint16_t offset;
	uint8_t len;
	uint8_t flags;
	uint8_t *mask;
	uint8_t *pattern;
};

struct rtw_wowlan_rx_filter {
	uint8_t action;
	uint8_t offset;
	uint8_t num_fields;
	struct rtw_wowlan_rx_filter_field fields[RTW_WOWLAN_RX_FILTER_MAX_FIELDS];
};

#if defined(__IAR_SYSTEMS_ICC__)
#pragma pack(1)
#else
#error "this structure needs to be packed!"
#endif
struct rtw_wowlan_status {
	uint32_t wakeup_reasons; //record wake up reason
	uint32_t filter_id; //record which pattern is matched
};
#if defined(__IAR_SYSTEMS_ICC__)
#pragma pack()
#else
#error "this structure needs to be packed!"
#endif

/**
 * struct rtw_wowlan_keepalive_packet
 *
 * @payload_len: data payload length
 * @payload: data payload buffer
 * @data_interval: interval at which to send data packets
**/
#define RTW_WOWLAN_MAX_KPALIVE_PKT 3
#define RTW_WOWLAN_MAX_KPALIVE_PKT_SZ 512
struct rtw_wowlan_keepalive_packet{
	uint8_t packet_id;
	int payload_len;
	uint8_t *payload;
	uint32_t data_interval;
	_wowTimer keepalive_tmr;
};

struct rtw_wowlan_ops {
	int (*DevWowlanInit)(void);	
	int (*DevWowlanEnable)(void);
	int (*DevWowlanDisable)(void);
	int (*DevWowlanWakeUp)(void);
	int (*DevWowlanSleep)(void);
};

/**
 * enum rtw_wowlan_proto_offloads - enabled protocol offloads
 * @RTW_WOWLAN_PROTO_OFFLOAD_ARP: ARP data is enabled
 */
enum rtw_wowlan_proto_offloads {
	RTW_WOWLAN_PROTO_OFFLOAD_ARP	= BIT(0),
	RTW_WOWLAN_PROTO_OFFLOAD_MAX	= 0x7FFFFFFF
};

/**
 * struct rtw_wowlan_proto_offload_common - ARP/NS offload common part
 * @enabled: enable flags
 * @remote_ipv4_addr: remote address to answer to (or zero if all)
 * @host_ipv4_addr: our IPv4 address to respond to queries for
 * @arp_mac_addr: our MAC address for ARP responses
 * @reserved: unused
 */
struct rtw_wowlan_proto_offload_common{
	int proto_enabled;
	uint32_t remote_ipv4_addr;
	uint32_t host_ipv4_addr;
	uint8_t host_mac_addr[ETH_ALEN];	
	uint16_t reserved;
};

struct rtw_wowlan {
	_wowlock wow_mutex;
	bool enabled;
	struct rtw_wowlan_status status;
	struct rtw_wowlan_ops ops;
	struct rtw_wowlan_proto_offload_common proto;
	bool proto_offload_enabled;
	struct rtw_wowlan_rx_filter *rx_filter[RTW_WOWLAN_MAX_RX_FILTERS];
	bool rx_filter_enabled[RTW_WOWLAN_MAX_RX_FILTERS];/* RX Data filter rule state - enabled/disabled */
	struct rtw_wowlan_keepalive_packet *tx_keepalive[RTW_WOWLAN_MAX_KPALIVE_PKT];
	bool tx_keepalive_enabled[RTW_WOWLAN_MAX_KPALIVE_PKT];/* TX keep avlive rule state - enabled/disabled */
};

#define eqMacAddr(a,b)						( ((a)[0]==(b)[0] && (a)[1]==(b)[1] && (a)[2]==(b)[2] && (a)[3]==(b)[3] && (a)[4]==(b)[4] && (a)[5]==(b)[5]) ? 1:0 )
#define cpMacAddr(des,src)					((des)[0]=(src)[0],(des)[1]=(src)[1],(des)[2]=(src)[2],(des)[3]=(src)[3],(des)[4]=(src)[4],(des)[5]=(src)[5])
#define cpIpAddr(des,src)					((des)[0]=(src)[0],(des)[1]=(src)[1],(des)[2]=(src)[2],(des)[3]=(src)[3])

#define RTW_WOWLAN_GET_ARP_PKT_OPERATION(__pHeader) 				ReadEF2Byte( ((uint8_t*)(__pHeader)) + 6)
#define RTW_WOWLAN_GET_ARP_PKT_SENDER_MAC_ADDR(__pHeader, _val) 	cpMacAddr((uint8_t*)(_val), ((uint8_t*)(__pHeader))+8)
#define RTW_WOWLAN_GET_ARP_PKT_SENDER_IP_ADDR(__pHeader, _val) 		cpIpAddr((uint8_t*)(_val), ((uint8_t*)(__pHeader))+14)
#define RTW_WOWLAN_GET_ARP_PKT_TARGET_MAC_ADDR(__pHeader, _val) 	cpMacAddr((uint8_t*)(_val), ((uint8_t*)(__pHeader))+18)
#define RTW_WOWLAN_GET_ARP_PKT_TARGET_IP_ADDR(__pHeader, _val) 	cpIpAddr((uint8_t*)(_val), ((uint8_t*)(__pHeader))+24)

#define RTW_WOWLAN_SET_ARP_PKT_HW(__pHeader, __Value)  				WriteEF2Byte( ((uint8_t*)(__pHeader)) + 0, __Value)
#define RTW_WOWLAN_SET_ARP_PKT_PROTOCOL(__pHeader, __Value)  			WriteEF2Byte( ((uint8_t*)(__pHeader)) + 2, __Value)
#define RTW_WOWLAN_SET_ARP_PKT_HW_ADDR_LEN(__pHeader, __Value)  		WriteEF1Byte( ((uint8_t*)(__pHeader)) + 4, __Value)
#define RTW_WOWLAN_SET_ARP_PKT_PROTOCOL_ADDR_LEN(__pHeader, __Value)  	WriteEF1Byte( ((uint8_t*)(__pHeader)) + 5, __Value)
#define RTW_WOWLAN_SET_ARP_PKT_OPERATION(__pHeader, __Value) 		WriteEF2Byte( ((uint8_t*)(__pHeader)) + 6, __Value)
#define RTW_WOWLAN_SET_ARP_PKT_SENDER_MAC_ADDR(__pHeader, _val) 	cpMacAddr(((uint8_t*)(__pHeader))+8, (uint8_t*)(_val))
#define RTW_WOWLAN_SET_ARP_PKT_SENDER_IP_ADDR(__pHeader, _val) 		cpIpAddr(((uint8_t*)(__pHeader))+14, (uint8_t*)(_val))
#define RTW_WOWLAN_SET_ARP_PKT_TARGET_MAC_ADDR(__pHeader, _val) 	cpMacAddr(((uint8_t*)(__pHeader))+18, (uint8_t*)(_val))
#define RTW_WOWLAN_SET_ARP_PKT_TARGET_IP_ADDR(__pHeader, _val) 		cpIpAddr(((uint8_t*)(__pHeader))+24, (uint8_t*)(_val))

#define RTW_WOWLAN_ARP_PKT_LEN		0x2A
#define RTW_WOWLAN_ARP_PKT_OPERATION_REQ		0x0100 //arp request
#define RTW_WOWLAN_ARP_PKT_OPERATION_RSP		0x0200 //arp response

extern uint8_t key_2char2num(uint8_t hch, uint8_t lch);
extern _LONG_CALL_ void __rtl_memDump_v1_00(const uint8_t *start, uint32_t size, char * strHeader);
#define rtw_wowlan_DumpForBytes(pData, Len) __rtl_memDump_v1_00(pData, Len, NULL)

#define PWOWLAN_TO_STATUS(pwowlan)			(&pwowlan->status)
#define PWOWLAN_TO_OPS(pwowlan)			(&pwowlan->ops)
#define PWOWLAN_TO_PROTO(pwowlan)			(&pwowlan->proto)
#define PWOWLAN_TO_RX_FILTER(pwowlan)		(pwowlan->rx_filter)
#define PWOWLAN_TO_TX_KEEPALIVE(pwowlan)	(pwowlan->tx_keepalive)

/**
 * rtw_wowlan_init: initialize wowlan service
 * arg: None
 * return: _SUCCESS or _FAIL
 */
extern int rtw_wowlan_init(void);

/**
 * cmd_wowlan_service: input commands to configure wowlan service
 * arg:
 * @argc: number of input parameter
 * @argv: content of input string
 * return: None
 */
extern void cmd_wowlan_service(int argc, char **argv);

/**
 * rtw_wowlan_process_rx_packet: entry for packet process in wowlan service once it starts
 * arg: 
 * @rx_pkt: receive packet from wlan/ethernet 
 * @pkt_len: receive packet length
 * return: _SUCCESS or _FAIL
 */
extern int rtw_wowlan_process_rx_packet(char *rx_pkt, uint16_t pkt_len);

/**
 * rtw_wowlan_wakeup_process: wake up process once the reasons are matched, 
 *       refer to enum rtw_wowlan_wakeup_reason
 * arg: 
 * @reason: wake up reason, refer to enum rtw_wowlan_wakeup_reason  
 * return: None
 */
extern void rtw_wowlan_wakeup_process(int reason);

/**
 * rtw_wowlan_is_enabled: if wowlan service is already enabled
 * this function is called in rx path and wifi_inidication when wowlan service is running
 * arg: None
 * return: _True if enable or _False if disable
 */
extern int rtw_wowlan_is_enabled(void);

/**
 * rtw_wowlan_get_wk_reason: query wake up reason, refer to enum rtw_wowlan_wakeup_reason
 * arg: None
 * return: wakeup_reason
 */
extern int rtw_wowlan_get_wk_reason(void);

/**
 * rtw_wowlan_dev_sleep: sleep process on Ameba side, pull control for example
 * this function is linked to dev_wowlan_sleep_process() in dev_wowlan.c
 * arg: None
 * return: None
 */
extern void rtw_wowlan_dev_sleep(void);

#endif
