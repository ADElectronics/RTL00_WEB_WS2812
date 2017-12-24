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

#ifndef __FREERTOS_INTFS_H_
#define __FREERTOS_INTFS_H_

//TODO
#if 0

struct intf_priv {
	
	uint8_t *intf_dev;
	uint32_t	max_iosz; 	//USB2.0: 128, USB1.1: 64, SDIO:64
	uint32_t	max_xmitsz; //USB2.0: unlimited, SDIO:512
	uint32_t	max_recvsz; //USB2.0: unlimited, SDIO:512

	volatile uint8_t *io_rwmem;
	volatile uint8_t *allocated_io_rwmem;
	uint32_t	io_wsz; //unit: 4bytes
	uint32_t	io_rsz;//unit: 4bytes
	uint8_t intf_status;	
	
	void (*_bus_io)(uint8_t *priv);	

/*
Under Sync. IRP (SDIO/USB)
A protection mechanism is necessary for the io_rwmem(read/write protocol)

Under Async. IRP (SDIO/USB)
The protection mechanism is through the pending queue.
*/

	_mutex ioctl_mutex;

	
#ifdef PLATFORM_LINUX	
	#ifdef CONFIG_USB_HCI	
	// when in USB, IO is through interrupt in/out endpoints
	struct usb_device 	*udev;
	PURB	piorw_urb;
	uint8_t io_irp_cnt;
	uint8_t bio_irp_pending;
	_sema io_retevt;
	_timer	io_timer;
	uint8_t bio_irp_timeout;
	uint8_t bio_timer_cancel;
	#endif
#endif

#ifdef PLATFORM_OS_XP
	#ifdef CONFIG_SDIO_HCI
		// below is for io_rwmem...	
		PMDL pmdl;
		PSDBUS_REQUEST_PACKET  sdrp;
		PSDBUS_REQUEST_PACKET  recv_sdrp;
		PSDBUS_REQUEST_PACKET  xmit_sdrp;

			PIRP		piorw_irp;

	#endif
	#ifdef CONFIG_USB_HCI
		PURB	piorw_urb;
		PIRP		piorw_irp;
		uint8_t io_irp_cnt;
		uint8_t bio_irp_pending;
		_sema io_retevt;	
	#endif	
#endif

};	


#ifdef CONFIG_R871X_TEST
int rtw_start_pseudo_adhoc(_adapter *padapter);
int rtw_stop_pseudo_adhoc(_adapter *padapter);
#endif

#endif	//#if 0

typedef struct _driver_priv {
	int drv_registered;

	_mutex hw_init_mutex;
#if defined(CONFIG_CONCURRENT_MODE) || defined(CONFIG_DUALMAC_CONCURRENT)
	//global variable
	_mutex h2c_fwcmd_mutex;
	_mutex setch_mutex;
	_mutex setbw_mutex;
#endif
} drv_priv, *pdrv_priv;


struct net_device *rtw_init_netdev(_adapter *padapter);
void rtw_os_indicate_disconnect( _adapter *adapter );

#ifdef CONFIG_PROC_DEBUG
void rtw_proc_init_one(struct net_device *dev);
void rtw_proc_remove_one(struct net_device *dev);
#else
//static void should be declared in .c file
//proc is not supported in freertos
//static void rtw_proc_init_one(struct net_device *dev){}
//static void rtw_proc_remove_one(struct net_device *dev){}
#define rtw_proc_init_one(dev)
#define rtw_proc_remove_one(dev)
#endif

extern int rtw_set_wpa_ie(_adapter *padapter, char *pie, unsigned short ielen);
extern void rtw_os_indicate_connect(_adapter *adapter);
extern void indicate_wx_custom_event(_adapter *padapter, char *msg);
extern int rtw_init_netdev_name(struct net_device *pnetdev, const char *ifname);
extern void netdev_lwip_post_sleep_processing(void);
extern void wireless_send_event(struct net_device *dev, unsigned int cmd, union iwreq_data *wrqu, char *extra);

#ifdef CONFIG_CONCURRENT_MODE
struct _io_ops;
_adapter *rtw_drv_if2_init(_adapter *primary_padapter, char *name, void (*set_intf_ops)(struct _io_ops *pops));
void rtw_drv_if2_free(_adapter *pbuddy_padapter);
#endif

#if defined(CONFIG_ISR_THREAD_MODE_POLLING) || defined(CONFIG_ISR_THREAD_MODE_INTERRUPT)
extern thread_return rtw_interrupt_thread(thread_context context);
#endif

#ifdef CONFIG_RECV_TASKLET_THREAD
extern thread_return rtw_recv_tasklet(thread_context context);
#endif

#ifdef CONFIG_XMIT_TASKLET_THREAD
extern thread_return rtw_xmit_tasklet(thread_context context);
#endif

extern struct net_device *rtw_drv_probe(struct net_device* parent_dev, uint32_t mode);	//Wlan driver init entry
extern void rtw_drv_entry(void);
extern void rtw_drv_halt(void);
extern int rtw_dev_remove(struct net_device *pnetdev);
extern int rtw_ioctl(struct net_device *dev, struct iwreq *rq, int cmd);

#if defined(CONFIG_LX_HCI)
uint32_t lextra_bus_dma_Interrupt (void* data);
#endif

#endif	//__FREERTOS_INTFS_H_

