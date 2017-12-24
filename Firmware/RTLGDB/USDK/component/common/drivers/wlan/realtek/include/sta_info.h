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
#ifndef __STA_INFO_H_
#define __STA_INFO_H_

#define IBSS_START_MAC_ID	2

#if 0 //move to wifi.h
#if defined(PLATFORM_ECOS)
#define NUM_STA 10	//Decrease STA due to memory limitation - Alex Fang
#elif defined(PLATFORM_FREERTOS)
//Decrease STA due to memory limitation - Alex Fang
#ifdef CONFIG_AP_MODE
#define NUM_STA (2 + AP_STA_NUM)	//2 + supported clients
#else
#define NUM_STA 2	//Client mode sta for AP and broadcast
#endif
#else
#define NUM_STA 32
#endif
#endif

#define NUM_ACL 16

//if mode ==0, then the sta is allowed once the addr is hit.
//if mode ==1, then the sta is rejected once the addr is non-hit.
struct rtw_wlan_acl_node {
        _list		        list;
        uint8_t       addr[ETH_ALEN];
        uint8_t       valid;
};

//mode=0, disable
//mode=1, accept unless in deny list
//mode=2, deny unless in accept list
struct wlan_acl_pool {
	int mode;
	int num;
	struct rtw_wlan_acl_node aclnode[NUM_ACL];
	_queue	acl_node_q;
};

typedef struct _RSSI_STA{
	int32_t	UndecoratedSmoothedPWDB;
	int32_t	UndecoratedSmoothedCCK;
	int32_t	UndecoratedSmoothedOFDM;
	uint64_t	PacketMap;
	uint8_t	ValidBit;
	uint32_t	OFDM_pkt;
}RSSI_STA, *PRSSI_STA;

struct	stainfo_stats	{

	//uint64_t	rx_pkts;
	uint64_t rx_mgnt_pkts;
	uint64_t rx_ctrl_pkts;
	uint64_t rx_data_pkts;

	//uint64_t	last_rx_pkts;
	uint64_t	last_rx_mgnt_pkts;
	uint64_t	last_rx_ctrl_pkts;
	uint64_t	last_rx_data_pkts;
	
	uint64_t	rx_bytes;
//	uint64_t	rx_drops;

	uint64_t	tx_pkts;
	uint64_t	tx_bytes;
//	uint64_t  tx_drops;

};

#ifdef CONFIG_TDLS
struct TDLS_PeerKey {
	uint8_t kck[16]; /* TPK-KCK */
	uint8_t tk[16]; /* TPK-TK; only CCMP will be used */
} ;
#endif //CONFIG_TDLS

struct sta_info {

	_lock	lock;
	_list	list; //free_sta_queue
	_list	hash_list; //sta_hash
	//_list asoc_list; //20061114
	//_list sleep_list;//sleep_q
	//_list wakeup_list;//wakeup_q
	_adapter *padapter;
	
	struct sta_xmit_priv sta_xmitpriv;
	struct sta_recv_priv sta_recvpriv;
	
	_queue sleep_q;
	unsigned int sleepq_len;
	
	uint state;
	uint aid;
	uint mac_id;
	uint qos_option;
	uint8_t	hwaddr[ETH_ALEN];

	uint	ieee8021x_blocked;	//0: allowed, 1:blocked 
	uint	dot118021XPrivacy; //aes, tkip...
	union Keytype	dot11tkiptxmickey;
	union Keytype	dot11tkiprxmickey;
	union Keytype	dot118021x_UncstKey;	
	union pn48		dot11txpn;			// PN48 used for Unicast xmit.
	union pn48		dot11rxpn;			// PN48 used for Unicast recv.


	uint8_t	bssrateset[16];
	uint32_t	bssratelen;
	int32_t  rssi;
	int32_t	signal_quality;
	
	uint8_t	cts2self;
	uint8_t	rtsen;

	uint8_t	raid;
	uint8_t 	init_rate;
	uint32_t	ra_mask;
	uint8_t	wireless_mode;	// NETWORK_TYPE
	struct stainfo_stats sta_stats;

#ifdef CONFIG_TDLS
	uint32_t	tdls_sta_state;
	uint8_t	dialog;
	uint8_t	SNonce[32];
	uint8_t	ANonce[32];
	uint32_t	TDLS_PeerKey_Lifetime;
	uint16_t	TPK_count;
	_timer	TPK_timer;
	struct TDLS_PeerKey	tpk;
	uint16_t	stat_code;
	uint8_t	off_ch;
	uint16_t	ch_switch_time;
	uint16_t	ch_switch_timeout;
	uint8_t	option;
	_timer	option_timer;
	_timer	base_ch_timer;
	_timer	off_ch_timer;

