/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2014 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
	 claim that you wrote the original software. If you use this software
	 in a product, an acknowledgment in the product documentation would be
	 appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
	 misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

union eK_Event;
typedef int eK_RendererFlip;
typedef void* eK_Texture;
typedef void* eK_Surface;
typedef void* eK_Renderer;
typedef void* eK_Point;
typedef void* eK_Window;
typedef union eK_Event eK_Event;
typedef int eK_Scancode;
typedef uint32_t eK_Keycode;
typedef int64_t eK_GestureID;
typedef int64_t eK_TouchID;
typedef int64_t eK_FingerID;
typedef int32_t eK_JoystickID;

#define eK_INIT_EVERYTHING  0x00000030
#define eK_WINDOW_MAXIMIZED 0x00000080
#define eK_WINDOW_SHOWN 0x00000004
#define eK_WINDOW_BORDERLESS 0x00000010
#define eK_WINDOWPOS_CENTERED 0x2FFF0000
#define eK_RENDERER_ACCELERATED 0x00000002
#define eK_RENDERER_PRESENTVSYNC 0x00000004
#define eK_BUTTON_LEFT		1
#define eK_BUTTON_MIDDLE	2
#define eK_BUTTON_RIGHT	3
#define eK_BUTTON_WHEELUP	4
#define eK_BUTTON_WHEELDOWN	5

typedef struct {
	int x, y;
	int w, h;
} eK_Rect;

extern "C" int SDL_Init(int32_t);
extern "C" void SDL_Quit(void);
extern "C" int TTF_Init();
extern "C" int TTF_WasInit();
extern "C" void TTF_Quit();

extern "C" eK_Surface *IMG_Load(const char *);
extern "C" void SDL_FreeSurface(eK_Surface*);

extern "C" eK_Texture *SDL_CreateTextureFromSurface(eK_Renderer*,eK_Surface*);
extern "C" int SDL_QueryTexture(eK_Texture*, void*, void*, int*, int*);
extern "C" void SDL_DestroyTexture(eK_Texture*);

extern "C" int SDL_RenderCopyEx(eK_Renderer*, eK_Texture*, const eK_Rect*, const eK_Rect*, const double, void*, const eK_RendererFlip);

extern "C" eK_Window* SDL_CreateWindow(const char*, int, int, int, int, uint32_t);
extern "C" void SDL_DestroyWindow(eK_Window*);
extern "C" eK_Renderer* SDL_CreateRenderer(eK_Window*, int, uint32_t);
extern "C" void SDL_DestroyRenderer(eK_Renderer*);
extern "C" void SDL_GetWindowSize(eK_Window*, int*, int*);

extern "C" int SDL_RenderClear(eK_Renderer*);
extern "C" int SDL_PollEvent(eK_Event*);
extern "C" void SDL_RenderPresent(eK_Renderer*);
extern "C" int SDL_SetRenderDrawColor(eK_Renderer*,uint8_t,uint8_t,uint8_t,uint8_t);

typedef struct eK_Keysym {
	eK_Scancode scancode;
	eK_Keycode sym;
	uint16_t mod;
	uint32_t unused;
} eK_Keysym;

#define eK_RELEASED 0
#define eK_PRESSED 1
typedef enum {
	eK_FIRSTEVENT = 0,
	eK_QUIT = 0x100,
	eK_APP_TERMINATING,
	eK_APP_LOWMEMORY,
	eK_APP_WILLENTERBACKGROUND,
	eK_APP_DIDENTERBACKGROUND,
	eK_APP_WILLENTERFOREGROUND,
	eK_APP_DIDENTERFOREGROUND,
	eK_WINDOWEVENT = 0x200,
	eK_SYSWMEVENT,
	eK_KEYDOWN = 0x300,
	eK_KEYUP,
	eK_TEXTEDITING,
	eK_TEXTINPUT,
	eK_MOUSEMOTION = 0x400,
	eK_MOUSEBUTTONDOWN,
	eK_MOUSEBUTTONUP,
	eK_MOUSEWHEEL,
	eK_JOYAXISMOTION = 0x600,
	eK_JOYBALLMOTION,
	eK_JOYHATMOTION,
	eK_JOYBUTTONDOWN,
	eK_JOYBUTTONUP,
	eK_JOYDEVICEADDED,
	eK_JOYDEVICEREMOVED,
	eK_CONTROLLERAXISMOTION = 0x650,
	eK_CONTROLLERBUTTONDOWN,
	eK_CONTROLLERBUTTONUP,
	eK_CONTROLLERDEVICEADDED,
	eK_CONTROLLERDEVICEREMOVED,
	eK_CONTROLLERDEVICEREMAPPED,
	eK_FINGERDOWN = 0x700,
	eK_FINGERUP,
	eK_FINGERMOTION,
	eK_DOLLARGESTURE = 0x800,
	eK_DOLLARRECORD,
	eK_MULTIGESTURE,
	eK_CLIPBOARDUPDATE = 0x900,
	eK_DROPFILE = 0x1000,
	eK_RENDER_TARGETS_RESET = 0x2000,
	eK_USEREVENT = 0x8000,
	eK_LASTEVENT = 0xFFFF
} eK_EventType;

