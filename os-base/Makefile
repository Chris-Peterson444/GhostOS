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
# LIB_DIR = ./lib/build_newlib

DEBUG_MODE=TRUE

ifdef DEBUG_MODE
DEFINES  += -DDEBUG
CFLAGS   += -O0 -g -ggdb
#LDFLAGS  += -Wl,-no_pie
else 
CFLAGS   += -O3
endif

LDFILE   = riscv32-console.ld
# INCLUDE  += -I $(INC_DIR) -L $(LIB_DIR)
INCLUDE  += -I $(INC_DIR)
CFLAGS   += -ffreestanding  -nostartfiles
# CFLAGS   += -ffreestanding  -nostartfiles -nostdlib -nodefaultlibs
LDFLAGS  +=
LDFLAGS  += -Wl,--gc-sections -Wl,-T,$(LDFILE)

TARGET_NAME = ghostOS

STARTUP_OBJS = 	$(OBJ_DIR)/main.o               \
                $(OBJ_DIR)/crt0.o               \
                $(OBJ_DIR)/interrupt.o          \
                $(OBJ_DIR)/startup.o            \
                $(OBJ_DIR)/InterruptHandler.o   \
                $(OBJ_DIR)/TimerISR.o           \
                $(OBJ_DIR)/Threads.o

SYSCALL_OBJS =  $(OBJ_DIR)/Syscalls.o

HARDWARE_OBJS = $(OBJ_DIR)/VideoControllerUtility.o

NEWLIB_OBJS =   $(OBJ_DIR)/close.o              \
				$(OBJ_DIR)/environ.o            \
				$(OBJ_DIR)/execve.o             \
				$(OBJ_DIR)/fork.o               \
				$(OBJ_DIR)/fstat.o              \
				$(OBJ_DIR)/getpid.o             \
				$(OBJ_DIR)/isatty.o             \
				$(OBJ_DIR)/kill.o               \
				$(OBJ_DIR)/link.o               \
				$(OBJ_DIR)/lseek.o              \
				$(OBJ_DIR)/open.o               \
				$(OBJ_DIR)/read.o               \
				$(OBJ_DIR)/sbrk.o               \
				$(OBJ_DIR)/stat.o               \
				$(OBJ_DIR)/times.o              \
				$(OBJ_DIR)/unlink.o             \
				$(OBJ_DIR)/wait.o               \
				$(OBJ_DIR)/write.o

TARGET_OBJS =   $(STARTUP_OBJS) $(SYSCALL_OBJS) $(HARDWARE_OBJS) $(NEWLIB_OBJS)

all: directories $(BIN_DIR)/$(TARGET_NAME)

$(BIN_DIR)/$(TARGET_NAME): $(TARGET_OBJS)
	$(CC) $(TARGET_OBJS) -o $(BIN_DIR)/$(TARGET_NAME) $(CFLAGS) $(DEFINES) $(LDFLAGS) 
	$(STRIP) $(BIN_DIR)/$(TARGET_NAME) -o $(BIN_DIR)/$(TARGET_NAME).strip

# Build all assembly files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDE) -c $< -o $@

# Build all C files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDE) -c $< -o $@

# Build all cpp files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) $(DEFINES) $(INCLUDE) -c $< -o $@

# Build all newlib interface files
$(OBJ_DIR)/%.o: $(SRC_DIR)/NewLibInterface/%.c
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDE) -c $< -o $@


directories: $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)
	
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)