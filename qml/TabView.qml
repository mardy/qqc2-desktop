/*
 * Copyright (C) 2019-2020 Alberto Mardegan <mardy@users.sourceforge.net>
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
import QtQuick.Layouts 1.3
import QtQuick.Templates 2.2 as T
import it.mardy.Desktop.private 1.0

FocusScope {
    id: root

    property Item tabBar: null
    property Item stack: stackLayout
    default property alias data: stackLayout.data

    implicitWidth: styleItem.implicitWidth
    implicitHeight: tabBar.implicitHeight + styleItem.implicitHeight

    onTabBarChanged: if (tabBar) {
        tabBar.parent = styleItem
        tabBar.focus = true
    }

    StyleItem {
        id: styleItem
        anchors.fill: parent
        control: root
        elementType: "tabframe"
        contentWidth: Math.max(tabBar.implicitWidth, stackLayout.implicitWidth)
        contentHeight: stackLayout.implicitHeight
        properties: {
            "orientation" : root.position == T.TabBar.Header ? "Top" : "Bottom",
            "tabBar": tabBar,
        }

        StackLayout {
            id: stackLayout
            property alias cm: styleItem.contentMargins
            anchors {
                fill: parent
                topMargin: cm.top
                leftMargin: cm.left
                rightMargin: cm.right
                bottomMargin: cm.bottom
            }
            currentIndex: tabBar ? tabBar.currentIndex : 0
        }
    }
}
