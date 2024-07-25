# Makefile for rebuilding decompiled GT2 artifacts
# Based on martinbean/thunder makefile from 2024-07-08

# Build options
VERSION := gt2_us12_simdisk
BASEPATH := config/$(VERSION)
BASEEXE := $(BASEPATH)/orig_bin/SCUS_944.88
BASEOVL := $(BASEPATH)/orig_bin/GT2.OVL
TARGET := scus_944.88
TARGETS := $(TARGET_MAIN) $(TARGET_OVR)
TARGET_MAIN := scus_944.88
TARGET_OVR := gt2_0
TARGET_LBL := mainexe
TARGET_MAIN_LBL := mainexe
TARGET_OVR_LBL := ovr
COMPARE ?= 1
NON_MATCHING ?= 0
VERBOSE ?= 0
BUILD_DIR ?= build

# Fail early if baserom does not exist
ifeq ($(wildcard $(BASEEXE)),)
$(error Baserom `$(BASEEXE)' not found.)
endif

# NON_MATCHING=1 implies COMPARE=0
ifeq ($(NON_MATCHING),1)
override COMPARE=0
endif

ifeq ($(VERBOSE),0)
V := @
endif

ifeq ($(OS),Windows_NT)
  DETECTED_OS=windows
else
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
    DETECTED_OS=linux
  endif
  ifeq ($(UNAME_S),Darwin)
    DETECTED_OS=macos
    MAKE=gmake
    CPPFLAGS += -xc++
  endif
endif

### Output ###

EXE          := $(BUILD_DIR)/$(TARGET).EXE
ELF          := $(BUILD_DIR)/$(TARGET).elf
LD_SCRIPT    := $(TARGET).ld
LD_MAP       := $(BUILD_DIR)/$(TARGET).map

### Tools ###

PYTHON     := python3
SPLAT_YAML := config/$(VERSION)/$(TARGET).yaml
SPLAT      := splat split $(SPLAT_YAML)
OVL_SPLIT  := $(PYTHON) tools/GTModTools/ovl.py unpack -o $(BASEPATH)/bin $(BASEOVL)
DIFF       := diff
MASPSX     := $(PYTHON) tools/maspsx/maspsx.py --aspsx-version=2.81 -G4096

CROSS    := mips-linux-gnu-
AS       := $(CROSS)as -EL
LD       := $(CROSS)ld -EL
OBJCOPY  := $(CROSS)objcopy
STRIP    := $(CROSS)strip
CPP      := tools/gcc2.8.1-mipsel/cpp
CC       := tools/homebrew-psyq44/cc1

PRINT := printf '
 ENDCOLOR := \033[0m
 WHITE     := \033[0m
 ENDWHITE  := $(ENDCOLOR)
 GREEN     := \033[0;32m
 ENDGREEN  := $(ENDCOLOR)
 BLUE      := \033[0;34m
 ENDBLUE   := $(ENDCOLOR)
 YELLOW    := \033[0;33m
 ENDYELLOW := $(ENDCOLOR)
 PURPLE    := \033[0;35m
 ENDPURPLE := $(ENDCOLOR)
ENDLINE := \n'

### Compiler Options ###

ASFLAGS        := -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections
CFLAGS         := -O2 -G0 -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fgnu-linker -mgas -mgpOPT -mgpopt -msoft-float -gcoff -quiet
CPPFLAGS       := -Iinclude
LDFLAGS        := -T config/$(VERSION)/$(TARGET_LBL)_undefined_syms.txt -T config/$(VERSION)/autogen/$(TARGET_LBL)_undefined_funcs_auto.txt \
                  -T $(BUILD_DIR)/$(TARGET).ld -Map $(LD_MAP) --no-check-sections -nostdlib

ifeq ($(NON_MATCHING),1)
CPPFLAGS += -DNON_MATCHING
endif

### Sources ###

# Object files
OBJECTS := $(shell grep -E 'build.+\.o' $(BASEPATH)/autogen/$(LD_SCRIPT) -o)
OBJECTS := $(OBJECTS:build/%=$(BUILD_DIR)/%)
DEPENDS := $(OBJECTS:=.d)

### Targets ###

all: $(EXE)

-include $(DEPENDS)

clean:
	$(V)rm -rf $(BUILD_DIR)

distclean: clean
	$(V)rm -rf $(BASEPATH)/autogen
	$(V)rm -rf asm
	$(V)rm -rf assets
	$(V)rm -rf src/autogen/*
	$(V)rm -rf $(BASEPATH)/ovl_bin

setup: distclean split

split:
	$(V)$(PYTHON) build_gen.py > build.ninja
	$(V)ninja

# Compile .c files
$(BUILD_DIR)/%.c.o: %.c
	@$(PRINT)$(GREEN)Compiling C file: $(ENDGREEN)$(BLUE)$<$(ENDBLUE)$(ENDLINE)
	@mkdir -p $(shell dirname $@)
	$(V)$(CPP) $(CPPFLAGS) -lang-c $< | $(CC) $(CFLAGS) | $(MASPSX) | $(AS) $(ASFLAGS) -o $@

# Compile .s files
$(BUILD_DIR)/%.s.o: %.s
	@$(PRINT)$(GREEN)Assembling asm file: $(ENDGREEN)$(BLUE)$<$(ENDBLUE)$(ENDLINE)
	@mkdir -p $(shell dirname $@)
	$(V)$(AS) $(ASFLAGS) -o $@ $<

# Create .o files from .bin files.
$(BUILD_DIR)/%.bin.o: %.bin
	@$(PRINT)$(GREEN)objcopying binary file: $(ENDGREEN)$(BLUE)$<$(ENDBLUE)$(ENDLINE)
	@mkdir -p $(shell dirname $@)
	$(V)$(LD) -r -b binary -o $@ $<

$(BUILD_DIR)/$(LD_SCRIPT): $(BASEPATH)/autogen/$(LD_SCRIPT)
	@$(PRINT)$(GREEN)Preprocessing linker script: $(ENDGREEN)$(BLUE)$<$(ENDBLUE)$(ENDLINE)
	$(V)cp $(BASEPATH)/autogen/$(LD_SCRIPT) $(BUILD_DIR)/$(LD_SCRIPT)

# Link the .o files into the .elf
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) $(BUILD_DIR)/$(LD_SCRIPT)
	@$(PRINT)$(GREEN)Linking elf file: $(ENDGREEN)$(BLUE)$@$(ENDBLUE)$(ENDLINE)
	$(V)$(LD) $(LDFLAGS) -o $@

# Convert the .elf to the final exe
$(EXE): $(BUILD_DIR)/$(TARGET).elf
	@$(PRINT)$(GREEN)Creating EXE: $(ENDGREEN)$(BLUE)$@$(ENDBLUE)$(ENDLINE)
	$(V)$(OBJCOPY) $< $@ -O binary
#	$(V)$(OBJCOPY) -O binary --gap-fill 0x00 --pad-to 0x05BFE0 $< $@
ifeq ($(COMPARE),1)
	@$(DIFF) $(BASEEXE) $(EXE) && printf "OK\n" || (echo 'The build succeeded, but did not match the base EXE. This is expected if you are making changes to the game. To skip this check, use "make COMPARE=0".' && false)
endif

### Make Settings ###

.PHONY: all clean distclean setup split

# Remove built-in implicit rules to improve performance
MAKEFLAGS += --no-builtin-rules

# Print target for debugging
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
