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
import QtQuick.Controls 2.2
import QtQuick.Templates 2.2 as T
import it.mardy.Desktop.private 1.0

T.GroupBox {
    id: root

    implicitWidth: contentWidth + leftPadding + rightPadding
    implicitHeight: contentHeight + topPadding + bottomPadding

    contentWidth: contentItem.implicitWidth || (contentChildren.length === 1 ? contentChildren[0].implicitWidth : 0)
    contentHeight: contentItem.implicitHeight || (contentChildren.length === 1 ? contentChildren[0].implicitHeight : 0)

    leftPadding: styleItem.contentMargins.left
    topPadding: styleItem.contentMargins.top
    rightPadding: styleItem.contentMargins.right
    bottomPadding: styleItem.contentMargins.bottom

    background: StyleItem {
        id: styleItem
        control: root
        elementType: "groupbox"
        text: root.title
        hasFocus: root.activeFocus
    }
}
