/*
 * Copyright 2017 Marco Martin <mart@kde.org>
 * Copyright 2017 The Qt Company Ltd.
 * Copyright (C) 2018 Alberto Mardegan <mardy@users.sourceforge.net>
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
import it.mardy.Desktop.private 1.0

Rectangle {
    id: background
    color: highlighted || (controlRoot.pressed && !controlRoot.checked && !controlRoot.sectionDelegate) ? SystemPaletteSingleton.highlight(enabled) : SystemPaletteSingleton.base(enabled)

    visible: controlRoot.ListView.view ? controlRoot.ListView.view.highlight === null : true
    Rectangle {
        anchors.fill: parent
        color: SystemPaletteSingleton.highlight(parent.enabled)
        opacity: controlRoot.hovered && !controlRoot.pressed ? 0.2 : 0
    }
}

