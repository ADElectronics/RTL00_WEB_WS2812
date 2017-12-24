# RTL8710 Flasher v0.0.alfa
# pvvx 2016.09.21
# modified by A_D (2017.11.29)

include userset.mk
include $(SDK_PATH)paths.mk

ifeq ($(FLASHER), Jlink)
# Jlink FLASHER_SPEED ..4000 kHz
FLASHER_SPEED ?= 3500
else 
ifeq ($(FLASHER),stlink-v2)
# stlink-v2 FLASHER_SPEED ..1800 kHz
FLASHER_SPEED ?= 1800
else
# over FLASHER_SPEED ..1000 kHz ?
FLASHER_SPEED ?= 1000
endif
endif

# COMPILED_BOOT if defined -> extract image1, boot head in elf
COMPILED_BOOT=1
# COMPILED_BOOT_BIN if !defined -> use source startup boot
#COMPILED_BOOT_BIN=1
# PADDINGSIZE defined -> image2 OTA
PADDINGSIZE =44k

NMAPFILE = $(OBJ_DIR)/$(TARGET).nmap

#RAM_IMAGE?= $(BIN_DIR)/ram.bin

RAM1_IMAGE ?= $(BIN_DIR)/ram_1.bin
RAM1P_IMAGE ?= $(BIN_DIR)/ram_1.p.bin
RAM1R_IMAGE ?= $(BIN_DIR)/ram_1.r.bin

RAM2_IMAGE = $(BIN_DIR)/ram_2.bin
RAM2P_IMAGE = $(BIN_DIR)/ram_2.p.bin
RAM2NS_IMAGE = $(BIN_DIR)/ram_2.ns.bin

RAM3_IMAGE = $(BIN_DIR)/sdram.bin
RAM3P_IMAGE = $(BIN_DIR)/sdram.p.bin

FLASH_IMAGE = $(BIN_DIR)/ram_all.bin
OTA_IMAGE = $(BIN_DIR)/ota.bin

#all: FLASH_IMAGE = $(BIN_DIR)/ram_all.bin
#all: OTA_IMAGE = $(BIN_DIR)/ota.bin
mp: FLASH_IMAGE = $(BIN_DIR)/ram_all_mp.bin
mp: OTA_IMAGE = $(BIN_DIR)/ota_mp.bin

TST_IMAGE = $(BIN_DIR)/ram_2.bin

.PHONY: genbin1 genbin23 flashburn reset test readfullflash flashboot flashwebfs flash_OTA runram runsdram
.NOTPARALLEL: all mp genbin1 genbin23 flashburn reset test readfullflash _endgenbin flashwebfs flash_OTA

all: $(ELFFILE) $(OTA_IMAGE) $(FLASH_IMAGE) _endgenbin
mp: $(ELFFILE) $(OTA_IMAGE) $(FLASH_IMAGE) _endgenbin

genbin1: $(ELFFILE) $(RAM1P_IMAGE) 

genbin23: $(ELFFILE) $(OTA_IMAGE) $(FLASH_IMAGE) _endgenbin 


_endgenbin:
	@echo "-----------------------------------------------------------"
	@echo "Image ($(OTA_IMAGE)) size $(shell printf '%d\n' $$(( $$(stat --printf="%s" $(OTA_IMAGE)) )) ) bytes"
	@echo "Image ($(FLASH_IMAGE)) size $(shell printf '%d\n' $$(( $$(stat --printf="%s" $(FLASH_IMAGE)) )) ) bytes"
	@echo "==========================================================="  

reset:
	@$(JLINK_EXE) -Device CORTEX-M3 -If SWD -Speed 1000 -CommanderScript $(FLASHER_PATH)RTL_Reset.JLinkScript

runram:	
	@$(JLINK_EXE) -Device CORTEX-M3 -If SWD -Speed 1000 -CommanderScript $(FLASHER_PATH)RTL_RunRAM.JLinkScript

runsdram:
	@$(JLINK_EXE) -Device CORTEX-M3 -If SWD -Speed 1000 -CommanderScript $(FLASHER_PATH)RTL_RunRAM_SDR.JLinkScript

readfullflash:
	@$(JLINK_EXE) -Device CORTEX-M3 -If SWD -Speed 1000 -CommanderScript $(FLASHER_PATH)RTL_FFlash.JLinkScript	

flashburn:
	@$(GDB) --command=$(FLASHER_PATH)gdb_wrflash.jlink

flashboot:
	@echo define call1>$(FLASHER_PATH)file_info.jlink
	@echo set '$$'ImageSize = $(shell printf '0x%X\n' $$(stat --printf="%s" $(BIN_DIR)/ram_1.p.bin))>>$(FLASHER_PATH)file_info.jlink
	@echo set '$$'ImageAddr = 0x000000>>$(FLASHER_PATH)file_info.jlink
	@echo end>>$(FLASHER_PATH)file_info.jlink
	@echo define call2>>$(FLASHER_PATH)file_info.jlink
	@echo FlasherWrite $(BIN_DIR)/ram_1.p.bin '$$'ImageAddr '$$'ImageSize>>$(FLASHER_PATH)file_info.jlink
	@echo end>>$(FLASHER_PATH)file_info.jlink
	@$(GDB) -x $(FLASHER_PATH)gdb_wrfile.jlink

