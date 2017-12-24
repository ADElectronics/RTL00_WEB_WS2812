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
#ifndef __LXBUS_OPS_H__
#define __LXBUS_OPS_H__


#if defined(CONFIG_RTL8195A) 
//extern uint32_t TxbdRxbdInitRtl8195a(PADAPTER Adapter);
//extern uint32_t TxbdRxbdResetRtl8195a(PADAPTER Adapter);

extern void InitLxDmaRtl8195a(_adapter * Adapter);
extern uint32_t rtl8195a_init_desc_ring(_adapter * padapter);
extern uint32_t rtl8195a_free_desc_ring(_adapter * padapter);
extern void rtl8195a_reset_desc_ring(_adapter * padapter);
extern void EnableDMA8195a(PADAPTER padapter);
extern void EnableInterrupt8195a(PADAPTER padapter);
extern void DisableDMA8195a(PADAPTER padapter);
extern void DisableInterrupt8195a(PADAPTER padapter);
extern int32_t	InterruptHandle8195a(PADAPTER Adapter);
extern void lxbus_set_intf_ops(struct _io_ops *pops);
extern void	rtl8195a_xmit_tasklet(void *priv);
extern void	rtl8195a_recv_tasklet(void *priv);
extern void	rtl8195a_prepare_bcn_tasklet(void *priv);
extern void rtl8195a_tx_int_handler(_adapter *padapter);
extern void InitInterrupt8195a(PADAPTER padapter);
extern void UpdateInterruptMask8195a(PADAPTER Adapter, uint32_t *pAddMSRB, uint32_t *pRemoveMSR);

#ifdef CONFIG_WOWLAN
extern void ClearInterrupt8195a(PADAPTER padapter);
#endif

extern void ClearWlPmcInterrupt8195a(PADAPTER padapter);
extern BOOLEAN	InterruptRecognized8195a(PADAPTER Adapter);
#elif  defined(CONFIG_RTL8711B)

extern uint32_t rtl8711b_init_desc_ring(_adapter * padapter);
extern uint32_t rtl8711b_free_desc_ring(_adapter * padapter);
extern void rtl8711b_reset_desc_ring(_adapter * padapter);
extern void EnableDMA8711b(PADAPTER padapter);
extern void EnableInterrupt8711b(PADAPTER padapter);
extern void DisableDMA8711b(PADAPTER padapter);
extern void DisableInterrupt8711b(PADAPTER padapter);
extern int32_t	InterruptHandle8711b(PADAPTER Adapter);
extern void lxbus_set_intf_ops(struct _io_ops *pops);
extern void	rtl8711b_xmit_tasklet(void *priv);
extern void	rtl8711b_recv_tasklet(void *priv);
extern void	rtl8711b_prepare_bcn_tasklet(void *priv);
extern void rtl8711b_tx_int_handler(_adapter *padapter);
extern void InitInterrupt8711b(PADAPTER padapter);
extern void UpdateInterruptMask8711b(PADAPTER Adapter, uint32_t *pAddMSRB, uint32_t *pRemoveMSR);

#ifdef CONFIG_WOWLAN
extern void ClearInterrupt8711b(PADAPTER padapter);
extern void DisableInterruptButCpwm28711b(PADAPTER padapter);
#endif

extern void ClearWlPmcInterrupt8711b(PADAPTER padapter);
extern BOOLEAN	InterruptRecognized8711b(PADAPTER Adapter);
#endif


#endif // !__LXBUS_OPS_H__

