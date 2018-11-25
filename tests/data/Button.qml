import QtQuick.Controls 2.2
import QtQuick.Window 2.2

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: label.implicitWidth
    height: label.implicitHeight

    Button {
        id: label
        anchors.fill: parent
        text: "Press me if you can"
    }
}
