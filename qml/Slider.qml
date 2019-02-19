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

T.Slider {
    id: controlRoot

    implicitWidth: background.implicitWidth
    implicitHeight: background.implicitHeight

    handle: Item {}
    
    snapMode: T.Slider.SnapOnRelease

    background: StyleItem {
        control: controlRoot
        elementType: "slider"
        sunken: controlRoot.pressed
        contentHeight: horizontal ? 22 : 200
        contentWidth: horizontal ? 200 : 22

        maximum: controlRoot.to*100
        minimum: controlRoot.from*100
        step: controlRoot.stepSize*100
        value: (horizontal ? controlRoot.visualPosition : 1 - controlRoot.visualPosition)*controlRoot.to*100
        horizontal: controlRoot.orientation === Qt.Horizontal
        enabled: controlRoot.enabled
        hasFocus: controlRoot.activeFocus
        hover: controlRoot.hovered
        activeControl: controlRoot.stepSize > 0 ? "ticks" : ""
    }
}
