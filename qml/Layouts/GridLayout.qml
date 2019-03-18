import QtQuick 2.0
import QtQuick.Layouts 1.2
import it.mardy.Desktop.private 1.0

FocusScope {
    id: wrapper

    default property alias data: layout.data
    property alias layoutDirection: layout.layoutDirection
    property alias flow: layout.flow
    property alias rows: layout.rows
    property alias rowSpacing: layout.rowSpacing
    property alias columns: layout.columns
    property alias columnSpacing: layout.columnSpacing

    implicitWidth: layout.implicitWidth + Style.layoutLeftMargin + Style.layoutRightMargin
    implicitHeight: layout.implicitHeight + Style.layoutTopMargin + Style.layoutBottomMargin

    GridLayout {
        id: layout

        anchors {
            fill: parent
            leftMargin: Style.layoutLeftMargin
            topMargin: Style.layoutTopMargin
            rightMargin: Style.layoutRightMargin
            bottomMargin: Style.layoutBottomMargin
        }
        rowSpacing: Style.layoutVerticalSpacing
        columnSpacing: Style.layoutHorizontalSpacing
    }
}
