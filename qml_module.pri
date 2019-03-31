#
#  W A R N I N G
#  -------------
#
# This file is not part of the Qt API.  It exists purely as an
# implementation detail.  It may change from version to version
# without notice, or even be removed.
#
# We mean it.
#

equals(TEMPLATE, app): TEMPLATE = aux

isEmpty(TARGETPATH): error("Must set TARGETPATH (QML import name)")

qmldir_file = $$_PRO_FILE_PWD_/qmldir

fq_qml_files =
for(qmlf, QML_FILES): fq_qml_files += $$absolute_path($$qmlf, $$_PRO_FILE_PWD_)

fq_aux_qml_files =
for(qmlf, AUX_QML_FILES): fq_aux_qml_files += $$absolute_path($$qmlf, $$_PRO_FILE_PWD_)

load(qt_build_paths)

static: \
    CONFIG += builtin_resources
else: \
    CONFIG += install_qml_files

builtin_resources {
    URITARGET = $$replace(URI, "\\.", "_")
    # In static builds, the QML engine reads also the qmldir file from the resources.
    static: $${URITARGET}.files = $$qmldir_file
    # Ensure the QML files are included in the resources.
    $${URITARGET}.files += $$fq_qml_files
    # qt-project.org/imports is the path used for locating imports inside the resources
    $${URITARGET}.prefix = /qt-project.org/imports/$$TARGETPATH
    RESOURCES += $${URITARGET}
}

qmldir2build.base = $$_PRO_FILE_PWD_
qmldir2build.files = $$qmldir_file $$fq_aux_qml_files $$fq_qml_files
qmldir2build.path = $$DESTDIR
CPP_FILES += qmldir2build

built_qml_files =
for(qmlf, QML_FILES): built_qml_files += $$absolute_path($$qmlf, $$DESTDIR)

# Install rules
qmldir2install.base = $$DESTDIR
qmldir2install.files = $$built_qml_files $$absolute_path(qmldir, $$DESTDIR)
qmldir2install.path = $$[QT_INSTALL_QML]/$$TARGETPATH
qmldir2install.CONFIG = no_check_exist
INSTALLS += qmldir2install