	_timer handshake_timer;
	_timer alive_timer1;
	_timer alive_timer2;
	uint8_t timer_flag;
	uint8_t alive_count;
#endif //CONFIG_TDLS

	//for A-MPDU TX, ADDBA timeout check	
	_timer addba_retry_timer;
#ifdef CONFIG_RECV_REORDERING_CTRL
	//for A-MPDU Rx reordering buffer control 
	struct recv_reorder_ctrl recvreorder_ctrl[16];
#endif
	//for A-MPDU Tx
	//unsigned char		ampdu_txen_bitmap;
	uint16_t	BA_starting_seqctrl[16];
	

#ifdef CONFIG_80211N_HT
	struct ht_priv	htpriv;	
#endif
	
	//Notes:	
	//STA_Mode:
	//curr_network(mlme_priv/security_priv/qos/ht) + sta_info: (STA & AP) CAP/INFO	
	//scan_q: AP CAP/INFO

	//AP_Mode:
	//curr_network(mlme_priv/security_priv/qos/ht) : AP CAP/INFO
	//sta_info: (AP & STA) CAP/INFO
		
#ifdef CONFIG_AP_MODE

	_list asoc_list;
	_list auth_list;
	 
	unsigned int expire_to;
#ifdef CONFIG_AP_POLLING_CLIENT_ALIVE
	unsigned int tx_null0;
	unsigned int tx_null0_fail;
	unsigned int tx_null0_retry;
#endif
	unsigned int auth_seq;
	unsigned int authalg;
	unsigned char chg_txt[128];

	uint16_t capability;	
	uint32_t flags;	

	int dot8021xalg;//0:disable, 1:psk, 2:802.1x
	int wpa_psk;//0:disable, bit(0): WPA, bit(1):WPA2
	int wpa_group_cipher;
	int wpa2_group_cipher;
	int wpa_pairwise_cipher;
	int wpa2_pairwise_cipher;	

	uint8_t bpairwise_key_installed;

#ifdef CONFIG_NATIVEAP_MLME
	uint8_t wpa_ie[32];

	uint8_t nonerp_set;
	uint8_t no_short_slot_time_set;
	uint8_t no_short_preamble_set;
	uint8_t no_ht_gf_set;
	uint8_t no_ht_set;
	uint8_t ht_20mhz_set;
#endif	// CONFIG_NATIVEAP_MLME

	unsigned int tx_ra_bitmap;
	uint8_t qos_info;

	uint8_t max_sp_len;
	uint8_t uapsd_bk;//BIT(0): Delivery enabled, BIT(1): Trigger enabled
	uint8_t uapsd_be;
	uint8_t uapsd_vi;
	uint8_t uapsd_vo;	

	uint8_t has_legacy_ac;
	unsigned int sleepq_ac_len;

#ifdef CONFIG_P2P
	//p2p priv data
	uint8_t is_p2p_device;
	uint8_t p2p_status_code;

	//p2p client info
	uint8_t dev_addr[ETH_ALEN];
	//uint8_t iface_addr[ETH_ALEN];//= hwaddr[ETH_ALEN]
	uint8_t dev_cap;
	uint16_t config_methods;
	uint8_t primary_dev_type[8];
	uint8_t num_of_secdev_type;
	uint8_t secdev_types_list[32];// 32/8 == 4;
	uint16_t dev_name_len;
	uint8_t dev_name[32];	
#endif //CONFIG_P2P

#ifdef CONFIG_TX_MCAST2UNI
	uint8_t under_exist_checking;
#endif	// CONFIG_TX_MCAST2UNI
	
#endif	// CONFIG_AP_MODE	

#ifdef CONFIG_IOCTL_CFG80211
	uint8_t *passoc_req;
	uint32_t assoc_req_len;
#endif

	//for DM
	RSSI_STA	 rssi_stat;
	
	//
	// ================ODM Relative Info=======================
	// Please be care, dont declare too much structure here. It will cost memory * STA support num.
	//
	//
	// 2011/10/20 MH Add for ODM STA info.	
	//
	// Driver Write
	uint8_t		bValid;				// record the sta status link or not?
	//uint8_t		WirelessMode;		// 
	uint8_t		IOTPeer;			// Enum value.	HT_IOT_PEER_E
	uint8_t		rssi_level;			//for Refresh RA mask
	// ODM Write
	//1 PHY_STATUS_INFO
	uint8_t		RSSI_Path[4];		// 
	uint8_t		RSSI_Ave;
	uint8_t		RXEVM[4];
	uint8_t		RXSNR[4];

