/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 *
 * Copyright 2011-2014 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <linux/fb.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>

#include <winpr/crt.h>
#include <winpr/path.h>
#include <winpr/synch.h>
#include <winpr/image.h>
#include <winpr/sysinfo.h>

#include <freerdp/log.h>
#include <freerdp/codec/color.h>
#include <freerdp/codec/region.h>

#include "../shadow_screen.h"
#include "../shadow_client.h"
#include "../shadow_capture.h"
#include "../shadow_surface.h"
#include "../shadow_subsystem.h"
#include "../shadow_mcevent.h"

#include "android_shadow.h"
#include <cutils/properties.h>
#include <utils/Log.h>

//#include <donatellocommon/array.h>

#define TAG SERVER_TAG("shadow.android")

int write_all(int fd, void *data, int size) {
    int left = size;
    char *buf = data;
    while (left > 0) {
        int written = write(fd, buf + (size - left), left);
        // If there was an error, or we failed to write for a reason other than being interrupted, bail
        if (written < 0 || (written == 0 && errno != EINTR)) {
            return 0;
        }

        left -= written;
    }

    return 1;
}


void android_shadow_input_synchronize_event(androidShadowSubsystem* subsystem, UINT32 flags)
{

}

void android_shadow_input_keyboard_event(androidShadowSubsystem* subsystem, UINT16 flags, UINT16 code)
{
    if (subsystem->keyboard_fd == 0)
    {
	return;
    }

    const int numEvents = 3;
    struct input_event keyboardEvents[numEvents];

    struct timeval currTime;
    gettimeofday(&currTime, NULL);

    ALOGE("Donatello keyboard code:%d", code);
    
    keyboardEvents[0].time = currTime;
    keyboardEvents[0].type = EV_KEY;
    keyboardEvents[0].code = code; 
    keyboardEvents[0].value = 1;

    keyboardEvents[2].time = currTime;
    keyboardEvents[2].type = EV_SYN;
    keyboardEvents[2].code = SYN_REPORT;
    keyboardEvents[2].value = 0;

    gettimeofday(&currTime, NULL);

    keyboardEvents[1].time = currTime;
    keyboardEvents[1].type = EV_KEY;
    keyboardEvents[1].code = code;
    keyboardEvents[1].value = 0;

    keyboardEvents[2].time = currTime;
    keyboardEvents[2].type = EV_SYN;
    keyboardEvents[2].code = SYN_REPORT;
    keyboardEvents[2].value = 0;

    int status = write_all(subsystem->keyboard_fd, &code, sizeof(code));

    if (status < 0)
    {
	ALOGE("android_shadow_input_keyboard_event failed to write mouse event");
    } 
}

void android_shadow_input_unicode_keyboard_event(androidShadowSubsystem* subsystem, UINT16 flags, UINT16 code)
{
    
}

