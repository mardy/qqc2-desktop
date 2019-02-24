import QtQuick.Layouts 1.2
import it.mardy.Desktop.private 1.0

GridLayout {
    anchors {
        leftMargin: Style.layoutLeftMargin
        topMargin: Style.layoutTopMargin
        rightMargin: Style.layoutRightMargin
        bottomMargin: Style.layoutBottomMargin
    }
    rowSpacing: Style.layoutVerticalSpacing
    columnSpacing: Style.layoutHorizontalSpacing
}
