include(../common-config.pri)

CONFIG += \
    c++11 \
    no_keywords

QT += \
    testlib \
    widgets

TEST_ENV="QML2_IMPORT_PATH=../qml/"
WRAPPER=
linux:WRAPPER="xvfb-run -s '-screen 0 640x480x24' -a"
check.commands = "$$TEST_ENV $$WRAPPER ./$(TARGET)"
check.depends = first
QMAKE_EXTRA_TARGETS += check
