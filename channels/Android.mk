LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -D HAVE_CONFIG_H
LOCAL_CFLAGS += -D ANDROID

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += external/FreeRDP
LOCAL_C_INCLUDES += external/FreeRDP/include 
LOCAL_C_INCLUDES += external/FreeRDP/include/freerdp/server
LOCAL_C_INCLUDES += external/FreeRDP/include/freerdp/codec
LOCAL_C_INCLUDES += external/FreeRDP/winpr/include 
LOCAL_C_INCLUDES += external/FreeRDP/rdtk/include 
LOCAL_C_INCLUDES += external/FreeRDP/channels/audin/client
LOCAL_C_INCLUDES += external/FreeRDP/channels/tsmf/client
LOCAL_C_INCLUDES += external/openssl/include
LOCAL_C_INCLUDES += external/tinyalsa/include

LOCAL_SRC_FILES := \
	audin/server/audin.c \
	cliprdr/client/cliprdr_format.c \
	cliprdr/client/cliprdr_main.c \
	cliprdr/server/cliprdr_main.c \
	disp/client/disp_main.c \
	drdynvc/client/drdynvc_main.c \
	drdynvc/server/drdynvc_main.c \
	drive/client/drive_file.c \
	drive/client/drive_main.c \
	echo/client/echo_main.c \
	echo/server/echo_main.c \
	encomsp/client/encomsp_main.c \
	encomsp/server/encomsp_main.c \
	parallel/client/parallel_main.c \
	printer/client/printer_main.c \
	rail/rail_common.c \
	rail/client/rail_main.c \
	rail/client/rail_orders.c \
	rdpdr/client/devman.c \
	rdpdr/client/irp.c \
	rdpdr/client/rdpdr_capabilities.c \
	rdpdr/client/rdpdr_main.c \
	rdpdr/server/rdpdr_main.c \
	rdpsnd/client/rdpsnd_main.c \
	rdpsnd/server/rdpsnd_main.c \
	remdesk/client/remdesk_main.c \
	remdesk/server/remdesk_main.c \
	smartcard/client/smartcard_main.c \
	smartcard/client/smartcard_operations.c \
	smartcard/client/smartcard_pack.c \
	tsmf/client/tsmf_audio.c \
	tsmf/client/tsmf_codec.c \
	tsmf/client/tsmf_decoder.c \
	tsmf/client/tsmf_ifman.c \
	tsmf/client/tsmf_main.c \
	tsmf/client/tsmf_media.c \

LOCAL_SHARED_LIBRARIES := libc libcutils libnetutils libssl libcrypto libwinpr librdtk libfreerdp
LOCAL_MODULE := libfreerdpchannels
include $(BUILD_SHARED_LIBRARY)
