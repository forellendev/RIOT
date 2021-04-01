# Hey Emacs, this is a -*- makefile -*-
#
# General-purpose makefile for ATMEL XMEGA
##
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make coff = Convert ELF to AVR COFF (for use with AVR Studio 3.x or VMLAB).
#
# make extcoff = Convert ELF to AVR Extended COFF (for use with AVR Studio
#                4.07 or greater).
#
# make program = Download the hex file to the device, using avrdude.  Please
#                customize the avrdude settings below first!
#
# make filename.s = Just compile filename.c into the assembler code only
#
# To rebuild project do "make clean" then "make all".
#

# user defined values

PKG_NAME = rlwe


# MCU name

MCU = atxmega128a1
#MCU = avrxmega2

# Is this a bootloader?
MAKE_BOOTLOADER=no

# Only program boot section
# (XMega only)
# This will create a target-boot.hex file with the program relocated to
# address 0 and then program the file directly to the boot section.  It
# is faster than programming the entire application section with
# nothing and has the added advantage of leaving the application
# section in tact
# Note: ignored if MAKE_BOOTLOADER is not set
PROG_BOOT_ONLY=no

# CPU Frequency
F_CPU=32000000

# for xboot automated configuration - overrides MCU and F_CPU if present
-include xboot-config.mk

# Preprocessor define
DEFINES = -DF_CPU=$(F_CPU)L

# Output format. (can be srec, ihex, binary)
FORMAT = ihex
#FORMAT = srec

# Target file name (without extension)
TARGET = foo


# List C source files here. (C dependencies are automatically generated.)



RNG = ./crypto/rng/avr_trng.c
RNG += ./crypto/rng/aes_prng.c
RNG += ./crypto/rng/AES_driver.c

SAMPLER = ./crypto/sampler/cdf_sampler.c
SAMPLE_4093 =  ./crypto/p4093/sampler_4093.c
SAMPLE_4096 =  ./crypto/p4096/sampler_4096.c

KECCAK = ./crypto/keccak/Keccak-avr8.c
KECCAK += ./crypto/keccak/KeccakF-1600-avr8.c

#KECCAK = ./crypto/keccak/Keccak-compact8.c




KARATSUBA = ./crypto/p4093/ksuba_4093.c
KARATSUBA += ./crypto/p4096/ksuba_4096.c
SCHOOL =  ./crypto/p4093/school_4093.c
NTT = ./crypto/p7681/ntt_7681_256.c
NTT += ./crypto/p12289/ntt_12289_512.c



SRC_SHARED  = $(RNG) 
SRC_SHARED += $(SAMPLER) 
SRC_SHARED += $(SAMPLE_4093)
SRC_SHARED += $(SAMPLE_4096)
SRC_SHARED += $(KARATSUBA) 
SRC_SHARED += $(SCHOOL) 
SRC_SHARED += $(NTT)
SRC_SHARED += $(KECCAK)



SRC_4093 = $(SRC_SHARED)
SRC_4093 += instances/inst_4093.c


SRC_TEST = ./test/test.c
SRC_TEST += ./device/usart_driver.c 
SRC_TEST += ./device/clksys_driver.c 
SRC_TEST += $(SRC_SHARED)

SRC_KEYGEN = ./test/keygen.c
SRC_KEYGEN += ./device/usart_driver.c 
SRC_KEYGEN += ./device/clksys_driver.c 
SRC_KEYGEN += $(SRC_SHARED)

SRC_TEST_SAMPLER = ./test/test_sampler.c
SRC_TEST_SAMPLER += ./device/usart_driver.c 
SRC_TEST_SAMPLER += ./device/clksys_driver.c 
SRC_TEST_SAMPLER += $(SRC_SHARED)

SRC_PROFILING = $(SRC_SHARED)
SRC_PROFILING += ./device/usart_driver.c 
SRC_PROFILING += ./device/clksys_driver.c 
SRC_PROFILING += ./profiling/LWEProfiling.c
SRC_PROFILING += ./profiling/measureKaratsuba4093.c
SRC_PROFILING += ./profiling/measureKaratsuba4096.c
SRC_PROFILING += ./profiling/measureNTT_12289_512.c
SRC_PROFILING += ./profiling/measureNTT_7681_256.c
SRC_PROFILING += ./profiling/measure_reduction.c
SRC_PROFILING += ./profiling/measureSchoolbook_4093.c
SRC_PROFILING += ./profiling/profiling.c



