# libsafecrypto
PKG_NAME = libopencm3
PKG_URL = https://github.com/libopencm3/libopencm3.git
PKG_VERSION = d60d7802fd20821a766675545b6ef7a2207207a3
PKG_LICENSE = LGPL

# manually set some RIOT env vars, so this Makefile can be called stand-alone
RIOTBASE ?= $(CURDIR)/../../..
RIOTTOOLS ?= $(CURDIR)/..
RIOTMAKE ?= $(RIOTBASE)/makefiles

include $(RIOTBASE)/pkg/pkg.mk

all:
	$(MAKE) -C $(PKG_SOURCE_DIR) -f $(RIOTBASE)/Makefile.base