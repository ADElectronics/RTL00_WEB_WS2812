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
#ifndef _RTW_HT_H_
#define _RTW_HT_H_

#include "wifi.h"

struct ht_priv
{
	uint32_t	ht_option;	
	uint32_t	ampdu_enable;//for enable Tx A-MPDU
	//uint8_t	baddbareq_issued[16];
	//uint32_t	tx_amsdu_enable;//for enable Tx A-MSDU
	//uint32_t	tx_amdsu_maxlen; // 1: 8k, 0:4k ; default:8k, for tx
	//uint32_t	rx_ampdu_maxlen; //for rx reordering ctrl win_sz, updated when join_callback.
	
	uint8_t	bwmode;//
	uint8_t	ch_offset;//PRIME_CHNL_OFFSET
	uint8_t	sgi;//short GI

	//for processing Tx A-MPDU
	uint8_t	agg_enable_bitmap;
	//uint8_t	ADDBA_retry_count;
	uint8_t	candidate_tid_bitmap;

	uint8_t	stbc_cap;
	
	struct rtw_ieee80211_ht_cap ht_cap;
	
};

#define	STBC_HT_ENABLE_RX			BIT0
#define	STBC_HT_ENABLE_TX			BIT1
#define	STBC_HT_TEST_TX_ENABLE		BIT2
#define	STBC_HT_CAP_TX				BIT3

typedef enum AGGRE_SIZE{
	HT_AGG_SIZE_8K = 0,
	HT_AGG_SIZE_16K = 1,
	HT_AGG_SIZE_32K = 2,
	HT_AGG_SIZE_64K = 3,
	VHT_AGG_SIZE_128K = 4,
	VHT_AGG_SIZE_256K = 5,
	VHT_AGG_SIZE_512K = 6,
	VHT_AGG_SIZE_1024K = 7,
}AGGRE_SIZE_E, *PAGGRE_SIZE_E;

#endif	//_RTL871X_HT_H_

