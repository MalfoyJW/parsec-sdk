/// @file
#pragma once

#include <stdint.h>
#include <stdbool.h>

#if defined(__CC_EXPORT__)
	#if defined(_WIN32)
		#define EXPORT __declspec(dllexport)
	#else
		#define EXPORT __attribute__((visibility("default")))
	#endif
#else
	#define EXPORT
#endif

#if defined(_WIN32)
	#pragma warning(disable: 4201)
#endif


/*** DEFINITIONS ***/

#define GUEST_NAME_LEN   320 ///< (320) Maximum length of a guest's name. Used in ::ParsecGuest.
#define ATTEMPT_ID_LEN   56  ///< (56) Length in bytes of an Attempt ID. Used in ::ParsecGuest and ::ParsecClientStatus.
#define HOST_NAME_LEN    256 ///< (256) Maximum length  of a host's name. Used in ::ParsecHostConfig.
#define HOST_DESC_LEN    512 ///< (512) Maximum length of a game's description. Used in ::ParsecHostConfig.
#define GAME_ID_LEN      72  ///< (72) Maximum length of a Game ID. Used in ::ParsecHostConfig.

#define PARSEC_VER_MAJOR 1   ///< (1) Parsec SDK breaking API/ABI change.
#define PARSEC_VER_MINOR 0   ///< (0) Parsec SDK internal implementation detail.

/// @brief 32-bit concatenated major/minor version.
#define PARSEC_VER \
	((uint32_t) (((uint16_t) PARSEC_VER_MAJOR << 16u) | ((uint16_t) PARSEC_VER_MINOR)))

/// @brief Default ::Parsec instance confgiuration passed to ::ParsecInit.
#define PARSEC_DEFAULTS {   \
	/*upnp       */ 1,      \
	/*clientPort */ 0,      \
	/*hostPort   */ 0,      \
}

/// @brief Default host configuration passed to ::ParsecHostStart and ::ParsecHostSetConfig.
#define PARSEC_HOST_DEFAULTS {     \
	/*resolutionX       */  0,     \
	/*resolutionY       */  0,     \
	/*refreshRate       */  60,    \
	/*adminMute         */  1,     \
	/*exclusiveInput    */  1,     \
	/*encoderFPS        */  0,     \
	/*encoderMaxBitrate */  10,    \
	/*encoderH265       */  0,     \
	/*maxGuests         */  20,    \
	/*name              */  "",    \
	/*desc              */  "",    \
	/*gameID            */  "",    \
	/*publicGame        */  false, \
}

/// @brief Default client configuration passed to ::ParsecClientConnect.
#define PARSEC_CLIENT_DEFAULTS {           \
	/*decoderSoftware */ 0,                \
	/*mediaContainer  */ CONTAINER_PARSEC, \
	/*protocol        */ PROTO_MODE_BUD,   \
	/*resolutionX     */ 0,                \
	/*resolutionY     */ 0,                \
	/*refreshRate     */ 60,               \
	/*pngCursor       */ false,            \
}


/*** ENUMERATIONS ***/

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Status codes indicating success, warning, or error.
/// @details Returned by most Parsec SDK functions. ::PARSEC_OK is `0`,
///     warnings are positive, errors are negative.
typedef enum ParsecStatus {
	PARSEC_OK                 = 0,       ///< 0

	WRN_CONTINUE              = 10,      ///< 10

	HOST_WRN_SHUTDOWN         = 4,       ///< 4
	HOST_WRN_KICKED           = 5,       ///< 5

	CONNECT_WRN_APPROVAL      = 6,       ///< 6
	CONNECT_WRN_DECLINED      = 8,       ///< 8
	CONNECT_WRN_CANCELED      = 9,       ///< 9
	CONNECT_WRN_PEER_GONE     = 99,      ///< 99

	DECODE_WRN_CONTINUE       = 1000,    ///< 1000
	DECODE_WRN_ACCEPTED       = 1001,    ///< 1001
	DECODE_WRN_REINIT         = 1003,    ///< 1003

	NETWORK_WRN_TIMEOUT       = 2000,    ///< 2000

	QUEUE_WRN_EMPTY           = 5000,    ///< 5000
	QUEUE_WRN_NO_BUFFER       = 5001,    ///< 5001
	QUEUE_WRN_TIMEOUT         = 5003,    ///< 5003

	AUDIO_WRN_NO_DATA         = 6000,    ///< 6000

	ERR_DEFAULT               = -1,      ///< -1

	PARSEC_NOT_RUNNING        = -3,      ///< -3
	PARSEC_ALREADY_RUNNING    = -4,      ///< -4
	PARSEC_NOT_IMPLEMENTED    = -5,      ///< -5

	DECODE_ERR_INIT           = -10,     ///< -10
	DECODE_ERR_LOAD           = -11,     ///< -11
	DECODE_ERR_MAP            = -13,     ///< -13
	DECODE_ERR_DECODE         = -14,     ///< -14
	DECODE_ERR_CLEANUP        = -15,     ///< -15
	DECODE_ERR_PARSE          = -16,     ///< -16
	DECODE_ERR_NO_SUPPORT     = -17,     ///< -17
	DECODE_ERR_PIXEL_FORMAT   = -18,     ///< -18
	DECODE_ERR_BUFFER         = -19,     ///< -19
	DECODE_ERR_RESOLUTION     = -20,     ///< -20

	WS_ERR_CONNECT            = -6101,   ///< -6101
	WS_ERR_POLL               = -3001,   ///< -3001
	WS_ERR_READ               = -3002,   ///< -3002
	WS_ERR_WRITE              = -3003,   ///< -3003
	WS_ERR_CLOSE              = -6105,   ///< -6105
	WS_ERR_PING               = -3005,   ///< -3005
	WS_ERR_PONG_TIMEOUT       = -3006,   ///< -3006
	WS_ERR_PONG               = -3007,   ///< -3007
	WS_ERR_AUTH               = -3008,   ///< -3008
	WS_ERR_GOING_AWAY         = -3009,   ///< -3009

	ZLIB_ERR_DEFLATE          = -5000,   ///< -5000
	ZLIB_ERR_INFLATE          = -5001,   ///< -5001

	NAT_ERR_PEER_PHASE        = -6023,   ///< -6023
	NAT_ERR_STUN_PHASE        = -6024,   ///< -6024
	NAT_ERR_NO_CANDIDATES     = -6033,   ///< -6033
	NAT_ERR_JSON_ACTION       = -6111,   ///< -6111
	NAT_ERR_NO_SOCKET         = -6112,   ///< -6112

	OPENGL_ERR_CONTEXT        = -7000,   ///< -7000
	OPENGL_ERR_SHARE          = -7001,   ///< -7001
	OPENGL_ERR_PIXFORMAT      = -7002,   ///< -7002
	OPENGL_ERR_CURRENT        = -7003,   ///< -7003
	OPENGL_ERR_DC             = -7004,   ///< -7004
	OPENGL_ERR_SHADER         = -7005,   ///< -7005
	OPENGL_ERR_PROGRAM        = -7006,   ///< -7006
	OPENGL_ERR_VERSION        = -7007,   ///< -7007
	OPENGL_ERR_TEXTURE        = -7008,   ///< -7008

	JSON_ERR_PARSE            = -8000,   ///< -8000
	JSON_ERR_MISSING          = -8001,   ///< -8001
	JSON_ERR_TYPE             = -8002,   ///< -8002
	JSON_ERR_VAL_TYPE         = -8003,   ///< -8003
	JSON_ERR_BUFFER           = -8004,   ///< -8004
	JSON_ERR_FOPEN            = -8005,   ///< -8005
	JSON_ERR_FREAD            = -8006,   ///< -8006
	JSON_ERR_FWRITE           = -8007,   ///< -8007

	AUDIO_ERR_INIT            = -9000,   ///< -9000
	AUDIO_ERR_CAPTURE         = -9001,   ///< -9001
	AUDIO_ERR_NETWORK         = -9002,   ///< -9002
	AUDIO_ERR_FREE            = -9003,   ///< -9003
	AUDIO_ERR_PLAY            = -9004,   ///< -9004

	AUDIO_OPUS_ERR_INIT       = -10000,  ///< -10000
	AUDIO_OPUS_ERR_DECODE     = -10001,  ///< -10001
	AUDIO_OPUS_ERR_ENCODE     = -10002,  ///< -10002

	NETWORK_ERR_BG_TIMEOUT    = -12007,  ///< -12007
	NETWORK_ERR_BAD_PACKET    = -12008,  ///< -12008
	NETWORK_ERR_BUFFER        = -12011,  ///< -12011
	NETWORK_ERR_SHUTDOWN      = -12017,  ///< -12017
	NETWORK_ERR_UNSUPPORTED   = -12018,  ///< -12018
	NETWORK_ERR_INTERRUPTED   = -12019,  ///< -12019

	SERVER_ERR_DISPLAY        = -13000,  ///< -13000
	SERVER_ERR_RESOLUTION     = -13008,  ///< -13008
	SERVER_ERR_MAX_RESOLUTION = -13009,  ///< -13009
	SERVER_ERR_NO_USER        = -13011,  ///< -13011
	SERVER_ERR_NO_ROOM        = -13012,  ///< -13012
	SERVER_ERR_VIDEO_DONE     = -13013,  ///< -13013
	SERVER_ERR_CLIENT_ABORT   = -13014,  ///< -13014
	SERVER_ERR_CLIENT_GONE    = -13015,  ///< -13015

	CAPTURE_ERR_INIT          = -14003,  ///< -14003
	CAPTURE_ERR_TEXTURE       = -14004,  ///< -14004

	ENCODE_ERR_INIT           = -15000,  ///< -15000
	ENCODE_ERR_ENCODE         = -15002,  ///< -15002
	ENCODE_ERR_BUFFER         = -15006,  ///< -15006
	ENCODE_ERR_PROPERTIES     = -15100,  ///< -15100
	ENCODE_ERR_LIBRARY        = -15101,  ///< -15101
	ENCODE_ERR_SESSION        = -15007,  ///< -15007
	ENCODE_ERR_SESSION1       = -15103,  ///< -15103
	ENCODE_ERR_SESSION2       = -15104,  ///< -15104
	ENCODE_ERR_OUTPUT_INIT    = -15105,  ///< -15105
	ENCODE_ERR_TEXTURE        = -15106,  ///< -15106
	ENCODE_ERR_OUTPUT         = -15107,  ///< -15107
	ENCODE_ERR_UNSUPPORTED    = -15108,  ///< -15108
	ENCODE_ERR_HANDLE         = -15109,  ///< -15109
	ENCODE_ERR_CAPS           = -15110,  ///< -15110

	UPNP_ERR                  = -19000,  ///< -19000

	D3D_ERR_TEXTURE           = -22000,  ///< -22000
	D3D_ERR_SHADER            = -22001,  ///< -22001
	D3D_ERR_BUFFER            = -22002,  ///< -22002
	D3D_ERR_LAYOUT            = -22003,  ///< -22003
	D3D_ERR_DEVICE            = -22004,  ///< -22004
	D3D_ERR_MT                = -22005,  ///< -22005
	D3D_ERR_ADAPTER           = -22006,  ///< -22006
	D3D_ERR_FACTORY           = -22007,  ///< -22007
	D3D_ERR_OUTPUT            = -22008,  ///< -22008
	D3D_ERR_CONTEXT           = -22009,  ///< -22009
	D3D_ERR_OUTPUT1           = -22010,  ///< -22010
	D3D_ERR_SWAP_CHAIN        = -22011,  ///< -22011
	D3D_ERR_DRAW              = -22012,  ///< -22012
	D3D_ERR_OUTPUT5           = -22013,  ///< -22013

	H26X_ERR_NOT_FOUND        = -23000,  ///< -23000

	AES_GCM_ERR_KEY_LEN       = -28000,  ///< -28000
	AES_GCM_ERR_ENCRYPT       = -28001,  ///< -28001
	AES_GCM_ERR_DECRYPT       = -28002,  ///< -28002
	AES_GCM_ERR_CTX           = -28003,  ///< -28003
	AES_GCM_ERR_BUFFER        = -28004,  ///< -28004
	AES_GCM_ERR_OVERFLOW      = -28005,  ///< -28005

	SCTP_ERR_GLOBAL_INIT      = -32000,  ///< -32000
	SCTP_ERR_WRITE            = -32001,  ///< -32001
	SCTP_ERR_SOCKET           = -32002,  ///< -32002
	SCTP_ERR_BIND             = -32003,  ///< -32003
	SCTP_ERR_CONNECT          = -32004,  ///< -32004

	DTLS_ERR_BIO_WRITE        = -33000,  ///< -33000
	DTLS_ERR_BIO_READ         = -33001,  ///< -33001
	DTLS_ERR_SSL              = -33002,  ///< -33002
	DTLS_ERR_BUFFER           = -33003,  ///< -33003
	DTLS_ERR_NO_DATA          = -33004,  ///< -33004
	DTLS_ERR_CERT             = -33005,  ///< -33005

	STUN_ERR_PACKET           = -34000,  ///< -34000
	STUN_ERR_PARSE_HEADER     = -34001,  ///< -34001
	STUN_ERR_PARSE_ADDRESS    = -34002,  ///< -34002

	SO_ERR_OPEN               = -35000,  ///< -35000
	SO_ERR_SYMBOL             = -35001,  ///< -35001

	PARSEC_ERR_VERSION        = -36000,  ///< -36000
	PARSEC_ERR_VER_DATA       = -36001,  ///< -36001

	RESAMPLE_ERR_INIT         = -37000,  ///< -37000
	RESAMPLE_ERR_RESAMPLE     = -37001,  ///< -37001

	UNITY_UNSUPPORTED_ENGINE  = -38000,  ///< Caused when the graphics render engine isn't supported in Unity.

	OPENSSL_ERR               = -600000, ///< `SSL_get_error` value will be subtracted from this value.

	#if defined(_WIN32)
	SOCKET_ERR                = -700000, ///< `WSAGetLastError` value will be subtracted from this value.
	#else
	SOCKET_ERR                = -800000, ///< `errno` value will be subtracted from this value.
	#endif

	__ERR_MAKE_32             = 0x7FFFFFFF,
} ParsecStatus;