void android_shadow_input_mouse_event(androidShadowSubsystem* subsystem, UINT16 flags, UINT16 x, UINT16 y)
{
    rdpShadowServer* server;
    rdpShadowSurface* surface;

    server = subsystem->server;
    surface = server->surface;

    if (subsystem->touch_fd == 0)
    {
	return;
    }

    struct timeval currTime;
    gettimeofday(&currTime, NULL);

    if (((flags & PTR_FLAGS_DOWN) || (flags & PTR_FLAGS_MOVE)) && (flags & PTR_FLAGS_BUTTON1))
    {
	const int numEvents = 6;
	struct input_event touchEvents[numEvents];

	touchEvents[0].time = currTime;
	touchEvents[0].type = EV_ABS;
	touchEvents[0].code = ABS_MT_POSITION_X;
	touchEvents[0].value = x;

	touchEvents[1].time = currTime;
	touchEvents[1].type = EV_ABS; 
	touchEvents[1].code = ABS_MT_POSITION_Y;
	touchEvents[1].value = y;

	touchEvents[2].time = currTime;
	touchEvents[2].type = EV_SYN;
	touchEvents[2].code = SYN_MT_REPORT;
	touchEvents[2].value = 0;

	touchEvents[3].time = currTime;
	touchEvents[3].type = EV_SYN;
	touchEvents[3].code = SYN_REPORT;
	touchEvents[3].value = 0;

	touchEvents[4].time = currTime;
	touchEvents[4].type = EV_SYN;
	touchEvents[4].code = SYN_MT_REPORT;
	touchEvents[4].value = 0;

	touchEvents[5].time = currTime;
	touchEvents[5].type = EV_SYN;
	touchEvents[5].code = SYN_REPORT;
	touchEvents[5].value = 0;
    
	int status = write_all(subsystem->touch_fd, touchEvents, sizeof(struct input_event) * numEvents);
	if (status < 0)
	{
	    ALOGE("android_shadow_input_mouse_event failed to write mouse event");
	}
    }
    else
    {
	const int numEvents = 2;
	struct input_event touchEvents[numEvents];

	touchEvents[0].time = currTime;
	touchEvents[0].type = EV_SYN;
	touchEvents[0].code = SYN_MT_REPORT;
	touchEvents[0].value = 0;

	touchEvents[1].time = currTime;
	touchEvents[1].type = EV_SYN;
	touchEvents[1].code = SYN_REPORT;
	touchEvents[1].value = 0;
    
	int status = write_all(subsystem->touch_fd, touchEvents, sizeof(struct input_event) * numEvents);
	if (status < 0)
	{
	    ALOGE("android_shadow_input_mouse_event failed to write mouse event");
	}
    }
}

void android_shadow_input_extended_mouse_event(androidShadowSubsystem* subsystem, UINT16 flags, UINT16 x, UINT16 y)
{

}

static void android_shadow_message_free(UINT32 id, SHADOW_MSG_OUT* msg)
{
    switch(id)
    {
    case SHADOW_MSG_OUT_POINTER_POSITION_UPDATE_ID:
	free(msg);
	break;

    case SHADOW_MSG_OUT_POINTER_ALPHA_UPDATE_ID:
	free(((SHADOW_MSG_OUT_POINTER_ALPHA_UPDATE*)msg)->xorMaskData);
	free(((SHADOW_MSG_OUT_POINTER_ALPHA_UPDATE*)msg)->andMaskData);
	free(msg);
	break;

    default:
	WLog_ERR(TAG, "Unknown message id: %u", id);
	free(msg);
	break;
    }
}

int android_shadow_pointer_position_update(androidShadowSubsystem* subsystem)
{
    return 1;
}

int android_shadow_pointer_alpha_update(androidShadowSubsystem* subsystem)
{
    return 1;
}

int android_shadow_query_cursor(androidShadowSubsystem* subsystem, BOOL getImage)
{
    return 1;
}

int android_shadow_blend_cursor(androidShadowSubsystem* subsystem)
{
    return 1;
}


int android_shadow_subsystem_process_message(androidShadowSubsystem* subsystem, wMessage* message)
{
    // TODO: Implement?

    if (message->Free)
	message->Free(message);

    return 1;
}

