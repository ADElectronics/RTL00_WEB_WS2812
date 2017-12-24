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
/*-------------------------------------------------------------------------------

	For type defines and data structure defines

--------------------------------------------------------------------------------*/


#ifndef __DRV_TYPES_H__
#define __DRV_TYPES_H__

#include <drv_conf.h>


#ifdef PLATFORM_OS_XP
#include <drv_types_xp.h>
#endif

#ifdef PLATFORM_OS_CE
#include <drv_types_ce.h>
#endif

#ifdef PLATFORM_LINUX
#include <drv_types_linux.h>
#endif


#if defined (__ICCARM__)
#define _PACKED         __packed
#define _WEAK           __weak
#else
#define _PACKED         __attribute__ ((packed))
#define _WEAK           __attribute__ ((weak))
#endif

// Assign memory sectinon usage
#if defined(CONFIG_PLATFORM_8195A) || defined(CONFIG_PLATFORM_8711B)
#include <section_config.h>
//#include "rtl_utility_ram.h"
#include "platform/platform_stdlib.h"

#else
#define SRAM_BD_DATA_SECTION
#define WLAN_ROM_TEXT_SECTION
#define WLAN_ROM_DATA_SECTION
#define _LONG_CALL_     
#endif

#ifdef CONFIG_TRACE_SKB
#define SKBLIST_ALL								0xFFFFFFFF
// receive
#define	SKBLIST_RECVBUF_MASK					0x0000000F
#define	SKBLIST_RECVBUF							0x00000001
#define	SKBLIST_RECVBUF_FREEQUEUE				0x00000002
#define	SKBLIST_RECVBUF_PENDINGQUEUE			0x00000004

#define	SKBLIST_RECVFRAME_MASK					0x000000F0
#define	SKBLIST_RECVFRAME						0x00000010
#define	SKBLIST_RECVFRAME_FREEQUEUE				0x00000020
#define	SKBLIST_RECVFRAME_SWDECQUEUE			0x00000040
#ifdef CONFIG_RECV_REORDERING_CTRL
#define	SKBLIST_RECVFRAME_REORDERQUEUE			0x00000080
#endif

// transmit
#define	SKBLIST_XMITBUF_MASK					0x0000FF00
#define	SKBLIST_XMITBUF							0x00000100
#define	SKBLIST_XMITEXTBUF						0x00000200
#define	SKBLIST_XMITBUF_FREEQUEUE				0x00000400
#define	SKBLIST_XMITEXTBUF_FREEQUEUE			0x00000800
#define	SKBLIST_XMITBUF_PENDINGQUEUE			0x00001000
#ifdef CONFIG_SDIO_TX_MULTI_QUEUE
#define	SKBLIST_XMITBUF_PENDING0QUEUE			0x00002000
#define	SKBLIST_XMITBUF_PENDING1QUEUE			0x00004000
#define	SKBLIST_XMITBUF_PENDING2QUEUE			0x00008000
#endif

#define	SKBLIST_XMITFRAME_MASK					0x0FFF0000
#define	SKBLIST_XMITFRAME						0x00010000
#define	SKBLIST_XMITFRAME_FREEQUEUE				0x00020000
#define	SKBLIST_XMITFRAME_SLEEPQUEUE			0x00040000
#define	SKBLIST_XMITFRAME_VOQUEUE				0x00100000
#define	SKBLIST_XMITFRAME_VIQUEUE				0x00200000
#define	SKBLIST_XMITFRAME_BEQUEUE				0x00400000
#define	SKBLIST_XMITFRAME_BKQUEUE				0x00800000
#define	SKBLIST_XMITFRAME_BMQUEUE				0x01000000

#define	SKBLIST_POOL							0x10000000
#endif

enum _NIC_VERSION {

	RTL8711_NIC,
	RTL8712_NIC,
	RTL8713_NIC,
	RTL8716_NIC

};

typedef struct _ADAPTER _adapter, ADAPTER, *PADAPTER;

#include "wireless.h"
#include <netdev.h>
#include <osdep_service.h>
#include <rtw_byteorder.h>
#include <rtw_io.h>
#include <hci_spec.h>

#include <wifi.h>

#ifdef CONFIG_80211N_HT
#include <rtw_ht.h>
#endif