# List Assembler source files here.
# Make them always end in a capital .S.  Files ending in a lowercase .s
# will not be considered source files but generated files (assembler
# output from the compiler), and will be deleted upon "make clean"!
# Even though the DOS/Win* filesystem matches both .s and .S the same,
# it will preserve the spelling of the filenames, and gcc itself does
# care about how the name is spelled on its command-line.

ASRC = ./crypto/p7681/mm7681.S
ASRC += ./crypto/p12289/mm12289.S
ASRC += ./crypto/p4093/math_asm_4093.S
ASRC += ./crypto/p4096/math_asm_4096.S
ASRC += ./device/measureRAM.S
ASRC += ./crypto/keccak/AVR8-rotate64.S
ASRC += ./crypto/keccak/Keccak-avr8-util.S
ASRC += ./profiling/mm24578.S

# Optimization level, can be [0, 1, 2, 3, s].
# 0 = turn off optimization. s = optimize for size.
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = s

# Debugging format.
# Native formats for AVR-GCC's -g are stabs [default], or dwarf-2.
# AVR (extended) COFF requires stabs, plus an avr-objcopy run.
DEBUG = stabs

# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
EXTRAINCDIRS =


# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD = -std=gnu99

# Place -D or -U options here
#CDEFS = -DBOOTSIZE=$(BOOTSIZE)
CDEFS = 

# Place -I options here
CINCS =


# Compiler flags.
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
COMMON_FLAGS = -g$(DEBUG)
COMMON_FLAGS += $(CDEFS) $(CINCS)
COMMON_FLAGS += -O$(OPT)
COMMON_FLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
COMMON_FLAGS += -ffunction-sections -fdata-sections
COMMON_FLAGS += -Wall
COMMON_FLAGS += -Wa,-adhlns=$(basename $<).lst
COMMON_FLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))

CFLAGS = $(COMMON_FLAGS)
CFLAGS += -Wstrict-prototypes
CFLAGS += $(CSTANDARD)
#CFLAGS += -flto
#CFLAGS += -fuse-linker-plugin
CXXFLAGS = $(COMMON_FLAGS)



# Assembler flags.
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -ahlms:    create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see avr-libc docs [FIXME: not yet described there]
ASFLAGS = -Wa,-adhlns=$(<:.S=.lst),-gstabs



#Additional libraries.

# Minimalistic printf version
#PRINTF_LIB_MIN = -Wl,-u,vfprintf -lprintf_min

# Floating point printf version (requires MATH_LIB = -lm below)
#PRINTF_LIB_FLOAT = -Wl,-u,vfprintf -lprintf_flt
PRINTF_LIB_FLOAT = -Wl,-u

PRINTF_LIB = $(PRINTF_LIB_MIN)

# Minimalistic scanf version
#SCANF_LIB_MIN = -Wl,-u,vfscanf -lscanf_min

# Floating point + %[ scanf version (requires MATH_LIB = -lm below)
SCANF_LIB_FLOAT = -Wl,-u

SCANF_LIB = $(SCANF_LIB_MIN)

MATH_LIB = -lm

# External memory options

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# used for variables (.data/.bss) and heap (malloc()).
#EXTMEMOPTS = -Wl,-Tdata=0x801100,--defsym=__heap_end=0x80ffff

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# only used for heap (malloc()).
#EXTMEMOPTS = -Wl,--defsym=__heap_start=0x801100,--defsym=__heap_end=0x80ffff

EXTMEMOPTS =

# Linker flags.
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDFLAGS = -Wl,-Map=$(TARGET).map,--cref
LDFLAGS += -Wl,--gc-sections
LDFLAGS += $(EXTMEMOPTS)
LDFLAGS += $(PRINTF_LIB) $(SCANF_LIB) $(MATH_LIB)





#---------------- Programming Options (avrdude) ----------------

# Programming hardware
# Type: avrdude -c ?
# to get a full listing.
#



# com1 = serial port. Use lpt1 to connect to parallel port.
AVRDUDE_PORT = usb    # programmer connected to serial device
AVRDUDE_PROGRAMMER = dragon_jtag

AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex
#AVRDUDE_WRITE_EEPROM = -U eeprom:w:$(TARGET).eep


