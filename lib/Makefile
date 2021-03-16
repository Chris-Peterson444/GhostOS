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
OS_INC_DIR = ./../os-base/include
NLIB_SRC_DIR = ./../os-base/src/NewLibInterface

DEBUG_MODE=TRUE

ifdef DEBUG_MODE
DEFINES  += -DDEBUG
CFLAGS   += -O0 -g -ggdb
#LDFLAGS  += -Wl,-no_pie
else 
CFLAGS   += -O3
endif

LDFILE   = riscv32-console.ld
INCLUDE  += -I $(INC_DIR) -I $(OS_INC_DIR)
ARFLAGS  = -cvq


TARGET_NAME = libghostutil.a 

TARGET_OBJS =  $(OBJ_DIR)/GraphicUtil.o \
			   $(OBJ_DIR)/SystemUtil.o

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
				$(OBJ_DIR)/stat.o               \
				$(OBJ_DIR)/times.o              \
				$(OBJ_DIR)/unlink.o             \
				$(OBJ_DIR)/wait.o               \
				$(OBJ_DIR)/write.o              \
				$(OBJ_DIR)/sbrk.o               

ALL_OBJS = $(TARGET_OBJS) $(NEWLIB_OBJS)

all: directories $(BIN_DIR)/$(TARGET_NAME)

$(BIN_DIR)/$(TARGET_NAME): $(ALL_OBJS)
	$(AR) $(ARFLAGS) $(BIN_DIR)/$(TARGET_NAME) $(ALL_OBJS)

# Build all assembly files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDE) -c $< -o $@

# Build all C files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDE) -c $< -o $@

# Build all cpp files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) $(DEFINES) $(INCLUDE) -c $< -o $@

# Build NewLibInterface files
$(OBJ_DIR)/%.o: $(NLIB_SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDE) -c $< -o $@

directories: $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)
	
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)