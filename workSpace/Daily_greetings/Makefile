# CONFIGURATION

ARGS ?=

## Main modules

TARGET = greetings

BUILD_DIR = build

INC_DIR = inc
SRC_DIR = src

OUTPUT_RELEASE_DIR = $(BUILD_DIR)/release
OUTPUT_DEVELOP_DIR = $(BUILD_DIR)/develop

CFLAGS = -Wall -Wextra -std=c99
CFLAGS_REL = $(CFLAGS) -O2 -DNDEBUG
CFLAGS_DEV = $(CFLAGS) -g

IFLAGS = $(addprefix -I, $(INC_DIR))

SRCS = $(foreach dir,$(SRC_DIR),$(wildcard $(dir)/*.c))
OBJS_DEV = $(patsubst %.c,%.o,$(addprefix $(OUTPUT_DEVELOP_DIR)/,$(notdir $(SRCS))))
OBJS_REL = $(patsubst %.c,%.o,$(addprefix $(OUTPUT_RELEASE_DIR)/,$(notdir $(SRCS))))

## Unity Library

UNITY_PROJ_DIR = ../../Unity

UNITY_BUILD_DIR = $(BUILD_DIR)/unity
UNITY_INC_DIR = $(UNITY_PROJ_DIR)/src \
				$(UNITY_PROJ_DIR)/extras/fixture/src \
				$(UNITY_PROJ_DIR)/extras/memory/src \
				inc
UNITY_SRC_DIR = $(UNITY_PROJ_DIR)/src \
				$(UNITY_PROJ_DIR)/extras/fixture/src \
				$(UNITY_PROJ_DIR)/extras/memory/src

UNITY_SRCS = $(foreach dir,$(UNITY_SRC_DIR),$(wildcard $(dir)/*.c))
UNITY_OBJS = $(patsubst %.c,%.o,$(addprefix $(UNITY_BUILD_DIR)/,$(notdir $(UNITY_SRCS))))

UNITY_IFLAGS = $(addprefix -I, $(UNITY_INC_DIR))
UNITY_CFLAGS = 

## Test - GENERAL

CUT_INC_DIR = inc
CUT_SRC_DIR = src

CUT_SRCS = $(filter-out %main.c, $(foreach dir,$(CUT_SRC_DIR),$(wildcard $(dir)/*c)))
CUT_OBJS = $(patsubst %.c,%.o,$(addprefix $(TEST_BUILD_DIR)/,$(notdir $(CUT_SRCS))))

CUT_IFLAGS = $(addprefix -I, $(CUT_INC_DIR))

TEST_BUILD_DIR = $(BUILD_DIR)/tests/general
TEST_INC_DIR = $(UNITY_INC_DIR)
TEST_SRC_DIR = tests/MoonPhase \
			   tests

TEST_SRCS = $(foreach dir,$(TEST_SRC_DIR),$(wildcard $(dir)/*c))
TEST_OBJS = $(patsubst %.c,%.o,$(addprefix $(TEST_BUILD_DIR)/,$(notdir $(TEST_SRCS)))) $(CUT_OBJS)

TEST_IFLAGS = $(addprefix -I, $(TEST_INC_DIR)) $(CUT_IFLAGS)
TEST_CFLAGS = -Wall -Wextra -g -std=c99

## Compiler

CC = clang

DEPFLAGS = -MMD -MP

## Search patterns

vpath %.c $(TEST_SRC_DIR) $(UNITY_SRC_DIR) $(SRC_DIR)

# RECIPES

## Executable recipe

.PHONY: all
all: rel test

# TARGET RELEASE

$(OUTPUT_RELEASE_DIR):
	@echo "[INFO] Creating build directory"
	@mkdir -p $@

$(OUTPUT_RELEASE_DIR)/$(TARGET): $(OBJS_REL)
	@echo "[INFO] Generating executable"
	$(CC) $^ -o $@

$(OUTPUT_RELEASE_DIR)/%.o:%.c | $(OUTPUT_RELEASE_DIR)
	@echo "[INFO] Generating object files"
	$(CC) -c $(DEPFLAGS) $(IFLAGS) $(CFLAGS_REL) $< -o $@

# TARGET DEVELOPMENT

$(OUTPUT_DEVELOP_DIR):
	@echo "[INFO] Creating build directory"
	@mkdir -p $@

$(OUTPUT_DEVELOP_DIR)/$(TARGET)-dev: $(OBJS_DEV)
	@echo "[INFO] Generating executable"
	$(CC) $^ -o $@

$(OUTPUT_DEVELOP_DIR)/%.o:%.c | $(OUTPUT_DEVELOP_DIR)
	@echo "[INFO] Generating object files"
	$(CC) -c $(DEPFLAGS) $(IFLAGS) $(CFLAGS_DEV) $< -o $@

## Unity static library 

$(UNITY_BUILD_DIR):
	@echo "[INFO] Creating build directory"
	@mkdir -p $(UNITY_BUILD_DIR)

$(UNITY_BUILD_DIR)/libunity.a: $(UNITY_OBJS)
	@echo "[INFO] Creating unity static library"
	ar rcs $@ $^
	ranlib $@

$(UNITY_BUILD_DIR)/%.o:%.c | $(UNITY_BUILD_DIR)
	@echo "[INFO] Generating object files"
	$(CC) -c $(DEPFLAGS) $(UNITY_IFLAGS) $(UNITY_CFLAGS) $< -o $@

## Tests - General

$(TEST_BUILD_DIR):
	@echo "[INFO] Creating build directory"
	@mkdir -p $(TEST_BUILD_DIR)

$(TEST_BUILD_DIR)/AllTests: $(TEST_OBJS) $(UNITY_BUILD_DIR)/libunity.a
	@echo "[INFO] Generating test executable"
	$(CC) $^ -o $@

$(TEST_BUILD_DIR)/%.o:%.c | $(TEST_BUILD_DIR)
	@echo "[INFO] Generating object files"
	$(CC) -c $(DEPFLAGS) $(TEST_IFLAGS) $(TEST_CFLAGS) $< -o $@

## Helper recepies

.PHONY: help
help:
	@echo "Available recepies:"
	@echo "   test    - Execute all tests"
	@echo "   rel     - Create release executable"
	@echo "   dev     - Create development executable"
	@echo "   debug   - Debug development executable"
	@echo "   clean   - Remove build directory"
	@echo "   run     - Execute dev binary"
	@echo "   install - Install executable"

.PHONY: rel
rel: $(OUTPUT_RELEASE_DIR)/$(TARGET)

.PHONY: dev
dev: $(OUTPUT_DEVELOP_DIR)/$(TARGET)-dev

.PHONY: debug
debug: $(OUTPUT_DEVELOP_DIR)/$(TARGET)-dev
	gdb $(OUTPUT_DEVELOP_DIR)/$(TARGET)-dev

.PHONY: clean
clean:
	@echo "[INFO] Cleaning build directory"
	@rm -rf $(BUILD_DIR)

.PHONY: test
test: $(TEST_BUILD_DIR)/AllTests
	@echo "[INFO] Executing tests - General"
	@$(TEST_BUILD_DIR)/AllTests -v

.PHONY: run
run: $(OUTPUT_DEVELOP_DIR)/$(TARGET)-dev
	@$< $(ARGS)

.PHONY: install
install: $(OUTPUT_RELEASE_DIR)/$(TARGET)
	@echo "[INFO] Creating bin folder in home folder"
	mkdir -p ~/bin
	@echo "[INFO] Copying executable to bin folder"
	cp $< ~/bin

-include $(OBJS_REL:.o=.d) $(OBJS_DEV:.o=.d) $(TEST_OBJS:.o=.d) $(UNITY_OBJS:.o=.d)