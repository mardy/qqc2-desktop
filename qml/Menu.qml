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


import QtQuick 2.7
import QtQuick.Layouts 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.2
import QtQuick.Templates 2.2 as T
import it.mardy.Desktop.private 1.0

T.Menu {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem ? contentItem.implicitWidth + leftPadding + rightPadding : 0)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             contentItem ? contentItem.implicitHeight : 0) + topPadding + bottomPadding

    margins: 0

    contentItem: ListView {
        implicitWidth: control.contentItem.childrenRect.width
        implicitHeight: contentHeight
        property bool hasCheckables: false
        property bool hasIcons: false
        model: control.contentModel

        interactive: ApplicationWindow.window ? contentHeight > ApplicationWindow.window.height : false
        clip: true
        currentIndex: control.currentIndex || 0
        keyNavigationEnabled: true
        keyNavigationWraps: true

        ScrollBar.vertical: ScrollBar {}
    }

    Connections {
        target: control.contentItem.contentItem
        onChildrenChanged: {
            for (var i in control.contentItem.contentItem.children) {
                var child = control.contentItem.contentItem.children[i];
                if (child.checkable) {
                    control.contentItem.hasCheckables = true;
                }
                if (child.icon && child.icon.hasOwnProperty("name") && (child.icon.name.length > 0 || child.icon.source.length > 0)) {
                    control.contentItem.hasIcons = true;
                }
            }
        }
    }

    enter: Transition {
        NumberAnimation {
            property: "opacity"
            from: 0
            to: 1
            easing.type: Easing.InOutQuad
            duration: 150
        }
    }

    exit: Transition {
        NumberAnimation {
            property: "opacity"
            from: 1
            to: 0
            easing.type: Easing.InOutQuad
            duration: 150
        }
    }

    background: Rectangle {
        radius: 2
        implicitWidth: 64
        implicitHeight: 40
        color: SystemPaletteSingleton.base(true)
        property color borderColor: SystemPaletteSingleton.windowText(true)
        border.color: Qt.rgba(borderColor.r, borderColor.g, borderColor.b, 0.3)
        layer.enabled: true
        
        layer.effect: DropShadow {
            transparentBorder: true
            radius: 8
            samples: 8
            horizontalOffset: 0
            verticalOffset: 2
            color: Qt.rgba(0, 0, 0, 0.3)
        }
    }
}
