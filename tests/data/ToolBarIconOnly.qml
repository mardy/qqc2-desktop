import QtQuick.Controls 2.3
import QtQuick.Window 2.2

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: Math.max(control.implicitWidth, header.implicitWidth)
    height: control.implicitHeight + header.implicitHeight
    header: ToolBar {
        ToolButton {
            text: "Press and rejoice"
            display: AbstractButton.IconOnly
            icon {
                source: "qrc:/geotag-handle.svg"
            }
        }
    }

    Button {
        id: control
        anchors.fill: parent
        focus: true
        text: "ok"
    }
}
