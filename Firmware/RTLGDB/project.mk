#=============================================
# SDK CONFIG
#=============================================

#USE_SDRAM = 1
#USE_POLARSSL = 1
#USE_P2P_WPS = 1
USE_MBED = 1
USE_GCC_LIB = 1

ifndef USE_AT
USE_NEWCONSOLE = 1
USE_WIFI_API = 1
endif

include $(SDK_PATH)sdkset.mk
#CFLAGS += -DDEFAULT_BAUDRATE=1562500
CFLAGS += -DLOGUART_STACK_SIZE=1024

#=============================================
# User Files
#=============================================

# main
ADD_SRC_C += project/main.c
ADD_SRC_C += project/user_start.c

# user
INCLUDES += project/WS2812
ADD_SRC_C += project/WS2812/WS2812.c
ADD_SRC_C += project/WS2812/ledfilters.c
ADD_SRC_C += project/WS2812/ledeffectsserver.c

#Web-server
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
