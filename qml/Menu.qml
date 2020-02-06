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


import QtQuick 2.7
import QtQuick.Layouts 1.2
import QtQuick.Controls QTQUICK_CONTROLS_VERSION
import QtQuick.Templates QTQUICK_CONTROLS_VERSION as T
import it.mardy.Desktop.private 1.0

T.Menu {
    id: root

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem ? contentItem.implicitWidth + leftPadding + rightPadding : 0)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             contentItem ? contentItem.implicitHeight : 0) + topPadding + bottomPadding
    leftPadding: styleItem.pixelMetric("menuhmargin") +
                 styleItem.pixelMetric("menupanelwidth")
    rightPadding: styleItem.pixelMetric("menuhmargin") +
                  styleItem.pixelMetric("menupanelwidth")
    topPadding: styleItem.pixelMetric("menuvmargin") +
                styleItem.pixelMetric("menupanelwidth")
    bottomPadding: styleItem.pixelMetric("menuvmargin") +
                   styleItem.pixelMetric("menupanelwidth")

    margins: 0

    contentItem: ListView {
        id: listView
        implicitWidth: childrenImplicitWidth + maxTabWidth
        implicitHeight: contentHeight
        property bool hasCheckables: false
        property bool hasIcons: false
        property int childrenImplicitWidth: 0
        property int maxTabWidth: 0
        model: root.contentModel

        interactive: ApplicationWindow.window ? contentHeight > ApplicationWindow.window.height : false
        clip: true
        currentIndex: root.currentIndex || 0
        keyNavigationEnabled: true
        keyNavigationWraps: true

        ScrollBar.vertical: ScrollBar {}
    }
    delegate: MenuItem {
        width: listView.width
        inMenuWithIcons: listView.hasIcons
        inMenuWithCheckables: listView.hasCheckables
        tabWidth: listView.maxTabWidth
    }
    onOpened: currentIndex = 0

    Connections {
        target: root.contentItem.contentItem
        onChildrenChanged: {
            var maxTabWidth = 0
            var implicitWidth = 0
            for (var i in root.contentItem.contentItem.children) {
                var child = root.contentItem.contentItem.children[i];
                implicitWidth = Math.max(implicitWidth, child.implicitWidth)
                if (child.checkable) {
                    root.contentItem.hasCheckables = true;
                }
                if (child.icon && child.icon.hasOwnProperty("name") && (child.icon.name.length > 0 || child.icon.source.length > 0)) {
                    root.contentItem.hasIcons = true;
                }
                if (child.contentItem) {
                    var tabWidth = child.contentItem.outputProperties.tabWidth
                    if (tabWidth && tabWidth > maxTabWidth)
                        maxTabWidth = tabWidth
                }
            }
            root.contentItem.childrenImplicitWidth = implicitWidth
            root.contentItem.maxTabWidth = maxTabWidth
        }
    }

    background: StyleItem {
        id: styleItem
        control: root.parent
        elementType: "menu"
    }
}
