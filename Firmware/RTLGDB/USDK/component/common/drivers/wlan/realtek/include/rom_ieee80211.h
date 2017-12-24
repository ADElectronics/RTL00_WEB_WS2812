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
#ifndef __ROM_IEEE80211_H
#define __ROM_IEEE80211_H

extern const uint8_t RTW_WPA_OUI_TYPE[] ;
extern const uint8_t WPA_CIPHER_SUITE_NONE[];
extern const uint8_t WPA_CIPHER_SUITE_WEP40[];
extern const uint8_t WPA_CIPHER_SUITE_TKIP[];
extern const uint8_t WPA_CIPHER_SUITE_CCMP[];
extern const uint8_t WPA_CIPHER_SUITE_WEP104[];
extern const uint16_t RSN_VERSION_BSD;
extern const uint8_t RSN_AUTH_KEY_MGMT_UNSPEC_802_1X[];
extern const uint8_t RSN_AUTH_KEY_MGMT_PSK_OVER_802_1X[];
extern const uint8_t RSN_CIPHER_SUITE_NONE[];
extern const uint8_t RSN_CIPHER_SUITE_WEP40[];
extern const uint8_t RSN_CIPHER_SUITE_TKIP[];
extern const uint8_t RSN_CIPHER_SUITE_CCMP[];
extern const uint8_t RSN_CIPHER_SUITE_WEP104[];

/* Parsed Information Elements */
struct rtw_ieee802_11_elems {
	uint8_t *ssid;
	uint8_t ssid_len;
	uint8_t *supp_rates;
	uint8_t supp_rates_len;
	uint8_t *fh_params;
	uint8_t fh_params_len;
	uint8_t *ds_params;
	uint8_t ds_params_len;
	uint8_t *cf_params;
	uint8_t cf_params_len;
	uint8_t *tim;
	uint8_t tim_len;
	uint8_t *ibss_params;
	uint8_t ibss_params_len;
	uint8_t *challenge;
	uint8_t challenge_len;
	uint8_t *erp_info;
	uint8_t erp_info_len;
	uint8_t *ext_supp_rates;
	uint8_t ext_supp_rates_len;
	uint8_t *wpa_ie;
	uint8_t wpa_ie_len;
	uint8_t *rsn_ie;
	uint8_t rsn_ie_len;
	uint8_t *wme;
	uint8_t wme_len;
	uint8_t *wme_tspec;
	uint8_t wme_tspec_len;
	uint8_t *wps_ie;
	uint8_t wps_ie_len;
	uint8_t *power_cap;
	uint8_t power_cap_len;
	uint8_t *supp_channels;
	uint8_t supp_channels_len;
	uint8_t *mdie;
	uint8_t mdie_len;
	uint8_t *ftie;
	uint8_t ftie_len;
	uint8_t *timeout_int;
	uint8_t timeout_int_len;
	uint8_t *ht_capabilities;
	uint8_t ht_capabilities_len;
	uint8_t *ht_operation;
	uint8_t ht_operation_len;
	uint8_t *vendor_ht_cap;
	uint8_t vendor_ht_cap_len;
};

typedef enum { ParseOK = 0, ParseUnknown = 1, ParseFailed = -1 } ParseRes;

ParseRes rtw_ieee802_11_parse_elems(uint8_t *start, uint len,
                struct rtw_ieee802_11_elems *elems,
                int show_errors);

uint8_t *rtw_set_fixed_ie(unsigned char *pbuf, unsigned int len, unsigned char *source, unsigned int *frlen);
uint8_t *rtw_set_ie(uint8_t *pbuf, sint index, uint len, uint8_t *source, uint *frlen);
uint8_t *rtw_get_ie(uint8_t*pbuf, sint index, uint32_t *len, sint limit);

void rtw_set_supported_rate(uint8_t* SupportedRates, uint mode) ;

unsigned char *rtw_get_wpa_ie(unsigned char *pie, uint32_t *wpa_ie_len, int limit);
unsigned char *rtw_get_wpa2_ie(unsigned char *pie, uint32_t *rsn_ie_len, int limit);
int rtw_get_wpa_cipher_suite(uint8_t *s);
int rtw_get_wpa2_cipher_suite(uint8_t *s);

int rtw_parse_wpa_ie(uint8_t* wpa_ie, int wpa_ie_len, int *group_cipher, int *pairwise_cipher, int *is_8021x);
int rtw_parse_wpa2_ie(uint8_t* wpa_ie, int wpa_ie_len, int *group_cipher, int *pairwise_cipher, int *is_8021x);

int rtw_get_sec_ie(uint8_t *in_ie,uint in_len,uint8_t *rsn_ie,uint16_t *rsn_len,uint8_t *wpa_ie,uint16_t *wpa_len);

uint8_t *rtw_get_wps_ie(uint8_t *in_ie, uint in_len, uint8_t *wps_ie, uint *wps_ielen);
uint8_t *rtw_get_wps_attr(uint8_t *wps_ie, uint wps_ielen, uint16_t target_attr_id ,uint8_t *buf_attr, uint32_t *len_attr);
uint8_t *rtw_get_wps_attr_content(uint8_t *wps_ie, uint wps_ielen, uint16_t target_attr_id ,uint8_t *buf_content, uint *len_content);

uint rtw_get_rateset_len(uint8_t	*rateset);

int rtw_get_bit_value_from_ieee_value(uint8_t val);

uint rtw_is_cckrates_included(uint8_t *rate);

uint rtw_is_cckratesonly_included(uint8_t *rate);

int rtw_check_network_type(unsigned char *rate, int ratelen, int channel);

uint8_t key_2char2num(uint8_t hch, uint8_t lch);

#endif /* __ROM_IEEE80211_H */

