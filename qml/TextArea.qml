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
import QtQuick.Window 2.1
import QtQuick.Templates 2.2 as T
import it.mardy.Desktop.private 1.0

T.TextArea {
    id: controlRoot

    implicitWidth: Math.max(contentWidth + leftPadding + rightPadding,
                            background ? background.implicitWidth : 0,
                            placeholder.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(contentHeight + topPadding + bottomPadding,
                             background ? background.implicitHeight : 0,
                             placeholder.implicitHeight + topPadding + bottomPadding)

    padding: 6

    color: SystemPaletteSingleton.text(controlRoot.enabled)
    selectionColor: SystemPaletteSingleton.highlight(controlRoot.enabled)
    selectedTextColor: SystemPaletteSingleton.highlightedText(controlRoot.enabled)
    wrapMode: Text.WordWrap
    verticalAlignment: TextEdit.AlignTop

    // Work around Qt bug where NativeRendering breaks for non-integer scale factors
    // https://bugreports.qt.io/browse/QTBUG-67007
    renderType: Screen.devicePixelRatio % 1 !== 0 ? Text.QtRendering : Text.NativeRendering
    selectByMouse: true

    Label {
        id: placeholder
        x: controlRoot.leftPadding
        y: controlRoot.topPadding
        width: controlRoot.width - (controlRoot.leftPadding + controlRoot.rightPadding)
        height: controlRoot.height - (controlRoot.topPadding + controlRoot.bottomPadding)

        text: controlRoot.placeholderText
        font: controlRoot.font
        color: SystemPaletteSingleton.text(false)
        horizontalAlignment: controlRoot.horizontalAlignment
        verticalAlignment: controlRoot.verticalAlignment
        visible: !controlRoot.length && !controlRoot.preeditText && (!controlRoot.activeFocus || controlRoot.horizontalAlignment !== Qt.AlignHCenter)
        elide: Text.ElideRight
    }

    background: StyleItem {
        id: style
        control: controlRoot
        elementType: "edit"
        implicitWidth: 200
        implicitHeight: 22

        sunken: true
        hasFocus: controlRoot.activeFocus
        hover: controlRoot.hovered
    }
}