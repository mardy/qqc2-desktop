TEMPLATE = subdirs
SUBDIRS = \
    tst_conformance.pro \
    tst_plugin.pro

linux {
    SUBDIRS += tst_conformance_offscreen.pro
    tst_conformance_offscreen.depends = tst_conformance
}
