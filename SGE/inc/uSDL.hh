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
extern "C" int SDL_GetMouseState(int*,int*);
extern "C" int SDL_RenderClear(eK_Renderer*);
extern "C" int SDL_PollEvent(eK_Event*);
extern "C" void SDL_RenderPresent(eK_Renderer*);
extern "C" int SDL_SetTextureAlphaMod(eK_Texture*,uint8_t);
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
	eK_WINDOWEVENT = 0x200,
	eK_KEYDOWN = 0x300,
	eK_KEYUP,
	eK_TEXTEDITING,
	eK_TEXTINPUT,
	eK_MOUSEMOTION = 0x400,
	eK_MOUSEBUTTONDOWN,
	eK_MOUSEBUTTONUP,
	eK_MOUSEWHEEL,
	eK_LASTEVENT = 0xFFFF
} eK_EventType;

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

typedef union eK_Event {
	uint32_t type;
	eK_KeyboardEvent key;
	eK_TextEditingEvent edit;
	eK_TextInputEvent text;
	eK_MouseMotionEvent motion;
	eK_MouseButtonEvent button;
	eK_MouseWheelEvent wheel;
	uint8_t padding[56];
} eK_Event;

typedef enum {
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
