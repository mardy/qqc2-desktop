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
import QtQuick.Templates 2.2 as T
import it.mardy.Desktop.private 1.0

T.SpinBox {
    id: controlRoot

    implicitWidth: Math.max(48, contentItem.implicitWidth + 2 * padding +  up.indicator.implicitWidth)
    implicitHeight: contentItem.implicitHeight + topPadding + bottomPadding

    padding: 6
    leftPadding: padding + (controlRoot.mirrored ? (up.indicator ? up.indicator.width : 0) : 0)
    rightPadding: padding + (controlRoot.mirrored ? 0 : (up.indicator ? up.indicator.width : 0))


    hoverEnabled: true

    validator: IntValidator {
        locale: controlRoot.locale.name
        bottom: Math.min(controlRoot.from, controlRoot.to)
        top: Math.max(controlRoot.from, controlRoot.to)
    }

    contentItem: TextInput {
        z: 2
        text: controlRoot.textFromValue(controlRoot.value, controlRoot.locale)
        opacity: controlRoot.enabled ? 1 : 0.3

        font: controlRoot.font
        color: SystemPaletteSingleton.text(controlRoot.enabled)
        selectionColor: SystemPaletteSingleton.highlight(controlRoot.enabled)
        selectedTextColor: SystemPaletteSingleton.highlightedText(controlRoot.enabled)
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter

        readOnly: !controlRoot.editable
        validator: controlRoot.validator
        inputMethodHints: Qt.ImhFormattedNumbersOnly

        MouseArea {
            anchors.fill: parent
            onPressed: mouse.accepted = false;
            onWheel: {
                if (wheel.pixelDelta.y < 0 || wheel.angleDelta.y < 0) {
                    controlRoot.decrease();
                } else {
                    controlRoot.increase();
                }
            }
        }
    }

    up.indicator: Item {
        implicitWidth: parent.height/2
        implicitHeight: implicitWidth
        x: controlRoot.mirrored ? 0 : parent.width - width
    }
    down.indicator: Item {
        implicitWidth: parent.height/2
        implicitHeight: implicitWidth
 
        x: controlRoot.mirrored ? 0 : parent.width - width
        y: parent.height - height
    }


    background: StyleItem {
        id: styleitem
        control: controlRoot
        elementType: "spinbox"
        anchors.fill: parent
        hover: controlRoot.hovered
        hasFocus: controlRoot.activeFocus
        enabled: controlRoot.enabled

        value: (controlRoot.up.pressed ? 1 : 0) |
                   (controlRoot.down.pressed ? 1<<1 : 0) |
                   ( controlRoot.value != controlRoot.to ? (1<<2) : 0) |
                   (controlRoot.value != controlRoot.from ? (1<<3) : 0) |
                   (controlRoot.up.hovered ? 0x1 : 0) |
                   (controlRoot.down.hovered ? (1<<1) : 0)
    }
}
