/*
 * Copyright 2017 Marco Martin <mart@kde.org>
 * Copyright 2017 The Qt Company Ltd.
 * Copyright (C) 2018 Alberto Mardegan <mardy@users.sourceforge.net>
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
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.2 as Controls
import QtQuick.Templates 2.2 as T
import it.mardy.Desktop.private 1.0

T.ToolTip {
    id: controlRoot

    x: parent ? (parent.width - implicitWidth) / 2 : 0
    y: -implicitHeight - 3

    implicitWidth: contentItem.implicitWidth + leftPadding + rightPadding
    implicitHeight: contentItem.implicitHeight + topPadding + bottomPadding

    margins: 6
    padding: 6

    closePolicy: T.Popup.CloseOnEscape | T.Popup.CloseOnPressOutsideParent | T.Popup.CloseOnReleaseOutsideParent

    contentItem: Controls.Label {
        text: controlRoot.text
        font: controlRoot.font
        color: SystemPaletteSingleton.text(true)
    }


    background: Rectangle {
        radius: 3
        opacity: 0.95
        color: SystemPaletteSingleton.base(true) // FIXME: use QPalette::ToolTipBase
        layer.enabled: true
        layer.effect: DropShadow {
            transparentBorder: true
            radius: 4
            samples: 8
            horizontalOffset: 0
            verticalOffset: 2
            color: Qt.rgba(0, 0, 0, 0.3)
        }
    }

}
