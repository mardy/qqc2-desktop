[![pipeline status](https://gitlab.com/mardy/qqc2-desktop-style/badges/master/pipeline.svg)](https://gitlab.com/mardy/qqc2-desktop-style/commits/master)
[![coverage report](https://gitlab.com/mardy/qqc2-desktop-style/badges/master/coverage.svg)](https://gitlab.com/mardy/qqc2-desktop-style/commits/master)

# QQC2 Desktop Style

This is a QML module which provide native look and feel for applications using
the Qt Quick Controls 2 API.

It is a [style](https://doc.qt.io/qt-5/qtquickcontrols2-styles.html) for
`QtQuick.Controls2` based on the `QtWidget`'s `QStyle` class. In order for this
style to be used, the application needs to instantiate a `QApplication` (rather
than just a `QGuiApplication`) and select the `desktop` style; the latter can
be achieved by other calling

    QQuickStyle::setStyle("desktop");

inside your `main()` function, or by starting the application using one of the
ways described
[here](https://doc.qt.io/qt-5/qtquickcontrols2-styles.html#using-styles-in-qt-quick-controls-2).

# Acknowledgements

This module is based on Marco Martin's [Kirigami QQC2
style](https://github.com/KDE/qqc2-desktop-style) module; the KDE dependency
was removed and development got focused on achieving maximum resemblance to the
QtWidget's look.
