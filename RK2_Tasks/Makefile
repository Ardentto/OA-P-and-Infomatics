CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = bank_system
SOURCES = bank_system.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run