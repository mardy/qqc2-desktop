import QtQuick.Controls 2.2
import QtQuick.Window 2.2

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: control.implicitWidth
    height: control.implicitHeight

    ScrollBar {
        id: control
        anchors.fill: parent
        focus: true
        orientation: Qt.Vertical
        position: 0.1
        stepSize: 0.1
    }
}
