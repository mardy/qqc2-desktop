import QtQuick.Controls 2.2
import QtQuick.Window 2.2

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: control.implicitWidth
    height: control.implicitHeight

    GroupBox {
        id: control
        anchors.fill: parent
        title: "Just a label"
        Label {
            anchors.fill: parent
            text: "Better look at the box"
        }
    }
}