#include <wlan_basic_types.h>
#include <rtw_intfs.h>
//#include <hal_pg.h>
#include <wlan_bssdef.h>
#include <rtw_cmd.h>
#include <rtw_xmit.h>
#include <rtw_recv.h>
#include <hal_com.h>
#include <rtw_qos.h>
#ifdef CONFIG_INCLUDE_WPA_PSK
#include <rtw_psk.h>
#endif
#include <rtw_security.h>
#include <rom_rtw_security.h>
#include <rtw_pwrctrl.h>
#include <rtw_eeprom.h>
#include <sta_info.h>
#include <rtw_mlme.h>
#include <rtw_debug.h>
#include <ieee80211.h>
#include <rom_ieee80211.h>
#include <rtw_ioctl_set.h>
#include <rtw_rf.h>
#include <rtw_event.h>
#include <rtw_led.h>
#include <rtw_mlme_ext.h>
#ifdef CONFIG_P2P_NEW
#include <rtw_p2p.h>
#endif
//#include <rtw_tdls.h>
#include <rtw_ap.h>
#include <rtw_efuse.h>

#include <osdep_intf.h>

#include <hci_intfs.h>

#ifdef CONFIG_WAPI_SUPPORT
#include <rtw_wapi.h>
#endif

#ifdef CONFIG_DRVEXT_MODULE
#include <drvext_api.h>
#endif

#ifdef CONFIG_MP_INCLUDED
#include <rtw_mp.h>
#endif

#ifdef CONFIG_BR_EXT
#include <rtw_br_ext.h>
#endif	// CONFIG_BR_EXT

#ifdef CONFIG_IOCTL_CFG80211
	#include "ioctl_cfg80211.h"
#endif //CONFIG_IOCTL_CFG80211

#define SPEC_DEV_ID_NONE BIT(0)
#define SPEC_DEV_ID_DISABLE_HT BIT(1)
#define SPEC_DEV_ID_ENABLE_PS BIT(2)
#define SPEC_DEV_ID_RF_CONFIG_1T1R BIT(3)
#define SPEC_DEV_ID_RF_CONFIG_2T2R BIT(4)
#define SPEC_DEV_ID_ASSIGN_IFNAME BIT(5)

struct specific_device_id{

	uint32_t		flags;

	uint16_t		idVendor;
	uint16_t		idProduct;

};

struct registry_priv
{
	uint8_t	chip_version;
//	uint8_t	rfintfs;
//	uint8_t	lbkmode;
	uint8_t	hci;
	NDIS_802_11_SSID	ssid;
//	uint8_t	network_mode;	//infra, ad-hoc, auto
	uint8_t	channel;//ad-hoc support requirement
	uint8_t	wireless_mode;//A, B, G, auto
	uint8_t 	scan_mode;//active, passive
//	uint8_t	radio_enable;
//	uint8_t	preamble;//long, short, auto
	uint8_t	vrtl_carrier_sense;//Enable, Disable, Auto
	uint8_t	vcs_type;//RTS/CTS, CTS-to-self
	uint16_t	rts_thresh;
//	uint8_t	adhoc_tx_pwr;
	uint8_t	soft_ap;
	uint8_t	power_mgnt;
	uint8_t 	ps_enable;
	uint8_t	ips_mode;
	uint8_t	smart_ps;
//	uint8_t	long_retry_lmt;
//	uint8_t	short_retry_lmt;
//	uint16_t	busy_thresh;
//	uint8_t	ack_policy;
	uint8_t	mp_mode;
	uint8_t	software_encrypt;
	uint8_t	software_decrypt;
	#ifdef CONFIG_TX_EARLY_MODE
	uint8_t   	early_mode;
	#endif
	uint8_t	acm_method;
	  //UAPSD
	uint8_t	wmm_enable;
	uint8_t	uapsd_enable;
//	uint8_t	uapsd_max_sp;
//	uint8_t	uapsd_acbk_en;
//	uint8_t	uapsd_acbe_en;
//	uint8_t	uapsd_acvi_en;
//	uint8_t	uapsd_acvo_en;

//	WLAN_BSSID_EX    dev_network;
	uint32_t  beacon_period;

#ifdef CONFIG_80211N_HT
	uint8_t	ht_enable;
#if !defined(NOT_SUPPORT_40M)
	uint8_t	cbw40_enable;
#endif
	uint8_t	ampdu_enable;//for tx
	uint8_t 	rx_stbc;
	uint8_t	ampdu_amsdu;//A-MPDU Supports A-MSDU is permitted
#endif
	//uint8_t	lowrate_two_xmit;

