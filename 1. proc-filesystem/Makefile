CXX = g++

# On Ubuntu VM C++17 works fine, but on matrix I had to use C++11
CXXFLAGS = -Wall -Wextra -std=c++17

TARGET = main
SRCS = main.cpp utils.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)