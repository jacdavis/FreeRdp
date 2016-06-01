LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -D HAVE_CONFIG_H
LOCAL_CFLAGS += -D ANDROID

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += bionic/libc/include
LOCAL_C_INCLUDES += external/FreeRDP
LOCAL_C_INCLUDES += external/FreeRDP/include 
LOCAL_C_INCLUDES += external/FreeRDP/winpr/include 
LOCAL_C_INCLUDES += external/FreeRDP/winpr/include/winpr
LOCAL_C_INCLUDES += external/openssl/include

LOCAL_SRC_FILES := \
	cache/bitmap.c \
	cache/brush.c \
	cache/cache.c \
	cache/glyph.c \
	cache/nine_grid.c \
	cache/offscreen.c \
	cache/palette.c \
	cache/pointer.c \
	codec/audio.c \
	codec/bitmap.c \
	codec/clear.c \
	codec/color.c \
	codec/dsp.c \
	codec/h264.c \
	codec/interleaved.c \
	codec/jpeg.c \
	codec/mppc.c \
	codec/ncrush.c \
	codec/nsc.c \
	codec/nsc_encode.c \
	codec/nsc_sse2.c \
	codec/planar.c \
	codec/progressive.c \
	codec/region.c \
	codec/rfx.c \
	codec/rfx_decode.c \
	codec/rfx_differential.c \
	codec/rfx_dwt.c \
	codec/rfx_encode.c \
	codec/rfx_neon.c \
	codec/rfx_quantization.c \
	codec/rfx_rlgr.c \
	codec/xcrush.c \
	codec/zgfx.c \
	common/addin.c \
	common/settings.c \
	common/assistance.c \
	core/activation.c \
	core/autodetect.c \
	core/bulk.c \
	core/capabilities.c \
	core/certificate.c \
	core/channels.c \
	core/client.c \
	core/codecs.c \
	core/connection.c \
	core/errbase.c \
	core/errconnect.c \
	core/errinfo.c \
	core/fastpath.c \
	core/freerdp.c \
	core/gcc.c \
	core/graphics.c \
	core/heartbeat.c \
	core/info.c \
	core/input.c \
	core/license.c \
	core/listener.c \
	core/mcs.c \
	core/message.c \
	core/metrics.c \
	core/multitransport.c \
	core/nego.c \
	core/nla.c \
	core/orders.c \
	core/peer.c \
	core/rdp.c \
	core/redirection.c \
	core/security.c \
	core/server.c \
	core/settings.c \
	core/surface.c \
	core/tcp.c \
	core/timezone.c \
	core/tpdu.c \
	core/tpkt.c \
	core/transport.c \
	core/update.c \
	core/window.c \
	core/gateway/http.c \
	core/gateway/ncacn_http.c \
	core/gateway/ntlm.c \
	core/gateway/rdg.c \
	core/gateway/rpc_bind.c \
	core/gateway/rpc.c \
	core/gateway/rpc_client.c \
	core/gateway/rpc_fault.c \
	core/gateway/rts.c \
	core/gateway/rts_signature.c \
	core/gateway/tsg.c \
	crypto/base64.c \
	crypto/ber.c \
	crypto/certificate.c \
	crypto/crypto.c \
	crypto/der.c \
	crypto/er.c \
	crypto/per.c \
	crypto/tls.c \
	gdi/16bpp.c \
	gdi/32bpp.c \
	gdi/8bpp.c \
	gdi/bitmap.c \
	gdi/brush.c \
	gdi/clipping.c \
	gdi/dc.c \
	gdi/drawing.c \
	gdi/gdi.c \
	gdi/gfx.c \
	gdi/graphics.c \
	gdi/line.c \
	gdi/palette.c \
	gdi/pen.c \
	gdi/region.c \
	gdi/shape.c \
	locale/keyboard.c \
	locale/keyboard_layout.c \
	locale/keyboard_sun.c \
	locale/keyboard_x11.c \
	locale/locale.c \
	locale/timezone.c \
	locale/xkb_layout_ids.c \
	primitives/prim_16to32bpp.c \
	primitives/prim_16to32bpp_opt.c \
	primitives/prim_add.c \
	primitives/prim_add_opt.c \
	primitives/prim_alphaComp.c \
	primitives/prim_alphaComp_opt.c \
	primitives/prim_andor.c \
	primitives/prim_andor_opt.c \
	primitives/prim_colors.c \
	primitives/prim_colors_opt.c \
	primitives/prim_copy.c \
	primitives/primitives.c \
	primitives/prim_set.c \
	primitives/prim_set_opt.c \
	primitives/prim_shift.c \
	primitives/prim_shift_opt.c \
	primitives/prim_sign.c \
	primitives/prim_sign_opt.c \
	primitives/prim_YCoCg.c \
	primitives/prim_YCoCg_opt.c \
	primitives/prim_YUV.c \
	primitives/prim_YUV_opt.c \
	utils/msusb.c \
	utils/passphrase.c \
	utils/pcap.c \
	utils/profiler.c \
	utils/ringbuffer.c \
	utils/signal.c \
	utils/stopwatch.c \


LOCAL_SHARED_LIBRARIES := libc libcutils libnetutils libssl libcrypto libwinpr 
LOCAL_MODULE := libfreerdp
include $(BUILD_SHARED_LIBRARY)
