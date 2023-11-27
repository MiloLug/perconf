# app version
VERSION = 0.0.1
BIN_NAME = perconf

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# flags
CPPFLAGS = -D_DEFAULT_SOURCE -DVERSION=\"${VERSION}\"
CFLAGS = \
	-std=c17 \
	-pedantic \
	-Wall \
	-Wno-deprecated-declarations \
	-ffast-math \
    -fno-finite-math-only \
    -march=native \
    -fno-exceptions \
	-Ofast \
	-fforce-emit-vtables \
	-faddrsig \
	${CPPFLAGS}

LDFLAGS = 

# compiler and linker
CC = clang
