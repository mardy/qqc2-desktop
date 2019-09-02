import QtQuick 2.2
import QtQuick.Controls 2.4
import QtQuick.Window 2.2
import QtQuick.Controls.Desktop 2.0

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: 400
    height: control.implicitHeight + 200

    menuBar: MenuBar {
        id: control

        Menu {
            title: qsTr("&File")
            Action { text: qsTr("&New...") }
            Action { text: qsTr("&Open...") }
        }
        Menu {
            title: qsTr("&Edit")
            Action { text: qsTr("&Copy"); icon.name: "edit-copy" }
            MenuSeparator {}
            Action { text: qsTr("Preferences...") }
        }
        Menu {
            title: qsTr("&Other")
            Action { text: qsTr("&Quit") }
            Action {
                text: qsTr("Checkable item")
                checkable: true
                checked: false
                shortcut: "Alt+I"
            }
            Action {
                text: qsTr("Checked")
                checkable: true
                checked: true
            }
        }

    }

    Label {
        id: label
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        text: "."
    }
}
