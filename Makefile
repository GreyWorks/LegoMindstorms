# Target specific macros
TARGET = HelloWorld

TARGET_CPP_SOURCES = HelloWorld.cpp
	
TOPPERS_OSEK_OIL_SOURCE = ./HelloWorld.oil

# Don't modify below part
TOPPERS_OSEK_ROOT_SG = C:/nxtOSEK/toppers_osek
O_PATH ?= build

# makefile for C++(.cpp) build
include /cygdrive/c/nxtOSEK/ecrobot/ecrobot++.mak
