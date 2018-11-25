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

    hoverEnabled: true

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