# Makefile

EXE := Lux
SRC := *.cpp
CXX := g++

EXEDIR := executables

# Default flags
LFLAGS := 
WFLAGS := -Wall -Wextra -Werror
CXXFLAGS := -std=c++20 $(WFLAGS) -O3 -DNDEBUG -flto
RFLAGS := -std=c++20 -O3 -DNDEBUG

# Platform-specific flags and libraries
ifeq ($(OS),Windows_NT)
    # Windows-specific flags and settings
    LFLAGS := 
    CXXFLAGS := $(CXXFLAGS) -DWIN32
    RFLAGS := $(RFLAGS) -static
    EXEDIR := $(EXEDIR)
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
endif

default:
	$(CXX) $(CXXFLAGS) $(SRC) $(LFLAGS) -o $(EXEDIR)/$(EXE)

release:
	$(CXX) $(RFLAGS) $(SRC) -mbmi2 -mavx2 -mpopcnt $(LFLAGS) -o $(EXEDIR)/$(EXE)-bmi2
	$(CXX) $(RFLAGS) $(SRC) -msse4.2 -msse4.1 -mssse3 -mpopcnt $(LFLAGS) -o $(EXEDIR)/$(EXE)-modern 
	$(CXX) $(RFLAGS) $(SRC) -mssse3 -mno-popcnt $(LFLAGS) -o $(EXEDIR)/$(EXE)-ssse3

$(shell mkdir $(EXEDIR))