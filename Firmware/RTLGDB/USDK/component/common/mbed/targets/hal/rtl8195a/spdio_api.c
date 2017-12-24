#include <spdio_api.h>
#include "hal_sdio.h"

#if 0 // - 	HalSdioRegisterTxCallback(spdio_rx_done_cb, (void *)obj); // ?????????? HalSdioRegisterRxDoneCallback(spdio_tx_done_cb, (void *)obj); // ?????????

struct spdio_t *g_spdio_priv = NULL;

int8_t spdio_rx_done_cb(void *padapter, uint8_t *data, uint16_t offset, uint16_t pktsize, uint8_t type){
	struct spdio_buf_t *buf = (struct spdio_buf_t *)data;
	struct spdio_t *obj = (struct spdio_t *)padapter;

	if(obj)
		return obj->rx_done_cb(obj, buf, (uint8_t *)(buf->buf_addr+offset), pktsize, type);
	else
		SPDIO_API_PRINTK("spdio rx done callback function is null!");
	return SUCCESS;
}

int8_t spdio_tx_done_cb(void *padapter, uint8_t *data, uint16_t offset, uint16_t pktsize, uint8_t type){
	struct spdio_t *obj = (struct spdio_t *)padapter;
	struct spdio_buf_t *buf = (struct spdio_buf_t *)data;
	if(obj)
		return obj->tx_done_cb(obj, buf);
	else
		SPDIO_API_PRINTK("spdio tx done callback function is null!");
	return SUCCESS;		
}


int8_t spdio_tx(struct spdio_t *obj, struct spdio_buf_t *pbuf){
extern int8_t HalSdioRxCallback(PHAL_SDIO_ADAPTER pSDIODev, void *pData, uint16_t Offset, uint16_t PktSize, uint8_t CmdType);
	return HalSdioRxCallback((uint8_t *)pbuf, 0, pbuf->buf_size, pbuf->type); // ?????????
}

void spdio_structinit(struct spdio_t *obj){
	obj->rx_bd_bufsz = SPDIO_RX_BUFSZ_ALIGN(2048+24); //extra 24 bytes for sdio header
	obj->rx_bd_num = 24;
	obj->tx_bd_num = 24;
	obj->priv = NULL;
	obj->rx_buf = NULL;
	obj->rx_done_cb = NULL;
	obj->tx_done_cb = NULL;
}

///////// Add pvvx, no ...
void  HalSdioRegisterRxCallback(char (*rx_done_cb)(void *priv, void* pbuf, uint8_t *pdata, uint16_t size, uint8_t type), void *obj)
{
	struct spdio_t * sp = (struct spdio_t *) obj;
	sp->rx_done_cb = rx_done_cb;
}

void  HalSdioRegisterTxDoneCallback(char (*tx_done_cb)(void *priv, void* pbuf), void *obj)
{
	struct spdio_t * sp = (struct spdio_t *) obj;
	sp->tx_done_cb = tx_done_cb;
}
///////

void spdio_init(struct spdio_t *obj)
{
	if(obj == NULL){
		SPDIO_API_PRINTK("spdio obj is NULL, spdio init failed!");
		return;
	}
	if((obj->rx_bd_num == 0) ||(obj->rx_bd_bufsz == 0) ||  (obj->rx_bd_bufsz%64)
		||(obj->tx_bd_num == 0) ||(obj->tx_bd_num%2)||(obj->rx_buf == NULL))
	{
		SPDIO_API_PRINTK("spdio obj resource isn't correctly inited, spdio init failed!");
		return;
	}
	g_spdio_priv = obj;
	HalSdioInit();
	HalSdioRegisterRxCallback(spdio_rx_done_cb, (void *)obj); // ??????????
	HalSdioRegisterTxDoneCallback(spdio_tx_done_cb, (void *)obj); // ?????????
}

void spdio_deinit(struct spdio_t *obj)
{	
	if(obj == NULL){
		SPDIO_API_PRINTK("spdio obj is NULL, spdio deinit failed");
		return;
	}
	HalSdioDeInit();
	g_spdio_priv = NULL;
}

#endif
