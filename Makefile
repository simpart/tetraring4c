TARGET_EXEC ?= libtetraring.so
 
BUILD_DIR ?= ./bin
SRC_DIRS ?= ./src

CC   := gcc 
SRCS := $(shell find $(SRC_DIRS) -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
 
INC_DIRS := ./hdr
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
 
CFLAGS ?= $(INC_FLAGS) -O3 -Wall -Wextra -MMD -MP -shared -fPIC
 
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ 
 
# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
 
.PHONY: clean
 
clean:
	$(RM) -r $(BUILD_DIR)
 
-include $(DEPS)
 
MKDIR_P ?= mkdir -p
