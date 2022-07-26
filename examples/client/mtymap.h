#pragma once

#include "matoya.h"
#include "parsec-dso.h"

static const ParsecKeycode MTY_KEY_TO_PARSEC[] = {
	[0x001] = 41,
	[0x002] = 30,
	[0x003] = 31,
	[0x004] = 32,
	[0x005] = 33,
	[0x006] = 34,
	[0x007] = 35,
	[0x008] = 36,
	[0x009] = 37,
	[0x00A] = 38,
	[0x00B] = 39,
	[0x00C] = 45,
	[0x00D] = 46,
	[0x00E] = 42,
	[0x00F] = 43,
	[0x010] = 20,
	[0x011] = 26,
	[0x012] = 8,
	[0x013] = 21,
	[0x014] = 23,
	[0x015] = 28,
	[0x016] = 24,
	[0x017] = 12,
	[0x018] = 18,
	[0x019] = 19,
	[0x01A] = 47,
	[0x01B] = 48,
	[0x01C] = 40,
	[0x11C] = 88,
	[0x01D] = 224,
	[0x11D] = 228,
	[0x01E] = 4,
	[0x01F] = 22,
	[0x020] = 7,
	[0x021] = 9,
	[0x022] = 10,
	[0x122] = 261,
	[0x023] = 11,
	[0x024] = 13,
	[0x025] = 14,
	[0x026] = 15,
	[0x027] = 51,
	[0x028] = 52,
	[0x029] = 53,
	[0x02A] = 225,
	[0x02B] = 49,
	[0x02C] = 29,
	[0x02D] = 27,
	[0x02E] = 6,
	[0x02F] = 25,
	[0x030] = 5,
	[0x031] = 17,
	[0x032] = 16,
	[0x033] = 54,
	[0x034] = 55,
	[0x035] = 56,
	[0x135] = 84,
	[0x036] = 229,
	[0x037] = 85,
	[0x137] = 70,
	[0x038] = 226,
	[0x138] = 230,
	[0x039] = 44,
	[0x03A] = 57,
	[0x03B] = 58,
	[0x03C] = 59,
	[0x03D] = 60,
	[0x03E] = 61,
	[0x03F] = 62,
	[0x040] = 63,
	[0x041] = 64,
	[0x042] = 65,
	[0x043] = 66,
	[0x044] = 67,
	[0x045] = 83,
	[0x046] = 71,
	[0x146] = 72,
	[0x047] = 95,
	[0x147] = 74,
	[0x048] = 96,
	[0x148] = 82,
	[0x049] = 97,
	[0x149] = 75,
	[0x04A] = 86,
	[0x04B] = 92,
	[0x14B] = 80,
	[0x04C] = 93,
	[0x04D] = 94,
	[0x14D] = 79,
	[0x04E] = 87,
	[0x04F] = 89,
	[0x14F] = 77,
	[0x050] = 90,
	[0x150] = 81,
	[0x051] = 91,
	[0x151] = 78,
	[0x052] = 98,
	[0x152] = 73,
	[0x053] = 99,
	[0x153] = 76,
	[0x056] = 100,
	[0x057] = 68,
	[0x058] = 69,
	[0x15B] = 227,
	[0x15C] = 231,
	[0x15D] = 118,
	[0x064] = 104,
	[0x065] = 105,
	[0x066] = 106,
	[0x067] = 107,
	[0x068] = 108,
	[0x069] = 109,
	[0x06A] = 110,
	[0x16D] = 263,
	[0x070] = 136,
	[0x073] = 135,
	[0x079] = 138,
	[0x07B] = 139,
	[0x07E] = 133,
	[0x07D] = 137,
};

static ParsecKeymod MTY_MOD_TO_PARSEC(MTY_Mod mty)
{
	ParsecKeymod p = 0;

	if (mty & MTY_MOD_LSHIFT) p |= MOD_LSHIFT;
	if (mty & MTY_MOD_RSHIFT) p |= MOD_RSHIFT;
	if (mty & MTY_MOD_LCTRL)  p |= MOD_LCTRL;
	if (mty & MTY_MOD_RCTRL)  p |= MOD_RCTRL;
	if (mty & MTY_MOD_LALT)   p |= MOD_LALT;
	if (mty & MTY_MOD_RALT)   p |= MOD_RALT;
	if (mty & MTY_MOD_LWIN)   p |= MOD_LGUI;
	if (mty & MTY_MOD_RWIN)   p |= MOD_RGUI;
	if (mty & MTY_MOD_CAPS)   p |= MOD_CAPS;
	if (mty & MTY_MOD_NUM)    p |= MOD_NUM;

	return p;
}

