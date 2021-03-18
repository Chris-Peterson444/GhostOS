TOOLPREFIX=riscv32-unknown-elf-
AR=$(TOOLPREFIX)ar
AS=$(TOOLPREFIX)as
CC=$(TOOLPREFIX)gcc
CPP=$(TOOLPREFIX)cpp
CXX=$(TOOLPREFIX)g++
LD=$(TOOLPREFIX)ld
OBJCOPY=$(TOOLPREFIX)objcopy
OBJDUMP=$(TOOLPREFIX)objdump
STRIP=$(TOOLPREFIX)strip

INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin
LIB_DIR = ./../lib
GHOST_LIB_DIR = $(LIB_DIR)/bin
GHOST_LIB_INC_DIR = $(LIB_DIR)/include/
LIB_OBJS_DIR = $(LIB_DIR)/obj

# LIB_OBJS =

DEBUG_MODE=True

ifdef DEBUG_MODE
DEFINES  += -DDEBUG
CFLAGS   += -O0 -g -ggdb
#LDFLAGS  += -Wl,-no_pie
LIBFLAGS +=
LIB_OBJS = $(addprefix $(LIB_OBJS_DIR)/, $(shell ls $(LIB_OBJS_DIR)/))
else 
CFLAGS   += -O3
LIBFLAGS = -L$(GHOST_LIB_DIR) -lghostutil
endif

LDFILE   = riscv32-console.ld
INCLUDE  += -I $(INC_DIR) -I $(GHOST_LIB_INC_DIR)
CFLAGS   += -ffreestanding  -nostartfiles
# CFLAGS   += -ffreestanding  -nostartfiles -nostdlib -nodefaultlibs
LDFLAGS  +=
LDFLAGS  += -Wl,--gc-sections -Wl,-T,$(LDFILE)


TARGET_NAME = application-test

LIB_TARGETS = library

TARGET_OBJS =   $(OBJ_DIR)/main.o               \
                $(OBJ_DIR)/crt0.o               \
                $(OBJ_DIR)/interrupt.o          \
                $(OBJ_DIR)/startup.o            \
                $(OBJ_DIR)/sbrk.o   

ALL_OBJS = $(LIB_OBJS) $(TARGET_OBJS)            

all: directories $(LIB_TARGETS) $(BIN_DIR)/$(TARGET_NAME)

$(BIN_DIR)/$(TARGET_NAME): $(ALL_OBJS)
	$(CC) $(ALL_OBJS) $(LIBFLAGS) -o $(BIN_DIR)/$(TARGET_NAME) $(CFLAGS) $(DEFINES) $(LDFLAGS) 
	$(STRIP) $(BIN_DIR)/$(TARGET_NAME) -o $(BIN_DIR)/$(TARGET_NAME).strip

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDE) -c $< -o $@

# $$(LIB_OBJS): library

# Compiling library files for debug mode
library:
	@cd $(LIB_DIR) && $(MAKE)
	
directories: $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)
	
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)