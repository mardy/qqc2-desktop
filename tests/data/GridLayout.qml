import QtQuick.Layouts 1.1
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Controls.Desktop.Layouts 2.0 as Desktop

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: control.implicitWidth + control.anchors.leftMargin + control.anchors.rightMargin
    height: control.implicitHeight + control.anchors.topMargin + control.anchors.bottomMargin

    Desktop.GridLayout {
        id: control
        anchors { fill: parent }
        columns: 2

        Button {
            focus: true
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
