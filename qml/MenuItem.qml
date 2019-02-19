/*
 * Copyright 2017 Marco Martin <mart@kde.org>
 * Copyright 2017 The Qt Company Ltd.
 * Copyright (C) 2018-2019 Alberto Mardegan <mardy@users.sourceforge.net>
 *
 * This file is part of qqc2-desktop.
 *
 * qqc2-desktop is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * qqc2-desktop is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with qqc2-desktop.  If not, see <http://www.gnu.org/licenses/>.
 */


import QtQuick 2.6
import QtQuick.Layouts 1.2
import QtQuick.Templates 2.2 as T
import it.mardy.Desktop.private 1.0

T.MenuItem {
    id: controlRoot

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: visible ? Math.max(background ? background.implicitHeight : 0,
                             Math.max(contentItem.implicitHeight,
                                      indicator ? indicator.implicitHeight : 0) + topPadding + bottomPadding) : 0
    baselineOffset: contentItem.y + contentItem.baselineOffset

    Layout.fillWidth: true
    padding: 4
    leftPadding: 8
    rightPadding: 8

    contentItem: RowLayout {
        Item {
           Layout.preferredWidth: (controlRoot.ListView.view && controlRoot.ListView.view.hasCheckables) || controlRoot.checkable ? controlRoot.indicator.width : 4
        }
        Image {
            Layout.alignment: Qt.AlignVCenter
            visible: (controlRoot.ListView.view && controlRoot.ListView.view.hasIcons) || (controlRoot.icon != undefined && (controlRoot.icon.name.length > 0 || controlRoot.icon.source.length > 0))
            source: controlRoot.icon ? (controlRoot.icon.name || controlRoot.icon.source) : ""
            Layout.preferredWidth: Layout.preferredHeight
        }
        Label {
            id: label
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true

            text: controlRoot.text
            font: controlRoot.font
            color: (controlRoot.highlighted || controlRoot.hovered) ? SystemPaletteSingleton.highlightedText(controlRoot.enabled) : SystemPaletteSingleton.text(controlRoot.enabled)
            elide: Text.ElideRight
            visible: controlRoot.text
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }
    }

//we can't use arrow: on old qqc2 releases
/* TODO
@DISABLE_UNDER_QQC2_2_3@    arrow: Kirigami.Icon {
@DISABLE_UNDER_QQC2_2_3@        x: controlRoot.mirrored ? controlRoot.padding : controlRoot.width - width - controlRoot.padding
@DISABLE_UNDER_QQC2_2_3@        y: controlRoot.topPadding + (controlRoot.availableHeight - height) / 2
@DISABLE_UNDER_QQC2_2_3@        source: controlRoot.mirrored ? "go-next-symbolic-rtl" : "go-next-symbolic"
@DISABLE_UNDER_QQC2_2_3@        selected: controlRoot.highlighted
@DISABLE_UNDER_QQC2_2_3@        width: Math.max(label.height, Kirigami.Units.iconSizes.small)
@DISABLE_UNDER_QQC2_2_3@        height: width
@DISABLE_UNDER_QQC2_2_3@        visible: controlRoot.subMenu
@DISABLE_UNDER_QQC2_2_3@    }
*/

    indicator: CheckIndicator {
        x: controlRoot.mirrored ? controlRoot.width - width - controlRoot.rightPadding : controlRoot.leftPadding
        y: controlRoot.topPadding + (controlRoot.availableHeight - height) / 2

        visible: controlRoot.checkable
        on: controlRoot.checked
        control: controlRoot
    }

    background: Item {
        anchors.fill: parent
        implicitWidth: 64

        Rectangle {
            anchors.fill: parent
            color: SystemPaletteSingleton.highlight(controlRoot.enabled)
            opacity: (controlRoot.highlighted || controlRoot.hovered) ? 1 : 0
            Behavior on opacity { NumberAnimation { duration: 150 } }
        }
    }
}
