CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Iinclude

SRC_DIR := src
BIN := ssd_simulator

SRCS := $(SRC_DIR)/main.cpp \
        $(SRC_DIR)/ssd_state.cpp \
        $(SRC_DIR)/ftl_gc.cpp \
        $(SRC_DIR)/ftl_write.cpp \
        $(SRC_DIR)/progress.cpp \
        $(SRC_DIR)/trace.cpp

OBJS := $(SRCS:.cpp=.o)

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean run
clean:
	rm -f $(OBJS) $(BIN)

run: $(BIN)
	./$(BIN)