	uint8_t	rf_config ;
//	uint8_t	low_power ;
	uint8_t	power_percentage_idx;

	uint8_t	wifi_spec;// !turbo_mode

	uint8_t	channel_plan;
#ifdef CONFIG_BT_COEXIST
	uint8_t	btcoex;
	uint8_t	bt_iso;
	uint8_t	bt_sco;
	uint8_t	bt_ampdu;
#endif
#if RX_AGGREGATION 
	BOOLEAN	bAcceptAddbaReq;
#endif
//	uint8_t	antdiv_cfg;
//	uint8_t	antdiv_type;

#ifdef CONFIG_AUTOSUSPEND
	uint8_t	usbss_enable;//0:disable,1:enable
#endif
#ifdef SUPPORT_HW_RFOFF_DETECTED
	uint8_t	hwpdn_mode;//0:disable,1:enable,2:decide by EFUSE config
	uint8_t	hwpwrp_detect;//0:disable,1:enable
#endif
#ifdef CONFIG_SUPPORT_HW_WPS_PBC
	uint8_t	hw_wps_pbc;//0:disable,1:enable
#endif

#ifdef CONFIG_ADAPTOR_INFO_CACHING_FILE
	char	adaptor_info_caching_file_path[PATH_LENGTH_MAX];
#endif

#ifdef CONFIG_LAYER2_ROAMING
	uint8_t	max_roaming_times; // the max number driver will try to roaming
#endif

#ifdef CONFIG_IOL
	bool 	force_iol; //enable iol without other concern
#endif

#ifdef CONFIG_80211D
	uint8_t 	enable80211d;
#endif

	uint8_t 	ifname[16];
	uint8_t 	if2name[16];
	
#if (RTW_NOTCH_FILTER != 0)
	uint8_t 	notch_filter;
#endif

#ifdef CONFIG_SPECIAL_SETTING_FOR_FUNAI_TV
	uint8_t 	force_ant;//0 normal,1 main,2 aux
	uint8_t 	force_igi;//0 normal
#endif

	//define for tx power adjust
	uint8_t	RegEnableTxPowerLimit;
	uint8_t	RegEnableTxPowerByRate;
#ifdef CONFIG_RF_GAIN_OFFSET
	uint8_t	RegEnableKFree;
#endif
	uint8_t	RegPowerBase;
	uint8_t	RegPwrTblSel;

	uint8_t adaptivity_en;
	uint8_t adaptivity_mode;
	uint8_t adaptivity_dml;
	uint8_t adaptivity_dc_backoff;
	int8_t adaptivity_th_l2h_ini;
//	uint8_t nhm_en;
};

//For registry parameters
#define RGTRY_OFT(field) ((uint32_t)FIELD_OFFSET(struct registry_priv,field))
#define RGTRY_SZ(field)   sizeof(((struct registry_priv*) 0)->field)
#define BSSID_OFT(field) ((uint32_t)FIELD_OFFSET(WLAN_BSSID_EX,field))
#define BSSID_SZ(field)   sizeof(((PWLAN_BSSID_EX) 0)->field)

#define MAX_CONTINUAL_URB_ERR 4

#ifdef CONFIG_CONCURRENT_MODE
#define is_primary_adapter(adapter) (adapter->adapter_type == PRIMARY_ADAPTER)
#define get_iface_type(adapter) (adapter->iface_type)
#else
#define is_primary_adapter(adapter) (1)
#define get_iface_type(adapter) (IFACE_PORT0)
#endif

enum _IFACE_TYPE {
	IFACE_PORT0, //mapping to port0 for C/D series chips
	IFACE_PORT1, //mapping to port1 for C/D series chip
	MAX_IFACE_PORT,
};

enum _ADAPTER_TYPE {
	PRIMARY_ADAPTER,
	SECONDARY_ADAPTER,
	MAX_ADAPTER,
};

struct dvobj_priv
{
	void *if1;
#ifdef CONFIG_CONCURRENT_MODE	
	void *if2;
#endif

