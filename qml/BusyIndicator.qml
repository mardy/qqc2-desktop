/*
 * Copyright 2018 Oleg Chernovskiy <adonai@xaker.ru>
 * Copyright 2018 The Qt Company Ltd.
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
import QtQuick.Templates 2.2 as T

T.BusyIndicator {
    id: controlRoot

    implicitWidth: contentItem.implicitWidth + leftPadding + rightPadding
    implicitHeight: contentItem.implicitHeight + topPadding + bottomPadding

    padding: 6
    spacing: Kirigami.Units.smallSpacing

    contentItem: Kirigami.Icon {
        source: "view-refresh"
        opacity: controlRoot.running ? 1 : 0
        smooth: true

        // appearing/fading opacity change
        Behavior on opacity {
            OpacityAnimator { duration: 250 }
        }

        // rotating loading icon
        RotationAnimator {
            target: controlRoot.contentItem
            running: controlRoot.visible && controlRoot.running
            from: 360
            to: 0
            loops: Animation.Infinite
            duration: 1000
        }
    }
}
