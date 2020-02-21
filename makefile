TARGET = ./build/main.out
CXX = g++ -std=c++17
CXXFLAGS = -Wall -Wextra -Werror -g3

HDRS = \
	   include

SRC_PATH = \
		   src

SRCS = \
	   $(SRC_PATH)/main.cpp \
	   $(SRC_PATH)/text.cpp \
	   
.PHONY: all clean

all: $(SRCS)
	$(CXX) $(CXXFLAGS) $(addprefix -I,$(HDRS)) -o $(TARGET) $(CXXFLAGS) $(SRCS)

clean:
	rm -rf $(TARGET)