/// @brief Log level.
/// @details Passed through ::ParsecLogCallback set with ::ParsecSetLogCallback.
typedef enum ParsecLogLevel {
	LOG_INFO      = 0x0069, ///< Messages interesting to support staff trying to figure out the context of an issue.
	LOG_DEBUG     = 0x0064, ///< Messages interesting to developers trying to debug an issue.
	__LOG_MAKE_32 = 0x7FFFFFFF,
} ParsecLogLevel;

/// @brief Keyboard input.
/// @details Member of ::ParsecKeyboardMessage.
typedef enum ParsecKeycode {
	KEY_A           = 4,   ///< 4
	KEY_B           = 5,   ///< 5
	KEY_C           = 6,   ///< 6
	KEY_D           = 7,   ///< 7
	KEY_E           = 8,   ///< 8
	KEY_F           = 9,   ///< 9
	KEY_G           = 10,  ///< 10
	KEY_H           = 11,  ///< 11
	KEY_I           = 12,  ///< 12
	KEY_J           = 13,  ///< 13
	KEY_K           = 14,  ///< 14
	KEY_L           = 15,  ///< 15
	KEY_M           = 16,  ///< 16
	KEY_N           = 17,  ///< 17
	KEY_O           = 18,  ///< 18
	KEY_P           = 19,  ///< 19
	KEY_Q           = 20,  ///< 20
	KEY_R           = 21,  ///< 21
	KEY_S           = 22,  ///< 22
	KEY_T           = 23,  ///< 23
	KEY_U           = 24,  ///< 24
	KEY_V           = 25,  ///< 25
	KEY_W           = 26,  ///< 26
	KEY_X           = 27,  ///< 27
	KEY_Y           = 28,  ///< 28
	KEY_Z           = 29,  ///< 29
	KEY_1           = 30,  ///< 30
	KEY_2           = 31,  ///< 31
	KEY_3           = 32,  ///< 32
	KEY_4           = 33,  ///< 33
	KEY_5           = 34,  ///< 34
	KEY_6           = 35,  ///< 35
	KEY_7           = 36,  ///< 36
	KEY_8           = 37,  ///< 37
	KEY_9           = 38,  ///< 38
	KEY_0           = 39,  ///< 39
	KEY_ENTER       = 40,  ///< 40
	KEY_ESCAPE      = 41,  ///< 41
	KEY_BACKSPACE   = 42,  ///< 42
	KEY_TAB         = 43,  ///< 43
	KEY_SPACE       = 44,  ///< 44
	KEY_MINUS       = 45,  ///< 45
	KEY_EQUALS      = 46,  ///< 46
	KEY_LBRACKET    = 47,  ///< 47
	KEY_RBRACKET    = 48,  ///< 48
	KEY_BACKSLASH   = 49,  ///< 49
	KEY_SEMICOLON   = 51,  ///< 51
	KEY_APOSTROPHE  = 52,  ///< 52
	KEY_BACKTICK    = 53,  ///< 53
	KEY_COMMA       = 54,  ///< 54
	KEY_PERIOD      = 55,  ///< 55
	KEY_SLASH       = 56,  ///< 56
	KEY_CAPSLOCK    = 57,  ///< 57
	KEY_F1          = 58,  ///< 58
	KEY_F2          = 59,  ///< 59
	KEY_F3          = 60,  ///< 60
	KEY_F4          = 61,  ///< 61
	KEY_F5          = 62,  ///< 62
	KEY_F6          = 63,  ///< 63
	KEY_F7          = 64,  ///< 64
	KEY_F8          = 65,  ///< 65
	KEY_F9          = 66,  ///< 66
	KEY_F10         = 67,  ///< 67
	KEY_F11         = 68,  ///< 68
	KEY_F12         = 69,  ///< 69
	KEY_PRINTSCREEN = 70,  ///< 70
	KEY_SCROLLLOCK  = 71,  ///< 71
	KEY_PAUSE       = 72,  ///< 72
	KEY_INSERT      = 73,  ///< 73
	KEY_HOME        = 74,  ///< 74
	KEY_PAGEUP      = 75,  ///< 75
	KEY_DELETE      = 76,  ///< 76
	KEY_END         = 77,  ///< 77
	KEY_PAGEDOWN    = 78,  ///< 78
	KEY_RIGHT       = 79,  ///< 79
	KEY_LEFT        = 80,  ///< 80
	KEY_DOWN        = 81,  ///< 81
	KEY_UP          = 82,  ///< 82
	KEY_NUMLOCK     = 83,  ///< 83
	KEY_KP_DIVIDE   = 84,  ///< 84
	KEY_KP_MULTIPLY = 85,  ///< 85
	KEY_KP_MINUS    = 86,  ///< 86
	KEY_KP_PLUS     = 87,  ///< 87
	KEY_KP_ENTER    = 88,  ///< 88
	KEY_KP_1        = 89,  ///< 89
	KEY_KP_2        = 90,  ///< 90
	KEY_KP_3        = 91,  ///< 91
	KEY_KP_4        = 92,  ///< 92
	KEY_KP_5        = 93,  ///< 93
	KEY_KP_6        = 94,  ///< 94
	KEY_KP_7        = 95,  ///< 95
	KEY_KP_8        = 96,  ///< 96
	KEY_KP_9        = 97,  ///< 97
	KEY_KP_0        = 98,  ///< 98
	KEY_KP_PERIOD   = 99,  ///< 99
	KEY_APPLICATION = 101, ///< 101
	KEY_F13         = 104, ///< 104
	KEY_F14         = 105, ///< 105
	KEY_F15         = 106, ///< 106
	KEY_F16         = 107, ///< 107
	KEY_F17         = 108, ///< 108
	KEY_F18         = 109, ///< 109
	KEY_F19         = 110, ///< 110
	KEY_MENU        = 118, ///< 118
	KEY_MUTE        = 127, ///< 127
	KEY_VOLUMEUP    = 128, ///< 128
	KEY_VOLUMEDOWN  = 129, ///< 129
	KEY_LCTRL       = 224, ///< 224
	KEY_LSHIFT      = 225, ///< 225
	KEY_LALT        = 226, ///< 226
	KEY_LGUI        = 227, ///< 227
	KEY_RCTRL       = 228, ///< 228
	KEY_RSHIFT      = 229, ///< 229
	KEY_RALT        = 230, ///< 230
	KEY_RGUI        = 231, ///< 231
	KEY_AUDIONEXT   = 258, ///< 258
	KEY_AUDIOPREV   = 259, ///< 259
	KEY_AUDIOSTOP   = 260, ///< 260
	KEY_AUDIOPLAY   = 261, ///< 261
	KEY_AUDIOMUTE   = 262, ///< 262
	KEY_MEDIASELECT = 263, ///< 263
	__KEY_MAKE_32   = 0x7FFFFFFF,
} ParsecKeycode;

