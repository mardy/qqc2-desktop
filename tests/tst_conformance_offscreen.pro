TEMPLATE = aux

include(tests.pri)

check.commands = "QT_STYLE_OVERRIDE=Windows $$TEST_ENV xvfb-run -s '-screen 0 640x480x24' -a ./tst_conformance"
QMAKE_EXTRA_TARGETS += check
