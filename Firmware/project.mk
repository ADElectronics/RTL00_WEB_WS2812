#===========================================================
# SDK CONFIG
#===========================================================

USE_MBED = 1
USE_GCC_LIB = 1

ifndef USE_AT
USE_NEWCONSOLE = 1
USE_WIFI_API = 1
endif

include $(SDK_PATH)sdkset.mk
#CFLAGS += -DDEFAULT_BAUDRATE=1562500
CFLAGS += -DLOGUART_STACK_SIZE=1024

#===========================================================
# Main Files
#===========================================================

# main
ADD_SRC_C += project/main.c
ADD_SRC_C += project/user_start.c

# user
INCLUDES += project/WS2812
ADD_SRC_C += project/WS2812/WS2812.c
ADD_SRC_C += project/WS2812/ledfilters.c
ADD_SRC_C += project/WS2812/ledeffectsserver.c

#===========================================================
# Additional Files
#===========================================================

ifdef USE_UVC
USE_SDRAM = 1
USE_GCC_LIB = 1
endif

ifdef USE_SDCARD
USE_FATFS = 1
USE_SDIOH = 1
endif

ifdef USE_SDCARD
ADD_SRC_C += project/console/sd_fat.c
endif

ifdef USE_UVC
ADD_SRC_C += project/console/uvc_capture_tst.c
endif

ifdef WEB_INA219_DRV
#ADD_SRC_C += project/driver/i2c_drv.c
ADD_SRC_C += project/ina219/ina219drv.c
#CFLAGS += -DUSE_I2C_CONSOLE=1
CFLAGS += -DWEB_INA219_DRV=1
endif

ifdef WEB_MLX90614_DRV
#ADD_SRC_C += project/driver/i2c_drv.c
#CFLAGS += -DUSE_I2C_CONSOLE=1
ADD_SRC_C += project/MLX90614/MLX90614.c
CFLAGS += -DWEB_MLX90614_DRV=1
endif

ifdef USE_I2C_CONSOLE
ADD_SRC_C += project/driver/i2c_drv.c
CFLAGS += -DUSE_I2C_CONSOLE=1
endif

ifdef WEB_ADC_DRV
ADD_SRC_C += project/driver/adc_drv.c
ADD_SRC_C += project/adc_ws/adc_ws.c
CFLAGS += -DWEB_ADC_DRV=1
endif

#===========================================================
# Web-server
#===========================================================

INCLUDES += project/web
ADD_SRC_C += project/tcpsrv/tcp_srv_conn.c
ADD_SRC_C += project/webfs/webfs.c
ADD_SRC_C += project/web/web_srv.c
ADD_SRC_C += project/web/web_utils.c
ADD_SRC_C += project/web/web_websocket.c
ADD_SRC_C += project/web/websock.c
ADD_SRC_C += project/web/web_int_callbacks.c
ADD_SRC_C += project/web/web_int_vars.c
ADD_SRC_C += project/web/web_auth.c
