# libsafecrypto
PKG_NAME=libsafecrypto
PKG_URL=https://github.com/safecrypto/libsafecrypto/
PKG_VERSION=65b962f6d608704336ac16f226c8a5ff63b75851 # 0.2.0-52
PKG_LICENSE=MIT

# manually set some RIOT env vars, so this Makefile can be called stand-alone
# RIOTBASE ?= $(CURDIR)/../../../RIOT
# RIOTTOOLS ?= $(CURDIR)/..
# RIOTMAKE ?= $(RIOTBASE)/makefiles

include $(RIOTBASE)/pkg/pkg.mk

RIOT_CFLAGS = $(INCLUDES)

# LIBSAFECRYPTO_MODULES = \
# INCLUDES += -I$(PKGDIRBASE)/libsafecrypto/include \
# INCLUDES += -I$(PKGDIRBASE)/libsafecrypto/src \
# INCLUDES += -I$(PKGDIRBASE)/libsafecrypto/bindings \
# INCLUDES += -I$(PKGDIRBASE)/libsafecrypto/build_tools \
# INCLUDES += -I$(PKGDIRBASE)/libsafecrypto/src/utils/crypto \
# INCLUDES += -I$(PKGDIRBASE)/libsafecrypto/src/utils/threading \
# INCLUDES += -I$(PKGDIRBASE)/libsafecrypto/src/schemes \

all: $(BINDIR)/$(PKG_NAME).a

$(BINDIR)/$(PKG_NAME).a: $(PKG_BUILD_DIR)/lib/libsafecrypto-riot.a
	cp $< $@

$(PKG_BUILD_DIR)/lib/libsafecrypto-riot.a: cross_compile


# Cross-compile libsafecrypto for Cortex-M4 devices
# TOOLCHAIN=/usr/compilers/gcc-arm-xxx-xxx
cross_compile:
	ls -la
	sudo ./configure --host=arm-none-eabi --prefix=$TOOLCHAIN --without-tests --disable-multithreading \
		CFLAGS="-mcpu=cortex-m4 -mthumb -mfpu=neon -O2 -falign-functions=16 -ffunction-sections \
		-fdata-sections --specs=nosys.specs" \


# Add this somehow to allow for custom cross-compiling (generate-xcompile-toolchain.sh)
# `$ ./configure --host=arm-none-eabi --prefix=$TOOLCHAIN --without-tests --disable-multithreading
#         CFLAGS="-mcpu=cortex-m4 -mthumb -mfpu=neon -O2 -falign-functions=16 -ffunction-sections
#         -fdata-sections --specs=nosys.specs"`

all:
	$(MAKE) -C $(PKG_SOURCE_DIR) -f $(RIOTBASE)/Makefile.base