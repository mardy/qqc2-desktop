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
import QtQuick.Templates 2.2 as T
import it.mardy.Desktop.private 1.0

T.ProgressBar {
    id: controlRoot

    property bool textVisible: true

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             contentItem.implicitHeight + topPadding + bottomPadding)

    contentItem: Item {}
    
    background: StyleItem {
        elementType: "progressbar"

        control: controlRoot
        maximum: indeterminate ? 0 : controlRoot.to*100
        minimum: indeterminate ? 0 : controlRoot.from*100
        value: indeterminate ? 0 : ((!controlRoot.inverted ? controlRoot.visualPosition : 1 - controlRoot.visualPosition)*controlRoot.to*100)
        horizontal: true
        enabled: controlRoot.enabled
        properties: {
            "textVisible": controlRoot.textVisible,
        }

        Timer {
            interval: 50
            running: controlRoot.indeterminate
            repeat: true
            onTriggered: parent.updateItem();
        }
    }
}
