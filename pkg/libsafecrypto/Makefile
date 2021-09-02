# libsafecrypto
PKG_NAME = libsafecrypto
PKG_URL = https://github.com/safecrypto/libsafecrypto
PKG_VERSION = 0.2.0-52
PKG_LICENSE = MIT

# manually set some RIOT env vars, so this Makefile can be called stand-alone
# RIOTBASE ?= $(CURDIR)/../../../RIOT
# RIOTTOOLS ?= $(CURDIR)/..
# RIOTMAKE ?= $(RIOTBASE)/makefiles

include $(RIOTBASE)/pkg/pkg.mk

LIBSAFECRYPTO_MODULES = \
INCLUDES += -I$(PKGDIRBASE)/libsafecrypto/include \
INCLUDES += -I$(PKGDIRBASE)/libsafecrypto/bindings \
INCLUDES += -I$(PKGDIRBASE)/libsafecrypto/build_tools \
INCLUDES += -I$(PKGDIRBASE)/libsafecrypto/src \
INCLUDES += -I$(PKGDIRBASE)/libsafecrypto/src/utils/crypto \
INCLUDES += -I$(PKGDIRBASE)/libsafecrypto/src/utils/threading \
INCLUDES += -I$(PKGDIRBASE)/libsafecrypto/src/schemes \

all:
	$(MAKE) -C $(PKG_SOURCE_DIR) -f $(RIOTBASE)/Makefile.base