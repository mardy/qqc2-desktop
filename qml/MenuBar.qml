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
import QtQuick.Controls QTQUICK_CONTROLS_VERSION
import QtQuick.Templates QTQUICK_CONTROLS_VERSION as T
import it.mardy.Desktop.private 1.0

T.MenuBar {
    id: root

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding)
    spacing: styleItem.pixelMetric("menubaritemspacing")
    leftPadding: styleItem.pixelMetric("menubarhmargin") +
                 styleItem.pixelMetric("menubarpanelwidth") +
                 spacing
    topPadding: styleItem.pixelMetric("menubarvmargin")

    delegate: MenuBarItem { }

    contentItem: Row {
        spacing: root.spacing
        Repeater {
            model: root.contentModel
        }
    }

    background: StyleItem {
        id: styleItem
        control: root
        elementType: "menubar"
        contentHeight: root.contentHeight
    }
}
