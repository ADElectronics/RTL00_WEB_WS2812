/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */


#ifndef _HAL_SPIFLASH__
#define _HAL_SPIFLASH__
//======================================================
// Header files

#define SPIC_CALIBRATION_IN_NVM         1   // if store the SPIC calibration data in the NVM
#ifndef CONFIG_IMAGE_SEPARATE       // Store SPIC Calibration only for seprated image
#undef SPIC_CALIBRATION_IN_NVM
#define SPIC_CALIBRATION_IN_NVM         0
#endif

//======================================================
// Definition
#define HAL_SPI_WRITE32(addr, value32)  HAL_WRITE32(SPI_FLASH_CTRL_BASE, addr, value32)
#define HAL_SPI_WRITE16(addr, value16)  HAL_WRITE16(SPI_FLASH_CTRL_BASE, addr, value16)
#define HAL_SPI_WRITE8(addr, value8)    HAL_WRITE8(SPI_FLASH_CTRL_BASE, addr, value8)
#define HAL_SPI_READ32(addr)            HAL_READ32(SPI_FLASH_CTRL_BASE, addr)
#define HAL_SPI_READ16(addr)            HAL_READ16(SPI_FLASH_CTRL_BASE, addr)
#define HAL_SPI_READ8(addr)             HAL_READ8(SPI_FLASH_CTRL_BASE, addr)

typedef struct _SPIC_PARA_MODE_ {
    uint8_t Valid	:1;		// valid
    uint8_t CpuClk	:3;		// CPU clock
    uint8_t BitMode	:2;		// Bit mode
	uint8_t Reserved	:2;		// reserved
} SPIC_PARA_MODE, *PSPIC_PARA_MODE;

typedef struct _SPIC_INIT_PARA_ {
    uint8_t  BaudRate;
    uint8_t  RdDummyCyle;
    uint8_t  DelayLine;
    union {
        uint8_t  Rsvd;
        uint8_t  Valid;
        SPIC_PARA_MODE Mode;
    };
#if defined(E_CUT_ROM_DOMAIN) || (!defined(CONFIG_RELEASE_BUILD_LIBRARIES))
    uint8_t id[3];
    uint8_t flashtype;
#endif
}SPIC_INIT_PARA, *PSPIC_INIT_PARA;


enum _SPIC_BIT_MODE_ {
    SpicOneBitMode = 0,
    SpicDualBitMode = 1,
    SpicQuadBitMode = 2,
	SpicMaxMode = 3
};

//======================================================
// Flash type used 
#define FLASH_OTHERS 0
#define FLASH_MXIC 1
#define FLASH_MXIC_4IO 2
#define FLASH_WINBOND 3
#define FLASH_MICRON 4
#define FLASH_EON 5

//#define FLASH_MXIC_MX25L4006E   0
//#define FLASH_MXIC_MX25L8073E   1
//#define FLASH_MICRON_N25Q512A 1
// The below parts are based on the flash characteristics
//====== Flash Command Definition  ======
//#if FLASH_MICRON_N25Q512A

/*Common command*/
#define FLASH_CMD_WREN      0x06            //write enable
#define FLASH_CMD_WRDI      0x04            //write disable
#define FLASH_CMD_WRSR      0x01            //write status register
#define FLASH_CMD_RDID      0x9F            //read idenfication
#define FLASH_CMD_RDSR      0x05            //read status register
#define FLASH_CMD_RDSFDP    0x5A            //Read SFDP
#define FLASH_CMD_READ      0x03            //read data
#define FLASH_CMD_FREAD     0x0B            //fast read data
#define FLASH_CMD_PP        0x02            //Page Program
#define FLASH_CMD_DREAD 	0x3B            //Double Output Mode command 1-1-2
#define FLASH_CMD_2READ 	0xBB            // 2 x I/O read  command 1-2-2
#define FLASH_CMD_QREAD 	0x6B            // 1I / 4O read command 1-1-4
#define FLASH_CMD_4READ 	0xEB            // 4 x I/O read  command 1-4-4
#define FLASH_CMD_DPP   	0xA2            // 1-1-2
#define FLASH_CMD_2PP   	0xD2            //  1-2-2
#define FLASH_CMD_QPP   	0x32            //  1-1-4
#define FLASH_CMD_4PP   	0x38            //quad page program 1-4-4
#define FLASH_CMD_SE    	0x20            //Sector Erase
#define FLASH_CMD_BE    	0xD8            //Block Erase(or 0x52)
#define FLASH_CMD_CE    	0xC7            //Chip Erase(or 0xC7)
#define FLASH_CMD_DP    	0xB9            //Deep Power Down
#define FLASH_CMD_RDP   	0xAB            //Release from Deep Power-Down

