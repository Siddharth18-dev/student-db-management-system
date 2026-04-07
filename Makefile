CXX = g++
CXXFLAGS = -std=c++17 -MMD -MP

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
BIN_DIR = bin
INSTALL_DIR = install/bin

# ================================
# Build Type (debug/release)
# ================================
BUILD_TYPE ?= release

ifeq ($(BUILD_TYPE), debug)
    CXXFLAGS += -g -O0
    BUILD_SUBDIR = debug
else
    CXXFLAGS += -O2
    BUILD_SUBDIR = release
endif

# ================================
# Source Files
# ================================
ALL_SRCS = $(shell find $(SRC_DIR) -name "*.cpp")

# Separate main.cpp
MAIN_SRC = $(SRC_DIR)/main.cpp
LIB_SRCS = $(filter-out $(MAIN_SRC), $(ALL_SRCS))

TEST_SRCS = $(shell find $(TEST_DIR) -name "*.cpp")

# ================================
# Object Files
# ================================
APP_OBJS = $(MAIN_SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/$(BUILD_SUBDIR)/%.o) \
           $(LIB_SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/$(BUILD_SUBDIR)/%.o)

LIB_OBJS = $(LIB_SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/$(BUILD_SUBDIR)/%.o)

TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/$(BUILD_SUBDIR)/tests/%.o)

DEPS = $(APP_OBJS:.o=.d) $(TEST_OBJS:.o=.d)

# ================================
# Targets
# ================================
APP_BIN = $(BIN_DIR)/StudentDBSystem
TEST_BIN = $(BIN_DIR)/test_runner

# ================================
# Build Application
# ================================
app: $(APP_OBJS)
	@echo "Building Application [$(BUILD_TYPE)]..."
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(APP_BIN)

# ================================
# Run Application
# ================================
run: app install
	@echo "Running Application..."
	./$(INSTALL_DIR)/StudentDBSystem

# ================================
# Install
# ================================
install: app
	@mkdir -p $(INSTALL_DIR)
	cp $(APP_BIN) $(INSTALL_DIR)

# ================================
# Test (Google Test)
# ================================
TEST_LIBS = -lgtest -lgtest_main -pthread

test: $(TEST_OBJS) $(LIB_OBJS)
	@echo "Building Tests [$(BUILD_TYPE)]..."
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(TEST_BIN) $(TEST_LIBS)

	@echo "Running Tests..."
	./$(TEST_BIN)

# ================================
# Compile Rules
# ================================
$(BUILD_DIR)/$(BUILD_SUBDIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/$(BUILD_SUBDIR)/tests/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ================================
# Clean
# ================================
clean:
	rm -rf build bin

-include $(DEPS)

.PHONY: app run install test clean