/*
 * Copyright 2017 Marco Martin <mart@kde.org>
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
import QtQuick.Templates 2.2 as T
import it.mardy.Desktop.private 1.0

T.DelayButton {
    id: controlRoot

    implicitWidth: background.implicitWidth
    implicitHeight: background.implicitHeight

    transition: Transition {
        NumberAnimation {
            duration: controlRoot.delay * (controlRoot.pressed ? 1.0 - controlRoot.progress : 0.3 * controlRoot.progress)
        }
    }

    contentItem: Item {}
    background: StyleItem {
        id: styleitem
        control: controlRoot
        elementType: "button"
        sunken: controlRoot.down || controlRoot.checked
        raised: !(controlRoot.down || controlRoot.checked)
        hover: controlRoot.hovered
        text: controlRoot.text
        hasFocus: controlRoot.activeFocus
        activeControl: controlRoot.isDefault ? "default" : "f"

        StyleItem {
            anchors { fill: parent; margins: 3 }
            elementType: "progressbar"

            control: controlRoot
            maximum: 100
            minimum: 0
            value: controlRoot.progress * 100
            horizontal: true
            visible: controlRoot.progress > 0 && !controlRoot.checked
        }
    }
}
