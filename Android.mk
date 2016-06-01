
LOCAL_PATH:= $(call my-dir)

include $(LOCAL_PATH)/winpr/Android.mk \
	$(LOCAL_PATH)/libfreerdp/Android.mk \
	$(LOCAL_PATH)/rdtk/Android.mk \
	$(LOCAL_PATH)/channels/Android.mk \
	$(LOCAL_PATH)/server/Android.mk
