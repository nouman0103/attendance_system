# Makefile for Windows using MSYS2 MinGW-w64 and g++

# Compiler and Linker
CXX := g++
LINKER := g++

# Compiler Flags
CXXFLAGS := -g -Wall  -D_WINDOWS -D_UNICODE -D__WXMSW__ -DNDEBUG -DNOPCH -std=c++11

# Include Directories
INCLUDES := -Idep/win/lib/gcc_lib/mswu \
           -Idep/win/include \
           -Iinclude \
           -Iinclude/panels

# Library Directories
LIBDIRS := -Ldep/win/lib/gcc_lib \
          -Lc:/mingw-w64/mingw64/x86_64-w64-mingw32/lib

# Libraries to Link
LIBS := -lwxmsw32u_core -lwxbase32u -lwxpng -lcomdlg32 \
       -lgdi32 -lcomctl32 -lole32 -loleaut32 -ldmoguids \
       -luuid -lwinspool -lz -lwxregexu -lwxzlib \
       -luxtheme -loleacc -lshlwapi -lversion

# Source and Output Directories
SRC_DIR := src
OUT_DIR := out

# Find all .cpp files in src directory and subdirectories using Make's wildcard
SOURCES := $(wildcard $(SRC_DIR)/*.cpp) \
           $(wildcard $(SRC_DIR)/panels/*.cpp) \
           $(wildcard $(SRC_DIR)/*/*/*.cpp)

# Generate object file paths by replacing src/ with out/ and .cpp with .o
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(OUT_DIR)/%.o, $(SOURCES))

# Target Executable
TARGET := $(OUT_DIR)/myapp.exe

# Phony Targets
.PHONY: all init compile link clean

# Default Target
all: init compile link

# Initialize build environment
init:
	@if not exist "$(OUT_DIR)" mkdir "$(OUT_DIR)"

# Compile all .cpp files to .o
compile: $(OBJECTS)

# Link all object files into the executable
link: $(TARGET)

# Pattern rule to compile .cpp to .o
$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c "$<" -o "$@"

# Link object files to create the executable
$(TARGET): $(OBJECTS)
	$(LINKER) $(CXXFLAGS) -mwindows -static $(OBJECTS) -o "$@" $(LIBDIRS) $(LIBS)

# Clean build artifacts
clean:
	del /Q /S "$(OUT_DIR)\*.o" "$(TARGET)"
	
