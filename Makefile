TARGET_EXEC := main.out

BUILD_DIR := ./build
SRC_DIR := ./src
LIB_DIR := ./lib

LIB_NAME := libvec3.a
LIB_SRC := $(SRC_DIR)/vec3.c
LIB_OBJ := $(BUILD_DIR)/vec3.o

SRCS := $(shell find $(SRC_DIR) -name '*.c' ! -name 'vec3.c')
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPP_FLAGS := $(INC_FLAGS)
CFLAGS := -Wall -Wpedantic -Wextra -std=gnu23 -O3
LTO_FLAGS := -flto

VERBOSE := 0
ifeq ($(VERBOSE), 1)
	V :=
else
	V := @
endif

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS) $(LIB_DIR)/$(LIB_NAME)
	@echo "Linking executable: $@"
	$(V)$(CC) $(LTO_FLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.c
	@echo "Compiling: $<"
	$(V)mkdir -p $(dir $@)
	$(V)$(CC) $(CPP_FLAGS) $(CFLAGS) -c $< -o $@

$(LIB_DIR)/$(LIB_NAME): $(LIB_OBJ)
	@echo "Creating static library:  $<"
	$(V)mkdir -p $(dir $@)
	$(V)ar rcs $@ $^

$(LIB_OBJ): $(LIB_SRC)
	@echo "Compiling library source: $<"
	$(V)mkdir -p $(dir $@)
	$(V)$(CC) $(CPP_FLAGS) $(CFLAGS) $(LTO_FLAGS) -c $< -o  $@

.PHONY: clean
clean:
	@echo "Cleaning build files..."
	$(V)rm -r $(BUILD_DIR) $(LIB_DIR)

.PHONY: verbose
verbose:
	@$(MAKE) VERBOSE=1
