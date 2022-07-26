UNAME = $(shell uname -s)


### LINUX ###
ifeq ($(UNAME), Linux)

PLATFORM = linux

SHARED_LIBS = \
	-lm \
	-ldl \
	-lGL \
	-lpthread
endif


### MACOS ###
ifeq ($(UNAME), Darwin)

export SDKROOT=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk

PLATFORM = macos

SHARED_LIBS = \
	-liconv \
	-framework OpenGL \
	-framework VideoToolbox \
	-framework CoreMedia \
	-framework CoreAudio \
	-framework AudioToolbox \
	-framework IOKit \
	-framework ForceFeedback \
	-framework Carbon \
	-framework AppKit \
	-framework Metal \
	-framework QuartzCore
endif


### COMMON ###
BIN_NAME = client
OBJS = main.o
STATIC_LIBS = lib/$(PLATFORM)/libmatoya.a

CFLAGS = \
	-Wall \
	-Wextra \
	-Wno-unused-value \
	-Wno-missing-field-initializers \
	-O3 \
	-I../../sdk \
	-Iinclude

all: clean clear $(OBJS)
	$(CC) -o $(BIN_NAME) $(OBJS) $(STATIC_LIBS) $(SHARED_LIBS)

clean:
	-@rm -rf $(OBJS)
	-@rm -rf $(BIN_NAME)

clear:
	clear
