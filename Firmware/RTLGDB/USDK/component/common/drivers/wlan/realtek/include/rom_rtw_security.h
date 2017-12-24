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
 ******************************************************************************
 *                                        
 * This is ROM code section. 
 *
 ******************************************************************************/
#ifndef __ROM_RTW_SECURITY_H_
#define __ROM_RTW_SECURITY_H_

struct mic_data
{
	uint32_t  K0, K1;         // Key
	uint32_t  L, R;           // Current state
	uint32_t  M;              // Message accumulator (single word)
	uint32_t     nBytesInM;      // # bytes in M
};

union  u_crc 
{    
	unsigned char	ch[4];    
	int i;  
};

//===============================
// WEP related
//===============================
void wep_80211_encrypt(
	uint8_t *pframe, uint32_t wlan_hdr_len, \
	uint32_t iv_len, uint32_t payload_len,\
	uint8_t* key, uint32_t key_len);

uint8_t wep_80211_decrypt(
	uint8_t *pframe, uint32_t wlan_hdr_len, 
	uint32_t iv_len, uint32_t payload_len,
	uint8_t* key, uint32_t key_len,
	union u_crc *pcrc\
	);

//===============================
// TKIP related
//===============================
void tkip_80211_encrypt(
	uint8_t *pframe, uint32_t wlan_hdr_len, \
	uint32_t iv_len, uint32_t payload_len,\
	uint8_t* key, uint32_t key_len,\
	uint8_t* ta);

uint8_t tkip_80211_decrypt(
	uint8_t *pframe, uint32_t wlan_hdr_len, \
	uint32_t iv_len, uint32_t payload_len,\
	uint8_t* key, uint32_t key_len,\
	uint8_t* ta, union u_crc *pcrc);

void tkip_micappendbyte(struct mic_data *pmicdata, uint8_t b );
void rtw_secmicsetkey(struct mic_data *pmicdata, uint8_t * key);
void rtw_secmicappend(struct mic_data *pmicdata, uint8_t * src, uint32_t nbytes );
void rtw_secgetmic(struct mic_data *pmicdata, uint8_t * dst );
void rtw_seccalctkipmic(uint8_t * key,uint8_t *header,uint8_t *data,uint32_t data_len,uint8_t *mic_code, uint8_t pri);
void tkip_phase1(uint16_t *p1k,const uint8_t *tk,const uint8_t *ta,uint32_t iv32);
void tkip_phase2(uint8_t *rc4key,const uint8_t *tk,const uint16_t *p1k,uint16_t iv16);


//===============================
// AES related
//===============================
void aes1_encrypt(uint8_t *key, uint8_t *data, uint8_t *ciphertext);
void aesccmp_construct_mic_iv(
	uint8_t *mic_iv, sint qc_exists, sint a4_exists, 
	uint8_t *mpdu, uint payload_length,uint8_t *pn_vector);
void aesccmp_construct_mic_header1(uint8_t *mic_header1, sint header_length, uint8_t *mpdu);
void aesccmp_construct_mic_header2(
	uint8_t *mic_header2, uint8_t *mpdu, sint a4_exists, sint qc_exists);
void aesccmp_construct_ctr_preload(
	uint8_t *ctr_preload, sint a4_exists, sint qc_exists,
	uint8_t *mpdu, uint8_t *pn_vector, sint c);

uint32_t aes_80211_encrypt(
	uint8_t *pframe, uint32_t wlan_hdr_len, \
	uint32_t payload_len, uint8_t *key, \
	uint32_t frame_type, uint8_t *mic);

uint32_t aes_80211_decrypt(
	uint8_t *pframe, uint32_t wlan_hdr_len, \
	uint32_t payload_len, uint8_t *key, \
	uint32_t frame_type, uint8_t *mic);
#endif	//__ROM_RTW_SECURITY_H_

