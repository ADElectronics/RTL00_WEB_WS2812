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
#ifndef __HCI_SPEC_H__
#define __HCI_SPEC_H__


#if defined(CONFIG_GSPI_HCI)
#include "gspi/gspi_spec.h"

// SPI Header Files
#ifdef PLATFORM_LINUX
#include <linux/spi/spi.h>
#endif

#define GSPI_CMD_LEN		4
#define HAL_INTERFACE_CMD_LEN			GSPI_CMD_LEN
#define GSPI_STATUS_LEN		8
#define HAL_INTERFACE_CMD_STATUS_LEN   	GSPI_STATUS_LEN
#define HAL_INTERFACE_OVERHEAD			(HAL_INTERFACE_CMD_LEN+HAL_INTERFACE_OVERHEAD)
//reserve tx headroom in case of softap forwarding unicase packet 
#define RX_RESERV_HEADROOM		(SKB_WLAN_TX_EXTRA_LEN>RX_DRIVER_INFO+RXDESC_SIZE)?(SKB_WLAN_TX_EXTRA_LEN-RX_DRIVER_INFO-RXDESC_SIZE):0
typedef struct gspi_data
{
	//uint8_t  func_number;

	//uint8_t  tx_block_mode;
	//uint8_t  rx_block_mode;
	uint16_t block_transfer_len; //uint32_t block_transfer_len;

#ifdef PLATFORM_LINUX
	struct spi_device *func;

	struct workqueue_struct *priv_wq;
	struct delayed_work irq_work;
#endif

#if defined(PLATFORM_FREERTOS) || defined (PLATFORM_CMSIS_RTOS)
	_mutex 	spi_mutex;	
#endif
} GSPI_DATA, *PGSPI_DATA;

#define INTF_DATA GSPI_DATA

//extern void spi_set_intf_ops(struct _io_ops *pops);
extern void spi_int_hdl(PADAPTER padapter);
#define rtw_hci_interrupt_handler(__adapter) spi_int_hdl(__adapter)

#elif defined(CONFIG_SDIO_HCI)
#include "sdio/sdio_spec.h"

#define GSPI_CMD_LEN		0
#define HAL_INTERFACE_CMD_LEN			GSPI_CMD_LEN
#define GSPI_STATUS_LEN		8
#define HAL_INTERFACE_CMD_STATUS_LEN   	GSPI_STATUS_LEN
#define HAL_INTERFACE_OVERHEAD			(HAL_INTERFACE_CMD_LEN+HAL_INTERFACE_OVERHEAD)
#define RX_RESERV_HEADROOM		(SKB_WLAN_TX_EXTRA_LEN>RX_DRIVER_INFO+RXDESC_SIZE)?(SKB_WLAN_TX_EXTRA_LEN-RX_DRIVER_INFO-RXDESC_SIZE):0

typedef struct gspi_data
{
	//uint8_t  func_number;

	//uint8_t  tx_block_mode;
	//uint8_t  rx_block_mode;
	uint16_t block_transfer_len; //uint32_t block_transfer_len;

#ifdef PLATFORM_LINUX
	struct spi_device *func;

	struct workqueue_struct *priv_wq;
	struct delayed_work irq_work;
#endif

	struct sdio_func	 *func;

#if defined(PLATFORM_FREERTOS) || defined (PLATFORM_CMSIS_RTOS)
	_mutex 	spi_mutex;	
#endif
} GSPI_DATA, *PGSPI_DATA;

#define INTF_DATA GSPI_DATA

//extern void spi_set_intf_ops(struct _io_ops *pops);
extern void spi_int_hdl(PADAPTER padapter);
#define rtw_hci_interrupt_handler(__adapter) spi_int_hdl(__adapter)

#elif defined(CONFIG_USB_HCI)
#include <usb_ops.h>
#include <usb_osintf.h>

#elif defined(CONFIG_PCI_HCI)
#include <pci_osintf.h>
#ifdef PLATFORM_LINUX
#include <linux/pci.h>
#endif

