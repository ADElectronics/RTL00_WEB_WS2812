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
#ifndef ROM_ARC4_H
#define ROM_ARC4_H

struct arc4context
{
	uint32_t x;
	uint32_t y;
	uint8_t state[256];
};

uint32_t crc32_get(uint8_t *buf, sint len);
void rt_arc4_init(struct arc4context 	*parc4ctx, uint8_t * key,uint32_t	key_len);
void rt_arc4_crypt(	struct arc4context	*parc4ctx, uint8_t * dest, uint8_t * src, uint32_t len);


#endif //ROM_ARC4_H
