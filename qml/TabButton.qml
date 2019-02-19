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


import QtQuick 2.6
import QtQml.Models 2.1
//for TabBar.*
import QtQuick.Controls 2.2
import QtQuick.Templates 2.2 as T
import it.mardy.Desktop.private 1.0

T.TabButton {
    id: controlRoot

    implicitWidth: Math.max(styleitem.implicitWidth, textMetrics.width + 8)
    implicitHeight: styleitem.implicitHeight
    baselineOffset: contentItem.y + contentItem.baselineOffset

    //This width: is important to make the tabbar internals not assume
    //all tabs have the same width
    width: implicitWidth
    padding: 0

    contentItem: Item {}

    background: StyleItem {
        id: styleitem

        TextMetrics {
            id: textMetrics
            text: controlRoot.text
        }

        control: controlRoot
        anchors.fill: parent
        elementType: "tab"
        paintMargins: 0
        property Item tabBar: controlRoot.parent.parent.parent

        property string orientation: tabBar.position == TabBar.Header ? "Top" : "Bottom"
        property string selectedpos: tabBar.currentIndex == controlRoot.ObjectModel.index + 1 ? "next" :
                                    tabBar.currentIndex == controlRoot.ObjectModel.index - 1 ? "previous" : ""
        property string tabpos: tabBar.count === 1 ? "only" : controlRoot.ObjectModel.index === 0 ? "beginning" : controlRoot.ObjectModel.index === tabBar.count - 1 ? "end" : "middle"

        properties: {
            "hasFrame" : true,
            "orientation": orientation,
            "tabpos": tabpos,
            "selectedpos": selectedpos,
            "icon": control.icon ? (control.icon.name || control.icon.source) : "",
            "iconColor": controlRoot.icon && controlRoot.icon.color.a > 0? controlRoot.icon.color : SystemPaletteSingleton.text(controlRoot.enabled)
        }

        enabled: controlRoot.enabled
        selected: controlRoot.checked
        text: controlRoot.text
        hover: controlRoot.hovered
        hasFocus: controlRoot.activeFocus
    }
}
