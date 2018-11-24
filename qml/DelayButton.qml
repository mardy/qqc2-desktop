/*
 * Copyright 2017 Marco Martin <mart@kde.org>
 * Copyright 2017 The Qt Company Ltd.
 *
 * GNU Lesser General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU Lesser
 * General Public License version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.LGPLv3 included in the
 * packaging of this file. Please review the following information to
 * ensure the GNU Lesser General Public License version 3 requirements
 * will be met: https://www.gnu.org/licenses/lgpl.html.
 *
 * GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 2.0 or later as published by the Free
 * Software Foundation and appearing in the file LICENSE.GPL included in
 * the packaging of this file. Please review the following information to
 * ensure the GNU General Public License version 2.0 requirements will be
 * met: http://www.gnu.org/licenses/gpl-2.0.html.
 */

import QtQuick 2.6
import QtQuick.Templates 2.2 as T
import it.mardy.Desktop.private 1.0

T.DelayButton {
    id: controlRoot

    implicitWidth: background.implicitWidth
    implicitHeight: background.implicitHeight

    hoverEnabled: true

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
