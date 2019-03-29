import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Controls.Desktop.Layouts 2.0 as Desktop

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: control.implicitWidth
    height: control.implicitHeight

    Component.onCompleted: combo.forceActiveFocus()
    Desktop.ColumnLayout {
        id: control
        anchors { fill: parent }

        Item { implicitHeight: 100 }

        ComboBox {
            id: combo
            Layout.fillWidth: true
            focus: true
            model: [ "one", "longer text, really long", "last" ]
        }

        Item { implicitHeight: 100 }
    }
}