int android_shadow_screen_grab(androidShadowSubsystem* subsystem)
{
    int status = 0;
    RECTANGLE_16 invalidRect;
    RECTANGLE_16 surfaceRect;
    rdpShadowScreen* screen;
    rdpShadowServer* server;
    rdpShadowSurface* surface;
    const RECTANGLE_16 *extents;
    BYTE* frameBufferRawBytes = NULL;
    struct fb_fix_screeninfo fi;
    struct fb_var_screeninfo vi;

    server = subsystem->server;
    surface = server->surface;
    screen = server->screen;

    surfaceRect.left = 0;
    surfaceRect.top = 0;
    surfaceRect.right = surface->width;
    surfaceRect.bottom = surface->height;

	
    const char* frameBufferPath = "/dev/graphics/fb0";
    int frameBufferFD = open(frameBufferPath, O_RDONLY);
    if (frameBufferFD < 0)
    {
	ALOGE("android_shadow_screen_grab begin - failure to open frame buffer");
	return -1;
    }

    if (ioctl(frameBufferFD, FBIOGET_FSCREENINFO, &fi) < 0)
    {
	ALOGE("android_shadow_screen_grab begin - failure get screen info");
	return -1;
    }

    if (ioctl(frameBufferFD, FBIOGET_VSCREENINFO, &vi) < 0)
    {
	ALOGE("android_shadow_screen_grab begin - failure get virtual screen info");
	return -1;
    }

    
    // TODO: will likely need to convert this to another format. Some devices use 565 for the framebuffer 
    // etc...
    // does this need to wait until screen buffer synchronize or is that automatic?
    frameBufferRawBytes = (BYTE*)mmap(0, fi.smem_len, PROT_READ, MAP_SHARED, frameBufferFD, 0);
    if (frameBufferRawBytes == MAP_FAILED)
    {
	ALOGE("android_shadow_screen_grab begin - failure read bytes of frame buffer");
	return -1;
    }

    // TODO: Need to worry about padding?
    int frameBufferBytesPerLine = vi.xres * (vi.bits_per_pixel / 8);
    int frameBufferByteLength = frameBufferBytesPerLine * vi.yres;
    status = shadow_capture_compare(
	surface->data, 
	surface->scanline, 
	surface->width, 
	surface->height,
	frameBufferRawBytes, 
	frameBufferBytesPerLine,
	&invalidRect
	);

    region16_union_rect(&(subsystem->invalidRegion), &(subsystem->invalidRegion), &invalidRect);
    region16_intersect_rect(&(subsystem->invalidRegion), &(subsystem->invalidRegion), &surfaceRect);

    if (!region16_is_empty(&(subsystem->invalidRegion)))
    {
	extents = region16_extents(&(subsystem->invalidRegion));

	int width = extents->right - extents->left;
	int height = extents->bottom - extents->top;

	freerdp_image_copy(
	    surface->data, 
	    PIXEL_FORMAT_XRGB32,
	    surface->scanline, 
	    extents->left, 
	    extents->top, 
	    width, 
	    height,
	    (BYTE*) frameBufferRawBytes, 
	    PIXEL_FORMAT_XRGB32,
	    frameBufferBytesPerLine, 
	    extents->left, 
	    extents->top, 
	    NULL
	    );

	//x11_shadow_blend_cursor(subsystem);

	shadow_multiclient_publish_and_wait(subsystem->updateEvent);
	region16_clear(&(subsystem->invalidRegion));
    }

    munmap(frameBufferRawBytes, fi.smem_len);
    close(frameBufferFD);

    return 1;
}

void* android_shadow_subsystem_thread(androidShadowSubsystem* subsystem)
{
    DWORD status;
    DWORD nCount;
    UINT64 cTime;
    DWORD dwTimeout;
    DWORD dwInterval;
    UINT64 frameTime;

    subsystem->captureFrameRate = 16;
    dwInterval = 1000 / subsystem->captureFrameRate;
    frameTime = GetTickCount64() + dwInterval;

    while (1)
    {
	// TODO: Make this alertable so it isn't spinning a core
	cTime = GetTickCount64();
	dwTimeout = (cTime > frameTime) ? 0 : frameTime - cTime;

	if ((GetTickCount64() > frameTime))
	{
	    android_shadow_screen_grab(subsystem);
	    //android_shadow_query_cursor(subsystem, FALSE);

	    dwInterval = 1000 / subsystem->captureFrameRate;
	    frameTime += dwInterval;
	}
    }

    ExitThread(0);
    return NULL;
}

