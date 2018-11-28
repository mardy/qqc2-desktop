TEMPLATE = aux

check.commands = "QT_STYLE_OVERRIDE=Windows xvfb-run -s '-screen 0 640x480x24' -a ./tst_conformance"
QMAKE_EXTRA_TARGETS += check
