# engine name
EXE      :=  Lux
CXXFLAGS := -O3 -std=c++20 -Wall -Wextra -pedantic -DNDEBUG -flto
CXX      := g++
SUFFIX   :=

ifeq ($(native),1)
    CXXFLAGS += -march=native
endif

# Detect Windows
ifeq ($(OS), Windows_NT)
    SUFFIX   := .exe
    CXXFLAGS += -static
    CXXFLAGS += -fuse-ld=lld
else
    DETECTED_OS := $(shell uname -s)
    ifneq (,$(findstring g++,$(shell $(CXX) --version)))
        ifneq ($(DETECTED_OS),Darwin)
            CXXFLAGS += -fuse-ld=lld
        endif
    endif
	CXXFLAGS += -pthread

endif

OUT     := $(EXE)$(SUFFIX)
SOURCES := $(wildcard *.cpp)
DEPENDS := $(patsubst %.cpp,%.d,$(SOURCES))

all: $(EXE)

$(EXE) : $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SOURCES)

clean:
	rm -rf *.o $(DEPENDS)