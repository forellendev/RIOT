# libsafecrypto
PKG_NAME = pqm4
PKG_URL = https://github.com/mupq/pqm4.git
PKG_VERSION = c32bcd017b202d418c9135e2df77be73a69044a0
PKG_LICENSE = MIT

# manually set some RIOT env vars, so this Makefile can be called stand-alone
RIOTBASE ?= $(CURDIR)/../../..
RIOTTOOLS ?= $(CURDIR)/..
RIOTMAKE ?= $(RIOTBASE)/makefiles

include $(RIOTBASE)/pkg/pkg.mk

all:
	$(MAKE) -C $(PKG_SOURCE_DIR) -f $(RIOTBASE)/Makefile.base