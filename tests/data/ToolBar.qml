import QtQuick.Controls 2.2
import QtQuick.Window 2.2

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: header.implicitWidth
    height: header.implicitHeight
    header: ToolBar {
        focus: true
    }
}
