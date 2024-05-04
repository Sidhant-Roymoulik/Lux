# From Bit-Genie

EXE := Lux
SRC := *.cpp
CXX := g++

EXEDIR := executables

LFLAGS   := -Wl,--whole-archive -lpthread -Wl,--no-whole-archive
WFLAGS   := -Wall -Wextra -Werror
CXXFLAGS := -std=c++20 $(WFLAGS) -O3 -DNDEBUG -flto -march=native
RFLAGS   := -std=c++20 -O3 -DNDEBUG -static 

default:
	$(CXX) $(CXXFLAGS) $(SRC) $(LFLAGS) -o $(EXEDIR)/$(EXE) 

release:
	$(CXX) $(RFLAGS) $(SRC) -mbmi2 -mavx2 -mpopcnt $(LFLAGS) -o $(EXEDIR)/$(EXE)-bmi2
	$(CXX) $(RFLAGS) $(SRC) -msse4.2 -msse4.1 -mssse3 -mpopcnt $(LFLAGS) -o $(EXEDIR)/$(EXE)-modern 
	$(CXX) $(RFLAGS) $(SRC) -mssse3 -mno-popcnt $(LFLAGS) -o $(EXEDIR)/$(EXE)-ssse3