	// ODM Write
	//1 TX_INFO (may changed by IC)
	//TX_INFO_T		pTxInfo;				// Define in IC folder. Move lower layer.
	//
	// ================ODM Relative Info=======================
	//
};

#define sta_rx_pkts(sta) \
	(sta->sta_stats.rx_mgnt_pkts \
	+ sta->sta_stats.rx_ctrl_pkts \
	+ sta->sta_stats.rx_data_pkts)

#define sta_last_rx_pkts(sta) \
	(sta->sta_stats.last_rx_mgnt_pkts \
	+ sta->sta_stats.last_rx_ctrl_pkts \
	+ sta->sta_stats.last_rx_data_pkts)

#define sta_update_last_rx_pkts(sta) \
	do { \
		sta->sta_stats.last_rx_mgnt_pkts = sta->sta_stats.rx_mgnt_pkts; \
		sta->sta_stats.last_rx_ctrl_pkts = sta->sta_stats.rx_ctrl_pkts; \
		sta->sta_stats.last_rx_data_pkts = sta->sta_stats.rx_data_pkts; \
	} while(0)

#define STA_RX_PKTS_ARG(sta) \
	sta->sta_stats.rx_mgnt_pkts \
	, sta->sta_stats.rx_ctrl_pkts \
	, sta->sta_stats.rx_data_pkts

#define STA_LAST_RX_PKTS_ARG(sta) \
	sta->sta_stats.last_rx_mgnt_pkts \
	, sta->sta_stats.last_rx_ctrl_pkts \
	, sta->sta_stats.last_rx_data_pkts

#define STA_PKTS_FMT "(m:%llu, c:%llu, d:%llu)"
	
struct	sta_priv {
	
	uint8_t *pallocated_stainfo_buf;
	uint32_t allocated_stainfo_size;
	uint8_t *pstainfo_buf;
	_queue	free_sta_queue;
	
	_lock sta_hash_lock;
	_list   sta_hash[NUM_STA];
	int asoc_sta_count;
	_queue sleep_q;
	_queue wakeup_q;
	
	_adapter *padapter;
	

#ifdef CONFIG_AP_MODE
	_list asoc_list;
	_list auth_list;
	_lock asoc_list_lock;
	_lock auth_list_lock;

	unsigned int auth_to;  //sec, time to expire in authenticating.
	unsigned int assoc_to; //sec, time to expire before associating.
	unsigned int expire_to; //sec , time to expire after associated.
	
	/* pointers to STA info; based on allocated AID or NULL if AID free
	 * AID is in the range 1-2007, so sta_aid[0] corresponders to AID 1
	 * and so on
	 */
	struct sta_info *sta_aid[NUM_STA];

	uint16_t sta_dz_bitmap;//only support 15 stations, staion aid bitmap for sleeping sta.
	uint16_t tim_bitmap;//only support 15 stations, aid=0~15 mapping bit0~bit15	

	uint16_t max_num_sta;
//TODO: AP
//	struct wlan_acl_pool acl_list;
#endif		
	
};


__inline static uint32_t wifi_mac_hash(uint8_t *mac)
{
        uint32_t x;

        x = mac[0];
        x = (x << 2) ^ mac[1];
        x = (x << 2) ^ mac[2];
        x = (x << 2) ^ mac[3];
        x = (x << 2) ^ mac[4];
        x = (x << 2) ^ mac[5];

        x ^= x >> 8;
        x  = x & (NUM_STA - 1);
		
        return x;
}


extern uint32_t	_rtw_init_sta_priv(_adapter *padapter);
extern uint32_t	_rtw_free_sta_priv(struct sta_priv *pstapriv);
extern struct sta_info *rtw_alloc_stainfo(struct	sta_priv *pstapriv, uint8_t *hwaddr);
extern uint32_t	rtw_free_stainfo(_adapter *padapter , struct sta_info *psta);
extern void rtw_free_all_stainfo(_adapter *padapter);
extern struct sta_info *rtw_get_stainfo(struct sta_priv *pstapriv, uint8_t *hwaddr);
extern uint32_t rtw_init_bcmc_stainfo(_adapter* padapter);
extern struct sta_info* rtw_get_bcmc_stainfo(_adapter* padapter);
extern uint8_t rtw_access_ctrl(_adapter *padapter, uint8_t *mac_addr);

#endif //_STA_INFO_H_

