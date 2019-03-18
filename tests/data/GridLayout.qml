import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Controls.Desktop.Layouts 2.0 as Desktop

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: control.implicitWidth
    height: control.implicitHeight

    Component.onCompleted: focused.forceActiveFocus()

    Desktop.GridLayout {
        id: control
        anchors { fill: parent }
        columns: 2

        Button {
            id: focused
            text: "Button 1"
        }

        Button {
            text: "Button 2"
        }

        Button {
            text: "Button 3"
        }

        Button {
            text: "Button 4"
        }
    }
}
