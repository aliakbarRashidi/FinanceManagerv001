include(root.pri)

TEMPLATE = app

TARGET = FinanceManager

QT += sql qml quick
CONFIG += c++11

UI_DIR = uics
MOC_DIR = mocs
OBJECTS_DIR = objs

RESOURCES += qml.qrc \
    assets.qrc

DISTFILES += doc/* mainpage.dox Doxyfile

OTHER_FILES += App/* \
    App/assets/scripts/* \
    App/assets/images/* \
    App/assets/icons/* \
    App/assets/database/* \
    README.md \
    TODO \
    Copyright \
    Changelog \
    logs/*

CONFIG(debug, debug|release) {
    DEFINES += SUPERVERBOSE
}

#CONFIG( debug, debug|release ) {
#    DESTDIR += "../dist/debug"
#} else {
#    DESTDIR += "../dist/release"
#}

SOURCES += main.cpp

PACKAGE_VERSION = $$FinanceManagerVersion
PACKAGE_NAME= FinanceManager

include(Logger/Logger.pri)
include(Engine/Engine.pri)
