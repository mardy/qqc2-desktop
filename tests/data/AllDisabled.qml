import QtQuick.Layouts 1.1
import QtQuick.Controls 2.2
import QtQuick.Window 2.2

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: control.implicitWidth + 18
    height: control.implicitHeight + 18

    ColumnLayout {
        id: control
        anchors { fill: parent; margins: 9 }
        spacing: 6
        enabled: false

        Button {
            Layout.fillWidth: true
            text: "Press me"
        }

        RadioButton {
            Layout.fillWidth: true
            text: "Radio"
        }

        RadioButton {
            Layout.fillWidth: true
            text: "Radio, selected"
            checked: true
        }

        CheckBox {
            Layout.fillWidth: true
            text: "CheckBox"
        }

        CheckBox {
            Layout.fillWidth: true
            text: "CheckBox, checked"
            checked: true
        }

        ComboBox {
            Layout.fillWidth: true
            model: [ "Combo box" ]
        }

        ComboBox {
            Layout.fillWidth: true
            editText: "Editable box"
            editable: true
        }

        TextField {
            Layout.fillWidth: true
            placeholderText: "Placeholder"
        }

        TextField {
            Layout.fillWidth: true
            text: "Some text"
        }

        SpinBox {
            Layout.fillWidth: true
            stepSize: 50
            from: 0
            to: 0
        }

        SpinBox {
            Layout.fillWidth: true
            stepSize: 50
            from: 0
            to: 100
            value: 10
        }

        Label {
            Layout.fillWidth: true
            text: "Text label"
        }

        ProgressBar {
            Layout.fillWidth: true
            from: 0
            to: 100
            value: 24
        }
    }
}
