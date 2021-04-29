!IF [if /I "%Platform%" EQU "x64" exit 1]
BITS = 64
!ELSE
BITS = 32
!ENDIF

BIN_NAME = client.exe
OBJS = main.obj

CFLAGS = \
	/nologo \
	/W4 \
	/O2 \
	/MT \
	/MP \
	/wd4201 \
	-I../../sdk \
	-Iinclude \
	-DBITS=$(BITS) \
	-DWIN32_LEAN_AND_MEAN \
	-DUNICODE

SHARED_LIBS = \
	libvcruntime.lib \
	libucrt.lib \
	libcmt.lib \
	kernel32.lib \
	gdi32.lib \
	winmm.lib \
	imm32.lib \
	shell32.lib \
	advapi32.lib \
	ole32.lib \
	oleaut32.lib \
	opengl32.lib \
	user32.lib \
	uuid.lib \
	version.lib \
	setupapi.lib \
	hid.lib \
	dxgi.lib \
	ws2_32.lib \
	bcrypt.lib \
	windowscodecs.lib \
	dxguid.lib \
	xinput9_1_0.lib \
	d3d9.lib \
	shlwapi.lib \
	d3d11.lib

STATIC_LIBS = \
	lib/windows/%Platform%/matoya.lib

LD_FLAGS = \
	/nodefaultlib \
	/nologo

all: clean clear $(OBJS)
	link $(LD_FLAGS) /out:$(BIN_NAME) *.obj $(STATIC_LIBS) $(SHARED_LIBS)

clean:
	-@del $(BIN_NAME)
	-@del *.obj

clear:
	cls
