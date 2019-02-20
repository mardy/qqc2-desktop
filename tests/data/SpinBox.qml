import QtQuick.Controls 2.2
import QtQuick.Window 2.2

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: label.implicitWidth
    height: label.implicitHeight

    SpinBox {
        id: label
        anchors.fill: parent
        focus: true
        stepSize: 50
        from: 0
        to: 100
    }
}
