# Compilers
CXX       ?= g++
CROSS     ?= aarch64-linux-gnu-
CXXFLAGS  := -Wall -Wextra -std=c++17 -O2 -MMD -MP

# Sources
SRC = main.cpp Map.cpp Player.cpp Game.cpp

# Host build
OBJ_HOST = $(SRC:.cpp=.o)
DEP_HOST = $(OBJ_HOST:.o=.d)
TARGET_HOST = sokoban

all: $(TARGET_HOST)

$(TARGET_HOST): $(OBJ_HOST)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEP_HOST)

# Cross-compile for aarch64
OBJ_AARCH64 = $(SRC:.cpp=_aarch64.o)
DEP_AARCH64 = $(OBJ_AARCH64:.o=.d)
TARGET_AARCH64 = sokoban-aarch64

$(TARGET_AARCH64): $(OBJ_AARCH64)
	$(CROSS)g++ $(CXXFLAGS) $^ -o $@

%_aarch64.o: %.cpp
	$(CROSS)g++ $(CXXFLAGS) -c $< -o $@

-include $(DEP_AARCH64)

clean:
	rm -f $(OBJ_HOST) $(DEP_HOST) $(TARGET_HOST)
	rm -f $(OBJ_AARCH64) $(DEP_AARCH64) $(TARGET_AARCH64)

.PHONY: all clean