#define 	INTF_CMD_LEN					0

#define	INTEL_VENDOR_ID				0x8086
#define	SIS_VENDOR_ID					0x1039
#define	ATI_VENDOR_ID					0x1002
#define	ATI_DEVICE_ID					0x7914
#define	AMD_VENDOR_ID					0x1022

#define	PCI_MAX_BRIDGE_NUMBER			255
#define	PCI_MAX_DEVICES				32
#define	PCI_MAX_FUNCTION				8

#define	PCI_CONF_ADDRESS   				0x0CF8   // PCI Configuration Space Address 
#define	PCI_CONF_DATA					0x0CFC   // PCI Configuration Space Data 

#define	PCI_CLASS_BRIDGE_DEV			0x06
#define	PCI_SUBCLASS_BR_PCI_TO_PCI	0x04

#define 	PCI_CAPABILITY_ID_PCI_EXPRESS	0x10

#define	U1DONTCARE 					0xFF	
#define	U2DONTCARE 					0xFFFF	
#define	U4DONTCARE 					0xFFFFFFFF

#define PCI_VENDER_ID_REALTEK		0x10ec

#define HAL_HW_PCI_8180_DEVICE_ID           	0x8180
#define HAL_HW_PCI_8185_DEVICE_ID           	0x8185	//8185 or 8185b
#define HAL_HW_PCI_8188_DEVICE_ID           	0x8188	//8185b		
#define HAL_HW_PCI_8198_DEVICE_ID           	0x8198	//8185b		
#define HAL_HW_PCI_8190_DEVICE_ID           	0x8190	//8190
#define HAL_HW_PCI_8723E_DEVICE_ID		0x8723	//8723E
#define HAL_HW_PCI_8192_DEVICE_ID           	0x8192	//8192 PCI-E
#define HAL_HW_PCI_8192SE_DEVICE_ID		0x8192	//8192 SE
#define HAL_HW_PCI_8174_DEVICE_ID           	0x8174	//8192 SE 
#define HAL_HW_PCI_8173_DEVICE_ID           	0x8173	//8191 SE Crab
#define HAL_HW_PCI_8172_DEVICE_ID           	0x8172	//8191 SE RE
#define HAL_HW_PCI_8171_DEVICE_ID           	0x8171	//8191 SE Unicron
#define HAL_HW_PCI_0045_DEVICE_ID			0x0045	//8190 PCI for Ceraga
#define HAL_HW_PCI_0046_DEVICE_ID			0x0046	//8190 Cardbus for Ceraga
#define HAL_HW_PCI_0044_DEVICE_ID			0x0044	//8192e PCIE for Ceraga
#define HAL_HW_PCI_0047_DEVICE_ID			0x0047	//8192e Express Card for Ceraga
#define HAL_HW_PCI_700F_DEVICE_ID			0x700F
#define HAL_HW_PCI_701F_DEVICE_ID			0x701F
#define HAL_HW_PCI_DLINK_DEVICE_ID		0x3304
#define HAL_HW_PCI_8192CET_DEVICE_ID		0x8191	//8192ce
#define HAL_HW_PCI_8192CE_DEVICE_ID		0x8178	//8192ce
#define HAL_HW_PCI_8191CE_DEVICE_ID		0x8177	//8192ce
#define HAL_HW_PCI_8188CE_DEVICE_ID		0x8176	//8192ce
#define HAL_HW_PCI_8192CU_DEVICE_ID      	0x8191	//8192ce
#define HAL_HW_PCI_8192DE_DEVICE_ID		0x8193	//8192de
#define HAL_HW_PCI_002B_DEVICE_ID			0x002B	//8192de, provided by HW SD
#define HAL_HW_PCI_8188EE_DEVICE_ID		0x8179