flashwebfs:
	@echo define call1>$(FLASHER_PATH)file_info.jlink
	@echo set '$$'ImageSize = $(shell printf '0x%X\n' $$(stat --printf="%s" $(BIN_DIR)/WEBFiles.bin))>>$(FLASHER_PATH)file_info.jlink
	@echo set '$$'ImageAddr = 0x0D0000>>$(FLASHER_PATH)file_info.jlink
	@echo end>>$(FLASHER_PATH)file_info.jlink
	@echo define call2>>$(FLASHER_PATH)file_info.jlink
	@echo FlasherWrite $(BIN_DIR)/WEBFiles.bin '$$'ImageAddr '$$'ImageSize>>$(FLASHER_PATH)file_info.jlink
	@echo end>>$(FLASHER_PATH)file_info.jlink
	@$(GDB) --command=$(FLASHER_PATH)gdb_wrfile.jlink

flash_OTA:
	@$(GDB) -x $(FLASHER_PATH)gdb_ota.jlink


$(NMAPFILE): $(ELFFILE)
	@echo "==========================================================="
	@echo "Build names map file"
	@echo $@
	@$(NM) $< | sort > $@
#	@echo "==========================================================="

$(FLASH_IMAGE): $(RAM1P_IMAGE) $(RAM2P_IMAGE) $(RAM3P_IMAGE)
	@echo "==========================================================="
	@echo "Make Flash image ($(FLASH_IMAGE))" 
#	@echo "==========================================================="
	@mkdir -p $(BIN_DIR)
	@rm -f $(FLASH_IMAGE) 
	@cat $(RAM1P_IMAGE) > $(FLASH_IMAGE)
#	@chmod 777 $(FLASH_IMAGE)
ifdef PADDINGSIZE
	@$(PADDING) $(PADDINGSIZE) 0xFF $(FLASH_IMAGE)
endif	
	@cat $(RAM2P_IMAGE) >> $(FLASH_IMAGE)
	@cat $(RAM3P_IMAGE) >> $(FLASH_IMAGE)
#	@echo "Image ($(FLASH_IMAGE)) size $(shell printf '%d\n' $$(( $$(stat --printf="%s" $(FLASH_IMAGE)) )) ) bytes"
#	@echo "==========================================================="
#	@rm $(BIN_DIR)/ram_*.p.bin  
	
$(OTA_IMAGE): $(RAM2NS_IMAGE) $(RAM3_IMAGE) 
	@echo "==========================================================="
	@echo "Make OTA image ($(OTA_IMAGE))"
	@rm -f $(OTA_IMAGE) 
	@cat $(RAM2NS_IMAGE) > $(OTA_IMAGE)
	@cat $(RAM3P_IMAGE) >> $(OTA_IMAGE)
#	@chmod 777 $(OTA_IMAGE)
	@$(CHCKSUM) $(OTA_IMAGE) || true
#	@echo "==========================================================="

$(RAM1P_IMAGE): $(ELFFILE) $(NMAPFILE) 
	@echo "==========================================================="
	@echo "Create image1r ($(RAM1R_IMAGE))"
#	@echo "===========================================================" .bootloader
ifdef COMPILED_BOOT
	@mkdir -p $(BIN_DIR)
	@rm -f $(RAM1_IMAGE) $(RAM1R_IMAGE)
ifdef COMPILED_BOOT_BIN
	@$(eval RAM1_START_ADDR := $(shell grep _binary_build_bin_ram_1_r_bin_start $(NMAPFILE) | awk '{print $$1}'))
	@$(eval RAM1_END_ADDR := $(shell grep _binary_build_bin_ram_1_r_bin_end $(NMAPFILE) | awk '{print $$1}'))
else
	@$(eval RAM1_START_ADDR := $(shell grep __ram_image1_text_start__ $(NMAPFILE) | awk '{print $$1}'))
	@$(eval RAM1_END_ADDR := $(shell grep __ram_image1_text_end__ $(NMAPFILE) | awk '{print $$1}'))
endif
	$(if $(RAM1_START_ADDR),,$(error "Not found __ram_image1_text_start__!"))
	$(if $(RAM1_END_ADDR),,$(error "Not found __ram_image1_text_end__!"))
ifeq ($(RAM1_START_ADDR),$(RAM1_END_ADDR))
ifdef COMPILED_BOOT_BIN
	$(OBJCOPY) --change-section-address .boot.head=0x10000ba8 -j .boot.head -j .bootloader -Obinary $(ELFFILE) $(RAM1P_IMAGE)
