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

#ifndef _RTW_IO_H_
#define _RTW_IO_H_

//IO Bus domain address mapping
#define DEFUALT_OFFSET					0x0   
#define WLAN_LOCAL_OFFSET    			0x10250000
#define WLAN_IOREG_OFFSET   			0x10260000
#define FW_FIFO_OFFSET 	    			0x10270000
#define TX_HIQ_OFFSET	    				0x10310000
#define TX_MIQ_OFFSET					0x1032000
#define TX_LOQ_OFFSET					0x10330000
#define RX_RXOFF_OFFSET	    			0x10340000

struct fifo_more_data {
	uint32_t more_data;
	uint32_t len;
};

struct dvobj_priv;

typedef struct _io_ops {
		int (*init_io_priv)(struct dvobj_priv *pdvobj);
		int (*write8_endian)(struct dvobj_priv *pdvobj, uint32_t addr, uint32_t buf, uint32_t big);

		uint8_t (*_read8)(struct dvobj_priv *pdvobj, uint32_t addr, int32_t *err);		
		uint16_t (*_read16)(struct dvobj_priv *pdvobj, uint32_t addr, int32_t *err);		
		uint32_t (*_read32)(struct dvobj_priv *pdvobj, uint32_t addr, int32_t *err);

		int32_t  (*_write8)(struct dvobj_priv *pdvobj, uint32_t addr, uint8_t buf, int32_t *err);		
		int32_t  (*_write16)(struct dvobj_priv *pdvobj, uint32_t addr,uint16_t buf, int32_t *err);		
		int32_t  (*_write32)(struct dvobj_priv *pdvobj, uint32_t addr, uint32_t buf, int32_t *err);

		int (*read_rx_fifo)(struct dvobj_priv *pdvobj, uint32_t addr, uint8_t *buf, uint32_t len, struct fifo_more_data *more_data);
		int (*write_tx_fifo)(struct dvobj_priv *pdvobj, uint32_t addr, uint8_t *buf, uint32_t len);		
} IO_OPS_T;

struct bus_transfer {
	void	*tx_buf;
	void	*rx_buf;
	unsigned	int len;
};

typedef struct _bus_drv_ops {
		int (*bus_drv_init)(ADAPTER *Adapter);
		int (*bus_send_msg)(PADAPTER Adapter, struct bus_transfer xfers[], uint32_t RegAction);
} BUS_DRV_OPS_T;

/*
struct	intf_hdl {

	uint32_t	intf_option;
	uint32_t	bus_status;
	uint32_t	do_flush;
	uint8_t	*adapter;
	uint8_t	*intf_dev;	
	struct intf_priv	*pintfpriv;
	uint8_t	cnt;
	void (*intf_hdl_init)(uint8_t *priv);
	void (*intf_hdl_unload)(uint8_t *priv);
	void (*intf_hdl_open)(uint8_t *priv);
	void (*intf_hdl_close)(uint8_t *priv);
	struct	_io_ops	io_ops;
	//uint8_t intf_status;//moved to struct intf_priv
	uint16_t len;
	uint16_t done_len;	

	_adapter *padapter;
	struct dvobj_priv *pintf_dev;//	pointer to &(padapter->dvobjpriv);
	
	struct _io_ops	io_ops;

};
*/

struct io_priv{
	struct _io_ops	io_ops;
};


extern uint8_t rtw_read8(ADAPTER *adapter, uint32_t addr);
extern uint16_t rtw_read16(ADAPTER *adapter, uint32_t addr);
extern uint32_t rtw_read32(ADAPTER *adapter, uint32_t addr);
extern int32_t rtw_write8(ADAPTER *adapter, uint32_t addr, uint8_t val);
extern int32_t rtw_write16(ADAPTER *adapter, uint32_t addr, uint16_t val);
extern int32_t rtw_write32(ADAPTER *adapter, uint32_t addr, uint32_t val);

#define PlatformEFIOWrite1Byte(_a,_b,_c)		\
	rtw_write8(_a,_b,_c)
#define PlatformEFIOWrite2Byte(_a,_b,_c)		\
	rtw_write16(_a,_b,_c)
#define PlatformEFIOWrite4Byte(_a,_b,_c)		\
	rtw_write32(_a,_b,_c)

#define PlatformEFIORead1Byte(_a,_b)		\
		rtw_read8(_a,_b)
#define PlatformEFIORead2Byte(_a,_b)		\
		rtw_read16(_a,_b)
#define PlatformEFIORead4Byte(_a,_b)		\
		rtw_read32(_a,_b)

extern IO_OPS_T io_ops;

extern uint32_t rtw_write_port(
	ADAPTER *adapter,
	uint32_t addr,
	uint32_t cnt,
	uint8_t *mem);
extern uint32_t rtw_read_port(
	ADAPTER *adapter,
	uint32_t addr,
	uint32_t cnt,
	uint8_t *mem,
	struct fifo_more_data *more_data);
extern void rtw_set_chip_endian(PADAPTER padapter);
extern int rtw_get_chip_endian(PADAPTER padapter);

int rtw_init_io_priv(_adapter *padapter, void (*set_intf_ops)(struct _io_ops *pops));

#endif	//_RTW_IO_H_

