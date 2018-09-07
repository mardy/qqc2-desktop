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
import it.mardy.Desktop.private

T.Button {
    id: controlRoot

    implicitWidth: background.implicitWidth
    implicitHeight: background.implicitHeight

    hoverEnabled: Qt.styleHints.useHoverEffects

    contentItem: Item {}
    background: StyleItem {
        id: styleitem
        anchors.fill: parent
        control: controlRoot
        elementType: "button"
        sunken: controlRoot.pressed || (controlRoot.checkable && controlRoot.checked)
        raised: !(controlRoot.pressed || (controlRoot.checkable && controlRoot.checked))
        hover: controlRoot.hovered
        text: controlRoot.text
        hasFocus: controlRoot.activeFocus
        activeControl: controlRoot.isDefault ? "default" : "f"
        properties: {
            "icon": controlRoot.icon ? (controlRoot.icon.name || controlRoot.icon.source) : "",
            "iconColor": controlRoot.icon && controlRoot.icon.color.a > 0? controlRoot.icon.color : "transparent"
        }
    }
}
