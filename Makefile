CXX 		:= clang++-6.0
CXXFLAGS	:= -Wall -Werror
BUILD		:= ./Build
OBJ_DIR		:= $(BUILD)/Objects
DEP_DIR		:= $(BUILD)/Dependencies
EXE			:= tracer
INCLUDE		:= \
	-I ./Source \
	-I ./Source/BRDFS \
	-I ./Source/BTDFS \
	-I ./Source/Cameras \
	-I ./Source/GeometricObjects \
	-I ./Source/Lights \
	-I ./Source/Mappings \
	-I ./Source/Materials \
	-I ./Source/Samplers \
	-I ./Source/Textures \
	-I ./Source/Tracers \
	-I ./Source/Utilities \
	-I ./Source/World
SRC 		:= \
	$(wildcard Source/*.cpp) \
	$(wildcard Source/BRDFS/*.cpp) \
	$(wildcard Source/BTDFS/*.cpp) \
	$(wildcard Source/Cameras/*.cpp) \
	$(wildcard Source/GeometricObjects/*.cpp) \
	$(wildcard Source/Lights/*.cpp) \
	$(wildcard Source/Mappings/*.cpp) \
	$(wildcard Source/Materials/*.cpp) \
	$(wildcard Source/Samplers/*.cpp) \
	$(wildcard Source/Textures/*.cpp) \
	$(wildcard Source/Tracers/*.cpp) \
	$(wildcard Source/Utilities/*.cpp) \
	$(wildcard Source/World/*.cpp)
OBJECTS		:= $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(EXE)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(EXE): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(EXE) $(OBJECTS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
