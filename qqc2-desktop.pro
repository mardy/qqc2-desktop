TEMPLATE = subdirs
SUBDIRS += \
    qml \
    plugin

!CONFIG(no_tests) {
    SUBDIRS += tests
    tests.depends = plugin
}

include(coverage.pri)