typedef struct eK_CommonEvent {
	uint32_t type;
	uint32_t timestamp;
} eK_CommonEvent;

typedef struct eK_WindowEvent {
	uint32_t type;
	uint32_t timestamp;
	uint32_t windowID;
	uint8_t event;
	uint8_t padding1;
	uint8_t padding2;
	uint8_t padding3;
	int32_t data1;
	int32_t data2;
} eK_WindowEvent;

typedef struct eK_KeyboardEvent {
	uint32_t type;
	uint32_t timestamp;
	uint32_t windowID;
	uint8_t state;
	uint8_t repeat;
	uint8_t padding2;
	uint8_t padding3;
	eK_Keysym keysym;
} eK_KeyboardEvent;

#define eK_TEXTEDITINGEVENT_TEXT_SIZE (32)
typedef struct eK_TextEditingEvent {
	uint32_t type;
	uint32_t timestamp;
	uint32_t windowID;
	char text[eK_TEXTEDITINGEVENT_TEXT_SIZE];
	int32_t start;
	int32_t length;
} eK_TextEditingEvent;

#define eK_TEXTINPUTEVENT_TEXT_SIZE (32)
typedef struct eK_TextInputEvent {
	uint32_t type;
	uint32_t timestamp;
	uint32_t windowID;
	char text[eK_TEXTINPUTEVENT_TEXT_SIZE];
} eK_TextInputEvent;

typedef struct eK_MouseMotionEvent {
	uint32_t type;
	uint32_t timestamp;
	uint32_t windowID;
	uint32_t which;
	uint32_t state;
	int32_t x;
	int32_t y;
	int32_t xrel;
	int32_t yrel;
} eK_MouseMotionEvent;

typedef struct eK_MouseButtonEvent {
	uint32_t type;
	uint32_t timestamp;
	uint32_t windowID;
	uint32_t which;
	uint8_t button;
	uint8_t state;
	uint8_t clicks;
	uint8_t padding1;
	int32_t x;
	int32_t y;
} eK_MouseButtonEvent;

typedef struct eK_MouseWheelEvent {
	uint32_t type;
	uint32_t timestamp;
	uint32_t windowID;
	uint32_t which;
	int32_t x;
	int32_t y;
} eK_MouseWheelEvent;

typedef struct eK_JoyAxisEvent {
	uint32_t type;
	uint32_t timestamp;
	eK_JoystickID which;
	uint8_t axis;
	uint8_t padding1;
	uint8_t padding2;
	uint8_t padding3;
	int16_t value;
	uint16_t padding4;
} eK_JoyAxisEvent;

typedef struct eK_JoyBallEvent {
	uint32_t type;
	uint32_t timestamp;
	eK_JoystickID which;
	uint8_t ball;
	uint8_t padding1;
	uint8_t padding2;
	uint8_t padding3;
	int16_t xrel;
	int16_t yrel;
} eK_JoyBallEvent;

typedef struct eK_JoyHatEvent {
	uint32_t type;
	uint32_t timestamp;
	eK_JoystickID which;
	uint8_t hat;
	uint8_t value;
	uint8_t padding1;
	uint8_t padding2;
} eK_JoyHatEvent;

typedef struct eK_JoyButtonEvent {
	uint32_t type;
	uint32_t timestamp;
	eK_JoystickID which;
	uint8_t button;
	uint8_t state;
	uint8_t padding1;
	uint8_t padding2;
} eK_JoyButtonEvent;

typedef struct eK_JoyDeviceEvent {
	uint32_t type;
	uint32_t timestamp;
	int32_t which;
} eK_JoyDeviceEvent;