	//For 92D, DMDP have 2 interface.
	//uint8_t	InterfaceNumber;
	//uint8_t	NumInterfaces;
#ifdef CONFIG_CONCURRENT_MODE
	void *padapters[MAX_IFACE_PORT];
	uint8_t iface_nums; // total number of ifaces used runtime
#endif
	//In /Out Pipe information
	//int	RtInPipe[2];
	uint8_t	RtOutPipe[3];//int	RtOutPipe[3];
	uint8_t	Queue2Pipe[HW_QUEUE_ENTRY];//for out pipe mapping

	//uint8_t	irq_alloc;

/*-------- below is for SDIO INTERFACE --------*/
#if defined(CONFIG_SDIO_HCI) || defined(CONFIG_GSPI_HCI)
	//
	// SDIO ISR Related
	//
	uint32_t sdio_himr;

	//
	// SDIO Tx FIFO related.
	//
	// HIQ, MID, LOW, PUB free pages; padapter->xmitpriv.free_txpg
	uint8_t  SdioTxFIFOFreePage[TX_FREE_PG_QUEUE];
	_lock SdioTxFIFOFreePageLock;

	//
	// SDIO Rx FIFO related.
	//
	uint16_t SdioRxFIFOSize;

#ifdef INTF_DATA
	INTF_DATA intf_data;
#endif
#endif //CONFIG_SDIO_HCI

/*-------- below is for USB INTERFACE --------*/

#ifdef CONFIG_USB_HCI

	uint8_t	irq_alloc; 
	uint8_t	nr_endpoint;
	uint8_t	ishighspeed;
	uint8_t	RtNumInPipes;
	uint8_t	RtNumOutPipes;
	int	ep_num[5]; //endpoint number

	int	RegUsbSS;

	_sema	usb_suspend_sema;

#ifdef CONFIG_USB_VENDOR_REQ_MUTEX
	_mutex  usb_vendor_req_mutex;
#endif

#ifdef CONFIG_USB_VENDOR_REQ_BUFFER_PREALLOC
	uint8_t * usb_alloc_vendor_req_buf;
	uint8_t * usb_vendor_req_buf;
#endif

#ifdef PLATFORM_WINDOWS
	//related device objects
	PDEVICE_OBJECT	pphysdevobj;//pPhysDevObj;
	PDEVICE_OBJECT	pfuncdevobj;//pFuncDevObj;
	PDEVICE_OBJECT	pnextdevobj;//pNextDevObj;

	uint8_t	nextdevstacksz;//unsigned char NextDeviceStackSize;	//= (CHAR)CEdevice->pUsbDevObj->StackSize + 1;

	//urb for control diescriptor request

#ifdef PLATFORM_OS_XP
	struct _URB_CONTROL_DESCRIPTOR_REQUEST descriptor_urb;
	PUSB_CONFIGURATION_DESCRIPTOR	pconfig_descriptor;//UsbConfigurationDescriptor;
#endif

#ifdef PLATFORM_OS_CE
	WCHAR			active_path[MAX_ACTIVE_REG_PATH];	// adapter regpath
	USB_EXTENSION	usb_extension;

	_nic_hdl		pipehdls_r8192c[0x10];
#endif

	uint32_t	config_descriptor_len;//uint32_t UsbConfigurationDescriptorLength;
#endif//PLATFORM_WINDOWS

#ifdef PLATFORM_LINUX
	struct usb_interface *pusbintf;
	struct usb_device *pusbdev;
#endif//PLATFORM_LINUX

#ifdef PLATFORM_FREEBSD
	struct usb_interface *pusbintf;
	struct usb_device *pusbdev;
#endif//PLATFORM_FREEBSD
	ATOMIC_T continual_urb_error;
#endif//CONFIG_USB_HCI

/*-------- below is for PCIE INTERFACE --------*/

#ifdef CONFIG_PCI_HCI
	uint8_t	irq_alloc; 

#ifdef PLATFORM_LINUX
	struct pci_dev *ppcidev;

	//PCI MEM map
	unsigned long	pci_mem_end;	/* shared mem end	*/
	unsigned long	pci_mem_start;	/* shared mem start	*/

	//PCI IO map
	unsigned long	pci_base_addr;	/* device I/O address	*/

	//PciBridge
	struct pci_priv	pcipriv;

	uint16_t	irqline;
	uint8_t	irq_enabled;
	RT_ISR_CONTENT	isr_content;
	_lock	irq_th_lock;

