CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall

SRC := src/main.cpp src/User.cpp src/TimeEntry.cpp src/CsvStorage.cpp
BIN := bin/time-tracker

all: $(BIN)

$(BIN): $(SRC)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRC)

clean:
	rm -rf bin