int android_create_touch_device() 
{
    int touch_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (touch_fd < 0) {
        ALOGE("Failed to open uinput device!  Error: %d", errno);
        return 0;
    }

    if (ioctl(touch_fd, UI_SET_EVBIT, EV_ABS) < 0 ||
        ioctl(touch_fd, UI_SET_EVBIT, EV_SYN) < 0) {
        ALOGE("Failed to configure uinput touch device (UI_SET_EVBIT)!  Error: %d", errno);
        return 0;
    }

    if (ioctl(touch_fd, UI_SET_ABSBIT, ABS_MT_POSITION_X) < 0 ||
        ioctl(touch_fd, UI_SET_ABSBIT, ABS_MT_POSITION_Y) < 0) {
        ALOGE("Failed to configure uinput touch device (UI_SET_ABSBIT)!  Error: %d", errno);
        return 0;
    }

    struct uinput_user_dev touch_dev;
    memset(&touch_dev, 0, sizeof(touch_dev));

    // TODO: These should go across the donatello pipes instead 
    // if possible. Meaning that the events should come through rdp and then get
    // routed to the donatello service. Doing so will have the security of rdp,
    // but the functionality of rdp
    snprintf(touch_dev.name, UINPUT_MAX_NAME_SIZE, "Donatello Virtual Touch Device RDP");
    touch_dev.id.bustype = BUS_VIRTUAL;
    const int DEV_VENDOR = 0x045e;
    touch_dev.id.vendor = DEV_VENDOR;
    const int TOUCH_DEV_PRODUCT = 0x4321;
    touch_dev.id.product = TOUCH_DEV_PRODUCT;
    const int TOUCH_DEV_VERSION = 1;
    touch_dev.id.version = TOUCH_DEV_VERSION;

    char heightString[PROP_VALUE_MAX];
    char widthString[PROP_VALUE_MAX];
    property_get("ro.vsemu.resolution.height", heightString, "640");
    property_get("ro.vsemu.resolution.width", widthString, "480");

    // Report large axes and scale the values later
    touch_dev.absmin[ABS_MT_POSITION_X] = 0;
    touch_dev.absmax[ABS_MT_POSITION_X] = atoi(widthString);
    touch_dev.absmin[ABS_MT_POSITION_Y] = 0;
    touch_dev.absmax[ABS_MT_POSITION_Y] = atoi(heightString);

    if (write_all(touch_fd, &touch_dev, sizeof(touch_dev)) < 0) {
        ALOGE("Failed to write uinput touch device config!  Error: %d", errno);
        return 0;
    }

    if (ioctl(touch_fd, UI_DEV_CREATE) < 0) {
        ALOGE("Failed to create uinput touch device (UI_DEV_CREATE)!  Error: %d", errno);
        return 0;
    }

    return touch_fd;
}


// Keys reported via "getinput -i" in Hyper-V
static const int valid_key_codes[] = {
    KEY_ESC,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,
    KEY_MINUS,
    KEY_EQUAL,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_Q,
    KEY_W,
    KEY_E,
    KEY_R,
    KEY_T,
    KEY_Y,
    KEY_U,
    KEY_I,
    KEY_O,
    KEY_P,
    KEY_LEFTBRACE,
    KEY_RIGHTBRACE,
    KEY_ENTER,
    KEY_LEFTCTRL,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_SEMICOLON,
    KEY_APOSTROPHE,
    KEY_GRAVE,
    KEY_LEFTSHIFT,
    KEY_BACKSLASH,
    KEY_Z,
    KEY_X,
    KEY_C,
    KEY_V,
    KEY_B,
    KEY_N,
    KEY_M,
    KEY_COMMA,
    KEY_DOT,
    KEY_SLASH,
    KEY_RIGHTSHIFT,
    KEY_KPASTERISK,
    KEY_LEFTALT,
    KEY_SPACE,
    KEY_CAPSLOCK,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_NUMLOCK,
    KEY_SCROLLLOCK,
    KEY_KP7,
    KEY_KP8,
    KEY_KP9,
    KEY_KPMINUS,
    KEY_KP4,
    KEY_KP5,
    KEY_KP6,
    KEY_KPPLUS,
    KEY_KP1,
    KEY_KP2,
    KEY_KP3,
    KEY_KP0,
    KEY_KPDOT,
    KEY_ZENKAKUHANKAKU,
    KEY_102ND,
    KEY_F11,
    KEY_F12,
    KEY_RO,
    KEY_KATAKANA,
    KEY_HIRAGANA,
    KEY_HENKAN,
    KEY_KATAKANAHIRAGANA,
    KEY_MUHENKAN,
    KEY_KPJPCOMMA,
    KEY_KPENTER,
    KEY_RIGHTCTRL,
    KEY_KPSLASH,
    KEY_SYSRQ,
    KEY_RIGHTALT,
    KEY_HOME,
    KEY_UP,
    KEY_PAGEUP,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_END,
    KEY_DOWN,
    KEY_PAGEDOWN,
    KEY_INSERT,
    KEY_DELETE,
    KEY_MACRO,
    KEY_MUTE,
    KEY_VOLUMEDOWN,
    KEY_VOLUMEUP,
    KEY_POWER,
    KEY_KPEQUAL,
    KEY_KPPLUSMINUS,
    KEY_PAUSE,
    KEY_KPCOMMA,
    KEY_HANGEUL,
    KEY_HANJA,
    KEY_YEN,
    KEY_LEFTMETA,
    KEY_RIGHTMETA,
    KEY_COMPOSE,
    KEY_STOP,
    KEY_CALC,
    KEY_SLEEP,
    KEY_WAKEUP,
    KEY_MAIL,
    KEY_BOOKMARKS,
    KEY_COMPUTER,
    KEY_BACK,
    KEY_FORWARD,
    KEY_NEXTSONG,
    KEY_PLAYPAUSE,
    KEY_PREVIOUSSONG,
    KEY_STOPCD,
    KEY_HOMEPAGE,
    KEY_REFRESH,
    KEY_F13,
    KEY_F14,
    KEY_F15,
    KEY_SEARCH,
    KEY_MEDIA,
};

