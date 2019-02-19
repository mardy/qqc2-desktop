/*
 * Copyright 2018 Kai Uwe Broulik <kde@privat.broulik.de>
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
import it.mardy.Desktop.private 1.0

StyleItem {
    elementType: "focusrect"
    // those random numbers come from QQC1 desktop style
    anchors {
        top: parent.top
        bottom: parent.bottom
        topMargin: parent.topPadding - 1
        bottomMargin: parent.bottomPadding - 1
    }
    // this is explicitly not using left anchor for auto mirroring
    // since the label's leftPadding/rightPadding already accounts for that
    x: parent.leftPadding - 2
    width: parent.implicitWidth - parent.leftPadding - parent.rightPadding + 3
    visible: control.activeFocus
}