# Uncomment the following if you want avrdude's erase cycle counter.
# Note that this counter needs to be initialized first using -Yn,
# see avrdude manual.
#AVRDUDE_ERASE_COUNTER = -y

# Uncomment the following if you do /not/ wish a verification to be
# performed after programming the device.
AVRDUDE_NO_VERIFY = -V

# Increase verbosity level.  Please use this when submitting bug
# reports about avrdude. See <http://savannah.nongnu.org/projects/avrdude>
# to submit bug reports.
#AVRDUDE_VERBOSE = -v -v

AVRDUDE_FLAGS = -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER)
AVRDUDE_FLAGS += $(AVRDUDE_NO_VERIFY)
AVRDUDE_FLAGS += $(AVRDUDE_VERBOSE)
AVRDUDE_FLAGS += $(AVRDUDE_ERASE_COUNTER)

# ---------------------------------------------------------------------------

# Processor definitions
MCU_S = $(subst atxmega,x,$(MCU))
ifneq ($(filter $(MCU_S), x16a4 x16d4 x16a4u),)
  BOOT_SECTION_START		=0x004000
endif
ifneq ($(filter $(MCU_S), x32a4 x32d4 x32a4u),)
  BOOT_SECTION_START		=0x008000
endif
ifneq ($(filter $(MCU_S), x64a1 x64a3 x64a4 x64d3 x64d4 x64a3u x64a4u x64b1 x64b3),)
  BOOT_SECTION_START		=0x010000
endif
ifneq ($(filter $(MCU_S), x128a1 x128a3 x128a4 x128d3 x128d4 x128a3u x128a4u x128b1 x128b3),)
  BOOT_SECTION_START		=0x020000
endif
ifneq ($(filter $(MCU_S), x192a1 x192a3 x192d3 x192a3u),)
  BOOT_SECTION_START		=0x030000
endif
ifneq ($(filter $(MCU_S), x256a1 x256a3 x256a3b x256d3 x256a3u x256a3bu),)
  BOOT_SECTION_START		=0x040000
endif

ifeq ($(MAKE_BOOTLOADER), yes)
# BOOT_SECTION_START (=Start of Boot Loader section
# in bytes - not words) as defined above.
LDFLAGS += -Wl,--section-start=.text=$(BOOT_SECTION_START)
endif

# ---------------------------------------------------------------------------

# Define directories, if needed.
#DIRAVR = "C:/Program Files (x86)/Atmel/AVR Tools/AVR Toolchain"
#DIRAVRBIN = $(DIRAVR)/bin
#DIRAVRUTILS = $(DIRAVR)/utils/bin
#DIRINC = .
#DIRLIB = $(DIRAVR)/avr/lib


# Define programs and commands.
#SHELL = $(DIRAVRUTILS)/sh
#NM = $(DIRAVRBIN)/avr-nm
#CC = $(DIRAVRBIN)/avr-gcc
#CXX = $(DIRAVRBIN)/avr-g++
#OBJCOPY = $(DIRAVRBIN)/avr-objcopy
#OBJDUMP= $(DIRAVRBIN)/avr-objdump
#SIZE = $(DIRAVRBIN)/avr-size --mcu=$(
#AVRDUDE = $(DIRAVRBIN)/avrdude.sh
#REMOVE = rm -f
#COPY = cp

# Define programs and commands.
SHELL = sh
CC = avr-gcc
CXX = avr-g++
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size --mcu=atmega8
NM = avr-nm
AVRDUDE = sudo avrdude
#AVRDUDE = avrdude
REMOVE = rm -f
COPY = cp
WINSHELL = cmd


# Define Messages
# English
MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = -------- begin --------
MSG_END = --------  end  --------
MSG_SIZE_BEFORE = Size before:
MSG_SIZE_AFTER = Size after:
MSG_COFF = Converting to AVR COFF:
MSG_EXTENDED_COFF = Converting to AVR Extended COFF:
MSG_FLASH = Creating load file for Flash:
MSG_BOOT = Creating load file for boot section:
MSG_EEPROM = Creating load file for EEPROM:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:



# Define all object files.
OBJ = $(addsuffix .o,$(basename $(SRC) $(ASRC)))

# Define all listing files.
LST = $(addsuffix .lst,$(basename $(SRC) $(ASRC)))