static const int valid_key_codes_count = sizeof(valid_key_codes) / sizeof(valid_key_codes[0]);

int android_create_keyboard_device() 
{
    int keyboard_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (keyboard_fd < 0) 
    {
        ALOGE("Failed to open uinput device!  Error: %d", errno);
        return 0;
    }

    if (ioctl(keyboard_fd, UI_SET_EVBIT, EV_KEY) < 0 ||
        ioctl(keyboard_fd, UI_SET_EVBIT, EV_SYN) < 0) 
    {
        ALOGE("Failed to configure uinput keyboard device (UI_SET_EVBIT)!  Error: %d", errno);
        return 0;
    }

    int i;
    for (i = 0; i < valid_key_codes_count; i++) 
    {
        if (ioctl(keyboard_fd, UI_SET_KEYBIT, valid_key_codes[i]) < 0) 
	{
            ALOGE("Failed to configure uinput keyboard device (UI_SET_KEYBIT)!  Error: %d", errno);
            return 0;
        }
    }

    struct uinput_user_dev keyboard_dev;
    memset(&keyboard_dev, 0, sizeof(keyboard_dev));

    snprintf(keyboard_dev.name, UINPUT_MAX_NAME_SIZE, "Donatello Virtual Keyboard Device RDP");
    keyboard_dev.id.bustype = BUS_VIRTUAL;
    const int DEV_VENDOR = 0x045e;
    keyboard_dev.id.vendor = DEV_VENDOR;
    const int KBD_DEV_PRODUCT = 0x8765;
    keyboard_dev.id.product = KBD_DEV_PRODUCT;
    keyboard_dev.id.version = 1;

    if (write(keyboard_fd, &keyboard_dev, sizeof(keyboard_dev)) < 0) 
    {
        ALOGE("Failed to write uinput keyboard device config!  Error: %d", errno);
        return 0;
    }

    if (ioctl(keyboard_fd, UI_DEV_CREATE) < 0) {
        ALOGE("Failed to create uinput keyboard device (UI_DEV_CREATE)!  Error: %d", errno);
        return 0;
    }

    return keyboard_fd;
}

int android_shadow_subsystem_init(androidShadowSubsystem* subsystem)
{
    subsystem->numMonitors = 1;

    char heightString[PROP_VALUE_MAX];
    char widthString[PROP_VALUE_MAX];

    property_get("ro.vsemu.resolution.height", heightString, "640");
    property_get("ro.vsemu.resolution.width", widthString, "480");

    subsystem->width = atoi(widthString);
    subsystem->height = atoi(heightString);

    subsystem->virtualScreen.left = 0;
    subsystem->virtualScreen.top = 0;
    subsystem->virtualScreen.right = subsystem->width;
    subsystem->virtualScreen.bottom = subsystem->height;
    subsystem->virtualScreen.flags = 1;
    
    subsystem->touch_fd = android_create_touch_device();
    subsystem->keyboard_fd = android_create_keyboard_device();

    return 1;
}

