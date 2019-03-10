import QtQuick 2.2
import QtQuick.Controls 2.2

ApplicationWindow {
    objectName: "qmlWindow"
    visible: true
    width: 300
    height: 200

    Component.onCompleted: dialog.open()

    Dialog {
        id: dialog
        title: "A dialog"
        standardButtons: Dialog.Ok | Dialog.Cancel

        Label {
            text: "Hello"
        }
    }
}
