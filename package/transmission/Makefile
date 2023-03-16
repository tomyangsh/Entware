#
# Copyright (C) 2009-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# XXX ext deps 3d-party

include $(TOPDIR)/rules.mk

PKG_NAME:=transmission
PKG_VERSION:=4.0.2
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_VERSION:=2a57b17031053999e66c7c094e5d6cd6ec4666aa
PKG_SOURCE_URL:=https://github.com/transmission/transmission
PKG_MIRROR_HASH:=2a026640a3880e550885924c6f92a4ea902dda600a2797b051150e4252dd96af

PKG_MAINTAINER:=Daniel Golle <daniel@makrotopia.org>
PKG_LICENSE:=GPL-2.0-or-later
PKG_LICENSE_FILES:=COPYING
PKG_CPE_ID:=cpe:/a:transmissionbt:transmission

PKG_CONFIG_DEPENDS:= \
	CONFIG_LIBCURL_GNUTLS \
	CONFIG_LIBCURL_MBEDTLS \
	CONFIG_LIBCURL_OPENSSL \
	CONFIG_LIBCURL_WOLFSSL \
	CONFIG_LIBCURL_NOSSL

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/transmission/template
  SUBMENU:=BitTorrent
  SECTION:=net
  CATEGORY:=Network
  TITLE:=BitTorrent client
  URL:=https://www.transmissionbt.com
  DEPENDS:=+libcurl +libevent2 +libminiupnpc +libnatpmp +libstdcpp
  DEPENDS+=+LIBCURL_NOSSL:libmbedtls +LIBCURL_GNUTLS:libmbedtls
endef

define Package/transmission-daemon
  $(call Package/transmission/template)
  USERID:=transmission=224:transmission=224
endef

define Package/transmission-cli
  $(call Package/transmission/template)
  TITLE+= (utilities)
endef

define Package/transmission-remote
  $(call Package/transmission/template)
  TITLE+= (remote)
endef

define Package/transmission-web
  $(call Package/transmission/template)
  TITLE+= (webinterface)
  DEPENDS:=+transmission-daemon
  PKGARCH:=all
endef

define Package/transmission-daemon/description
 Transmission is a simple BitTorrent client.
 It features a very simple, intuitive interface
 on top on an efficient, cross-platform back-end.
 This package contains the daemon itself.
endef

define Package/transmission-cli/description
 CLI utilities for transmission.
endef

define Package/transmission-remote/description
 CLI remote interface for transmission.
endef

define Package/transmission-web/description
 Webinterface resources for transmission.
endef

define Package/transmission-daemon/conffiles
/opt/etc/transmission/settings.json
endef

TARGET_CFLAGS += -pthread

CMAKE_OPTIONS += \
	-DENABLE_CLI=ON \
	-DENABLE_DAEMON=ON \
	-DENABLE_NLS=OFF \
	-DENABLE_TESTS=OFF \
	-DENABLE_UTILS=ON \
	-DENABLE_UTP=ON \
	-DINSTALL_DOC=OFF \
	-DENABLE_GTK=OFF \
	-DENABLE_QT=OFF \
	-DENABLE_MAC=OFF \
	-DENABLE_WEB=OFF \
	-DWITH_KQUEUE=OFF \
	-DWITH_SYSTEMD=OFF \
	-DRUN_CLANG_TIDY=OFF \
	-DUSE_SYSTEM_DEFLATE=OFF \
	-DUSE_SYSTEM_DHT=OFF \
	-DUSE_SYSTEM_MINIUPNPC=ON \
	-DUSE_SYSTEM_NATPMP=ON \
	-DUSE_SYSTEM_B64=OFF \
	-DUSE_SYSTEM_PSL=OFF \
	$(if $(CONFIG_LIBCURL_NOSSL),-DWITH_CRYPTO=mbedtls) \
	$(if $(CONFIG_LIBCURL_GNUTLS),-DWITH_CRYPTO=mbedtls) \
	$(if $(CONFIG_LIBCURL_MBEDTLS),-DWITH_CRYPTO=mbedtls) \
	$(if $(CONFIG_LIBCURL_OPENSSL),-DWITH_CRYPTO=openssl) \
	$(if $(CONFIG_LIBCURL_WOLFSSL),-DWITH_CRYPTO=wolfssl)

define Build/Prepare
	$(call Build/Prepare/Default)
	mv $(PKG_BUILD_DIR)/third-party/dht $(PKG_BUILD_DIR)/third-party/libdht
endef

define Package/transmission-daemon/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/transmission-daemon $(1)/opt/bin/
	$(INSTALL_DIR) $(1)/opt/etc/init.d/
	$(INSTALL_BIN) files/S88transmission $(1)/opt/etc/init.d/
	$(INSTALL_DIR) $(1)/opt/etc/transmission/{blocklists,resume,torrents,watchdir}
	$(INSTALL_CONF) files/settings.json $(1)/opt/etc/transmission
	$(INSTALL_DIR) $(1)/opt/etc/sysctl.d/
	$(INSTALL_CONF) files/transmission.sysctl $(1)/opt/etc/sysctl.d/20-transmission.conf
#	$(call InstallSeccomp,$(1),./files/transmission-daemon.json)
endef

define Package/transmission-cli/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) \
		$(PKG_INSTALL_DIR)/opt/bin/transmission-{cli,create,edit,show} \
			$(1)/opt/bin/
endef

define Package/transmission-remote/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/transmission-remote $(1)/opt/bin/
endef

define Package/transmission-web/install
	$(INSTALL_DIR) $(1)/opt/share/transmission
	$(CP) $(PKG_INSTALL_DIR)/opt/share/transmission/public_html $(1)/opt/share/transmission/
endef

$(eval $(call BuildPackage,transmission-daemon))
$(eval $(call BuildPackage,transmission-cli))
$(eval $(call BuildPackage,transmission-remote))
$(eval $(call BuildPackage,transmission-web))
