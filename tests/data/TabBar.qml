import QtQuick 2.2
import QtQuick.Controls 2.3
import QtQuick.Window 2.2
import QtQuick.Controls.Desktop 2.0

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: control.implicitWidth
    height: control.implicitHeight
    Component.onCompleted: firstTab.forceActiveFocus()
    TabView {
        id: control
        anchors.fill: parent
        tabBar: TabBar {
            id: tabBar

            TabButton {
                id: firstTab
                text: "Tab 1"
            }

            TabButton {
                text: "Second tab, long label"
            }
        }

        Button {
            text: "Press me"
        }
    }
}
