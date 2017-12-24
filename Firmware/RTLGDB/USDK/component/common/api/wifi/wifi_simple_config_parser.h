#ifndef __SIMPLE_CONFIG_H__
#define __SIMPLE_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif


  /*  This macro means user take simple config
   *  lib to another platform such as linux, and
   *  have no rom crypto libs of simple config,
   *  so we take simple_config_crypto as a sw lib 
   *  This macro is used by Realtek internal to generate simple config lib
   *  Please delete this macro after generation.
   */
#define SIMPLE_CONFIG_PLATFORM_LIB 0

#include "platform_opts.h"
#include "autoconf.h"



/* platform related settings */
#if (defined(CONFIG_PLATFORM_8195A)|| defined(CONFIG_PLATFORM_8711B))
/*
#undef uint32_t
#undef int32_t
#undef uint8_t
#undef int8_t
#undef uint16_t
#undef int16_t
typedef unsigned int uint32_t;
typedef signed int int32_t;
typedef unsigned char uint8_t;
typedef char int8_t;
typedef unsigned short int uint16_t;
typedef signed short int int16_t;
*/
#else
#include "osdep_service.h"
#endif

typedef int  (*simple_config_printf_fn) (char const * fmt, ...);
typedef void* (*simple_config_memset_fn) (uint8_t *dst0, int32_t Val, uint32_t length);
typedef void* (*simple_config_memcpy_fn) ( void *s1, const void *s2, uint32_t n );
typedef uint32_t (*simple_config_strlen_fn) (const char *s);
typedef char * (*simple_config_strcpy_fn) (char  *dest, const char  *src);
typedef void (*simple_config_free_fn) (uint8_t *pbuf, uint32_t sz);
typedef uint8_t*  (*simple_config_zmalloc_fn) (uint32_t sz);
typedef uint8_t* (*simple_config_malloc_fn) (uint32_t sz);
typedef int (*simple_config_memcmp_fn) (const void *av, const void *bv, uint32_t len);
typedef uint32_t (*simple_config_ntohl_fn)(uint32_t x);



struct simple_config_lib_config {
	simple_config_printf_fn printf;
	simple_config_memset_fn memset;
	simple_config_memcpy_fn memcpy;
	simple_config_strlen_fn strlen;
	simple_config_strcpy_fn strcpy;
	simple_config_free_fn free;
	simple_config_zmalloc_fn zmalloc;
	simple_config_malloc_fn malloc;
	simple_config_memcmp_fn memcmp;
	simple_config_ntohl_fn _ntohl;


	int *is_promisc_callback_unlock;

};

#pragma pack(1)
struct rtk_test_sc {
	/* API exposed to user */
	unsigned char		ssid[32];
	unsigned char		password[65];	
	unsigned int		ip_addr;
};

/* expose data */
extern int32_t is_promisc_callback_unlock;
extern uint8_t g_bssid[6];
extern uint8_t get_channel_flag;
extern uint8_t g_security_mode;

/* expose API */
extern int32_t rtk_sc_init(char *custom_pin_code, struct simple_config_lib_config* config);
extern int32_t rtk_start_parse_packet(uint8_t *da, uint8_t *sa, int32_t len,  void * user_data, void *backup_sc);
extern void rtk_restart_simple_config(void);
extern void rtk_sc_deinit();
extern void wifi_enter_promisc_mode();
extern void whc_fix_channel();
extern void whc_unfix_channel();


#ifdef __cplusplus
}
#endif

#endif /* __SIMPLE_CONFIG_H__*/
