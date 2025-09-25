CC := gcc
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
TARGET := $(BUILD_DIR)/variables_and_data_types.exe

SRCS_RAW := $(shell find . -name '*.c')
SRCS := $(patsubst ./%,%,$(SRCS_RAW))
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

INCLUDE_DIRS := . \
    components \
	components/peripherals \
    components/drivers \
    components/sensors \
    components/utils \
    modes

CPPFLAGS := $(addprefix -I,$(INCLUDE_DIRS))
CFLAGS ?= -Wall -Wextra #-std=c11

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