/// @brief Stateful modifier keys applied to keyboard input.
/// @details Member of ::ParsecKeyboardMessage. These values may be bitwise OR'd together.
typedef enum ParsecKeymod {
	MOD_NONE      = 0x0000, ///< No stateful modifier key active.
	MOD_NUM       = 0x1000, ///< `NUMLOCK` is currently active.
	MOD_CAPS      = 0x2000, ///< `CAPSLOCK` is currently active.
	__MOD_MAKE_32 = 0x7FFFFFFF,
} ParsecKeymod;

/// @brief Mouse button.
/// @details Member of ::ParsecMouseButtonMessage.
typedef enum ParsecMouseButton {
	MOUSE_L         = 1, ///< Left mouse button.
	MOUSE_MIDDLE    = 2, ///< Middle mouse button.
	MOUSE_R         = 3, ///< Right mouse button.
	MOUSE_X1        = 4, ///< Extra mouse button 1.
	MOUSE_X2        = 5, ///< Extra mouse button 2.
	__MOUSE_MAKE_32 = 0x7FFFFFFF,
} ParsecMouseButton;

/// @brief Gamepad button.
/// @details Member of ::ParsecGamepadButtonMessage.
typedef enum ParsecGamepadButton {
	GAMEPAD_BUTTON_A          = 0,  ///< A button.
	GAMEPAD_BUTTON_B          = 1,  ///< B button.
	GAMEPAD_BUTTON_X          = 2,  ///< X button.
	GAMEPAD_BUTTON_Y          = 3,  ///< Y button.
	GAMEPAD_BUTTON_BACK       = 4,  ///< Back button.
	GAMEPAD_BUTTON_GUIDE      = 5,  ///< Guide button.
	GAMEPAD_BUTTON_START      = 6,  ///< Start button.
	GAMEPAD_BUTTON_LSTICK     = 7,  ///< Left thumbstick button.
	GAMEPAD_BUTTON_RSTICK     = 8,  ///< Right thumbstick button.
	GAMEPAD_BUTTON_LSHOULDER  = 9,  ///< Left shoulder (bumper) button.
	GAMEPAD_BUTTON_RSHOULDER  = 10, ///< Right shoulder (bumper) button.
	GAMEPAD_BUTTON_DPAD_UP    = 11, ///< Analog DPAD up.
	GAMEPAD_BUTTON_DPAD_DOWN  = 12, ///< Analog DPAD down.
	GAMEPAD_BUTTON_DPAD_LEFT  = 13, ///< Analog DPAD left.
	GAMEPAD_BUTTON_DPAD_RIGHT = 14, ///< Analog DPAD right.
	__GAMEPAD_BUTTON_MAKE_32  = 0x7FFFFFFF,
} ParsecGamepadButton;

/// @brief Gamepad axes related to thumbsticks and triggers.
/// @details Member of ::ParsecGamepadAxisMessage.
typedef enum ParsecGamepadAxis {
	GAMEPAD_AXIS_LX        = 0, ///< Gamepad left thumbstick x-axis.
	GAMEPAD_AXIS_LY        = 1, ///< Gamepad left thumbstick y-axis.
	GAMEPAD_AXIS_RX        = 2, ///< Gamepad right thumbstick x-axis.
	GAMEPAD_AXIS_RY        = 3, ///< Gamepad right thumbstick y-axis.
	GAMEPAD_AXIS_TRIGGERL  = 4, ///< Gamepad left trigger value.
	GAMEPAD_AXIS_TRIGGERR  = 5, ///< Gamepad right trigger value.
	__GAMEPAD_AXIS_MAKE_32 = 0x7FFFFFFF,
} ParsecGamepadAxis;

/// @brief Input message type.
/// @details Member of ::ParsecMessage.
typedef enum ParsecMessageType {
	MESSAGE_KEYBOARD       = 1, ///< `keyboard` ::ParsecKeyboardMessage is valid in ::ParsecMessage.
	MESSAGE_MOUSE_BUTTON   = 2, ///< `mouseButton` ::ParsecMouseButtonMessage is valid in ::ParsecMessage.
	MESSAGE_MOUSE_WHEEL    = 3, ///< `mouseWheel` ::ParsecMouseWheelMessage is valid in ::ParsecMessage.
	MESSAGE_MOUSE_MOTION   = 4, ///< `mouseMotion` ::ParsecMouseMotionMessage is valid in ::ParsecMessage.
	MESSAGE_GAMEPAD_BUTTON = 5, ///< `gamepadButton` ::ParsecGamepadButtonMessage is valid in ::ParsecMessage.
	MESSAGE_GAMEPAD_AXIS   = 6, ///< `gamepadAxis` ::ParsecGamepadAxisMessage is valid in ::ParsecMessage.
	MESSAGE_GAMEPAD_UNPLUG = 7, ///< `gamepadUnplug` ::ParsecGamepadUnplugMessage is valid in ::ParsecMessage.
	__MESSAGE_MAKE_32      = 0x7FFFFFFF,
} ParsecMessageType;

