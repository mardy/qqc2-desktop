import QtQuick 2.0
import QtQuick.Layouts 1.2
import it.mardy.Desktop.private 1.0

FocusScope {
    id: wrapper

    default property alias data: layout.data
    property alias layoutDirection: layout.layoutDirection
    property alias spacing: layout.spacing

    implicitWidth: layout.implicitWidth + Style.layoutLeftMargin + Style.layoutRightMargin
    implicitHeight: layout.implicitHeight + Style.layoutTopMargin + Style.layoutBottomMargin

    ColumnLayout {
        id: layout

        anchors {
            fill: parent
            leftMargin: Style.layoutLeftMargin
            topMargin: Style.layoutTopMargin
            rightMargin: Style.layoutRightMargin
            bottomMargin: Style.layoutBottomMargin
        }
        spacing: Style.layoutVerticalSpacing
    }
}
