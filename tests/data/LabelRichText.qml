import QtQuick.Controls 2.2
import QtQuick.Window 2.2

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: control.implicitWidth
    height: control.implicitHeight

    Label {
        id: control
        anchors.fill: parent
        text: "<u>Just</u> <b>a</b> <i>simple</i> <font color=\"red\">label</font>"
    }
}
