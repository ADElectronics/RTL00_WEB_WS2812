#=============================================
# Compilation tools
#=============================================
CROSS_COMPILE = $(GCC_PATH)arm-none-eabi-
AR = $(CROSS_COMPILE)ar
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
NM = $(CROSS_COMPILE)nm
LD = $(CROSS_COMPILE)gcc
GDB = $(CROSS_COMPILE)gdb
SIZE = $(CROSS_COMPILE)size
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

#=============================================
# TARGET dirs
#=============================================
TARGET ?= Debug
OBJ_DIR ?= $(TARGET)/obj
BIN_DIR ?= $(TARGET)/bin
ELFFILE ?= $(OBJ_DIR)/$(TARGET).axf

#=============================================
# Make bunary tools
#=============================================
PICK = $(TOOLS_PATH)pick.exe
PADDING = $(TOOLS_PATH)padding.exe
CHCKSUM = $(TOOLS_PATH)checksum.exe

#=============================================
# J-Link tools
#=============================================
JLINK_GDB ?= JLinkGDBServer.exe
JLINK_EXE ?= JLink.exe
