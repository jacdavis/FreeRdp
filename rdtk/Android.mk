LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -D HAVE_CONFIG_H
LOCAL_CFLAGS += -D ANDROID

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += external/FreeRDP
LOCAL_C_INCLUDES += external/FreeRDP/include 
LOCAL_C_INCLUDES += external/FreeRDP/winpr/include 
LOCAL_C_INCLUDES += external/FreeRDP/rdtk/include 
LOCAL_C_INCLUDES += external/FreeRDP/include/freerdp/codec 
LOCAL_C_INCLUDES += external/openssl/include

LOCAL_SRC_FILES := \
	librdtk/rdtk_button.c \
	librdtk/rdtk_engine.c \
	librdtk/rdtk_font.c \
	librdtk/rdtk_label.c \
	librdtk/rdtk_nine_patch.c \
	librdtk/rdtk_resources.c \
	librdtk/rdtk_surface.c \
	librdtk/rdtk_text_field.c \

LOCAL_SHARED_LIBRARIES := libc libcutils libnetutils libssl libcrypto libwinpr libfreerdp
LOCAL_MODULE := librdtk
include $(BUILD_SHARED_LIBRARY)