#define HAL_MEMORY_MAPPED_IO_RANGE_8190PCI 		0x1000     //8190 support 16 pages of IO registers
#define HAL_HW_PCI_REVISION_ID_8190PCI			0x00
#define HAL_MEMORY_MAPPED_IO_RANGE_8192PCIE	0x4000	//8192 support 16 pages of IO registers
#define HAL_HW_PCI_REVISION_ID_8192PCIE			0x01
#define HAL_MEMORY_MAPPED_IO_RANGE_8192SE		0x4000	//8192 support 16 pages of IO registers
#define HAL_HW_PCI_REVISION_ID_8192SE			0x10
#define HAL_HW_PCI_REVISION_ID_8192CE			0x1
#define HAL_MEMORY_MAPPED_IO_RANGE_8192CE		0x4000	//8192 support 16 pages of IO registers
#define HAL_HW_PCI_REVISION_ID_8192DE			0x0
#define HAL_MEMORY_MAPPED_IO_RANGE_8192DE		0x4000	//8192 support 16 pages of IO registers

enum pci_bridge_vendor {
	PCI_BRIDGE_VENDOR_INTEL = 0x0,//0b'0000,0001
	PCI_BRIDGE_VENDOR_ATI, //= 0x02,//0b'0000,0010
	PCI_BRIDGE_VENDOR_AMD, //= 0x04,//0b'0000,0100
	PCI_BRIDGE_VENDOR_SIS ,//= 0x08,//0b'0000,1000
	PCI_BRIDGE_VENDOR_UNKNOWN, //= 0x40,//0b'0100,0000
	PCI_BRIDGE_VENDOR_MAX ,//= 0x80
} ;

// copy this data structor defination from MSDN SDK
typedef struct _PCI_COMMON_CONFIG {
	uint16_t	VendorID;
	uint16_t	DeviceID;
	uint16_t	Command;
	uint16_t	Status;
	uint8_t	RevisionID;
	uint8_t	ProgIf;
	uint8_t	SubClass;
	uint8_t	BaseClass;
	uint8_t	CacheLineSize;
	uint8_t	LatencyTimer;
	uint8_t	HeaderType;
	uint8_t	BIST;

	union {
	struct _PCI_HEADER_TYPE_0 {
		uint32_t	BaseAddresses[6];
		uint32_t	CIS;
		uint16_t	SubVendorID;
		uint16_t	SubSystemID;
		uint32_t	ROMBaseAddress;
		uint8_t	CapabilitiesPtr;
		uint8_t	Reserved1[3];
		uint32_t	Reserved2;

		uint8_t	InterruptLine;
		uint8_t	InterruptPin;
		uint8_t	MinimumGrant;
		uint8_t	MaximumLatency;
	} type0;
#if 0
	struct _PCI_HEADER_TYPE_1 {
		uint32_t BaseAddresses[PCI_TYPE1_ADDRESSES];
		uint8_t PrimaryBusNumber;
		uint8_t SecondaryBusNumber;
		uint8_t SubordinateBusNumber;
		uint8_t SecondaryLatencyTimer;
		uint8_t IOBase;
		uint8_t IOLimit;
		uint16_t SecondaryStatus;
		uint16_t MemoryBase;
		uint16_t MemoryLimit;
		uint16_t PrefetchableMemoryBase;
		uint16_t PrefetchableMemoryLimit;
		uint32_t PrefetchableMemoryBaseUpper32;
		uint32_t PrefetchableMemoryLimitUpper32;
		uint16_t IOBaseUpper;
		uint16_t IOLimitUpper;
		uint32_t Reserved2;
		uint32_t ExpansionROMBase;
		uint8_t InterruptLine;
		uint8_t InterruptPin;
		uint16_t BridgeControl;
	} type1;

	struct _PCI_HEADER_TYPE_2 {
		uint32_t BaseAddress;
		uint8_t CapabilitiesPtr;
		uint8_t Reserved2;
		uint16_t SecondaryStatus;
		uint8_t PrimaryBusNumber;
		uint8_t CardbusBusNumber;
		uint8_t SubordinateBusNumber;
		uint8_t CardbusLatencyTimer;
		uint32_t MemoryBase0;
		uint32_t MemoryLimit0;
		uint32_t MemoryBase1;
		uint32_t MemoryLimit1;
		uint16_t IOBase0_LO;
		uint16_t IOBase0_HI;
		uint16_t IOLimit0_LO;
		uint16_t IOLimit0_HI;
		uint16_t IOBase1_LO;
		uint16_t IOBase1_HI;
		uint16_t IOLimit1_LO;
		uint16_t IOLimit1_HI;
		uint8_t InterruptLine;
		uint8_t InterruptPin;
		uint16_t BridgeControl;
		uint16_t SubVendorID;
		uint16_t SubSystemID;
		uint32_t LegacyBaseAddress;
		uint8_t Reserved3[56];
		uint32_t SystemControl;
		uint8_t MultiMediaControl;
		uint8_t GeneralStatus;
		uint8_t Reserved4[2];
		uint8_t GPIO0Control;
		uint8_t GPIO1Control;
		uint8_t GPIO2Control;
		uint8_t GPIO3Control;
		uint32_t IRQMuxRouting;
		uint8_t RetryStatus;
		uint8_t CardControl;
		uint8_t DeviceControl;
		uint8_t Diagnostic;
	} type2;
#endif
	} u;

	uint8_t	DeviceSpecific[108];
} PCI_COMMON_CONFIG , *PPCI_COMMON_CONFIG;

