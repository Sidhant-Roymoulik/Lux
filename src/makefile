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
    # Using cmd.exe for Windows commands
    MKDIR := cmd /c if not exist "$(EXEDIR)" mkdir "$(EXEDIR)"
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
    MKDIR := mkdir -p $(EXEDIR)
endif

# Directory creation
create_dir:
	$(MKDIR)

default: create_dir
	$(CXX) $(CXXFLAGS) $(SRC) $(LFLAGS) -o $(EXEDIR)/$(EXE)

release: create_dir
	$(CXX) $(RFLAGS) $(SRC) -mbmi2 -mavx2 -mpopcnt $(LFLAGS) -o $(EXEDIR)/$(EXE)-bmi2
	$(CXX) $(RFLAGS) $(SRC) -msse4.2 -msse4.1 -mssse3 -mpopcnt $(LFLAGS) -o $(EXEDIR)/$(EXE)-modern 
	$(CXX) $(RFLAGS) $(SRC) -mssse3 -mno-popcnt $(LFLAGS) -o $(EXEDIR)/$(EXE)-ssse3