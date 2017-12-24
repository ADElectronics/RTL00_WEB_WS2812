/* mbed Microcontroller Library
 *******************************************************************************
 * Copyright (c) 2014, Realtek Semiconductor Corp.
 * All rights reserved.
 *
 * This module is a confidential and proprietary property of RealTek and
 * possession or use of this module requires written permission of RealTek.
 *******************************************************************************
 */

#include "rtl8195a.h"

#ifdef CONFIG_EFUSE_EN
/* in hal_efuse.h
extern void  ReadEfuseContant1(OUT uint8_t *pContant);
extern uint8_t WriteEfuseContant1(IN uint8_t CodeWordNum, IN uint8_t WordEnable, IN uint8_t *pContant);
extern void ReadEOTPContant(OUT uint8_t *pContant);
extern void  WriteEOTPContant(IN uint8_t *pContant);
extern uint8_t GetRemainingEfuseLength(void);
extern void HALJtagOff(void);
*/

/**
  * @brief  get remaining efuse length 
  * @retval  remaining efuse length 
  */
int  efuse_get_remaining_length(void)
{
    return GetRemainingEfuseLength();
}


/**
  * @brief  Read efuse contant of specified user 
  * @param  data: Specified the address to save the readback data.
  */
void  efuse_mtp_read(uint8_t * data)
{
    ReadEfuseContant1(data);
    return;
}

/**
  * @brief  Write user's contant to efuse
  * @param  *data: Specified the data to be programmed.
  * @param len: Specifies the data length of programmed data.
  * @retval   status: Success:0~32 or Failure: -1.
  */
int  efuse_mtp_write(uint8_t *data, uint8_t len)
{
    
    uint8_t len_low, len_high, word_enable = 0;	
	
	if( (len & 0x01) == 1)
		len += 1;
	
 	if(len > 32){
 		return -1;
 	}
 	if(len == 0){
		return 0;
 	}
	
	len_low = len & 0x07;
	len_high = (len >> 3) & 0x07;
	
	if(len_low == 0)
		word_enable = 0;
	else if(len_low == 2)
		word_enable = 1;
	else if(len_low == 4)
		word_enable = 3;
	else if(len_low == 6)
		word_enable = 7;
		
	switch (len_high){
		case 0:
			WriteEfuseContant1(0, word_enable, data);
			break;
			
		case 1:
			WriteEfuseContant1(0, 0xf, data);
			WriteEfuseContant1(1, word_enable, data+8);	
			break;

		case 2:
			WriteEfuseContant1(0, 0xf, data);
			WriteEfuseContant1(1, 0xf, data+8);
			WriteEfuseContant1(2, word_enable, data+8);
			break;

		case 3:
			WriteEfuseContant1(0, 0xf, data);
			WriteEfuseContant1(1, 0xf, data+8);
			WriteEfuseContant1(2, 0xf, data+16);
			WriteEfuseContant1(3, word_enable, data+24);
			break;

		case 4:
			WriteEfuseContant1(0, 0xf, data);
			WriteEfuseContant1(1, 0xf, data+8);
			WriteEfuseContant1(2, 0xf, data+16);
			WriteEfuseContant1(3, 0xf, data+24);
	}		
	return len;
}


/**
 * @brief  Read efuse OTP contant 
 * @param  address: Specifies the offset of the OTP.
 * @param len: Specifies the length of readback data.
 * @param  buf: Specified the address to save the readback data.
 */
int efuse_otp_read(uint8_t address, uint8_t len, uint8_t *buf)
{
	uint8_t content[32];	// the OTP max length is 32
	
	if((address+len) > 32)
		return -1;
	ReadEOTPContant(content);
	_memcpy(buf, content+address, len);
	return 0;
}


/**
  * @brief  Write user's contant to OTP efuse
  * @param  address: Specifies the offset of the programmed OTP.
  * @param len: Specifies the data length of programmed data.
   * @param  *buf: Specified the data to be programmed.
  * @retval   status: Success:0 or Failure: -1.
  */
int efuse_otp_write(uint8_t address, uint8_t len, uint8_t *buf)
{
	uint8_t content[32];	// the OTP max length is 32
	
	if((address+len) > 32)
		return -1;
	_memset(content, 0xFF, 32);
	_memcpy(content+address, buf, len);
	WriteEOTPContant(content);
	return 0;
}


/**
  * @brief  Disable jtag
  */
int efuse_disable_jtag(void)
{
    HALJtagOff();
    return 0;
}
#endif