# Compiler flags to generate dependency files.
### GENDEPFLAGS = -Wp,-M,-MP,-MT,$(*F).o,-MF,.dep/$(@F).d
GENDEPFLAGS = -MD -MP -MF .dep/$(@F).d

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS) $(GENDEPFLAGS) $(DEFINES)
ALL_CXXFLAGS = -mmcu=$(MCU)  -I. $(CXXFLAGS) $(GENDEPFLAGS) $(DEFINES)
ALL_ASFLAGS = -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS) $(DEFINES)


# Default target.
all:
	make run TARGET='test' SRC='$(SRC_TEST)'
	make run TARGET='test_sampler' SRC='$(SRC_TEST_SAMPLER)'
	make run TARGET='profiling' SRC='$(SRC_PROFILING)'
	touch instances/inst_4093.c
	make run TARGET='S4093_192' SRC='$(SRC_4093)' DEF='-DALGOSELECT=192 -DALGO=0'
	touch instances/inst_4093.c
	make run TARGET='S4093_256' SRC='$(SRC_4093)' DEF='-DALGOSELECT=256 -DALGO=0'
	touch instances/inst_4093.c
	make run TARGET='S4093_320' SRC='$(SRC_4093)' DEF='-DALGOSELECT=320 -DALGO=0'
	touch instances/inst_4093.c
	make run TARGET='K4093_192' SRC='$(SRC_4093)' DEF='-DALGOSELECT=192 -DALGO=1'
	touch instances/inst_4093.c
	make run TARGET='K4093_256' SRC='$(SRC_4093)' DEF='-DALGOSELECT=256 -DALGO=1'
	touch instances/inst_4093.c
	make run TARGET='K4093_320' SRC='$(SRC_4093)' DEF='-DALGOSELECT=320 -DALGO=1'
	touch instances/inst_4093.c
	make run TARGET='K4096_192' SRC='$(SRC_4093)' DEF='-DALGOSELECT=192 -DALGO=5'
	touch instances/inst_4093.c
	make run TARGET='K4096_256' SRC='$(SRC_4093)' DEF='-DALGOSELECT=256 -DALGO=5'
	touch instances/inst_4093.c
	make run TARGET='K4096_320' SRC='$(SRC_4093)' DEF='-DALGOSELECT=320 -DALGO=5'
	touch instances/inst_4093.c
	make run TARGET='N7681_256' SRC='$(SRC_4093)' DEF='-DALGOSELECT=256 -DALGO=2'
	touch instances/inst_4093.c
	make run TARGET='N12289_512' SRC='$(SRC_4093)' DEF='-DALGOSELECT=512 -DALGO=2'
	touch instances/inst_4093.c
	avr-size *.elf







run: begin gccversion sizebefore build sizeafter finished end

build: elf hex eep lss sym

elf: $(TARGET).elf
hex: $(TARGET).hex $(BOOT_TARGET)
eep: $(TARGET).eep
lss: $(TARGET).lss
sym: $(TARGET).sym



# Eye candy.
# AVR Studio 3.x does not check make's exit code but relies on
# the following magic strings to be generated by the compile job.
begin:
	@echo
	@echo $(MSG_BEGIN)

finished:
	@echo $(MSG_ERRORS_NONE)

end:
	@echo $(MSG_END)
	@echo


# Display size of file.
HEXSIZE = $(SIZE) --target=$(FORMAT) $(TARGET).hex
ELFSIZE = $(SIZE) --mcu=$(MCU) -A $(TARGET).elf
sizebefore: 
	@if [ -f $(TARGET).elf ]; then echo; echo $(MSG_SIZE_BEFORE); $(ELFSIZE); echo; fi

sizeafter:
	@if [ -f $(TARGET).elf ]; then echo; echo $(MSG_SIZE_AFTER); $(ELFSIZE); echo; fi



# Display compiler version information.
gccversion :
	@$(CC) --version

program_tests:
	make do_program TARGET='test'

program_keygen:
	make do_program TARGET='keygen'

program_test_sampler:
	make do_program TARGET='test_sampler'

program_profiling:
	make do_program TARGET='profiling'

program_4093_256:
	make do_program TARGET='4093_256'


do_program: $(TARGET).hex $(TARGET).eep
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)


# Convert ELF to COFF for use in debugging / simulating in AVR Studio or VMLAB.
COFFCONVERT=$(OBJCOPY) --debugging \
--change-section-address .data-0x800000 \
--change-section-address .bss-0x800000 \
--change-section-address .noinit-0x800000 \
--change-section-address .eeprom-0x810000


