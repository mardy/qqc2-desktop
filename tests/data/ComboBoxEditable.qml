import QtQuick.Controls 2.2
import QtQuick.Window 2.2

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: control.implicitWidth
    height: control.implicitHeight

    ComboBox {
        id: control
        anchors.fill: parent
        focus: true
        editable: true
        editText: "one"
        model: [ "one", "longer text, really long", "last" ]
    }
}
