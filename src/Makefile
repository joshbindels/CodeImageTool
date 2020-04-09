GCC=clang++
TARGET=APP
FLAGS=-std=c++14 -Iinclude
SRCS=src/*.cpp
HEADERS=include/*.hpp

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(GCC) -o $(TARGET) $(SRCS) $(FLAGS)