int android_shadow_subsystem_uninit(androidShadowSubsystem* subsystem)
{
    if (!subsystem)
	return -1;

    if (subsystem->event)
    {
	CloseHandle(subsystem->event);
	subsystem->event = NULL;
    }

    return 1;
}

int android_shadow_subsystem_start(androidShadowSubsystem* subsystem)
{
    if (!subsystem)
	return -1;


    if (!(subsystem->thread = CreateThread(NULL, 0,
					   (LPTHREAD_START_ROUTINE) android_shadow_subsystem_thread,
					   (void*) subsystem, 0, NULL)))
    {
	WLog_ERR(TAG, "Failed to create thread");
	return -1;
    }

    return 1;
}

int android_shadow_subsystem_stop(androidShadowSubsystem* subsystem)
{
    if (!subsystem)
	return -1;

    return 1;
}

int android_shadow_enum_monitors(MONITOR_DEF* monitors, int maxMonitors)
{
    ALOGE("android_shadow_enum_monitors");
    char heightString[PROP_VALUE_MAX];
    char widthString[PROP_VALUE_MAX];

    property_get("ro.vsemu.resolution.height", heightString, "640");
    property_get("ro.vsemu.resolution.width", widthString, "480");

    monitors[0].left = 0; 
    monitors[0].top = 0;
    monitors[0].bottom = atoi(heightString);	
    monitors[0].right = atoi(widthString);	
    monitors[0].flags =1;

    // Android only has one monitor;
    return 1;
}

androidShadowSubsystem* android_shadow_subsystem_new()
{
    ALOGE("android_shadow_subsystem_new begin");
    androidShadowSubsystem* subsystem;

    subsystem = (androidShadowSubsystem*) calloc(1, sizeof(androidShadowSubsystem));

    if (!subsystem)
	return NULL;

    subsystem->numMonitors = android_shadow_enum_monitors(subsystem->monitors, 16);


    subsystem->SynchronizeEvent = (pfnShadowSynchronizeEvent) android_shadow_input_synchronize_event;
    subsystem->KeyboardEvent = (pfnShadowKeyboardEvent) android_shadow_input_keyboard_event;
    subsystem->UnicodeKeyboardEvent = (pfnShadowUnicodeKeyboardEvent) android_shadow_input_unicode_keyboard_event;
    subsystem->MouseEvent = (pfnShadowMouseEvent) android_shadow_input_mouse_event;
    subsystem->ExtendedMouseEvent = (pfnShadowExtendedMouseEvent) android_shadow_input_extended_mouse_event;

    return subsystem;
}

void android_shadow_subsystem_free(androidShadowSubsystem* subsystem)
{
    if (!subsystem)
	return;

    android_shadow_subsystem_uninit(subsystem);

    free(subsystem);
}

FREERDP_API int Android_ShadowSubsystemEntry(RDP_SHADOW_ENTRY_POINTS* pEntryPoints)
{
    ALOGE("Android_ShadowSubsystemEntry begin");
    pEntryPoints->New = (pfnShadowSubsystemNew) android_shadow_subsystem_new;
    pEntryPoints->Free = (pfnShadowSubsystemFree) android_shadow_subsystem_free;

    pEntryPoints->Init = (pfnShadowSubsystemInit) android_shadow_subsystem_init;
    pEntryPoints->Uninit = (pfnShadowSubsystemInit) android_shadow_subsystem_uninit;

    pEntryPoints->Start = (pfnShadowSubsystemStart) android_shadow_subsystem_start;
    pEntryPoints->Stop = (pfnShadowSubsystemStop) android_shadow_subsystem_stop;

    pEntryPoints->EnumMonitors = (pfnShadowEnumMonitors) android_shadow_enum_monitors;

    return 1;
}
