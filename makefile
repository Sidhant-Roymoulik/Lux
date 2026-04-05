# Makefile

EXE := Lux
SRC := src/*.cpp
CC  ?= gcc
CXX ?= g++

EXEDIR := src/executables

# Detect MSYS2/MinGW and fix temp dir for native g++ (cygpath is MSYS2-only, safe no-op elsewhere)
WIN_TEMP := $(shell cygpath -m /tmp 2>/dev/null)
ifneq ($(WIN_TEMP),)
    export TMP  := $(WIN_TEMP)
    export TEMP := $(WIN_TEMP)
endif

# Default flags
LFLAGS := 
WFLAGS := -Wall -Wextra -Werror
CXXFLAGS := -std=c++20 $(WFLAGS) -O3 -DNDEBUG
RFLAGS := -std=c++20 -O3 -DNDEBUG

# Platform-specific flags and libraries
ifeq ($(OS),Windows_NT)
    # Windows-specific flags and settings
    LFLAGS   := -Wl,--whole-archive -lpthread -Wl,--no-whole-archive
		CXXFLAGS := -std=c++20 $(WFLAGS) -O3 -DNDEBUG -march=native
		RFLAGS   := -std=c++20 -O3 -DNDEBUG -static
    IS_ARM   := 0
else
    # Unix-like (Linux, macOS)
    ifeq ($(shell uname),Darwin)
        # macOS specific settings
        LFLAGS :=
        CXXFLAGS := $(CXXFLAGS) -stdlib=libc++
        RFLAGS := $(RFLAGS) -stdlib=libc++
    else
        # Ubuntu specific settings
        LFLAGS := -Wl,--whole-archive -lpthread -Wl,--no-whole-archive
        CXXFLAGS := $(CXXFLAGS) -march=native
    endif
    ifeq ($(shell uname -m),arm64)
        IS_ARM := 1
    else
        IS_ARM := 0
    endif
endif

# On MSYS2/MinGW, link statically to avoid runtime DLL search issues
ifneq ($(WIN_TEMP),)
    LFLAGS += -static
endif

default:
	$(CXX) $(RFLAGS) -march=native $(SRC) $(LFLAGS) -o $(EXE)

dev:
	$(CXX) $(CXXFLAGS) $(SRC) $(LFLAGS) -o $(EXEDIR)/$(EXE)

release:
ifeq ($(IS_ARM),1)
	$(CXX) $(RFLAGS) $(SRC) -march=native $(LFLAGS) -o $(EXEDIR)/$(EXE)-native
else
	$(CXX) $(RFLAGS) $(SRC) -mbmi2 -mavx2 -mpopcnt $(LFLAGS) -o $(EXEDIR)/$(EXE)-bmi2
	$(CXX) $(RFLAGS) $(SRC) -msse4.2 -msse4.1 -mssse3 -mpopcnt $(LFLAGS) -o $(EXEDIR)/$(EXE)-modern
	$(CXX) $(RFLAGS) $(SRC) -mssse3 -mno-popcnt $(LFLAGS) -o $(EXEDIR)/$(EXE)-ssse3
endif

$(shell mkdir -p $(EXEDIR))