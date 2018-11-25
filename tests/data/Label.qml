import QtQuick.Controls 2.2
import QtQuick.Window 2.2

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: label.implicitWidth
    height: label.implicitHeight

    Label {
        id: label
        anchors.fill: parent
        text: "Just a simple label"
    }
}
