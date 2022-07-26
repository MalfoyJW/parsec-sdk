#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "parsec-dso.h"

#if defined(_WIN32)
	#if !defined(BITS)
		#define BITS 64
	#endif
	#if (BITS == 64)
		#define SDK_PATH "../../sdk/windows/parsec.dll"
	#else
		#define SDK_PATH "../../sdk/windows/parsec32.dll"
	#endif
#elif defined(__APPLE__)
	#define SDK_PATH "../../sdk/macos/libparsec.dylib"
#else
	#define SDK_PATH "../../sdk/linux/libparsec.so"
#endif

static void logCallback(ParsecLogLevel level, const char *msg, void *opaque)
{
	opaque;

	printf("[%s] %s\n", level == LOG_DEBUG ? "D" : "I", msg);
}

static void guestStateChange(ParsecGuest *guest)
{
	switch (guest->state) {
		case GUEST_CONNECTED:
			printf("%s#%d connected.\n", guest->name, guest->userID);
			break;
		case GUEST_DISCONNECTED:
			printf("%s#%d disconnected.\n", guest->name, guest->userID);
			break;
		default:
			break;
	}
}

int32_t main(int32_t argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: host sessionID\n");
		return 1;
	}

	ParsecDSO *parsec = NULL;
	ParsecStatus e = ParsecInit(NULL, NULL, SDK_PATH, &parsec);
	if (e != PARSEC_OK) goto except;

	ParsecSetLogCallback(parsec, logCallback, NULL);

	ParsecHostConfig cfg = PARSEC_HOST_DEFAULTS;
	ParsecHostStart(parsec, HOST_DESKTOP, &cfg, argv[1]);

	while (true) {
		for (ParsecHostEvent event; ParsecHostPollEvents(parsec, 1000, &event);) {
			switch (event.type) {
				case HOST_EVENT_GUEST_STATE_CHANGE:
					guestStateChange(&event.guestStateChange.guest);
					break;
				default:
					break;
			}
		}
	}

	except:

	ParsecDestroy(parsec);

	return 0;
}
