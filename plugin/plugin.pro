include(../common-config.pri)

TARGET = qqc2desktopstyleplugin
TARGETPATH = it/mardy/Desktop/private
IMPORT_VERSION = 1.0

URI = it.mardy.Desktop.private

QT += qml quick widgets

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

HEADERS += \
    icon_p.h \
    padding_p.h \
    qqc2desktopstyleplugin.h \
    style_p.h \
    styleitem_p.h

SOURCES += \
    icon.cpp \
    qqc2desktopstyleplugin.cpp \
    style.cpp \
    styleitem.cpp

QML_FILES += \
    DefaultListItemBackground.qml \
    FocusRect.qml \
    SystemPaletteSingleton.qml

OTHER_FILES += \
    $$QML_FILES \
    qmldir

CONFIG += no_cxx_module

# This is needed so that QML files are copied into DESTDIR
AUX_QML_FILES = $$QML_FILES

# Workaround, as the qml_plugin macro overrides our flags
SAVED_QMAKE_CXXFLAGS = $$QMAKE_CXXFLAGS
SAVED_QMAKE_LDFLAGS = $$QMAKE_LDFLAGS
load(qml_plugin)
QMAKE_CXXFLAGS += $$SAVED_QMAKE_CXXFLAGS
QMAKE_LDFLAGS += $$SAVED_QMAKE_LDFLAGS
