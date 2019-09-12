UNAME = $(shell uname -s)


### LINUX ###
ifeq ($(UNAME), Linux)

SHARED_LIBS = -ldl
endif


### MACOS ###
ifeq ($(UNAME), Darwin)

export SDKROOT=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk

endif


### COMMON ###
BIN_NAME = host
OBJS = main.o

CFLAGS = \
	-Wall \
	-Wextra \
	-Wno-unused-value \
	-Wno-missing-field-initializers \
	-O3 \
	-I../../sdk \
	-Iinclude

all: clean clear $(OBJS)
	$(CC) -o $(BIN_NAME) $(OBJS) $(SHARED_LIBS)

clean:
	-@rm -rf $(OBJS)
	-@rm -rf $(BIN_NAME)

clear:
	clear