else
#	$(OBJCOPY) -j .rom_ram -Obinary $(ELFFILE) $(RAM_IMAGE)
	$(OBJCOPY) -j .ram.start.table -j .ram_image1.text -Obinary $(ELFFILE) $(RAM1R_IMAGE)
	$(PICK) 0x$(RAM1_START_ADDR) 0x$(RAM1_END_ADDR) $(RAM1R_IMAGE) $(RAM1P_IMAGE) head+reset_offset 0x0B000
endif
else 
	$(error "BOOT-image size = 0")
#	$(error Flasher: COMPILE_BOOT = No)
endif	
else
	@if [ -s $(RAM1R_IMAGE) ]; then echo "Use external $(RAM1R_IMAGE)!"; fi 
endif

$(RAM2P_IMAGE): $(ELFFILE) $(NMAPFILE) 
	@echo "==========================================================="
	@echo "Create image2p ($(RAM2P_IMAGE))"
#	@echo "==========================================================="
	@mkdir -p $(BIN_DIR)
	@rm -f $(RAM2_IMAGE) $(RAM2P_IMAGE)
	@$(eval RAM2_START_ADDR = $(shell grep __ram_image2_text $(NMAPFILE) | grep _start__ | awk '{print $$1}'))
	@$(eval RAM2_END_ADDR = $(shell grep __ram_image2_text $(NMAPFILE) | grep _end__ | awk '{print $$1}'))
	$(if $(RAM2_START_ADDR),,$(error "Not found __ram_image2_text_start__!"))
	$(if $(RAM2_END_ADDR),,$(error "Not found __ram_image2_text_end__!"))
	@$(OBJCOPY) -j .image2.start.table -j .ram_image2.text -j .ram_image2.rodata -j .ram.data -Obinary $(ELFFILE) $(RAM2_IMAGE)
	@$(PICK) 0x$(RAM2_START_ADDR) 0x$(RAM2_END_ADDR) $(RAM2_IMAGE) $(RAM2P_IMAGE) body+reset_offset+sig

$(RAM2NS_IMAGE):$(ELFFILE) $(NMAPFILE) 
	@echo "==========================================================="
	@echo "Create image2ns ($(RAM2NS_IMAGE))"
#	@echo "==========================================================="
	mkdir -p $(BIN_DIR)
	rm -f $(RAM2_IMAGE) $(RAM2NS_IMAGE)
	$(eval RAM2_START_ADDR = $(shell grep __ram_image2_text $(NMAPFILE) | grep _start__ | awk '{print $$1}'))
	$(eval RAM2_END_ADDR = $(shell grep __ram_image2_text $(NMAPFILE) | grep _end__ | awk '{print $$1}'))
	$(if $(RAM2_START_ADDR),,$(error "Not found __ram_image2_text_start__!"))
	$(if $(RAM2_END_ADDR),,$(error "Not found __ram_image2_text_end__!"))
	$(OBJCOPY) -j .image2.start.table -j .ram_image2.text -j .ram_image2.rodata -j .ram.data -Obinary $(ELFFILE) $(RAM2_IMAGE)
	$(PICK) 0x$(RAM2_START_ADDR) 0x$(RAM2_END_ADDR) $(RAM2_IMAGE) $(RAM2NS_IMAGE) body+reset_offset

$(RAM3_IMAGE): $(ELFFILE) $(NMAPFILE) 
	@echo "==========================================================="
	@echo "Create image3 (SDRAM, $(RAM3P_IMAGE))"
#	@echo "==========================================================="
	@mkdir -p $(BIN_DIR)
	@rm -f $(RAM3_IMAGE) $(RAM3P_IMAGE)
	@$(eval RAM3_START_ADDR = $(shell grep __sdram_data_ $(NMAPFILE) | grep _start__ | awk '{print $$1}'))
	@$(eval RAM3_END_ADDR = $(shell grep __sdram_data_ $(NMAPFILE) | grep _end__ | awk '{print $$1}'))
	$(if $(RAM3_START_ADDR),,$(error "Not found __sdram_data_start__!"))
	$(if $(RAM3_END_ADDR),,$(error "Not found __sdram_data_end__!"))
#ifneq ($(RAM3_START_ADDR),$(RAM3_END_ADDR))
	@echo	$(RAM3_START_ADDR) $(RAM3_END_ADDR)
	@$(OBJCOPY) -j .image3 -j .sdr_text -j .sdr_rodata -j .sdr_data -Obinary $(ELFFILE) $(RAM3_IMAGE)
	$(PICK) 0x$(RAM3_START_ADDR) 0x$(RAM3_END_ADDR) $(RAM3_IMAGE) $(RAM3P_IMAGE) body+reset_offset
#else
#	@rm -f $(RAM3_IMAGE) $(RAM3P_IMAGE)
#	@echo "SDRAM not used (size = 0)"
#endif
	
$(ELFFILE):
	$(error Falsher: file $@ not found)

clean:
	@rm -f $(BIN_DIR)/*.bin
	