coff: $(TARGET).elf
	@echo
	@echo $(MSG_COFF) $(TARGET).cof
	$(COFFCONVERT) -O coff-avr $< $(TARGET).cof


extcoff: $(TARGET).elf
	@echo
	@echo $(MSG_EXTENDED_COFF) $(TARGET).cof
	$(COFFCONVERT) -O coff-ext-avr $< $(TARGET).cof



# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	@echo
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

%-boot.hex: %.hex
	@echo
	@echo $(MSG_BOOT) $@
	$(OBJCOPY) -O $(FORMAT) --change-addresses -$(BOOT_SECTION_START) $< $@

%.eep: %.elf
	@echo
	@echo $(MSG_EEPROM) $@
	-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 -O $(FORMAT) $< $@

# Create extended listing file from ELF output file.
%.lss: %.elf
	@echo
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -S $< > $@

# Create a symbol table from ELF output file.
%.sym: %.elf
	@echo
	@echo $(MSG_SYMBOL_TABLE) $@
	$(NM) -n $< > $@

# Link: create ELF output file from object files.
.SECONDARY : $(TARGET).elf
.PRECIOUS : $(OBJ)
%.elf: $(OBJ)
	@echo
	@echo $(MSG_LINKING) $@
	$(CC) $(ALL_CFLAGS) $(OBJ) --output $@ $(LDFLAGS)

# Compile: create object files from C source files.
%.o : %.c
	@echo
	@echo $(MSG_COMPILING) $<
	$(CC) -c $(ALL_CFLAGS) $(DEF) $< -o $@


# Compile: create object files from C++ source files.
%.o : %.cpp
	@echo
	@echo $(MSG_COMPILING) $<
	$(CXX) -c $(ALL_CXXFLAGS) $< -o $@


# Compile: create assembler files from C source files.
%.s : %.c
	$(CC) -S $(ALL_CFLAGS) $< -o $@


# Compile: create assembler files from C++ source files.
%.s : %.cpp
	$(CXX) -S $(ALL_CXXFLAGS) $< -o $@


# Assemble: create object files from assembler source files.
%.o : %.S
	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(CC) -c $(ALL_ASFLAGS) $< -o $@



# Target: clean project.
clean:
	make do_clean TARGET='test' SRC='$(SRC_TEST)'
	make do_clean TARGET='keygen' SRC='$(SRC_KEYGEN)'
	make do_clean TARGET='profiling' SRC='$(SRC_PROFILING)'
	make do_clean TARGET='test_sampler' SRC='$(SRC_TEST_SAMPLER)'
	make do_clean TARGET='K4093_192' SRC='$(SRC_4093)'
	make do_clean TARGET='K4093_256' SRC='$(SRC_4093)'
	make do_clean TARGET='K4093_320' SRC='$(SRC_4093)'
	make do_clean TARGET='S4093_192' SRC='$(SRC_4093)'
	make do_clean TARGET='S4093_256' SRC='$(SRC_4093)'
	make do_clean TARGET='S4093_320' SRC='$(SRC_4093)'
	make do_clean TARGET='N7681_256' SRC='$(SRC_4093)'
	make do_clean TARGET='N12289_512' SRC='$(SRC_4093)'

do_clean: begin clean_list finished end

clean_list :
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) $(TARGET).hex
	$(REMOVE) $(TARGET)-boot.hex
	$(REMOVE) $(TARGET).eep
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).cof
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(TARGET).map
	$(REMOVE) $(TARGET).a90
	$(REMOVE) $(TARGET).sym
	$(REMOVE) $(TARGET).lnk
	$(REMOVE) $(TARGET).lss
	$(REMOVE) $(OBJ)
	$(REMOVE) $(LST)
	$(REMOVE) $(addsuffix .s,$(basename $(SRC)))
	$(REMOVE) $(addsuffix .d,$(basename $(SRC)))
	$(REMOVE) .dep/*

include $(RIOTBASE)/pkg/pkg.mk

all:
	$(MAKE) -C $(PKG_SOURCE_DIR) -f $(RIOTBASE)/Makefile.base

# Include the dependency files.
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)


# Listing of phony targets.
.PHONY : all begin finish end sizebefore sizeafter gccversion \
	build elf hex eep lss sym coff extcoff \
	clean clean_list program