/*Micron Special command*/
#define FLASH_CMD_DE    	0xC4	// DIE ERASE
#define FLASH_CMD_4PP2   	0x12	// 4-BYTE PAGE PROGRAM
#define FLASH_CMD_RFSR 		0x70	// READ FLAG STATUS REGISTER
#define FLASH_CMD_CFSR 		0x50	// CLEAR FLAG STATUS REGISTER
#define FLASH_CMD_RNCR 		0xB5	// READ NONVOLATILE CONFIGURATION REGISTER
#define FLASH_CMD_WNCR 		0xB1	// WRITE NONVOLATILE CONFIGURATION REGISTER
#define FLASH_CMD_RVCR 		0x85	// READ VOLATILE CONFIGURATION REGISTER
#define FLASH_CMD_WVCR 		0x81	// WRITE VOLATILE CONFIGURATION REGISTER
#define FLASH_CMD_REVCR 	0x65	// READ ENHANCED VOLATILE CONFIGURATION REGISTER
#define FLASH_CMD_WEVCR		0x61	// WRITE ENHANCED VOLATILE CONFIGURATION REGISTER
#define FLASH_CMD_REAR		0xC8	// READ EXTENDED ADDRESS REGISTER
#define FLASH_CMD_WEAR		0xC5	// WRITE EXTENDED ADDRESS REGISTER
#define FLASH_CMD_ENQUAD	0x35	// ENTER QUAD
#define FLASH_CMD_EXQUAD	0xF5	// EXIT QUAD
#define FLASH_CMD_ROTPA		0x4B	// READ OTP ARRAY
#define FLASH_CMD_POTPA		0x42	// PROGRAM OTP ARRAY

/*MXIC Special command*/
#define FLASH_CMD_RDCR      0x15        	//read configurate register
#define FLASH_CMD_REMS2     0xEF            // read ID for 2x I/O mode
#define FLASH_CMD_REMS4     0xDF            // read ID for 4x I/O mode
#define FLASH_CMD_ENSO      0xB1            // enter secured OTP
#define FLASH_CMD_EXSO      0xC1            // exit secured OTP
#define FLASH_CMD_RDSCUR    0x2B            // read security register
#define FLASH_CMD_WRSCUR    0x2F            // write security register

/* EON Special command*/
#define FLASH_CMD_EOTPM		0x3A		//  Enter OTP Mode (3Ah)

//#endif
#if 0
#if FLASH_MXIC_MX25L4006E
    #define FLASH_CMD_WREN      0x06            //write enable
    #define FLASH_CMD_WRDI      0x04            //write disable
    #define FLASH_CMD_WRSR      0x01            //write status register
    #define FLASH_CMD_RDID      0x9F            //read idenfication
    #define FLASH_CMD_RDSR      0x05            //read status register
    #define FLASH_CMD_READ      0x03            //read data
    #define FLASH_CMD_FREAD     0x0B            //fast read data
    #define FLASH_CMD_RDSFDP    0x5A            //Read SFDP
    #define FLASH_CMD_RES       0xAB            //Read Electronic ID
    #define FLASH_CMD_REMS      0x90            //Read Electronic Manufacturer & Device ID
    #define FLASH_CMD_DREAD     0x3B            //Double Output Mode command
    #define FLASH_CMD_SE        0x20            //Sector Erase
    #define FLASH_CMD_BE        0xD8            //Block Erase(or 0x52)
    #define FLASH_CMD_CE        0x60            //Chip Erase(or 0xC7)
    #define FLASH_CMD_PP        0x02            //Page Program
    #define FLASH_CMD_DP        0xB9            //Deep Power Down
    #define FLASH_CMD_RDP       0xAB            //Release from Deep Power-Down
    #define FLASH_CMD_RDCR      0x15        //read configurate register
    #define FLASH_CMD_2READ     0xBB            // 2 x I/O read  command
    #define FLASH_CMD_4READ     0xEB            // 4 x I/O read  command
    #define FLASH_CMD_QREAD     0x6B            // 1I / 4O read command
    #define FLASH_CMD_4PP       0x38            //quad page program
    #define FLASH_CMD_FF        0xFF            //Release Read Enhanced
    #define FLASH_CMD_REMS2     0xEF            // read ID for 2x I/O mode
    #define FLASH_CMD_REMS4     0xDF            // read ID for 4x I/O mode
    #define FLASH_CMD_ENSO      0xB1            // enter secured OTP
    #define FLASH_CMD_EXSO      0xC1            // exit secured OTP
    #define FLASH_CMD_RDSCUR    0x2B            // read security register
    #define FLASH_CMD_WRSCUR    0x2F            // write security register    
