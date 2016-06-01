LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -D HAVE_CONFIG_H
LOCAL_CFLAGS += -D ANDROID

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += bionic/libc/include
LOCAL_C_INCLUDES += external/openssl
LOCAL_C_INCLUDES += external/openssl/include/openssl
LOCAL_C_INCLUDES += external/FreeRDP
LOCAL_C_INCLUDES += external/FreeRDP/include 
LOCAL_C_INCLUDES += external/FreeRDP/winpr/include 
LOCAL_C_INCLUDES += external/FreeRDP/winpr/include/winpr
LOCAL_C_INCLUDES += external/FreeRDP/winpr/libwinpr/crt
LOCAL_C_INCLUDES += external/FreeRDP/winpr/libwinpr/utils
LOCAL_C_INCLUDES += external/FreeRDP/winpr/libwinpr/utils/trio
LOCAL_C_INCLUDES += external/FreeRDP/winpr/libwinpr/utils/wlog
LOCAL_C_INCLUDES += external/openssl/include

LOCAL_LDLIBS += -lpthread 

LOCAL_SRC_FILES := \
	libwinpr/asn1/asn1.c \
	libwinpr/bcrypt/bcrypt.c \
	libwinpr/crt/alignment.c \
	libwinpr/crt/buffer.c \
	libwinpr/crt/conversion.c \
	libwinpr/crt/memory.c \
	libwinpr/crt/string.c \
	libwinpr/crt/unicode.c \
	libwinpr/crt/utf.c \
	libwinpr/com/com.c \
	libwinpr/comm/comm.c \
	libwinpr/comm/comm_io.c \
	libwinpr/comm/comm_ioctl.c \
	libwinpr/comm/comm_sercx2_sys.c \
	libwinpr/comm/comm_sercx_sys.c \
	libwinpr/comm/comm_serial_sys.c \
	libwinpr/credentials/credentials.c \
	libwinpr/credui/credui.c \
	libwinpr/crypto/cert.c \
	libwinpr/crypto/crypto.c \
	libwinpr/dsparse/dsparse.c \
	libwinpr/environment/environment.c \
	libwinpr/error/error.c \
	libwinpr/file/file.c \
	libwinpr/file/generic.c \
	libwinpr/file/namedPipeClient.c \
	libwinpr/file/pattern.c \
	libwinpr/handle/handle.c \
	libwinpr/handle/nonehandle.c \
	libwinpr/heap/heap.c \
	libwinpr/input/keycode.c \
	libwinpr/input/scancode.c \
	libwinpr/input/virtualkey.c \
	libwinpr/interlocked/interlocked.c \
	libwinpr/io/device. \
	libwinpr/io/io.c \
	libwinpr/library/library.c \
	libwinpr/locale/locale.c \
	libwinpr/memory/memory.c \
	libwinpr/nt/nt.c \
	libwinpr/path/path.c \
	libwinpr/path/shell.c \
	libwinpr/pipe/pipe.c \
	libwinpr/pool/callback.c \
	libwinpr/pool/callback_cleanup.c \
	libwinpr/pool/callback_environment.c \
	libwinpr/pool/cleanup_group.c \
	libwinpr/pool/io.c \
	libwinpr/pool/pool.c \
	libwinpr/pool/synch.c \
	libwinpr/pool/timer.c \
	libwinpr/pool/work.c \
	libwinpr/registry/registry.c \
	libwinpr/registry/registry_reg.c \
	libwinpr/rpc/midl.c \
	libwinpr/rpc/ndr_array.c \
	libwinpr/rpc/ndr.c \
	libwinpr/rpc/ndr_context.c \
	libwinpr/rpc/ndr_correlation.c \
	libwinpr/rpc/ndr_pointer.c \
	libwinpr/rpc/ndr_private.c \
	libwinpr/rpc/ndr_simple.c \
	libwinpr/rpc/ndr_string.c \
	libwinpr/rpc/ndr_structure.c \
	libwinpr/rpc/ndr_union.c \
	libwinpr/rpc/rpc.c \
	libwinpr/security/security.c \
	libwinpr/shell/shell.c \
	libwinpr/smartcard/smartcard.c \
	libwinpr/smartcard/smartcard_inspect.c \
	libwinpr/smartcard/smartcard_pcsc.c \
	libwinpr/smartcard/smartcard_winscard.c \
	libwinpr/sspi/sspi.c \
	libwinpr/sspi/sspi_export.c \
	libwinpr/sspi/sspi_winpr.c \
	libwinpr/sspi/NTLM/ntlm_av_pairs.c \
	libwinpr/sspi/NTLM/ntlm.c \
	libwinpr/sspi/NTLM/ntlm_compute.c \
	libwinpr/sspi/NTLM/ntlm_message.c \
	libwinpr/sspi/Negotiate/negotiate.c \
	libwinpr/sspi/CredSSP/credssp.c \
	libwinpr/sspi/Schannel/schannel.c \
	libwinpr/sspi/Schannel/schannel_openssl.c \
	libwinpr/sspicli/sspicli.c \
	libwinpr/synch/address.c \
	libwinpr/synch/barrier.c \
	libwinpr/synch/condition.c \
	libwinpr/synch/critical.c \
	libwinpr/synch/event.c \
	libwinpr/synch/init.c \
	libwinpr/synch/mutex.c \
	libwinpr/synch/semaphore.c \
	libwinpr/synch/sleep.c \
	libwinpr/synch/srw.c \
	libwinpr/synch/timer.c \
	libwinpr/synch/wait.c \
	libwinpr/sysinfo/sysinfo.c \
	libwinpr/thread/argv.c \
	libwinpr/thread/process.c \
	libwinpr/thread/thread.c \
	libwinpr/thread/tls.c \
	libwinpr/timezone/timezone.c \
	libwinpr/utils/cmdline.c \
	libwinpr/utils/debug.c \
	libwinpr/utils/image.c \
	libwinpr/utils/ini.c \
	libwinpr/utils/ntlm.c \
	libwinpr/utils/print.c \
	libwinpr/utils/sam.c \
	libwinpr/utils/ssl.c \
	libwinpr/utils/stream.c \
	libwinpr/utils/winpr.c \
	libwinpr/utils/collections/ArrayList.c \
	libwinpr/utils/collections/BipBuffer.c \
	libwinpr/utils/collections/BitStream.c \
	libwinpr/utils/collections/BufferPool.c \
	libwinpr/utils/collections/CountdownEvent.c \
	libwinpr/utils/collections/Dictionary.c \
	libwinpr/utils/collections/HashTable.c \
	libwinpr/utils/collections/KeyValuePair.c \
	libwinpr/utils/collections/LinkedList.c \
	libwinpr/utils/collections/ListDictionary.c \
	libwinpr/utils/collections/MessagePipe.c \
	libwinpr/utils/collections/MessageQueue.c \
	libwinpr/utils/collections/ObjectPool.c \
	libwinpr/utils/collections/PubSub.c \
	libwinpr/utils/collections/Queue.c \
	libwinpr/utils/collections/Reference.c \
	libwinpr/utils/collections/Stack.c \
	libwinpr/utils/collections/StreamPool.c \
	libwinpr/utils/lodepng/lodepng.c \
	libwinpr/utils/trio/trio.c \
	libwinpr/utils/trio/trionan.c \
	libwinpr/utils/trio/triostr.c \
	libwinpr/utils/wlog/Appender.c \
	libwinpr/utils/wlog/BinaryAppender.c \
	libwinpr/utils/wlog/CallbackAppender.c \
	libwinpr/utils/wlog/ConsoleAppender.c \
	libwinpr/utils/wlog/DataMessage.c \
	libwinpr/utils/wlog/FileAppender.c \
	libwinpr/utils/wlog/ImageMessage.c \
	libwinpr/utils/wlog/Layout.c \
	libwinpr/utils/wlog/Message.c \
	libwinpr/utils/wlog/PacketMessage.c \
	libwinpr/utils/wlog/TextMessage.c \
	libwinpr/utils/wlog/wlog.c \
	libwinpr/winhttp/winhttp.c \
	libwinpr/winsock/winsock.c \
	libwinpr/wnd/wnd.c \
	libwinpr/wtsapi/wtsapi.c \
	tools/makecert/makecert.c \
	tools/makecert/cli/main.c \

LOCAL_SHARED_LIBRARIES := libc libcutils libnetutils libdl libssl libcrypto
LOCAL_MODULE := libwinpr
include $(BUILD_SHARED_LIBRARY)
