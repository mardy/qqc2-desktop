/*
 * Copyright 2018 Marco Martin <mart@kde.org>
 * Copyright 2017 The Qt Company Ltd.
 * Copyright (C) 2018-2020 Alberto Mardegan <mardy@users.sourceforge.net>
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
import QtQuick.Controls 2.2 as Controls
import it.mardy.Desktop.private 1.0

T.RoundButton {
    id: controlRoot

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             contentItem.implicitHeight + topPadding + bottomPadding)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    transform: Translate {
        x: controlRoot.down || controlRoot.checked ? 1 : 0
        y: controlRoot.down || controlRoot.checked ? 1 : 0
    }
    contentItem: Item {
        implicitWidth: mainLayout.implicitWidth
        implicitHeight: mainLayout.implicitHeight
        RowLayout {
            id: mainLayout
            anchors.centerIn: parent
            Controls.Label {
                text: controlRoot.text
            }
        }
    }
    background: Rectangle {
        property color borderColor: SystemPaletteSingleton.text(controlRoot.enabled)

        implicitWidth: 32
        implicitHeight: 32
        radius: controlRoot.radius
        color: controlRoot.down ? Qt.lighter(borderColor, 1.1) : SystemPaletteSingleton.base(controlRoot.enabled)

        border.color: (controlRoot.hovered || controlRoot.highlighted) ? Qt.lighter(SystemPaletteSingleton.highlight(true), 1.2) : borderColor
        border.width: 1

        Rectangle {
            radius: controlRoot.radius
            anchors.fill: parent
            visible: !controlRoot.flat
            gradient: Gradient {
                GradientStop { position: 0.0; color: Qt.rgba(1, 1, 1, 0.13) }
                GradientStop { position: 1.0; color: Qt.rgba(0, 0, 0, 0.03) }
            }
        }
        Rectangle {
            z: -1
            radius: controlRoot.radius
            visible: !controlRoot.down && !controlRoot.checked && !controlRoot.flat
            anchors {
                topMargin: 1
                bottomMargin: -1
                fill: parent
            }
            color: Qt.rgba(0, 0, 0, 0.15)
        }
    }
}
