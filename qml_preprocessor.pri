defineReplace(qtStripProPwd) {
    return($$relative_path($$1, $$_PRO_FILE_PWD_))
}


QTQUICK_CONTROLS_VERSION="2.2"
versionAtLeast(QT_VERSION, "5.12.0"): QTQUICK_CONTROLS_VERSION="2.12"

CPP = cpp -C -P -nostdinc
CPP_OP=
win32 {
    CPP = $$QMAKE_CXX /EP /C
    CPP_OP = ">"
}

for (cp, CPP_FILES) {
    isEmpty($${cp}.files): next()
    pfx = copy_$${cp}
    notdir = false
    dir = false
    for (f, $${cp}.files) {
        fil = $$absolute_path($$f, $$_PRO_FILE_PWD_)
        tfiles = $$files($$fil/*)
        isEmpty(tfiles): \
            notdir = true
        else: \
            dir = true
        $${pfx}.files += $$fil
    }
    $$dir:$$notdir: \
        error("COPIES entry $$cp lists both files and directories.")
    path = $$eval($${cp}.path)
    isEmpty(path): error("COPIES entry $$cp defines no .path")
    base = $$eval($${cp}.base)
    isEmpty(base) {
        $${pfx}.output = $$path/${QMAKE_FILE_IN_NAME}
    } else: isEqual(base, $$_PRO_FILE_PWD_) {
        $${pfx}.output = $$path/${QMAKE_FUNC_FILE_IN_qtStripProPwd}
    } else {
        eval(defineReplace(qtStripSrcDir_$$cp) { \
            return(\$\$relative_path(\$\$1, $$val_escape(base))) \
        })
        $${pfx}.output = $$path/${QMAKE_FUNC_FILE_IN_qtStripSrcDir_$$cp}
    }
    $${pfx}.input = $${pfx}.files
    $${pfx}.commands = $${CPP} \
        -DQT_VERSION="0x0$${QT_MAJOR_VERSION}$$format_number($$QT_MINOR_VERSION, obase=16 width=2 zeropad)$$format_number($$QT_PATCH_VERSION, obase=16 width=2 zeropad)" \
        -DQTQUICK_CONTROLS_VERSION=$${QTQUICK_CONTROLS_VERSION} \
        -DQTQUICK_VERSION="2.$${QT_MINOR_VERSION}" \
        ${QMAKE_FILE_IN} $$CPP_OP ${QMAKE_FILE_OUT}
    $${pfx}.name = Preprocess ${QMAKE_FILE_IN}
    $${pfx}.CONFIG = no_link no_clean target_predeps
    QMAKE_EXTRA_COMPILERS += $${pfx}
}