/// @brief Color formats for raw image data.
/// @details Member of ::ParsecFrame.
typedef enum ParsecColorFormat {
	FORMAT_UNKNOWN   = 0,
	FORMAT_NV12      = 1, ///< 4:2:0 full width/height Y plane followed by an interleaved half width/height UV plane.
	FORMAT_I420      = 2, ///< 4:2:0 full width/height Y plane followed by a half width/height U plane followed by a half width/height V plane.
	FORMAT_NV16      = 3, ///< 4:2:2 full width/height Y plane followed by an interleaved half width full height UV plane.
	FORMAT_I422      = 4, ///< 4:2:2 full width/height Y plane followed by a half width full height U plane followed by a half width full height V plane.
	FORMAT_BGRA      = 5, ///< 32-bits per pixel, 8-bits per channel BGRA.
	FORMAT_RGBA      = 6, ///< 32-bits per pixel, 8-bits per channel RGBA.
	__FORMAT_MAKE_32 = 0x7FFFFFFF,
} ParsecColorFormat;

/// @brief Network protocol used for peer-to-peer connections.
/// @details Member of ::ParsecClientConfig.
typedef enum ParsecProtocol {
	PROTO_MODE_BUD       = 1, ///< Parsec's low-latency optimized BUD protocol.
	PROTO_MODE_SCTP      = 2, ///< SCTP protocol compatible with WebRTC data channels.
	__PROTO_MODE_MAKE_32 = 0x7FFFFFFF,
} ParsecProtocol;

/// @brief Video stream container.
/// @details Member of ::ParsecClientConfig.
typedef enum ParsecContainer {
	CONTAINER_PARSEC    = 0, ///< Parsec's custom container compatible with native decoding.
	CONTAINER_MP4       = 2, ///< MP4 box container compatible with web browser Media Source Extensions.
	__CONTAINER_MAKE_32 = 0x7FFFFFFF,
} ParsecContainer;

/// @brief PCM audio format.
/// @details Passed to ::ParsecHostSubmitAudio.
typedef enum ParsecPCMFormat {
	PCM_FORMAT_FLOAT     = 1, ///< 32-bit floating point samples.
	PCM_FORMAT_INT16     = 2, ///< 16-bit signed integer samples.
	__PCM_FORMAT_MAKE_32 = 0x7FFFFFFF,
} ParsecPCMFormat;

/// @brief Guest connection lifecycle states.
/// @details Member of ::ParsecGuest and passed to ::ParsecHostGetGuests.
typedef enum ParsecGuestState {
	GUEST_WAITING      = 0x01, ///< The guest is currently waiting for the host to allow them via ::ParsecHostAllowGuest. ::HOST_DESKTOP only.
	GUEST_CONNECTING   = 0x02, ///< The guest is attempting to make a peer-to-peer connection to the host.
	GUEST_CONNECTED    = 0x04, ///< The guest successfully connected.
	GUEST_DISCONNECTED = 0x08, ///< The guest disconnected.
	GUEST_FAILED       = 0x10, ///< The guest failed peer-to-peer negotiation.
	__GUEST_MAKE_32    = 0x7FFFFFFF,
} ParsecGuestState;

/// @brief Host mode of operation.
/// @details Passed to ::ParsecHostStart.
typedef enum ParsecHostMode {
	HOST_DESKTOP   = 1, ///< The host intends to share their entire desktop. Permission and approval systems apply. Windows only.
	HOST_GAME      = 2, ///< Parsec is integrated into a game. The game uses the `Submit` model to provide output.
	__HOST_MAKE_32 = 0x7FFFFFFF,
} ParsecHostMode;

/// @brief Host event type.
/// @details Member of ::ParsecHostEvent.
typedef enum ParsecHostEventType {
	HOST_EVENT_GUEST_STATE_CHANGE = 1, ///< A guest has changed connection state, `guestStateChange` is valid in ::ParsecHostEvent.
	HOST_EVENT_USER_DATA          = 2, ///< User-defined message from a guest, `userData is valid in ::ParsecHostEvent.
	HOST_EVENT_INVALID_SESSION_ID = 4, ///< The host's Session ID has become invalid.
	__HOST_EVENT_MAKE_32          = 0x7FFFFFFF,
} ParsecHostEventType;

/// @brief Client event type.
/// @details Member of ::ParsecClientEvent.
typedef enum ParsecClientEventType {
	CLIENT_EVENT_CURSOR    = 1, ///< A cursor mode change or image update is available, `cursor` is valid in ::ParsecClientEvent. Call ::ParsecGetBuffer in the case of an image update.
	CLIENT_EVENT_RUMBLE    = 2, ///< Gamepad rumble event, `rumble` is valid in ::ParsecClientEvent.
	CLIENT_EVENT_USER_DATA = 3, ///< User-defined message from the host, `userData` is valid in ::ParsecClientEvent.
	CLIENT_EVENT_BLOCKED   = 4, ///< The client has been temporarily blocked from sending input and receiving host output.
	CLIENT_EVENT_UNBLOCKED = 5, ///< The client has returned to normal operation after receiving a ::CLIENT_EVENT_BLOCKED.
	__CLIENT_EVENT_MAKE_32 = 0x7FFFFFFF,
} ParsecClientEventType;


/*** STRUCTS ***/

/// @brief ::Parsec instance configuration.
/// @details Passed to ::ParsecInit and returned by ::ParsecGetConfig. `clientPort` and `hostPort`
///     serve as the first port used when the `bind` call is made internally. If the port is already in use,
///     the next port will be tried until an open port has been found or 50 attempts have been made.
typedef struct ParsecConfig {
	int32_t upnp;       ///< `1` enables and maintains UPnP to assist NAT traversal, `0` disables it.
	int32_t clientPort; ///< First port tried for client connections. A value of `0` uses a pseudo random default.
	int32_t hostPort;   ///< First port used to accept host connections. A value of `0` uses a pseudo random default.
} ParsecConfig;

/// @brief Video frame properties.
/// @details Passed through ::ParsecFrameCallback after calling ::ParsecClientPollFrame.
typedef struct ParsecFrame {
	ParsecColorFormat format; ///< Color format.
	uint32_t size;            ///< Size in bytes of the `image` buffer parameter of ::ParsecFrameCallback.
	uint32_t width;           ///< Width in pixels of the visible area of the frame.
	uint32_t height;          ///< Height in pixels of the visible area of the frame.
	uint32_t fullWidth;       ///< Actual width of the frame including padding.
	uint32_t fullHeight;      ///< Actual height of the frame including padding.
} ParsecFrame;

/// @brief Cursor properties.
/// @details Member of ::ParsecClientCursorEvent, which is itself a member of ::ParsecClientEvent,
///     returned by ::ParsecClientPollEvents. Also passed to ::ParsecHostSubmitCursor to update the cursor while
///     in ::HOST_GAME. When polled from ::ParsecClientPollEvents, `positionX` and `positionY` are
///     affected by the values set via ::ParsecClientSetDimensions.
typedef struct ParsecCursor {
	uint32_t size;      ///< Size in bytes of the cursor image buffer.
	uint32_t positionX; ///< When leaving relative mode, the horizontal position in screen coordinates where the cursor reappears.
	uint32_t positionY; ///< When leaving relative mode, the vertical position in screen coordinates where the cursor reappears.
	uint16_t width;     ///< Width of the cursor image in pixels.
	uint16_t height;    ///< Height of the cursor position in pixels.
	uint16_t hotX;      ///< Horizontal pixel position of the cursor hotspot within the image.
	uint16_t hotY;      ///< Vertical pixel position of the cursor hotspot within the image.
	bool modeUpdate;    ///< `true` if the cursor mode should be updated. The `relative`, `positionX`, and `positionY` members are valid.
	bool imageUpdate;   ///< `true` if the cursor image should be updated. The `width`, `height`, `hotX`, `hotY`, and `size` members are valid.
	bool relative;      ///< `true` if in relative mode, meaning the client should submit mouse motion in relative distances rather than absolute screen coordinates.
	uint8_t __pad[1];
} ParsecCursor;

/// @brief Guest input permissions.
/// @details Member of ::ParsecGuest and passed to ::ParsecHostSetPermissions. Only relevant in ::HOST_DESKTOP.
typedef struct ParsecPermissions {
	bool gamepad;  ///< The guest can send gamepad input.
	bool keyboard; ///< The guest can send keyboard input.
	bool mouse;    ///< The guest can send mouse button.
	uint8_t __pad[1];
} ParsecPermissions;

/// @brief Latency performance metrics.
/// @details Member of ::ParsecGuest and ::ParsecClientStatus.
typedef struct ParsecMetrics {
	float encodeLatency;  ///< Average time in milliseconds for the host to encode a frame.
	float decodeLatency;  ///< Average time in milliseconds for the client to decode a frame.
	float networkLatency; ///< Average round trip time between the client and host.
} ParsecMetrics;

