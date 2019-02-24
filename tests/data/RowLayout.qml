import QtQuick.Layouts 1.1
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Controls.Desktop.Layouts 2.0 as Desktop

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: control.implicitWidth + control.anchors.leftMargin + control.anchors.rightMargin
    height: control.implicitHeight + control.anchors.topMargin + control.anchors.bottomMargin

    Desktop.RowLayout {
        id: control
        anchors { fill: parent }

        ProgressBar {
            from: 0
            to: 100
            value: 75
        }

        Button {
            focus: true
            text: "Just a button"
        }

        Button {
            text: "Press me"
        }
    }
}