#elif  FLASH_MXIC_MX25L8073E
    #define FLASH_CMD_WREN      0x06            //write enable
    #define FLASH_CMD_WRDI      0x04            //write disable
    #define FLASH_CMD_WRSR      0x01            //write status register
    #define FLASH_CMD_RDID      0x9F            //read idenfication
    #define FLASH_CMD_RDSR      0x05            //read status register
    #define FLASH_CMD_READ      0x03            //read data
    #define FLASH_CMD_FREAD     0x0B            //fast read data
    #define FLASH_CMD_RDSFDP    0x5A            //Read SFDP
    #define FLASH_CMD_RES       0xAB            //Read Electronic ID
    #define FLASH_CMD_REMS      0x90            //Read Electronic Manufacturer & Device ID
    #define FLASH_CMD_DREAD     0x3B            //Double Output Mode command
    #define FLASH_CMD_SE        0x20            //Sector Erase
    #define FLASH_CMD_BE        0x52            //Block Erase
    #define FLASH_CMD_CE        0x60            //Chip Erase(or 0xC7)
    #define FLASH_CMD_PP        0x02            //Page Program
    #define FLASH_CMD_DP        0xB9            //Deep Power Down
    #define FLASH_CMD_RDP       0xAB            //Release from Deep Power-Down
    #define FLASH_CMD_2READ     0xBB            // 2 x I/O read  command
    #define FLASH_CMD_4READ     0xEB            // 4 x I/O read  command
    #define FLASH_CMD_QREAD     0x6B            // 1I / 4O read command
    #define FLASH_CMD_4PP       0x38            //quad page program
    #define FLASH_CMD_FF        0xFF            //Release Read Enhanced
    #define FLASH_CMD_REMS2     0xEF            // read ID for 2x I/O mode
    #define FLASH_CMD_REMS4     0xDF            // read ID for 4x I/O mode
    #define FLASH_CMD_ENSO      0xB1            // enter secured OTP
    #define FLASH_CMD_EXSO      0xC1            // exit secured OTP
    #define FLASH_CMD_RDSCUR    0x2B            // read security register
    #define FLASH_CMD_WRSCUR    0x2F            // write security register
#else
    #define FLASH_CMD_WREN      0x06            //write enable
    #define FLASH_CMD_WRDI      0x04            //write disable
    #define FLASH_CMD_WRSR      0x01            //write status register
    #define FLASH_CMD_RDID      0x9F            //read idenfication
    #define FLASH_CMD_RDSR      0x05            //read status register
    #define FLASH_CMD_READ      0x03            //read data
    #define FLASH_CMD_FREAD     0x0B            //fast read data
    #define FLASH_CMD_RDSFDP    0x5A            //Read SFDP
    #define FLASH_CMD_RES       0xAB            //Read Electronic ID
    #define FLASH_CMD_REMS      0x90            //Read Electronic Manufacturer & Device ID
    #define FLASH_CMD_DREAD     0x3B            //Double Output Mode command
    #define FLASH_CMD_SE        0x20            //Sector Erase
    #define FLASH_CMD_BE        0x52            //Block Erase
    #define FLASH_CMD_CE        0x60            //Chip Erase(or 0xC7)
    #define FLASH_CMD_PP        0x02            //Page Program
    #define FLASH_CMD_DP        0xB9            //Deep Power Down
    #define FLASH_CMD_RDP       0xAB            //Release from Deep Power-Down
    #define FLASH_CMD_2READ     0xBB            // 2 x I/O read  command
    #define FLASH_CMD_4READ     0xEB            // 4 x I/O read  command
    #define FLASH_CMD_QREAD     0x6B            // 1I / 4O read command
    #define FLASH_CMD_4PP       0x38            //quad page program
    #define FLASH_CMD_FF        0xFF            //Release Read Enhanced
    #define FLASH_CMD_REMS2     0xEF            // read ID for 2x I/O mode
    #define FLASH_CMD_REMS4     0xDF            // read ID for 4x I/O mode
    #define FLASH_CMD_ENSO      0xB1            // enter secured OTP
    #define FLASH_CMD_EXSO      0xC1            // exit secured OTP
    #define FLASH_CMD_RDSCUR    0x2B            // read security register
    #define FLASH_CMD_WRSCUR    0x2F            // write security register