typedef struct _RT_PCI_CAPABILITIES_HEADER {
    uint8_t   CapabilityID;
    uint8_t   Next;
} RT_PCI_CAPABILITIES_HEADER, *PRT_PCI_CAPABILITIES_HEADER;

struct pci_priv{
	BOOLEAN		pci_clk_req;
	
	uint8_t	pciehdr_offset;
	//  PCIeCap is only differece between B-cut and C-cut.
	//  Configuration Space offset 72[7:4] 
	//  0: A/B cut 
	//  1: C cut and later.
	uint8_t	pcie_cap;
	uint8_t	linkctrl_reg;
	
	uint8_t	busnumber;
	uint8_t	devnumber;	
	uint8_t	funcnumber;	

	uint8_t	pcibridge_busnum;
	uint8_t	pcibridge_devnum;
	uint8_t	pcibridge_funcnum;
	uint8_t	pcibridge_vendor;
	uint16_t	pcibridge_vendorid;
	uint16_t	pcibridge_deviceid;
	uint8_t	pcibridge_pciehdr_offset;
	uint8_t	pcibridge_linkctrlreg;	

	uint8_t	amd_l1_patch;
};

typedef struct _RT_ISR_CONTENT
{
	union{
		uint32_t			IntArray[2];
		uint32_t			IntReg4Byte;
		uint16_t			IntReg2Byte;
	};
}RT_ISR_CONTENT, *PRT_ISR_CONTENT;

//#define RegAddr(addr)           (addr + 0xB2000000UL)
//some platform macros will def here
static inline void NdisRawWritePortUlong(uint32_t port,  uint32_t val) 		
{
	outl(val, port);
	//writel(val, (uint8_t *)RegAddr(port));	
}

static inline void NdisRawWritePortUchar(uint32_t port,  uint8_t val)
{
	outb(val, port);
	//writeb(val, (uint8_t *)RegAddr(port));
}

static inline void NdisRawReadPortUchar(uint32_t port, uint8_t *pval)
{
	*pval = inb(port);
	//*pval = readb((uint8_t *)RegAddr(port));
}

static inline void NdisRawReadPortUshort(uint32_t port, uint16_t *pval)
{
	*pval = inw(port);
	//*pval = readw((uint8_t *)RegAddr(port));
}

static inline void NdisRawReadPortUlong(uint32_t port, uint32_t *pval)
{
	*pval = inl(port);
	//*pval = readl((uint8_t *)RegAddr(port));
}
#elif defined(CONFIG_LX_HCI)
#define GSPI_CMD_LEN		0
#define GSPI_STATUS_LEN		0
#include "lxbus/lxbus_spec.h"
#endif // interface define

#if 0 //TODO
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
#endif
#endif //__HCI_SPEC_H__

