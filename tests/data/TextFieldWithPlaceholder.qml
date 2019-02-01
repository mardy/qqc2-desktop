import QtQuick.Controls 2.2
import QtQuick.Window 2.2

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: 300
    height: control.implicitHeight

    TextField {
        id: control
        anchors.fill: parent
        focus: true
        width: parent.width
        placeholderText: "Write something"
    }
}