/// @brief Guest properties.
/// @details Member of ::ParsecGuestStateChangeEvent and ::ParsecUserDataEvent. Returned by ::ParsecHostGetGuests
///     and ::ParsecHostPollInput.
typedef struct ParsecGuest {
	ParsecPermissions perms;        ///< Guest input permissions. ::HOST_DESKTOP only.
	ParsecMetrics metrics;          ///< Latency performance metrics, only valid in state ::GUEST_CONNECTED.
	ParsecGuestState state;         ///< Guest connection lifecycle states.
	uint32_t id;                    ///< Guest ID passed to various host functions.
	uint32_t userID;                ///< Parsec unique user ID.
	char name[GUEST_NAME_LEN];      ///< UTF-8 null-terminated name guest name string.
	char attemptID[ATTEMPT_ID_LEN]; ///< Unique connection ID valid while `state` is ::GUEST_WAITING, otherwise filled with zeroes. ::HOST_DESKTOP only.
	bool owner;                     ///< The guest is also the owner of the host computer. ::HOST_DESKTOP only.
	uint8_t __pad[3];
} ParsecGuest;

/// @brief Keyboard message.
/// @details Member of ::ParsecMessage.
typedef struct ParsecKeyboardMessage {
	ParsecKeycode code;  ///< Keyboard input.
	ParsecKeymod mod;    ///< Stateful modifier keys applied to keyboard input.
	bool pressed;        ///< `true` if pressed, `false` if released.
	uint8_t __pad[3];
} ParsecKeyboardMessage;

/// @brief Mouse button message.
/// @details Member of ::ParsecMessage.
typedef struct ParsecMouseButtonMessage {
	ParsecMouseButton button; ///< Mouse button.
	bool pressed;             ///< `true` if clicked, `false` if released.
	uint8_t __pad[3];
} ParsecMouseButtonMessage;

/// @brief Mouse wheel message.
/// @details Member of ::ParsecMessage.
typedef struct ParsecMouseWheelMessage {
	int32_t x; ///< Horizontal delta of mouse wheel rotation. Negative values scroll left.
	int32_t y; ///< Vertical delta of mouse wheel rotation. Negative values scroll up.
} ParsecMouseWheelMessage;

/// @brief Mouse motion message.
/// @details Member of ::ParsecMessage. Mouse motion can be sent in either relative or absolute mode via
///     the `relative` member. Absolute mode treats the `x` and `y` values as the exact destination for where
///     the cursor will appear. These values are sent from the client in device screen coordinates and are translated
///     in accordance with the values set via ::ParsecClientSetDimensions. Relative mode `x` and `y` values are not
///     affected by ::ParsecClientSetDimensions and move the cursor with a signed delta value from its previous location.
typedef struct ParsecMouseMotionMessage {
	int32_t x;     ///< The absolute horizontal screen coordinate of the cursor  if `relative` is `false`, or the delta (can be negative) if `relative` is `true`.
	int32_t y;     ///< The absolute vertical screen coordinate of the cursor if `relative` is `false`, or the delta (can be negative) if `relative` is `true`.
	bool relative; ///< `true` for relative mode, `false` for absolute mode. See above.
	uint8_t __pad[3];
} ParsecMouseMotionMessage;

/// @brief Gamepad button message.
/// @details Member of ::ParsecMessage.
typedef struct ParsecGamepadButtonMessage {
	ParsecGamepadButton button; ///< Gamepad button.
	uint32_t id;                ///< Unique client-provided index identifying the gamepad.
	bool pressed;               ///< `true` if the button was pressed, `false` if released.
	uint8_t __pad[3];
} ParsecGamepadButtonMessage;

/// @brief Gamepad axis message.
/// @details Member of ::ParsecMessage.
typedef struct ParsecGamepadAxisMessage {
	ParsecGamepadAxis axis; ///< Gamepad axes related to thumbsticks and triggers.
	uint32_t id;            ///< Unique client-provided index identifying the gamepad.
	int16_t value;          ///< The new value of the axis between -32,768 (left/down) and 32,767 (right/up).
	uint8_t __pad[2];
} ParsecGamepadAxisMessage;

/// @brief Gamepad unplug message.
/// @details Member of ::ParsecMessage.
typedef struct ParsecGamepadUnplugMessage {
	uint32_t id; ///< Unique client-provided index identifying the gamepad.
} ParsecGamepadUnplugMessage;

/// @brief Generic input message that can represent any message type.
/// @details Passed to ::ParsecClientSendMessage or returned by ::ParsecHostPollInput while
///     in ::HOST_GAME. The application can switch on the `type` member to see which `Message`
///     struct should be evaluated. The `Message` structs are unioned.
typedef struct ParsecMessage {
	ParsecMessageType type;                       ///< Input message type.
	union {
		ParsecKeyboardMessage keyboard;           ///< Keyboard message.
		ParsecMouseButtonMessage mouseButton;     ///< Mouse button message.
		ParsecMouseWheelMessage mouseWheel;       ///< Mouse wheel message.
		ParsecMouseMotionMessage mouseMotion;     ///< Mouse motion message.
		ParsecGamepadButtonMessage gamepadButton; ///< Gamepad button message.
		ParsecGamepadAxisMessage gamepadAxis;     ///< Gamepad axis message.
		ParsecGamepadUnplugMessage gamepadUnplug; ///< Gamepad unplug message.
	};
} ParsecMessage;

/// @brief Client configuration.
/// @details Passed to ::ParsecClientConnect. Regarding `resolutionX`, `resolutionY`, and `refreshRate`:
///     These settings apply only in ::HOST_DESKTOP if the client is the first client to connect, and that client is
///     the owner of the computer. Setting `resolutionX` or `resolutionY` to `0` will leave the host resolution unaffected,
///     otherwise the host will attempt to find the closest matching resolution / refresh rate.
typedef struct ParsecClientConfig {
	int32_t decoderSoftware; ///< `true` to force decoding of video frames via a software implementation.
	int32_t mediaContainer;  ///< ::ParsecContainer value.
	int32_t protocol;        ///< ::ParsecProtocol value.
	int32_t resolutionX;     ///< See above.
	int32_t resolutionY;     ///< See above.
	int32_t refreshRate;     ///< See above.
	bool pngCursor;          ///< `true` to return compressed PNG cursor images during ::ParsecClientPollEvents, `false` to return a 32-bit RGBA image.
	uint8_t __pad[3];
} ParsecClientConfig;

/// @brief Client connection health and status information.
/// @details Returned by ::ParsecClientGetStatus.
typedef struct ParsecClientStatus {
	ParsecMetrics metrics;          ///< Latency performance metrics.
	char attemptID[ATTEMPT_ID_LEN]; ///< Most recent connection `attemptID`. Valid even if ::ParsecClientConnect does not return ::PARSEC_OK.
	bool networkFailure;            ///< Client is currently experiencing network failure.
	bool decoderFallback;           ///< `true` if the client had to fallback to software decoding after being unable to internally initialize a hardware accelerated decoder.
	uint8_t __pad[1];
} ParsecClientStatus;

/// @brief Cursor mode/image update event.
/// @details Member of ::ParsecClientEvent.
typedef struct ParsecClientCursorEvent {
	ParsecCursor cursor; ///< Cursor properties.
	uint32_t key;        ///< Buffer lookup key passed to ::ParsecGetBuffer to retrieve the cursor image, if available.
} ParsecClientCursorEvent;

/// @brief Gamepad rumble data event.
/// @details Member of ::ParsecClientEvent.
typedef struct ParsecClientRumbleEvent {
	uint32_t gamepadID; ///< Unique client-assigned index identifying the gamepad connected to the client.
	uint8_t motorBig;   ///< 8-bit unsigned value for large motor vibration.
	uint8_t motorSmall; ///< 8-bit unsigned value for small motor vibration.
	uint8_t __pad[2];
} ParsecClientRumbleEvent;

/// @brief User-defined host message event.
/// @details Member of ::ParsecClientEvent.
typedef struct ParsecClientUserDataEvent {
	uint32_t id;   ///< User-defined message ID set by the host.
	uint32_t key;  ///< Buffer lookup key passed to ::ParsecGetBuffer to retrieve the message.
} ParsecClientUserDataEvent;

/// @brief Generic client event that can represent any event type.
/// @details Returned by ::ParsecClientPollEvents. The application can switch on the `type` member to see
///     which `Event` struct should be evaluated. The `Event` structs are unioned.
typedef struct ParsecClientEvent {
	ParsecClientEventType type;             ///< Client event type.
	union {
		ParsecClientCursorEvent cursor;     ///< Cursor mode/image update event.
		ParsecClientRumbleEvent rumble;     ///< Gamepad rumble data event.
		ParsecClientUserDataEvent userData; ///< User-defined host message event.
	};
} ParsecClientEvent;

