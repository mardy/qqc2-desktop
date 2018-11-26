import QtQuick.Controls 2.2
import QtQuick.Window 2.2

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: control.implicitWidth
    height: control.implicitHeight

    CheckBox {
        id: control
        anchors.fill: parent
        text: "Enable stuff"
        focus: true
    }
}
