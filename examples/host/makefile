!IF [if /I "%Platform%" EQU "x64" exit 1]
BITS = 64
!ELSE
BITS = 32
!ENDIF

BIN_NAME = host.exe
OBJS = main.obj

CFLAGS = \
	/nologo \
	/W4 \
	/O2 \
	/MT \
	/MP \
	-I../../sdk \
	-DBITS=$(BITS) \
	-DWIN32_LEAN_AND_MEAN \
	-DUNICODE

SHARED_LIBS = \
	libvcruntime.lib \
	libucrt.lib \
	libcmt.lib \
	kernel32.lib

LD_FLAGS = \
	/nodefaultlib \
	/nologo

all: clean clear $(OBJS)
	link $(LD_FLAGS) /out:$(BIN_NAME) *.obj $(SHARED_LIBS)

clean:
	-@del $(BIN_NAME)
	-@del *.obj

clear:
	cls
