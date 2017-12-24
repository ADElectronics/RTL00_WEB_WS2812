#ifndef _UTIL_H
#define _UTIL_H

#include <wireless.h>
#include <wlan_intf.h>
#include <wifi_constants.h> 
#include "wifi_structures.h"  

#ifdef	__cplusplus
extern "C" {
#endif

int wext_get_ssid(const char *ifname, uint8_t *ssid);
int wext_set_ssid(const char *ifname, const uint8_t *ssid, uint16_t ssid_len);
int wext_set_auth_param(const char *ifname, uint16_t idx, uint32_t value);
int wext_set_key_ext(const char *ifname, uint16_t alg, const uint8_t *addr, int key_idx, int set_tx, const uint8_t *seq, uint16_t seq_len, uint8_t *key, uint16_t key_len);
int wext_get_enc_ext(const char *ifname, uint16_t *alg, uint8_t *key_idx, uint8_t *passphrase);
int wext_set_passphrase(const char *ifname, const uint8_t *passphrase, uint16_t passphrase_len);
int wext_get_passphrase(const char *ifname, uint8_t *passphrase);
int wext_set_mode(const char *ifname, int mode);
int wext_get_mode(const char *ifname, int *mode);
int wext_set_ap_ssid(const char *ifname, const uint8_t *ssid, uint16_t ssid_len);
int wext_set_country(const char *ifname, rtw_country_code_t country_code);
int wext_get_rssi(const char *ifname, int *rssi);
int wext_set_channel(const char *ifname, uint8_t ch);
int wext_get_channel(const char *ifname, uint8_t *ch);
int wext_register_multicast_address(const char *ifname, rtw_mac_t *mac);
int wext_unregister_multicast_address(const char *ifname, rtw_mac_t *mac);
int wext_set_scan(const char *ifname, char *buf, uint16_t buf_len, uint16_t flags);
int wext_get_scan(const char *ifname, char *buf, uint16_t buf_len);
int wext_set_mac_address(const char *ifname, char * mac);
int wext_get_mac_address(const char *ifname, char * mac);
int wext_enable_powersave(const char *ifname, uint8_t lps_mode, uint8_t ips_mode);
int wext_disable_powersave(const char *ifname);
#define wext_disable_powersave(n) wext_enable_powersave(n, 0, 0)
int wext_set_tdma_param(const char *ifname, uint8_t slot_period, uint8_t rfon_period_len_1, uint8_t rfon_period_len_2, uint8_t rfon_period_len_3);
int wext_set_lps_dtim(const char *ifname, uint8_t lps_dtim);
int wext_get_lps_dtim(const char *ifname, uint8_t *lps_dtim);
int wext_get_tx_power(const char *ifname, uint8_t *poweridx);
int wext_set_txpower(const char *ifname, int poweridx);
int wext_get_associated_client_list(const char *ifname, void * client_list_buffer, uint16_t buffer_length);
int wext_get_ap_info(const char *ifname, rtw_bss_info_t * ap_info, rtw_security_t* security);
int wext_mp_command(const char *ifname, char *cmd, int show_msg);
int wext_private_command(const char *ifname, char *cmd, int show_msg);
int wext_private_command_with_retval(const char *ifname, char *cmd, char *ret_buf, int ret_len);
void wext_wlan_indicate(unsigned int cmd, union iwreq_data *wrqu, char *extra);
int wext_set_pscan_channel(const char *ifname, uint8_t *ch, uint8_t *pscan_config, uint8_t length);
int wext_set_autoreconnect(const char *ifname, uint8_t mode, uint8_t retyr_times, uint16_t timeout);
int wext_get_autoreconnect(const char *ifname, uint8_t *mode);
int wext_set_adaptivity(rtw_adaptivity_mode_t adaptivity_mode);
int wext_set_adaptivity_th_l2h_ini(uint8_t l2h_threshold);
int wext_get_auto_chl(const char *ifname, unsigned char *channel_set, unsigned char channel_num);
int wext_set_sta_num(unsigned char ap_sta_num);
int wext_del_station(const char *ifname, unsigned char* hwaddr);
int wext_init_mac_filter(void);
int wext_deinit_mac_filter(void);
int wext_add_mac_filter(unsigned char* hwaddr);
int wext_del_mac_filter(unsigned char* hwaddr);
int wext_set_tos_value(const char *ifname, uint8_t *tos_value);
#ifdef CONFIG_CUSTOM_IE
int wext_add_custom_ie(const char *ifname, void * cus_ie, int ie_num);
int wext_update_custom_ie(const char *ifname, void * cus_ie, int ie_index);
int wext_del_custom_ie(const char *ifname);
#endif

#define wext_handshake_done rltk_wlan_handshake_done

int wext_send_mgnt(const char *ifname, char *buf, uint16_t buf_len, uint16_t flags);
int wext_send_eapol(const char *ifname, char *buf, uint16_t buf_len, uint16_t flags);
int wext_set_gen_ie(const char *ifname, char *buf, uint16_t buf_len, uint16_t flags);

#ifdef	__cplusplus
}
#endif

#endif /* _UTIL_H */