#endif //#if FLASH_MXIC_MX25L4006E
#endif
// ============================

// =====  Flash Parameter Definition  =====
//#if FLASH_MICRON_N25Q512A
#if 0
#define FLASH_RD_2IO_EN         1
#define FLASH_RD_2O_EN          1
#define FLASH_RD_4IO_EN         1
#define FLASH_RD_4O_EN          1
#define FLASH_WR_2IO_EN         1
#define FLASH_WR_2O_EN          1
#define FLASH_WR_4IO_EN         1
#define FLASH_WR_4O_EN          1                             
#endif
#define FLASH_DM_CYCLE_2O  0x08 // 1-1-2
#define FLASH_DM_CYCLE_2IO 0x04 // 1-2-2
#define FLASH_DM_CYCLE_4O  0x08 // 1-1-4
#define FLASH_DM_CYCLE_4IO 0x08 // 1-4-4
#define FLASH_VLD_DUAL_CMDS (BIT_WR_BLOCKING | BIT_RD_DUAL_I)// 1-1-2
#define FLASH_VLD_QUAD_CMDS (BIT_WR_BLOCKING | BIT_RD_QUAD_IO)// 1-4-4
#define FLASH_VLD_QUAD_CMDS2 (BIT_WR_BLOCKING | BIT_RD_QUAD_O)// 1-1-4


//#endif

#if 0
#if FLASH_MXIC_MX25L4006E
#define FLASH_RD_2IO_EN         1
#define FLASH_RD_2O_EN          0
#define FLASH_RD_4IO_EN         1
#define FLASH_RD_4O_EN          0
#define FLASH_WR_2IO_EN        1
#define FLASH_WR_2O_EN          0
#define FLASH_WR_4IO_EN         1
#define FLASH_WR_4O_EN          0    
#define FLASH_DM_CYCLE_2O  0x04 // 1-1-2
#define FLASH_DM_CYCLE_2IO 0x08 // 1-2-2
#define FLASH_DM_CYCLE_4O  0x04 // 1-1-4
#define FLASH_DM_CYCLE_4IO 0x08 // 1-4-4
#define FLASH_VLD_DUAL_CMDS (BIT_WR_BLOCKING | BIT_WR_DUAL_II | BIT_RD_DUAL_IO)
#define FLASH_VLD_QUAD_CMDS (BIT_WR_BLOCKING | BIT_WR_QUAD_II | BIT_RD_QUAD_IO)
    
#elif  FLASH_MXIC_MX25L8073E //This flash model is just for prototype, if you want to use it, 
                             //the code MUST be rechecked according to the flash spec.
    #define FLASH_RD_2IO_EN         1
    #define FLASH_RD_2O_EN          0
    #define FLASH_RD_4IO_EN         1
    #define FLASH_RD_4O_EN          0
    #define FLASH_WR_2IO_EN         1
    #define FLASH_WR_2O_EN          0
    #define FLASH_WR_4IO_EN         1
    #define FLASH_WR_4O_EN          0                             
    
    #define FLASH_DM_CYCLE_2O  0x08
    #define FLASH_DM_CYCLE_2IO 0x04
    #define FLASH_DM_CYCLE_4O  0x08
    #define FLASH_DM_CYCLE_4IO 0x04
    
    #define FLASH_VLD_DUAL_CMDS (BIT_WR_BLOCKING | BIT_RD_DUAL_IO)
    #define FLASH_VLD_QUAD_CMDS (BIT_WR_BLOCKING | BIT_WR_QUAD_II | BIT_RD_QUAD_IO)
#else
    #define FLASH_RD_2IO_EN         1
    #define FLASH_RD_2O_EN          0
    #define FLASH_RD_4IO_EN         1
    #define FLASH_RD_4O_EN          0
    #define FLASH_WR_2IO_EN         1
    #define FLASH_WR_2O_EN          0
    #define FLASH_WR_4IO_EN         1
    #define FLASH_WR_4O_EN          0
    
    #define FLASH_DM_CYCLE_2O  0x08
    #define FLASH_DM_CYCLE_2IO 0x04
    #define FLASH_DM_CYCLE_4O  0x08
    #define FLASH_DM_CYCLE_4IO 0x04
    
    #define FLASH_VLD_DUAL_CMDS (BIT_WR_BLOCKING | BIT_RD_DUAL_IO)  
    #define FLASH_VLD_QUAD_CMDS (BIT_WR_BLOCKING | BIT_WR_QUAD_II | BIT_RD_QUAD_IO)
