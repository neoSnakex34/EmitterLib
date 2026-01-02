

# variables
CXX = g++
CXXFLAGS = -O2 -std=c++11 -Wall -Wextra -pedantic -g 

INCLUDE_DIRS = ./

TARGET = main

SRC = main.cpp

OBJ = $(SRC:.cpp=.o)

$(TARGET) : $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

