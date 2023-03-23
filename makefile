CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRC = thread_pool.cpp test.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = test

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

thread_pool.o: thread_pool.cpp thread_pool.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test.o: test.cpp thread_pool.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)