static ParsecMouseButton MTY_BUTTON_TO_PARSEC[] = {
	[MTY_BUTTON_LEFT]   = MOUSE_L,
	[MTY_BUTTON_MIDDLE] = MOUSE_MIDDLE,
	[MTY_BUTTON_RIGHT]  = MOUSE_R,
	[MTY_BUTTON_X1]     = MOUSE_X1,
	[MTY_BUTTON_X2]     = MOUSE_X2,
};

static void MTY_EVENT_TO_PARSEC(const MTY_Event *mty, ParsecMessage *p)
{
	switch (mty->type) {
		case MTY_EVENT_MOTION:
			p->type = MESSAGE_MOUSE_MOTION;
			p->mouseMotion.stream = mty->window;
			p->mouseMotion.x = mty->motion.x;
			p->mouseMotion.y = mty->motion.y;
			p->mouseMotion.relative = mty->motion.relative;
			p->mouseMotion.scaleRelative = mty->motion.synth;
			break;
		case MTY_EVENT_BUTTON:
			p->type = MESSAGE_MOUSE_BUTTON;
			p->mouseButton.button = MTY_BUTTON_TO_PARSEC[mty->button.button];
			p->mouseButton.pressed = mty->button.pressed;
			break;
		case MTY_EVENT_KEY:
			p->type = MESSAGE_KEYBOARD;
			p->keyboard.code = MTY_KEY_TO_PARSEC[mty->key.key];
			p->keyboard.mod = MTY_MOD_TO_PARSEC(mty->key.mod);
			p->keyboard.pressed = mty->key.pressed;
			break;
		case MTY_EVENT_SCROLL:
			p->type = MESSAGE_MOUSE_WHEEL;
			p->mouseWheel.x = mty->scroll.x;
			p->mouseWheel.y = mty->scroll.y;
			break;
		case MTY_EVENT_CONTROLLER: {
			const MTY_ControllerEvent *c = &mty->controller;
			ParsecGamepadStateMessage *pc = &p->gamepadState;

			p->type = MESSAGE_GAMEPAD_STATE;

			pc->id = c->id;
			pc->buttons = 0;

			pc->buttons |= c->buttons[MTY_CBUTTON_A] ? GAMEPAD_STATE_A : 0;
			pc->buttons |= c->buttons[MTY_CBUTTON_B] ? GAMEPAD_STATE_B : 0;
			pc->buttons |= c->buttons[MTY_CBUTTON_X] ? GAMEPAD_STATE_X : 0;
			pc->buttons |= c->buttons[MTY_CBUTTON_Y] ? GAMEPAD_STATE_Y : 0;
			pc->buttons |= c->buttons[MTY_CBUTTON_START] ? GAMEPAD_STATE_START : 0;
			pc->buttons |= c->buttons[MTY_CBUTTON_BACK] ? GAMEPAD_STATE_BACK : 0;
			pc->buttons |= c->buttons[MTY_CBUTTON_LEFT_THUMB] ? GAMEPAD_STATE_LEFT_THUMB : 0;
			pc->buttons |= c->buttons[MTY_CBUTTON_RIGHT_THUMB] ? GAMEPAD_STATE_RIGHT_THUMB : 0;
			pc->buttons |= c->buttons[MTY_CBUTTON_LEFT_SHOULDER] ? GAMEPAD_STATE_LEFT_SHOULDER : 0;
			pc->buttons |= c->buttons[MTY_CBUTTON_RIGHT_SHOULDER] ? GAMEPAD_STATE_RIGHT_SHOULDER : 0;
			pc->buttons |= c->buttons[MTY_CBUTTON_GUIDE] ? GAMEPAD_STATE_GUIDE : 0;

			pc->buttons |= MTY_DPAD_UP(c) ? GAMEPAD_STATE_DPAD_UP : 0;
			pc->buttons |= MTY_DPAD_DOWN(c) ? GAMEPAD_STATE_DPAD_DOWN : 0;
			pc->buttons |= MTY_DPAD_LEFT(c) ? GAMEPAD_STATE_DPAD_LEFT : 0;
			pc->buttons |= MTY_DPAD_RIGHT(c) ? GAMEPAD_STATE_DPAD_RIGHT : 0;

			pc->thumbLX = c->axes[MTY_CAXIS_THUMB_LX].value;
			pc->thumbLY = c->axes[MTY_CAXIS_THUMB_LY].value;
			pc->thumbRX = c->axes[MTY_CAXIS_THUMB_RX].value;
			pc->thumbRY = c->axes[MTY_CAXIS_THUMB_RY].value;
			pc->leftTrigger = (uint8_t) c->axes[MTY_CAXIS_TRIGGER_L].value;
			pc->rightTrigger = (uint8_t) c->axes[MTY_CAXIS_TRIGGER_R].value;
			break;
		}
		case MTY_EVENT_DISCONNECT:
			p->type = MESSAGE_GAMEPAD_UNPLUG;
			p->gamepadUnplug.id = mty->controller.id;
			break;
		default:
			break;
	}
}
