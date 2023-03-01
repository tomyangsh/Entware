#
# Copyright (C) 2021 Sebastian Kemper <sebastian_ml@gmx.net>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=coturn
PKG_VERSION:=4.6.1
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/coturn/coturn/tar.gz/$(PKG_VERSION)?
PKG_HASH:=8fba86e593ed74adc46e002e925cccff2819745371814f42465fbe717483f1d8

PKG_LICENSE:=BSD-COTURN-CITRIX COMBINED-CITRIX-VIVOCHA-BSD MIT-HASH
PKG_LICENSE_FILES:=LICENSE src/apps/relay/dbdrivers/* src/server/ns_turn_khash.h

PKG_MAINTAINER:=Jiri Slachta <jiri@slachta.eu>, Sebastian Kemper <sebastian_ml@gmx.net>

PKG_BUILD_PARALLEL:=1

PKG_INSTALL:=1

PKG_CONFIG_DEPENDS+= \
	CONFIG_COTURN_ENABLE_MYSQL \
	CONFIG_COTURN_ENABLE_POSTGRESQL \
	CONFIG_COTURN_ENABLE_REDIS \
	CONFIG_COTURN_ENABLE_SQLITE

PKG_CPE_ID:=cpe:/a:coturn_project:coturn

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/coturn
  TITLE:=coturn TURN and STUN Server
  CATEGORY:=Network
  SECTION:=net
  SUBMENU:=Telephony
  URL:=https://github.com/coturn/coturn
  USERID:=turnserver=379:turnserver=379
  DEPENDS := \
	  +libevent2 \
	  +libevent2-extra \
	  +libevent2-pthreads \
	  +libevent2-openssl \
	  +libopenssl \
	  +COTURN_ENABLE_MYSQL:libmariadb \
	  +COTURN_ENABLE_POSTGRESQL:libpq \
	  +COTURN_ENABLE_REDIS:libhiredis \
	  +COTURN_ENABLE_SQLITE:libsqlite3
#  FILE_MODES:=/etc/turnserver:turnserver:turnserver:0750
endef

define Package/coturn/conffiles
/opt/etc/turnserver
endef

define Package/coturn/config
  menu "coturn configuration"
    depends on PACKAGE_coturn

    config COTURN_ENABLE_SQLITE
      bool "SQLite support"
      default y
      help
        Enable SQLite support

    config COTURN_ENABLE_MYSQL
      bool "MySQL support"
      default n
      help
        Enable MySQL support

    config COTURN_ENABLE_POSTGRESQL
      bool "PostgreSQL support"
      default n
      help
        Enable PostgreSQL support

    config COTURN_ENABLE_REDIS
      bool "Redis support"
      default n
      help
        Enable Redis support

  endmenu
endef

define Package/coturn/description
The TURN Server is a VoIP media traffic NAT traversal server and
gateway. It can be used as a general-purpose network traffic TURN server
and gateway, too.
endef

define Package/coturn/install
	$(INSTALL_DIR) \
		$(1)/opt/etc/{init.d,turnserver} $(1)/opt/{bin,share/coturn}
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/opt/etc/turnserver.conf.default \
		$(1)/opt/etc/turnserver/turnserver.conf
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/turn* $(1)/opt/bin
	$(INSTALL_BIN) ./files/S90turnserver \
		$(1)/opt/etc/init.d
#	$(INSTALL_CONF) ./files/turnserver.conf \
#		$(1)/etc/config/turnserver
ifneq ($(CONFIG_COTURN_ENABLE_MYSQL)$(CONFIG_COTURN_ENABLE_POSTGRESQL)$(CONFIG_COTURN_ENABLE_SQLITE),)
	$(INSTALL_DATA) \
		$(PKG_INSTALL_DIR)/opt/share/coturn/{schema,testsqldbsetup}.sql \
		$(1)/opt/share/coturn
endif
ifeq ($(CONFIG_COTURN_ENABLE_SQLITE),y)
	$(INSTALL_DIR) $(1)/opt/var/lib/turn
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/examples/var/db/turndb \
		$(1)/opt/var/lib/turn
endif
ifneq ($(CONFIG_COTURN_ENABLE_REDIS),)
	$(INSTALL_DATA) \
		$(PKG_INSTALL_DIR)/opt/share/coturn/schema.{stats,userdb}.redis \
		$(1)/opt/share/coturn
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/share/coturn/testredisdbsetup.sh \
		$(1)/opt/share/coturn
endif
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/examples/ca/turn_server_*.pem \
		$(1)/opt/etc/turnserver
endef

CONFIGURE_ARGS+= \
	--confdir=/opt/etc \
	--disable-rpath \
	--schemadir=/opt/share/coturn \
	--turndbdir=/opt/var/lib/turn

CONFIGURE_VARS+= \
	ARCHIVERCMD="$(TARGET_AR) -r" \
	LIBEV_OK=1 \
	TURN_NO_PROMETHEUS=1 \
	TURN_NO_SCTP=1 \
	TURN_NO_SYSTEMD=1 \
	TURN_NO_MONGO=1 \
	$(if $(CONFIG_COTURN_ENABLE_MYSQL),,TURN_NO_MYSQL=1) \
	$(if $(CONFIG_COTURN_ENABLE_POSTGRESQL),,TURN_NO_PQ=1) \
	$(if $(CONFIG_COTURN_ENABLE_REDIS),,TURN_NO_HIREDIS=1) \
	$(if $(CONFIG_COTURN_ENABLE_SQLITE),,TURN_NO_SQLITE=1)

define Build/InstallDev
endef

$(eval $(call BuildPackage,coturn))
