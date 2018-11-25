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


import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Templates 2.2 as T
import it.mardy.Desktop.private 1.0

T.ScrollView {
    id: controlRoot

    clip: true

    implicitWidth: Math.max(background ? background.implicitWidth : 0, contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0, contentHeight + topPadding + bottomPadding)

    contentWidth: contentItem ? contentItem.contentWidth : 0
    contentHeight: contentItem ? contentItem.contentHeight : 0

    //create a background only after Component.onCompleted, see on the component creation below for explanation
    Component.onCompleted: {
        if (!controlRoot.background) {
            controlRoot.background = backgroundComponent.createObject(controlRoot);
        }
    }

    /* TODO: recheck this:
     * create a background only after Component.onCompleted because:
     * implementations can set their own background in a declarative way
     * ScrollView {background.visible: true} must *not* work, becasue all  upstream styles don't have a background so applications using this would break with other styles
     * This is child of scrollHelper as it would break native scrollview finding of the flickable if it was a direct child
     */
    Component {
        id: backgroundComponent
        StyleItem {
            control: controlRoot
            elementType: "edit"
            visible: false
            sunken: true
            hasFocus: controlRoot.activeFocus || scrollHelper.flickableItem.activeFocus
            hover: controlRoot.hovered
        }
    }
    ScrollBar.vertical: ScrollBar {
        id: verticalScrollBar
        parent: controlRoot
        x: controlRoot.mirrored ? 0 : controlRoot.width - width
        y: controlRoot.topPadding
        height: controlRoot.availableHeight
        active: controlRoot.ScrollBar.horizontal || controlRoot.ScrollBar.horizontal.active
    }

    ScrollBar.horizontal: ScrollBar {
        parent: controlRoot
        x: controlRoot.leftPadding
        y: controlRoot.height - height
        width: controlRoot.availableWidth
        active: controlRoot.ScrollBar.vertical || controlRoot.ScrollBar.vertical.active
    }
}