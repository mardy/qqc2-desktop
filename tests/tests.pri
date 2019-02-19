include(../common-config.pri)

CONFIG += \
    c++11 \
    no_keywords

QT += \
    testlib \
    widgets

TEST_ENV="QML2_IMPORT_PATH=../qml/"
check.commands = "$$TEST_ENV xvfb-run -s '-screen 0 640x480x24' -a ./$${TARGET}"
check.depends = $${TARGET}
QMAKE_EXTRA_TARGETS += check