	//ASPM
	uint8_t	const_pci_aspm;
	uint8_t	const_amdpci_aspm;
	uint8_t	const_hwsw_rfoff_d3;
	uint8_t	const_support_pciaspm;
	// pci-e bridge */
	uint8_t 	const_hostpci_aspm_setting;
	// pci-e device */
	uint8_t 	const_devicepci_aspm_setting;
	uint8_t 	b_support_aspm; // If it supports ASPM, Offset[560h] = 0x40, otherwise Offset[560h] = 0x00.
	uint8_t	b_support_backdoor;
	uint8_t bdma64;
#endif//PLATFORM_LINUX

#if defined(PLATFORM_FREERTOS) || defined (PLATFORM_CMSIS_RTOS)
	uint8_t	irq_enabled;
	_lock	irq_th_lock;
#endif //PLATFORM_FREERTOS

#endif//CONFIG_PCI_HCI

#ifdef CONFIG_LX_HCI
	uint8_t	irq_alloc; 
#if defined(PLATFORM_FREERTOS) || defined (PLATFORM_CMSIS_RTOS)
	uint8_t	irq_enabled;
	_lock	irq_th_lock;
#endif //PLATFORM_FREERTOS
#endif

};

#ifdef PLATFORM_LINUX
static struct device *dvobj_to_dev(struct dvobj_priv *dvobj)
{
	/* todo: get interface type from dvobj and the return the dev accordingly */
#ifdef RTW_DVOBJ_CHIP_HW_TYPE
#endif

#ifdef CONFIG_USB_HCI
	return &dvobj->pusbintf->dev;
#endif
#ifdef CONFIG_SDIO_HCI
	return &dvobj->intf_data.func->dev;
#endif
#ifdef CONFIG_GSPI_HCI
	return &dvobj->intf_data.func->dev;
#endif
#ifdef CONFIG_PCI_HCI
	return &dvobj->ppcidev->dev;
#endif
}
#endif

#ifdef CONFIG_CONCURRENT_MODE
struct co_data_priv{

	//george@20120518
	//current operating channel/bw/ch_offset
	//save the correct ch/bw/ch_offset whatever the inputted values are
	//when calling set_channel_bwmode() at concurrent mode
	//for debug check or reporting to layer app (such as wpa_supplicant for nl80211)
	uint8_t co_ch;
	uint8_t co_bw;
	uint8_t co_ch_offset;
	uint8_t rsvd;

};
#endif //CONFIG_CONCURRENT_MODE

typedef enum _DRIVER_STATE{
	DRIVER_NORMAL = 0,
	DRIVER_DISAPPEAR = 1,
	DRIVER_REPLACE_DONGLE = 2,
}DRIVER_STATE;

#ifdef CONFIG_INTEL_PROXIM
struct proxim {
	bool proxim_support;
	bool proxim_on;

	void *proximity_priv;
	int (*proxim_rx)(_adapter *padapter,
		union recv_frame *precv_frame);
	uint8_t	(*proxim_get_var)(_adapter* padapter, uint8_t type);
};
#endif	//CONFIG_INTEL_PROXIM

#ifdef CONFIG_MAC_LOOPBACK_DRIVER
typedef struct loopbackdata
{
	_sema	sema;
	_thread_hdl_ lbkthread;
	uint8_t bstop;
	uint32_t cnt;
	uint16_t size;
	uint16_t txsize;
	uint8_t txbuf[0x8000];
	uint16_t rxsize;
	uint8_t rxbuf[0x8000];
	uint8_t msg[100];

}LOOPBACKDATA, *PLOOPBACKDATA;
#endif

struct _ADAPTER{
#ifdef CONFIG_EASY_REPLACEMENT
	int	DriverState;// for disable driver using module, use dongle to replace module.
	int	bDongle;//build-in module or external dongle

#endif
#ifdef PLATFORM_LINUX
	int	pid[3];//process id from UI, 0:wps, 1:hostapd, 2:dhcpcd
#endif	

#ifdef CONFIG_PROC_DEBUG
	uint16_t 	chip_type;
#endif

	uint16_t	HardwareType;
	uint16_t	interface_type;//USB,SDIO,SPI,PCI
	uint32_t	work_mode; //STA, AP, STA+AP, PROMISC, P2P

