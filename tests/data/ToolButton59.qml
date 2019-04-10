import QtQuick.Controls 2.2
import QtQuick.Window 2.2

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: control.implicitWidth
    height: control.implicitHeight

    ToolButton {
        id: control
        anchors.fill: parent
        focus: true
        text: "Press me if you can"
    }
}
