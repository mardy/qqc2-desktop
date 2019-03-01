import QtQuick.Controls 2.2
import QtQuick.Window 2.2

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: 200
    height: control.implicitHeight

    ScrollBar {
        id: control
        anchors.fill: parent
        focus: true
        orientation: Qt.Horizontal
        active: true
        size: 0.1
        position: 0.9
        stepSize: 0.1
    }
}
