# CMAKE configuration file. This file is responsible for handling the builds of all
# native code in the project and linking any native libraries as well.

# GENERAL SETTINGS
cmake_minimum_required(VERSION 3.6.0)

# CODE LOCATIONS
set(CPP_ROOT ${CMAKE_SOURCE_DIR}/src/main/cpp)
set(LIB_DST ${CMAKE_SOURCE_DIR}/libs/)
set(LIB_SRC ${PROJECT_SOURCE_DIR}/../../../sdk/android/${ANDROID_ABI})
file(COPY ${LIB_SRC} DESTINATION ${LIB_DST})

# COMPILER FLAGS
set(CMAKE_CC_FLAGS "\
	-Wall \
	-Wextra \
	-Wno-unused-function \
	-Wno-write-strings \
	-Wno-unused-value \
	-Wno-unused-parameter \
	-Wno-unused-result \
	-Wno-unused-variable \
	-Wno-sign-compare \
	-I${PROJECT_SOURCE_DIR}/../../../sdk \
	-fPIC \
	-O2")

set(CMAKE_C_FLAGS "${CMAKE_CC_FLAGS} -Wno-c99-extensions")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wno-c++11-compat-deprecated-writable-strings")

# PRE-COMPLIED THIRD PARTY LIBRARIES
add_library( libMain STATIC IMPORTED )
set_target_properties( libMain PROPERTIES IMPORTED_LOCATION ${LIB_DST}/${ANDROID_ABI}/libparsec.so )

# CLIENT LIBRARIES
set(CC_FILES
	${CPP_ROOT}/bindings.c
	${CPP_ROOT}/implementation.c
	${CPP_ROOT}/aaudio.c
)

add_library( parsec-bindings SHARED ${CC_FILES} )

target_include_directories(parsec-bindings PRIVATE
	"${CPP_ROOT}/")

# LINK (Seperated by library origin)
target_link_libraries(
	parsec-bindings libMain
	GLESv3 z jnigraphics mediandk aaudio OpenMAXAL log android EGL)
