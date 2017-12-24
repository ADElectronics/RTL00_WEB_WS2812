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
#ifndef __RTL_UTILITY_H_
#define __RTL_UTILITY_H_

void RtlMemcpy(void* dec, void* sour, uint32_t sz);
uint32_t RtlMemcmp(void *dst, void *src, uint32_t sz);
void RtlMemset(void *pbuf, uint32_t c, uint32_t sz);

int8_t *
RtlStrncpy(
    IN  int8_t *dest, 
    IN  const int8_t *src, 
    IN  SIZE_T count
);

int8_t *
RtlStrcpy(
    IN  int8_t *dest, 
    IN  const int8_t *src
);


SIZE_T
RtlStrlen(
    IN  const int8_t *s
);


SIZE_T
RtlStrnlen(
    IN  const int8_t *s, 
    IN  SIZE_T count
);


int 
RtlStrcmp(
    IN  const int8_t *cs, 
    IN  const int8_t *ct

);

int
RtlStrncmp(
    IN  const int8_t *cs, 
    IN  const int8_t *ct, 
    IN  SIZE_T count
);

#endif


