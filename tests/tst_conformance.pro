TARGET = tst_conformance

include(tests.pri)

QT += \
    quickcontrols2 \
    uitools

SOURCES += \
    tst_conformance.cpp

DATA_DIR = $${TOP_SRC_DIR}/tests/data
DEFINES += \
    DATA_DIR=\\\"$${DATA_DIR}\\\"

check.commands = "FONTCONFIG_FILE=$${DATA_DIR}/fonts.conf xvfb-run -s '-screen 0 640x480x24' -a ./$${TARGET}"
