TC_DIR := ..
include $(TC_DIR)/Makefile.platform

BIN_DIR := $(TC_DIR)/sdk/bin
BIN := slinky
all: $(BIN_DIR)/$(BIN)$(BIN_EXT)

INCLUDES += -Isrc
FLAGS += -g
WARNFLAGS := -Werror -Wall -Wno-uninitialized

# ABI header
SDK_INCLUDE := $(TC_DIR)/sdk/include
INCLUDES += -I$(SDK_INCLUDE)
FLAGS += -DNOT_USERSPACE

include Makefile.objs
DEPFILES := $(OBJS:.o=.d)

# Versioning
FLAGS += -DSDK_VERSION=$(shell git describe --tags)

# LLVM
FLAGS += -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS
CCFLAGS += -fno-rtti
INCLUDES += -I$(LLVM_INC)
LIBS += \
	$(LLVM_LIB)/libLLVMInstCombine.a \
	$(LLVM_LIB)/libLLVMipo.a \
	$(LLVM_LIB)/libLLVMipa.a \
	$(LLVM_LIB)/libLLVMLinker.a \
	$(LLVM_LIB)/libLLVMScalarOpts.a \
	$(LLVM_LIB)/libLLVMTransformUtils.a \
	$(LLVM_LIB)/libLLVMSelectionDAG.a \
	$(LLVM_LIB)/libLLVMAnalysis.a \
	$(LLVM_LIB)/libLLVMBitReader.a \
	$(LLVM_LIB)/libLLVMInterpreter.a \
	$(LLVM_LIB)/libLLVMExecutionEngine.a \
	$(LLVM_LIB)/libLLVMAsmPrinter.a \
	$(LLVM_LIB)/libLLVMCodeGen.a \
	$(LLVM_LIB)/libLLVMTarget.a \
	$(LLVM_LIB)/libLLVMAsmParser.a \
	$(LLVM_LIB)/libLLVMMCDisassembler.a \
	$(LLVM_LIB)/libLLVMMCParser.a \
	$(LLVM_LIB)/libLLVMMC.a \
	$(LLVM_LIB)/libLLVMCore.a \
	$(LLVM_LIB)/libLLVMSupport.a

# Platform LLVM deps
ifeq ($(BUILD_PLATFORM), windows32)
    LIBS += -limagehlp -lpsapi
endif
ifeq ($(BUILD_PLATFORM), Linux)
    LIBS += -ldl
endif

# Platform UUID deps
ifeq ($(BUILD_PLATFORM), windows32)
    LIBS += -lrpcrt4 -lws2_32
endif
ifeq ($(BUILD_PLATFORM), Linux)
    LIBS += -luuid
endif

# The DEBUG-ness of this build must match what LLVM was compiled with.
# Our libraries in deps are release builds, but if you want to set LLVM_LIB
# yourself, you can turn debugging back on.
#
# XXX: We'd love to use -O4 for link-time optimization on Mac OS, but it
#      seems to be broken on some people's machines still...

ifeq ($(DEBUG),)
	FLAGS += -DNDEBUG
	FLAGS += -O3 -fomit-frame-pointer
endif

# Automatic dependency generation (*.d files)
FLAGS += -MMD

CFLAGS += $(FLAGS) $(WARNFLAGS) $(INCLUDES)
CCFLAGS += $(FLAGS) $(WARNFLAGS) $(INCLUDES)
LDFLAGS += $(FLAGS) $(LIBS) $(LIB_STDCPP)

# Symbol table trimming
ifeq ($(BUILD_PLATFORM), Darwin)
	LDFLAGS += -Xlinker -unexported_symbol -Xlinker "*"
endif

# Disable implicit rules. Speeds up make, especially on Windows.
.SUFFIXES:

ifeq ($(BUILD_PLATFORM), windows32)
$(BIN_DIR)/$(BIN)$(BIN_EXT): $(OBJS)
	$(CC) -o "src/$(BIN)-d.exe" $(OBJS) $(LDFLAGS)
	strip -s "src/$(BIN)-d$(BIN_EXT)" -o "src/$(BIN)-stripped$(BIN_EXT)"
	rm -f "$(BIN_DIR)/$(BIN)$(BIN_EXT)"
	$(UPX) -o "$(BIN_DIR)/$(BIN)$(BIN_EXT)" "src/$(BIN)-stripped$(BIN_EXT)"
endif

ifeq ($(BUILD_PLATFORM), Linux)
$(BIN_DIR)/$(BIN): $(OBJS)
	$(CC) -o "src/$(BIN)-d" $(OBJS) $(LDFLAGS)
	strip -s "src/$(BIN)-d" -o "src/$(BIN)-stripped"
	rm -f "$(BIN_DIR)/$(BIN)"
	$(UPX) -o "$(BIN_DIR)/$(BIN)" "src/$(BIN)-stripped"
endif

ifeq ($(BUILD_PLATFORM), Darwin)
$(BIN_DIR)/$(BIN): $(OBJS)
	$(CC) -o src/$(BIN)-d $(OBJS) $(LDFLAGS)
	strip -o $(BIN_DIR)/$(BIN) src/$(BIN)-d
endif

%.o: %.cpp $(TABLES)
	$(CC) -c $(CCFLAGS) $*.cpp -o $*.o

%.o: %.c
	$(CC) -c $(CFLAGS) $*.c -o $*.o

.PHONY: clean

clean:
	rm -Rf $(BIN_DIR)/$(BIN)$(BIN_EXT) $(OBJS) $(DEPFILES) $(TABLES)

-include $(DEPFILES)
