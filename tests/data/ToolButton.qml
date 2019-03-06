import QtQuick.Controls 2.3
import QtQuick.Window 2.2

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: control.implicitWidth
    height: control.implicitHeight

    ToolButton {
        id: control
        anchors.fill: parent
        focus: true
        text: "Press me if you can"
        display: AbstractButton.IconOnly
        icon {
            source: "qrc:/geotag-handle.svg"
        }
    }
}
