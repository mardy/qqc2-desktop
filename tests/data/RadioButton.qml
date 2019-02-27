import QtQuick.Controls 2.2
import QtQuick.Window 2.2

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: control.implicitWidth
    height: control.implicitHeight

    RadioButton {
        id: control
        objectName: "control"
        anchors.fill: parent
        focus: true
        text: "First"
    }
}
