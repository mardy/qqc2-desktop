import QtQuick 2.2
import QtQuick.Controls 2.4
import QtQuick.Window 2.2
import QtQuick.Controls.Desktop 2.0

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: 300
    height: control.implicitHeight + label.implicitHeight

    menuBar: MenuBar {
        id: control

        Menu {
            title: qsTr("&File")
            Action { text: qsTr("&New...") }
            Action { text: qsTr("&Open...") }
        }
        Menu {
            title: qsTr("&Edit")
            Action { text: qsTr("&Copy") }
        }
        Menu {
            title: qsTr("&Other")
            Action { text: qsTr("&Quit") }
        }

    }

    Label {
        id: label
        text: "."
    }
}
