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
import QtQuick.Layouts 1.2
import QtQuick.Templates 2.2 as T
import it.mardy.Desktop.private 1.0

T.MenuItem {
    id: root

    property bool inMenuWithIcons: false
    property bool inMenuWithCheckables: false
    property int tabWidth: 0

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: visible ? Math.max(background ? background.implicitHeight : 0,
                             Math.max(contentItem.implicitHeight,
                                      indicator ? indicator.implicitHeight : 0) + topPadding + bottomPadding) : 0
    baselineOffset: contentItem.y + contentItem.baselineOffset

    Layout.fillWidth: true

    contentItem: StyleItem {
        id: styleItem
        control: root
        elementType: "menuitem"
        text: root.text
        selected: root.highlighted
        hasFocus: root.activeFocus
        on: root.checked
        properties: {
            "icon": root.icon,
            "inMenuWithIcons": root.inMenuWithIcons,
            "inMenuWithCheckables": root.inMenuWithCheckables,
            "tabWidth": root.tabWidth,
            "checkable": root.checkable,
            "shortcut": root.action ? root.action.shortcut : null
        }
    }

    indicator: Item {}

    background: Item {}
}
