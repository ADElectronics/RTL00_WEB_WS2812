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
#ifndef _RTW_P2P_H_
#define _RTW_P2P_H_

#define P2P_WILDCARD_SSID "DIRECT-"
#define P2P_WILDCARD_SSID_LEN 7

#define P2P_SEND_ACTION_AFTER_PROBE_RSP 1

#define RTW_P2P_SEND_ACTION_SUCCESS	0
#define RTW_P2P_SEND_ACTION_FAILED		2

static inline bool rtw_p2p_chk_state(struct wifidirect_info *wdinfo, enum P2P_STATE state)
{
	return wdinfo->p2p_state == state;
}
static inline bool rtw_p2p_chk_role(struct wifidirect_info *wdinfo, enum P2P_ROLE role)
{
	return wdinfo->role == role;
}

extern void rtw_p2p_remain_on_channel(_adapter *padapter, uint8_t channel, uint8_t wait_time);
extern void rtw_p2p_cancel_remain_on_channel(_adapter *padapter);
extern void rtw_p2p_special_scan_param(_adapter *padapter, uint8_t channel, uint8_t *mac);
extern void rtw_p2p_set_p2p_role(_adapter *padapter, uint32_t role);
extern void rtw_p2p_set_p2p_state(_adapter *padapter, uint32_t state);
extern int rtw_p2p_send_mgnt(_adapter *padapter, uint8_t *data, uint16_t len, uint16_t flags);
extern void rtw_p2p_indicate_mgnt(_adapter *padapter, uint8_t *data, uint16_t len, uint8_t channel);
extern void rtw_indicate_sta_assoc(_adapter *padapter, uint8_t *addr, uint8_t *buf, uint16_t len);
extern void rtw_p2p_indicate_sta_disassoc(_adapter *padapter, uint8_t *addr);
extern void rtw_p2p_indicate_send_action_done(_adapter *padapter, uint16_t status);

extern int rtw_p2p_init_mlme_ext(_adapter *padapter);
extern void rtw_p2p_deinit_mlme_ext(_adapter *padapter);
extern int rtw_init_p2p_wdinfo(_adapter *padapter);
extern void rtw_deinit_p2p_wdinfo(_adapter *padapter);
extern void rtw_p2p_pre_tx_scan_cmd_callback(_adapter *padapter);

#endif //_RTW_P2P_H_

