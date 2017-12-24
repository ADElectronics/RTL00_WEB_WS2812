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

#ifndef ROM_MD5_H
#define ROM_MD5_H

#if PSK_SUPPORT_TKIP

/* MD5 context. */
typedef struct {
  uint32_t state[4];                                   /* state (ABCD) */
  uint32_t count[2];        /* number of bits, modulo 2^64 (lsb first) */
  uint8_t buffer[64];                         /* input buffer */
} md5_ctx;

void rt_md5_init(md5_ctx *context);
void rt_md5_append(md5_ctx *context, uint8_t *input, uint32_t inputLen);
void rt_md5_final(uint8_t digest[16], md5_ctx *context);
void rt_md5_hmac(unsigned char *text, int text_len, unsigned char *key,
		 int key_len, void * digest);


#endif	//#if PSK_SUPPORT_TKIP
#endif
