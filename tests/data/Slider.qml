import QtQuick.Controls 2.2
import QtQuick.Window 2.2

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: control.implicitWidth
    height: control.implicitHeight

    Slider {
        id: control
        anchors.fill: parent
        focus: true
        from: 0
        to: 100
        value: 36
    }
}