/// @brief Host configuration.
/// @details Member of ::ParsecHostStatus, passed to ::ParsecHostStart and ::ParsecHostSetConfig.
typedef struct ParsecHostConfig {
	int32_t resolutionX;       ///< Resolution width. ::HOST_DESKTOP owner only.
	int32_t resolutionY;       ///< Resolution height. ::HOST_DESKTOP owner only.
	int32_t refreshRate;       ///< Refresh rate in Hz. ::HOST_DESKTOP owner only.
	int32_t adminMute;         ///< Mute local audio on owner connection. ::HOST_DESKTOP owner only.
	int32_t exclusiveInput;    ///< Block remote input when local host input occurs. ::HOST_DESKTOP only.
	int32_t encoderFPS;        ///< Desired frames per second.
	int32_t encoderMaxBitrate; ///< Maximum output bitrate in Mbps, split between guests.
	int32_t encoderH265;       ///< Allow H.265 codec.
	int32_t maxGuests;         ///< Total number of guests allowed at once. This number should not include the local host.
	char name[HOST_NAME_LEN];  ///< UTF-8 null-terminated name string. May be zeroed to use hostname.
	char desc[HOST_DESC_LEN];  ///< UTF-8 null-terminated description string. ::HOST_GAME only.
	char gameID[GAME_ID_LEN];  ///< Game unique identifier issued by Parsec. ::HOST_GAME only.
	bool publicGame;           ///< Set to `true` to allow the hosting session to be visible publicly in the Parsec Arcade. ::HOST_GAME only.
	uint8_t __pad[3];
} ParsecHostConfig;

/// @brief Host runtime status.
/// @details Returned by ::ParsecHostGetStatus.
typedef struct ParsecHostStatus {
	ParsecHostConfig cfg;  ///< The currently active host configuration.
	uint32_t numGuests;    ///< The number of guests currently in state ::GUEST_CONNECTED.
	bool running;          ///< The host is currently accepting guests after calling ::ParsecHostStart.
	bool invalidSessionID; ///< `true` if the host's Session ID has become invalid. The host must call ::ParsecHostSetConfig with a valid `sessionID` to continue hosting.
	bool gamepadSupport;   ///< `true` if the virtual gamepad driver is working properly, otherwise `false`. ::HOST_DESKTOP only.
	uint8_t __pad[1];
} ParsecHostStatus;

/// @brief Guest connection state change event.
/// @details Member of ::ParsecHostEvent.
typedef struct ParsecGuestStateChangeEvent {
	ParsecGuest guest; ///< Guest properties. The `state` member can be used to evaluate the guest's state change.
} ParsecGuestStateChangeEvent;

/// @brief User-defined guest message event.
/// @details Member of ::ParsecHostEvent.
typedef struct ParsecUserDataEvent {
	ParsecGuest guest; ///< Guest ::ParsecGuest properties.
	uint32_t id;       ///< User-defined message ID set by the client.
	uint32_t key;      ///< Buffer lookup key passed to ::ParsecGetBuffer to retrieve the message.
} ParsecUserDataEvent;

/// @brief Generic host event that can represent any event type.
/// @details Returned by ::ParsecHostPollEvents. The application can switch on the `type` member
///     to see which `Event` struct should be evaluated. The `Event` structs are unioned.
typedef struct ParsecHostEvent {
	ParsecHostEventType type;                         ///< Host event type.
	union {
		ParsecGuestStateChangeEvent guestStateChange; ///< Guest connection state change event.
		ParsecUserDataEvent userData;                 ///< User-defined guest message event.
	};
} ParsecHostEvent;


/*** TYPEDEFS ***/

/// @brief Parsec instance.
/// @details Returned by ::ParsecInit.
typedef struct Parsec Parsec;

/// @brief OpenGL/GLES 32-bit unsigned integer.
/// @details Passed to ::ParsecHostGLSubmitFrame. Prevents obligatory include of GL headers.
typedef uint32_t ParsecGLuint;

/// @brief D3D11 `ID3D11Device`.
/// @details Passed to ::ParsecHostD3D11SubmitFrame. Prevents obligatory include of d3d11.h.
typedef void ParsecD3D11Device;

/// @brief D3D11 `ID3D11DeviceContext`.
/// @details Passed to ::ParsecHostD3D11SubmitFrame. Prevents obligatory include of d3d11.h.
typedef void ParsecD3D11DeviceContext;

/// @brief D3D11 `ID3D11Texture2D`.
/// @details Passed to ::ParsecHostD3D11SubmitFrame. Prevents obligatory include of d3d11.h.
typedef void ParsecD3D11Texture2D;

/// @brief Fired when a new log message is available from the Parsec SDK.
/// @details Passed to ::ParsecSetLogCallback.
/// @param level ::ParsecLogLevel level value.
/// @param msg Null-terminated UTF-8 string containing the full log message.
/// @param opaque User supplied context passed to ::ParsecSetLogCallback.
typedef void (*ParsecLogCallback)(ParsecLogLevel level, char *msg, void *opaque);

/// @brief Fired synchronously if a new frame is available from the host.
/// @details Passed to ::ParsecClientPollFrame.
/// @param frame Video frame properties.
/// @param image The video frame buffer containing image data.
/// @param opaque User supplied context passed to ::ParsecClientPollFrame.
typedef void (*ParsecFrameCallback)(ParsecFrame *frame, uint8_t *image, void *opaque);

/// @brief Fired synchronously if new audio is available from the host.
/// @details Passed to ::ParsecClientPollAudio.
/// @param pcm 16-bit signed, two channel, 48KHz PCM audio samples.
/// @param frames Number of audio frames.
/// @param opaque User supplied context passed to ::ParsecClientPollAudio.
typedef void (*ParsecAudioCallback)(int16_t *pcm, uint32_t frames, void *opaque);


/*** INSTANCE FUNCTIONS ***/

#if defined(PARSEC_DSO)
#define ParsecInit                 (*ParsecInit)
#define ParsecDestroy              (*ParsecDestroy)
#define ParsecGetConfig            (*ParsecGetConfig)
#define ParsecGetBuffer            (*ParsecGetBuffer)
#define ParsecFree                 (*ParsecFree)
#define ParsecSetLogCallback       (*ParsecSetLogCallback)
#define ParsecVersion              (*ParsecVersion)
#define ParsecClientConnect        (*ParsecClientConnect)
#define ParsecClientDisconnect     (*ParsecClientDisconnect)
#define ParsecClientGetStatus      (*ParsecClientGetStatus)
#define ParsecClientSetDimensions  (*ParsecClientSetDimensions)
#define ParsecClientPollFrame      (*ParsecClientPollFrame)
#define ParsecClientPollAudio      (*ParsecClientPollAudio)
#define ParsecClientPollEvents     (*ParsecClientPollEvents)
#define ParsecClientGLRenderFrame  (*ParsecClientGLRenderFrame)
#define ParsecClientGLDestroy      (*ParsecClientGLDestroy)
#define ParsecClientSendMessage    (*ParsecClientSendMessage)
#define ParsecClientSendUserData   (*ParsecClientSendUserData)
#define ParsecHostStart            (*ParsecHostStart)
#define ParsecHostStop             (*ParsecHostStop)
#define ParsecHostGetStatus        (*ParsecHostGetStatus)
#define ParsecHostSetConfig        (*ParsecHostSetConfig)
#define ParsecHostGetGuests        (*ParsecHostGetGuests)
#define ParsecHostKickGuest        (*ParsecHostKickGuest)
#define ParsecHostSendUserData     (*ParsecHostSendUserData)
#define ParsecHostPollEvents       (*ParsecHostPollEvents)
#define ParsecHostAllowGuest       (*ParsecHostAllowGuest)
#define ParsecHostSetPermissions   (*ParsecHostSetPermissions)
#define ParsecHostPollInput        (*ParsecHostPollInput)
#define ParsecHostSubmitAudio      (*ParsecHostSubmitAudio)
#define ParsecHostSubmitCursor     (*ParsecHostSubmitCursor)
#define ParsecHostSubmitRumble     (*ParsecHostSubmitRumble)
#define ParsecHostGLSubmitFrame    (*ParsecHostGLSubmitFrame)
#define ParsecHostD3D11SubmitFrame (*ParsecHostD3D11SubmitFrame)

