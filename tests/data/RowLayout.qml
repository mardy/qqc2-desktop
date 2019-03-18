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

    Desktop.RowLayout {
        id: control
        anchors { fill: parent }

        ProgressBar {
            from: 0
            to: 100
            value: 75
        }

        Button {
            id: focused
            text: "Just a button"
        }

        Button {
            text: "Press me"
        }
    }
}
