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

RESOURCES += data/ui.qrc