#endif
#endif
#if 0
//======================================================
// Function prototype
BOOLEAN SpicFlashInitRtl8195A(uint8_t SpicBitMode);

_LONG_CALL_
extern void SpicLoadInitParaFromClockRtl8195A(uint8_t CpuClkMode, uint8_t BaudRate, PSPIC_INIT_PARA pSpicInitPara); 

// spi-flash controller initialization
_LONG_CALL_
extern void SpicInitRtl8195A(uint8_t InitBaudRate, uint8_t SpicBitMode);

// wait sr[0] = 0, wait transmission done
_LONG_CALL_
extern void SpicWaitBusyDoneRtl8195A(void);

// wait spi-flash status register[0] = 0
//_LONG_CALL_
//extern void SpicWaitWipDoneRtl8195A(SPIC_INIT_PARA SpicInitPara);
#endif

//======================================================
// ROM Function prototype
_LONG_CALL_ void SpiFlashAppV02(IN  void *Data);
_LONG_CALL_ROM_ void SpicInitRtl8195AV02(IN  uint8_t InitBaudRate,IN  uint8_t SpicBitMode);

_LONG_CALL_ROM_ void SpicEraseFlashRtl8195AV02(void);

_LONG_CALL_ROM_ void SpicLoadInitParaFromClockRtl8195AV02(IN  uint8_t CpuClkMode,IN  uint8_t BaudRate,IN  PSPIC_INIT_PARA pSpicInitPara);


void SpicBlockEraseFlashRtl8195A(IN uint32_t Address);
void SpicSectorEraseFlashRtl8195A(IN uint32_t Address);
void SpicDieEraseFlashRtl8195A(IN uint32_t Address);
void SpicWriteProtectFlashRtl8195A(IN uint32_t Protect);
void SpicWaitWipDoneRefinedRtl8195A(IN  SPIC_INIT_PARA SpicInitPara);
void SpicWaitOperationDoneRtl8195A(IN SPIC_INIT_PARA SpicInitPara);
void SpicRxCmdRefinedRtl8195A(IN  uint8_t cmd,IN  SPIC_INIT_PARA SpicInitPara);
uint8_t SpicGetFlashStatusRefinedRtl8195A(IN  SPIC_INIT_PARA SpicInitPara);
void SpicInitRefinedRtl8195A(IN  uint8_t InitBaudRate, IN  uint8_t SpicBitMode);
uint32_t SpicWaitWipRtl8195A(void); // IN  SPIC_INIT_PARA SpicInitPara);
uint32_t SpicOneBitCalibrationRtl8195A(IN uint8_t SysCpuClk);
void SpicDisableRtl8195A(void);
void SpicDeepPowerDownFlashRtl8195A(void);
void SpicUserProgramRtl8195A(IN uint8_t * data, IN SPIC_INIT_PARA SpicInitPara, IN uint32_t addr, IN uint32_t * LengthInfo);
void SpicUserReadRtl8195A(IN uint32_t Length, IN uint32_t addr, IN uint8_t * data, IN uint8_t BitMode);
void SpicUserReadFourByteRtl8195A(IN uint32_t Length, IN uint32_t addr, IN uint32_t * data, IN uint8_t BitMode);
void SpicReadIDRtl8195A(void);
void SpicSetFlashStatusRefinedRtl8195A(IN uint32_t data, IN SPIC_INIT_PARA SpicInitPara);
void SpicSetExtendAddrRtl8195A(IN uint32_t data, IN SPIC_INIT_PARA SpicInitPara);
uint8_t SpicGetExtendAddrRtl8195A(IN SPIC_INIT_PARA SpicInitPara);
#if SPIC_CALIBRATION_IN_NVM
void SpicNVMCalLoad(uint8_t BitMode, uint8_t CpuClk);
void SpicNVMCalLoadAll(void);
void SpicNVMCalStore(uint8_t BitMode, uint8_t CpuClk);
#endif  // #if SPIC_CALIBRATION_IN_NVM

#endif //_HAL_SPIFLASH__