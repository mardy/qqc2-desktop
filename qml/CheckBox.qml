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
import QtQuick.Controls 2.2
import it.mardy.Desktop.private 1.0

T.CheckBox {
    id: controlRoot

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             Math.max(contentItem.implicitHeight,
                                      indicator ? indicator.implicitHeight : 0) + topPadding + bottomPadding)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    padding: 1
    spacing: 4 // FIXME: on Mac this should be 2

    hoverEnabled: true

    contentItem: Item {}

    background: StyleItem {
        control: controlRoot
        elementType: "checkbox"
        text: controlRoot.text
        sunken: controlRoot.down
        on: controlRoot.checkState == Qt.Checked
        hasFocus: controlRoot.activeFocus
        properties: {
            "partiallyChecked": controlRoot.checkState == Qt.PartiallyChecked,
            "icon": controlRoot.icon ? (controlRoot.icon.name || controlRoot.icon.source) : "",
            "iconColor": controlRoot.icon && controlRoot.icon.color.a > 0? controlRoot.icon.color : "transparent"
        }
    }
}
