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
import QtQuick.Templates 2.2 as T
import it.mardy.Desktop.private 1.0

T.SpinBox {
    id: root

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: background ? background.implicitHeight :
                            (contentItem.implicitHeight + topPadding + bottomPadding)

    leftPadding: style.subControlRect("edit").x
    rightPadding: background.implicitWidth - (style.subControlRect("edit").x + style.subControlRect("edit").width)
    topPadding: style.subControlRect("edit").y
    bottomPadding: background.implicitHeight - (style.subControlRect("edit").y + style.subControlRect("edit").height)

    editable: true // that's the default for QSpinBox

    validator: IntValidator {
        locale: root.locale.name
        bottom: Math.min(root.from, root.to)
        top: Math.max(root.from, root.to)
    }

    contentItem: TextField {
        z: 2
        text: root.textFromValue(root.value, root.locale)
        hasFrame: false
        opacity: root.enabled ? 1 : 0.3

        font: root.font

        readOnly: !root.editable
        validator: root.validator
        inputMethodHints: Qt.ImhFormattedNumbersOnly

        onActiveFocusChanged: cursorPosition = 0
        onTextChanged: style.sendKeyRelease(Qt.Key_Enter) // force value update

        MouseArea {
            anchors.fill: parent
            onPressed: mouse.accepted = false;
            onWheel: {
                if (wheel.pixelDelta.y < 0 || wheel.angleDelta.y < 0) {
                    root.decrease();
                } else {
                    root.increase();
                }
            }
        }
    }

    up.indicator: Item {
        implicitWidth: parent.height/2
        implicitHeight: implicitWidth
        x: parent.width - width
    }
    down.indicator: Item {
        implicitWidth: parent.height/2
        implicitHeight: implicitWidth
 
        x: parent.width - width
        y: parent.height - height
    }

    background: StyleItem {
        id: style
        control: root
        elementType: "spinbox"
        anchors.fill: parent
        hover: root.hovered
        hasFocus: root.activeFocus
        enabled: root.enabled
        contentHeight: root.contentItem.implicitHeight
        // compute texts for min and max values; the styleitem will split them
        // and measure their length
        text: root.textFromValue(root.from) + '_' + root.textFromValue(root.to)

        value: (root.up.pressed ? 1 : 0) |
                   (root.down.pressed ? 1<<1 : 0) |
                   (root.value != root.to ? (1<<2) : 0) |
                   (root.value != root.from ? (1<<3) : 0) |
                   (root.up.hovered ? 0x1 : 0) |
                   (root.down.hovered ? (1<<1) : 0)
    }
}