typedef struct eK_ControllerAxisEvent {
	uint32_t type;
	uint32_t timestamp;
	eK_JoystickID which;
	uint8_t axis;
	uint8_t padding1;
	uint8_t padding2;
	uint8_t padding3;
	int16_t value;
	uint16_t padding4;
} eK_ControllerAxisEvent;

typedef struct eK_ControllerButtonEvent {
	uint32_t type;
	uint32_t timestamp;
	eK_JoystickID which;
	uint8_t button;
	uint8_t state;
	uint8_t padding1;
	uint8_t padding2;
} eK_ControllerButtonEvent;

typedef struct eK_ControllerDeviceEvent {
	uint32_t type;
	uint32_t timestamp;
	int32_t which;
} eK_ControllerDeviceEvent;

typedef struct eK_TouchFingerEvent {
	uint32_t type;
	uint32_t timestamp;
	eK_TouchID touchId;
	eK_FingerID fingerId;
	float x;
	float y;
	float dx;
	float dy;
	float pressure;
} eK_TouchFingerEvent;

typedef struct eK_MultiGestureEvent {
	uint32_t type;
	uint32_t timestamp;
	eK_TouchID touchId;
	float dTheta;
	float dDist;
	float x;
	float y;
	uint16_t numFingers;
	uint16_t padding;
} eK_MultiGestureEvent;

typedef struct eK_DollarGestureEvent {
	uint32_t type;
	uint32_t timestamp;
	eK_TouchID touchId;
	eK_GestureID gestureId;
	uint32_t numFingers;
	float error;
	float x;
	float y;
} eK_DollarGestureEvent;

typedef struct eK_DropEvent {
	uint32_t type;
	uint32_t timestamp;
	char *file;
} eK_DropEvent;

typedef struct eK_QuitEvent {
	uint32_t type;
	uint32_t timestamp;
} eK_QuitEvent;

typedef struct eK_OSEvent {
	uint32_t type;
	uint32_t timestamp;
} eK_OSEvent;

typedef struct eK_UserEvent {
	uint32_t type;
	uint32_t timestamp;
	uint32_t windowID;
	int32_t code;
	void *data1;
	void *data2;
} eK_UserEvent;
struct eK_SysWMmsg;
typedef struct eK_SysWMmsg eK_SysWMmsg;

typedef struct eK_SysWMEvent {
	uint32_t type;
	uint32_t timestamp;
	eK_SysWMmsg *msg;
} eK_SysWMEvent;

typedef union eK_Event {
	uint32_t type;
	eK_CommonEvent common;
	eK_WindowEvent window;
	eK_KeyboardEvent key;
	eK_TextEditingEvent edit;
	eK_TextInputEvent text;
	eK_MouseMotionEvent motion;
	eK_MouseButtonEvent button;
	eK_MouseWheelEvent wheel;
	eK_JoyAxisEvent jaxis;
	eK_JoyBallEvent jball;
	eK_JoyHatEvent jhat;
	eK_JoyButtonEvent jbutton;
	eK_JoyDeviceEvent jdevice;
	eK_ControllerAxisEvent caxis;
	eK_ControllerButtonEvent cbutton;
	eK_ControllerDeviceEvent cdevice;
	eK_QuitEvent quit;
	eK_UserEvent user;
	eK_SysWMEvent syswm;
	eK_TouchFingerEvent tfinger;
	eK_MultiGestureEvent mgesture;
	eK_DollarGestureEvent dgesture;
	eK_DropEvent drop;
	uint8_t padding[56];
} eK_Event;

typedef enum
{
	KMOD_NONE = 0x0000,
	KMOD_LSHIFT = 0x0001,
	KMOD_RSHIFT = 0x0002,
	KMOD_LCTRL = 0x0040,
	KMOD_RCTRL = 0x0080,
	KMOD_LALT = 0x0100,
	KMOD_RALT = 0x0200,
	KMOD_LGUI = 0x0400,
	KMOD_RGUI = 0x0800,
	KMOD_NUM = 0x1000,
	KMOD_CAPS = 0x2000,
	KMOD_MODE = 0x4000,
	KMOD_RESERVED = 0x8000
} SDL_Keymod;

#define KMOD_CTRL	(KMOD_LCTRL|KMOD_RCTRL)
#define KMOD_SHIFT	(KMOD_LSHIFT|KMOD_RSHIFT)
#define KMOD_ALT	(KMOD_LALT|KMOD_RALT)
#define KMOD_GUI	(KMOD_LGUI|KMOD_RGUI)