typedef struct ParsecAPI {
#endif

/// @brief Initialize ::Parsec instance.
/// @param[in] ver Always pass ::PARSEC_VER.
/// @param[in] cfg ::Parsec instance configuration. May be `NULL` to use ::PARSEC_DEFAULTS.
/// @param[in] reserved Reserved for future use. Set to `NULL`.
/// @param[out] ps New ::Parsec instance.
/// @returns ::PARSEC_ERR_VERSION if this header is incompatible with the linked Parsec SDK binary,
///     otherwise ::PARSEC_OK.
EXPORT ParsecStatus
ParsecInit(uint32_t ver, ParsecConfig *cfg, void *reserved, Parsec **ps);

/// @brief Destroy ::Parsec instance.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
EXPORT void
ParsecDestroy(Parsec *ps);

/// @brief Get ::Parsec runtime configuration.
/// @details Useful for querying a ::Parsec instance in the case the client/host ports were randomly selected.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[out] cfg ::Parsec instance configuration, reflects randomly selected ports if ports were set to `0`
///     during ::ParsecInit.
EXPORT void
ParsecGetConfig(Parsec *ps, ParsecConfig *cfg);

/// @brief Get an internal dynamically allocated buffer by 32-bit lookup key.
/// @details The return value is dynamically allocated and must be passed to ::ParsecFree after use.
///     The size of the buffer should always be known in advance of calling this function.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] key 32-bit lookup key returned by various polling functions.
/// @returns `NULL` if the lookup key was invalid or the buffer was already retrieved, otherwise a
///     dynamically allocated buffer. Call ::ParsecFree after use.
EXPORT void *
ParsecGetBuffer(Parsec *ps, uint32_t key);

/// @brief Free a dynamically allocated buffer returned by ::ParsecGetBuffer.
/// @param[in] ptr Buffer return by ::ParsecGetBuffer.
EXPORT void
ParsecFree(void *ptr);

/// @brief Receive log messages accross all ::Parsec instances.
/// @details The callback is not thread safe and must use proper synchronization on the `opaque` context.
///     This function may be called with `NULL` as both arguments to remove any previously set callback. This
///     function takes effect globally and applies to all initialized ::Parsec instances.
/// @param[in] callback Fired when a new log message is available from the Parsec SDK.
/// @param[in] opaque User supplied context to be passed through `callback`.
EXPORT void
ParsecSetLogCallback(ParsecLogCallback callback, void *opaque);

/// @brief Retrieve the Parsec SDK internal ::PARSEC_VER.
/// @details This is useful when loading the Parsec SDK at runtime to prevent major version
///     incompatibility. ::PARSEC_VER_MAJOR is the upper 16 bits, ::PARSEC_VER_MINOR is the lower 16 bits.
EXPORT uint32_t
ParsecVersion(void);


/*** CLIENT FUNCTIONS ***/

/// @brief Connect to a remote Parsec host.
/// @details Performs authentication, peer-to-peer negotiation, and NAT traversal.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] cfg Client configuration. May be left `NULL` to use ::PARSEC_CLIENT_DEFAULTS.
/// @param[in] sessionID Session ID obtained via the [Parsec API](https://github.com/parsec-cloud/parsec-sdk/tree/master/api/public).
/// @param[in] peerID Remote host Peer ID obtained via the [Parsec API](https://github.com/parsec-cloud/parsec-sdk/tree/master/api/public).
/// @returns ::PARSEC_OK on successful connection, otherwise a ::ParsecStatus error value.
EXPORT ParsecStatus
ParsecClientConnect(Parsec *ps, ParsecClientConfig *cfg, char *sessionID, char *peerID);

/// @brief Disconnect client.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
EXPORT void
ParsecClientDisconnect(Parsec *ps);

/// @brief Get client connection health and status information.
/// @details This function should be polled during runtime to check if a client session should continue.
///     The return value can be used to stop a client session and proceed to cleanup if not ::PARSEC_OK.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[out] status Client connection health and status information.
/// @returns ::PARSEC_OK if the client is running properly, otherwise a ::ParsecStatus error value.
EXPORT ParsecStatus
ParsecClientGetStatus(Parsec *ps, ParsecClientStatus *status);

/// @brief Set client window dimensions and screen scale.
/// @details The window size and screen scale are used internally to translate mouse coordinates
///     and set the viewport during rendering (if `RenderFrame` wrappers are used).
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] width The window width in screen coordinates.
/// @param[in] height The window height in screen coordinates.
/// @param[in] scale The screen scale used to translate device screen coordinates into pixels.
/// @returns ::PARSEC_OK on success or ::PARSEC_NOT_RUNNING if the client is not connected.
EXPORT ParsecStatus
ParsecClientSetDimensions(Parsec *ps, uint32_t width, uint32_t height, float scale);

/// @brief Poll for a new video frame from the host and make it available in system memory.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] callback Fired synchronously if a new frame is available from the host.
/// @param[in] timeout Timeout in milliseconds to wait for a new frame to become available.
/// @param[in] opaque User supplied context to be passed through `callback`.
/// @returns ::PARSEC_OK if a new frame was available and the callback fired, otherwise
///     a ::ParsecStatus warning value on timeout.
EXPORT ParsecStatus
ParsecClientPollFrame(Parsec *ps, ParsecFrameCallback callback, uint32_t timeout, void *opaque);

/// @brief Poll for new audio from the host.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] callback Fired synchronously if new audio is available from the host.
/// @param[in] timeout Timeout in milliseconds to wait for new audio to become available.
/// @param[in] opaque User supplied context to be passed through `callback`.
/// @returns ::PARSEC_OK if new audio frames were available and the callback fired, otherwise
///     a ::ParsecStatus warning value on timeout.
EXPORT ParsecStatus
ParsecClientPollAudio(Parsec *ps, ParsecAudioCallback callback, uint32_t timeout, void *opaque);

/// @brief Poll client events.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] timeout Timeout in milliseconds to wait for a new event to become available.
/// @param[out] event Generic client event that can represent any event type.
/// @returns `true` if a new event was available and `event` is valid, otherwise `false` if
///     no events were available.
EXPORT bool
ParsecClientPollEvents(Parsec *ps, uint32_t timeout, ParsecClientEvent *event);

/// @brief Waits for and efficiently renders a remote video frame with OpenGL/GLES.
/// @details If the timeout expires, the previous frame is rendered. Must be called from a
///     thread with a current OpenGL/GLES 2.0 compatible context.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] timeout Time in milliseconds to wait for a new frame or render the previous frame and return.
/// @returns ::PARSEC_OK if a new frame was rendered, otherwise a ::ParsecStatus warning if the previous frame was rendered.
EXPORT ParsecStatus
ParsecClientGLRenderFrame(Parsec *ps, uint32_t timeout);

/// @brief Cleanup internal OpenGL/GLES state.
/// @details Must be called from a thread with a current OpenGL/GLES 2.0 compatible context.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
EXPORT void
ParsecClientGLDestroy(Parsec *ps);

/// @brief Send an input message to the remote host.
/// @details This function sends one of the input types defined in ::ParsecMessageType set in the
///     `type` member of the ::ParsecMessage `msg` parameter. The indicated message type is then filled
///     out in the appropriate `Message` struct in `msg`.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] msg Generic input message than can represet any message type.
/// @returns ::PARSEC_OK if the message was sent successfully, otherwise a ::ParsecStatus error value.
EXPORT ParsecStatus
ParsecClientSendMessage(Parsec *ps, ParsecMessage *msg);

/// @brief Send a user-defined string to the remote host.
/// @details The host may set an optional callback to process user-defined messages. These messages may be any
///     type of data serialized via JSON or XML. Note: Parsec's peer-to-peer protocol is optimized for
///     targeted bitrate, low-latency media streaming and not bulk file transfer. Very large messages sent
///     via this function may unnecessarily burden both the client and the host.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] id User-defined message ID considered by the host.
/// @param[in] text Null-terminated UTF-8 string.
/// @returns ::PARSEC_OK if the message was sent successfully, otherwise a ::ParsecStatus error value.
EXPORT ParsecStatus
ParsecClientSendUserData(Parsec *ps, uint32_t id, char *text);


/*** HOST FUNCTIONS ***/

/// @brief Start accepting guests.
/// @details ::HOST_DESKTOP sessions capture the host computer's entire desktop or any fullscreen
///     application. ::HOST_DESKTOP is available on Windows only.\n\n
///     ::HOST_GAME sessions are intended for integration within a game's render/audio/input loops.
///     ::HOST_GAME requires that the application call ::ParsecHostSubmitAudio and ::ParsecHostD3D11SubmitFrame
///     (or similar) to push data to guests, and call ::ParsecHostPollInput to process input from guests.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] mode Host mode of operation. See above.
/// @param[in] cfg Host configuration. May be updated later via ::ParsecHostSetConfig. May be `NULL`
///     to use ::PARSEC_HOST_DEFAULTS.
/// @param[in] sessionID Session ID obtained via the [Parsec API](https://github.com/parsec-cloud/parsec-sdk/tree/master/api/public).
/// @returns Always ::PARSEC_OK on Windows, otherwise ::PARSEC_OK in ::HOST_GAME or ::PARSEC_NOT_IMPLEMENTED.
EXPORT ParsecStatus
ParsecHostStart(Parsec *ps, ParsecHostMode mode, ParsecHostConfig *cfg, char *sessionID);

