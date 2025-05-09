#
# Copyright (C) 2010-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libusb
ifeq ($(CONFIG_LINUX_2_6_36),y)
PKG_VERSION:=1.0.22
PKG_RELEASE:=4
PKG_HASH:=75aeb9d59a4fdb800d329a545c2e6799f732362193b465ea198f2aa275518157
else
PKG_VERSION:=1.0.27
PKG_RELEASE:=1
PKG_HASH:=ffaa41d741a8a3bee244ac8e54a72ea05bf2879663c098c82fc5757853441575
endif
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=\
  https://github.com/libusb/libusb/releases/download/v$(PKG_VERSION) \
  @SF/$(PKG_NAME)

PKG_MAINTAINER:= Felix Fietkau <nbd@nbd.name>
PKG_LICENSE:=LGPL-2.1-or-later
PKG_LICENSE_FILES:=COPYING
PKG_CPE_ID:=cpe:/a:libusb:libusb

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/libusb-1.0
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=A library for accessing Linux USB devices
  DEPENDS:=+libpthread +librt +libatomic
  URL:=https://libusb.info/
  ABI_VERSION:=0
endef

define Package/libusb-1.0/description
  libusb is a C library that gives applications easy access to USB devices on
  many different operating systems.
endef

define Package/fxload
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=fxload firmware loader
  URL:=https://linux-hotplug.sourceforge.net
  DEPENDS:=+libusb-1.0
endef

define Package/fxload/description
This program is conveniently able to download firmware into FX, FX2,
and FX2LP EZ-USB devices, as well as the original AnchorChips EZ-USB.
It is intended to be invoked by hotplug scripts when the unprogrammed
device appears on the bus.
endef

TARGET_CFLAGS += $(FPIC)
CONFIGURE_ARGS += \
	--enable-examples-build \
	--disable-log \
	--disable-udev

define Build/InstallDev
	$(INSTALL_DIR) $(1)/opt/include/libusb-1.0
	$(CP) $(PKG_INSTALL_DIR)/opt/include/libusb-1.0/libusb.h $(1)/opt/include/libusb-1.0/
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libusb-1.0.* $(1)/opt/lib/
	$(INSTALL_DIR) $(1)/opt/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/pkgconfig/libusb-1.0.pc $(1)/opt/lib/pkgconfig/
endef

define Package/libusb-1.0/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libusb-1.0.so* $(1)/opt/lib/
endef

define Package/fxload/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/examples/.libs/fxload $(1)/opt/sbin
endef

$(eval $(call BuildPackage,libusb-1.0))
$(eval $(call BuildPackage,fxload))