	struct	dvobj_priv	*dvobj;
	struct	mlme_priv	mlmepriv;
	struct	mlme_ext_priv	mlmeextpriv;
	struct	cmd_priv	cmdpriv;
	struct	evt_priv	evtpriv;
	//struct	io_queue	*pio_queue;
	struct 	io_priv	iopriv;
	struct	xmit_priv	xmitpriv;
	struct	recv_priv	recvpriv;
	struct	sta_priv	stapriv;
	struct	security_priv	securitypriv;
	struct	registry_priv	registrypriv;
	struct	pwrctrl_priv	pwrctrlpriv;
	struct 	eeprom_priv eeprompriv;
//TODO
//	struct	led_priv	ledpriv;


#ifdef CONFIG_MP_INCLUDED
       struct	mp_priv	mppriv;
#endif

#ifdef CONFIG_DRVEXT_MODULE
	struct	drvext_priv	drvextpriv;
#endif

#if defined(CONFIG_HOSTAPD_MLME) && defined (CONFIG_AP_MODE)
	struct	hostapd_priv	*phostapdpriv;
#endif

#ifdef CONFIG_IOCTL_CFG80211
#ifdef CONFIG_P2P
	struct cfg80211_wifidirect_info	cfg80211_wdinfo;
#endif //CONFIG_P2P
#endif //CONFIG_IOCTL_CFG80211

#ifdef CONFIG_P2P_NEW
	struct wifidirect_info	wdinfo;
#endif //CONFIG_P2P

#ifdef CONFIG_TDLS
	struct tdls_info	tdlsinfo;
#endif //CONFIG_TDLS

#ifdef CONFIG_WAPI_SUPPORT
	uint8_t	WapiSupport;
	RT_WAPI_T	wapiInfo;
#endif


#ifdef CONFIG_WFD
	struct wifi_display_info wfd_info;
#endif //CONFIG_WFD

	PVOID		HalData;
	uint32_t 		hal_data_sz;
	struct hal_ops	HalFunc;

	int32_t	bDriverStopped;
	int32_t	bSurpriseRemoved;
	int32_t	bCardDisableWOHSM;
	uint8_t	RxStop;	//Used to stop rx thread as early as possible

	uint32_t	IsrContent;
	uint32_t	ImrContent;

	uint8_t	EepromAddressSize;
	uint8_t	hw_init_completed;
	uint8_t	bDriverIsGoingToUnload;
	uint8_t	init_adpt_in_progress;
	uint8_t	bMpDriver;

#ifdef CONFIG_AP_MODE
	uint8_t	bForwardingDisabled;
#endif

#if defined(CONFIG_EVENT_THREAD_MODE)
	_thread_hdl_	evtThread;
#endif
#if defined(CONFIG_ISR_THREAD_MODE_POLLING) || defined(CONFIG_ISR_THREAD_MODE_INTERRUPT)
	struct task_struct	isrThread;
#endif
	struct task_struct	cmdThread;
#ifdef CONFIG_XMIT_THREAD_MODE
	struct task_struct	xmitThread;
#endif
#if defined(CONFIG_RECV_THREAD_MODE)
	struct task_struct	recvThread;
#endif
#ifdef CONFIG_RECV_TASKLET_THREAD
	struct task_struct	recvtasklet_thread;
#endif
#ifdef CONFIG_XMIT_TASKLET_THREAD
#ifdef PLATFORM_LINUX
	struct tasklet_struct xmit_tasklet;
#else
	struct task_struct	xmittasklet_thread;
#endif
#endif
#ifdef CONFIG_SDIO_XMIT_THREAD
	struct task_struct	SdioXmitThread;
#endif //CONFIG_XMIT_TASKLET_THREAD


#if !defined(PLATFORM_LINUX) && !defined(PLATFORM_ECOS) && !defined(PLATFORM_FREERTOS) && !defined(PLATFORM_CMSIS_RTOS)
	NDIS_STATUS (*dvobj_init)(struct dvobj_priv *dvobj);
	void (*dvobj_deinit)(struct dvobj_priv *dvobj);
#endif

	void (*intf_start)(_adapter * adapter);
	void (*intf_stop)(_adapter * adapter);

#ifdef PLATFORM_WINDOWS
	_nic_hdl		hndis_adapter;//hNdisAdapter(NDISMiniportAdapterHandle);
	_nic_hdl		hndis_config;//hNdisConfiguration;
	NDIS_STRING fw_img;