/// @brief Disconnect all guests and stop hosting.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
EXPORT void
ParsecHostStop(Parsec *ps);

/// @brief Get current hosting status.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[out] status Host runtime status.
EXPORT void
ParsecHostGetStatus(Parsec *ps, ParsecHostStatus *status);

/// @brief Set host configuration.
/// @details Calling this function will cause the new settings within `cfg` to take effect immediately.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] cfg Host configuration. May be `NULL` to use ::PARSEC_HOST_DEFAULTS.
/// @param[in] sessionID Session ID obtained via the [Parsec API](https://github.com/parsec-cloud/parsec-sdk/tree/master/api/public).
///     May be `NULL` to continue to use the previously set Session ID.
/// @returns ::PARSEC_OK on success or ::PARSEC_NOT_RUNNING if the host has not been started.
EXPORT ParsecStatus
ParsecHostSetConfig(Parsec *ps, ParsecHostConfig *cfg, char *sessionID);

/// @brief Get a list of all connected and/or waiting guests.
/// @details The return value `guests` is dynamically allocated and must be passed to ::ParsecFree after use.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] state Guest connection lifecycle state. Bitwise or of ::GUEST_CONNECTED and/or ::GUEST_WAITING.
/// @param[out] guests Pointer to an array of guests. May be `NULL` to query the number of guests but not set the array.
/// @returns The length of the array returned in `guests`.
EXPORT uint32_t
ParsecHostGetGuests(Parsec *ps, ParsecGuestState state, ParsecGuest **guests);

/// @brief Kick guest.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] guestID `id` member of ::ParsecGuest returned by ::ParsecHostGetGuests.
/// @returns ::PARSEC_OK if the guest was successfully kicked, otherwise a ::ParsecStatus error value.
EXPORT ParsecStatus
ParsecHostKickGuest(Parsec *ps, uint32_t guestID);

/// @brief Send a user-defined message to a guest.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] guestID `id` member of ::ParsecGuest returned by ::ParsecHostGetGuests.
/// @param[in] id User-defined message ID considered by the client.
/// @param[in] text Null-terminated UTF-8 string.
/// @returns ::PARSEC_OK if the message was successfully sent, otherwise a ::ParsecStatus error value.
EXPORT ParsecStatus
ParsecHostSendUserData(Parsec *ps, uint32_t guestID, uint32_t id, char *text);

/// @brief Poll host events.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] timeout Timeout in milliseconds to wait for a new event to become available.
/// @param[out] event Generic host event that can represent any event type.
/// @returns `true` if a new event was available and `event` was filled, otherwise `false` if
///     no events were available.
EXPORT bool
ParsecHostPollEvents(Parsec *ps, uint32_t timeout, ParsecHostEvent *event);

/// @brief Allow or reject a pending guest. ::HOST_DESKTOP only.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] attemptID Unique connection ID found in ::ParsecGuest struct obtained via ::ParsecHostGetGuests.
/// @param[in] allow `true` to allow the guest to connect, `false` to have them disconnect immediately.
/// @returns ::PARSEC_OK on success or ::PARSEC_NOT_RUNNING if the host has not been started.
EXPORT ParsecStatus
ParsecHostAllowGuest(Parsec *ps, char *attemptID, bool allow);

/// @brief Change guest input permissions. ::HOST_DESKTOP only.
/// @details Current input permissions can be queried with ::ParsecHostGetGuests.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] guestID `id` member of ::ParsecGuest returned by ::ParsecHostGetGuests.
/// @param[in] perms Guest input permissions.
/// @returns ::PARSEC_OK if permissions were set successfully, otherwise a ::ParsecStatus error value.
EXPORT ParsecStatus
ParsecHostSetPermissions(Parsec *ps, uint32_t guestID, ParsecPermissions *perms);

/// @brief Poll input messages from connected guests. ::HOST_GAME only.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] timeout Timeout in milliseconds to wait for a new input message to become available.
/// @param[out] guest Guest properties. May be left `NULL`.
/// @param[out] msg Generic input message that can represent any message type.
/// @returns `true` if a new message was availalble and `msg` was filled, otherwise `false` if
///     no messages were available.
EXPORT bool
ParsecHostPollInput(Parsec *ps, uint32_t timeout, ParsecGuest *guest, ParsecMessage *msg);

/// @brief Submit PCM audio to connected guests. ::HOST_GAME only.
/// @details Audio must be submitted in two channel PCM.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] format PCM audio format.
/// @param[in] sampleRate PCM sample rate in Hz.
/// @param[in] pcm Audio buffer containing two channel frames.
/// @param[in] frames The number of audio frames contained in `pcm`.
/// @returns ::PARSEC_OK on success or ::PARSEC_NOT_RUNNING if the host has not been started.
EXPORT ParsecStatus
ParsecHostSubmitAudio(Parsec *ps, ParsecPCMFormat format, uint32_t sampleRate, uint8_t *pcm, uint32_t frames);

/// @brief Submit a cursor mode and/or image update to connected guests. ::HOST_GAME only.
/// @details The cursor image buffer must be in 32-bit RGBA with no padding or bitmap header.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] cursor Cursor properties.
/// @param[in] image 32-bits per pixel RGBA cursor image buffer.
/// @returns ::PARSEC_OK on success or ::PARSEC_NOT_RUNNING if the host has not been started.
EXPORT ParsecStatus
ParsecHostSubmitCursor(Parsec *ps, ParsecCursor *cursor, uint8_t *image);

/// @brief Submit gamepad rumble data to a connected guests. ::HOST_GAME only.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] guestID `id` member of ::ParsecGuest returned by ::ParsecHostGetGuests.
/// @param[in] gamepadID Unique client-assigned index identifying the gamepad connected to the client.
/// @param[in] motorBig 8-bit unsigned value for large motor vibration.
/// @param[in] motorSmall 8-bit unsigned value for small motor vibration.
/// @returns ::PARSEC_OK on success or ::PARSEC_NOT_RUNNING if the host has not been started.
EXPORT ParsecStatus
ParsecHostSubmitRumble(Parsec *ps, uint32_t guestID, uint32_t gamepadID, uint8_t motorBig, uint8_t motorSmall);

/// @brief Submit rendered OpenGL frame to connected guests. ::HOST_GAME only.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] frame GLuint `GL_TEXTURE_2D` representing a rendered frame.
/// @returns ::PARSEC_OK if the frame was submitted successfully, otherwise a ::ParsecStatus error value.
EXPORT ParsecStatus
ParsecHostGLSubmitFrame(Parsec *ps, ParsecGLuint frame);

/// @brief Submit rendered D3D11 frame to connected guests. ::HOST_GAME only. Windows only.
/// @param[in] ps ::Parsec instance returned by ::ParsecInit.
/// @param[in] device Cast to `ID3D11Device *` used within your render loop.
/// @param[in] context Cast to `ID3D11DeviceContext *` used within your render loop.
/// @param[in] frame Cast to `ID3D11Texture2D *` representing a rendered frame.
/// @returns ::PARSEC_OK if the frame was submitted successfully, otherwise a ::ParsecStatus error value.
EXPORT ParsecStatus
ParsecHostD3D11SubmitFrame(Parsec *ps, ParsecD3D11Device *device, ParsecD3D11DeviceContext *context,
	ParsecD3D11Texture2D *frame);

#if defined(PARSEC_DSO)
} ParsecAPI;

#undef ParsecInit
#undef ParsecDestroy
#undef ParsecGetConfig
#undef ParsecGetBuffer
#undef ParsecFree
#undef ParsecSetLogCallback
#undef ParsecVersion
#undef ParsecClientConnect
#undef ParsecClientDisconnect
#undef ParsecClientGetStatus
#undef ParsecClientSetDimensions
#undef ParsecClientPollFrame
#undef ParsecClientPollAudio
#undef ParsecClientPollEvents
#undef ParsecClientGLRenderFrame
#undef ParsecClientGLDestroy
#undef ParsecClientSendMessage
#undef ParsecClientSendUserData
#undef ParsecHostStart
#undef ParsecHostStop
#undef ParsecHostGetStatus
#undef ParsecHostSetConfig
#undef ParsecHostGetGuests
#undef ParsecHostKickGuest
#undef ParsecHostSendUserData
#undef ParsecHostPollEvents
#undef ParsecHostAllowGuest
#undef ParsecHostSetPermissions
#undef ParsecHostPollInput
#undef ParsecHostSubmitAudio
#undef ParsecHostSubmitCursor
#undef ParsecHostSubmitRumble
#undef ParsecHostGLSubmitFrame
#undef ParsecHostD3D11SubmitFrame
#endif

#ifdef __cplusplus
}
#endif

#if defined(_WIN32)
	#pragma warning(default: 4201)
#endif