	uint32_t	NdisPacketFilter;
	uint8_t	MCList[MAX_MCAST_LIST_NUM][6];
	uint32_t	MCAddrCount;
#endif //end of PLATFORM_WINDOWS

#ifdef PLATFORM_ECOS
	_nic_hdl pnetdev;
	int bup;
	struct net_device_stats stats;
#endif	//#ifdef PLATFORM_ECOS

#if defined(PLATFORM_FREERTOS) || defined (PLATFORM_CMSIS_RTOS)
	_nic_hdl	pnetdev;
	int		bup;
	struct net_device_stats stats;
#endif	//#ifdef PLATFORM_FREERTOS

#ifdef PLATFORM_LINUX
	_nic_hdl pnetdev;

	// used by rtw_rereg_nd_name related function
	struct rereg_nd_name_data {
		_nic_hdl old_pnetdev;
		char old_ifname[IFNAMSIZ];
		uint8_t old_ips_mode;
		uint8_t old_bRegUseLed;
	} rereg_nd_name_priv;

	int bup;
	struct net_device_stats stats;
	struct iw_statistics iwstats;
	struct proc_dir_entry *dir_dev;// for proc directory

#ifdef CONFIG_IOCTL_CFG80211
	struct wireless_dev *rtw_wdev;
#endif //CONFIG_IOCTL_CFG80211

#endif //end of PLATFORM_LINUX

#ifdef PLATFORM_FREEBSD
	_nic_hdl pifp;
	int bup;
	_lock glock;
#endif //PLATFORM_FREEBSD
	uint8_t net_closed;

	uint8_t bFWReady;
	//uint8_t bBTFWReady;
	//uint8_t bReadPortCancel;
	//uint8_t bWritePortCancel;
	uint8_t bLinkInfoDump;
	uint8_t bRxRSSIDisplay;
#ifdef CONFIG_AUTOSUSPEND
	uint8_t	bDisableAutosuspend;
#endif

	_adapter *pbuddy_adapter;

	_mutex *hw_init_mutex;
#if defined(CONFIG_CONCURRENT_MODE) 
	uint8_t isprimary; //is primary adapter or not
	uint8_t adapter_type;
	uint8_t iface_type; //interface port type

	//for global synchronization
	_mutex *ph2c_fwcmd_mutex;
	_mutex *psetch_mutex;
	_mutex *psetbw_mutex;

	struct co_data_priv *pcodatapriv;//data buffer shared among interfaces
#endif

#ifdef CONFIG_BR_EXT
	_lock					br_ext_lock;
	//unsigned int			macclone_completed;
	struct nat25_network_db_entry	*nethash[NAT25_HASH_SIZE];
	int				pppoe_connection_in_progress;
	unsigned char			pppoe_addr[MACADDRLEN];
	unsigned char			scdb_mac[MACADDRLEN];
	unsigned char			scdb_ip[4];
	struct nat25_network_db_entry	*scdb_entry;
	unsigned char			br_mac[MACADDRLEN];
	unsigned char			br_ip[4];

	struct br_ext_info		ethBrExtInfo;
#endif	// CONFIG_BR_EXT

#ifdef CONFIG_INTEL_PROXIM
	/* intel Proximity, should be alloc mem
	 * in intel Proximity module and can only
	 * be used in intel Proximity mode */
	struct proxim proximity;
#endif	//CONFIG_INTEL_PROXIM

#ifdef CONFIG_MAC_LOOPBACK_DRIVER
	PLOOPBACKDATA ploopback;
#endif

        uint8_t    fix_rate;
#ifdef CONFIG_CAC_TEST
	unsigned char     in_cta_test;
#endif
	/* This flag is used to dynamically enabling debug message if
	  	certain sympton happen. Use iwpriv command to enable it */
#if defined(CONFIG_DEBUG_DYNAMIC)	
	uint8_t	debug_level;
#endif

};

#define adapter_to_dvobj(adapter) (adapter->dvobj)
#define adapter_to_pwrctl(adapter) (&adapter->pwrctrlpriv)

int rtw_handle_dualmac(_adapter *adapter, bool init);

__inline static uint8_t *myid(struct eeprom_priv *peepriv)
{
	return (peepriv->mac_addr);
}

#if 0 //#if (CONFIG_LWIP_LAYER == 0)
// For FPGA test program
#define _htons(x) (x)
#define _htons(x) (x)
#define _htons(x) (x)
#define _htons(x) (x)
#endif

//fast reconnection function prototype
typedef int (*init_done_ptr)(void);
#endif //__DRV_TYPES_H__

