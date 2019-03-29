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
import QtQuick.Window 2.2
import QtQuick.Templates 2.2 as T
import QtQuick.Controls 2.2 as Controls
import QtGraphicalEffects 1.0
import it.mardy.Desktop.private 1.0

T.ComboBox {
    id: controlRoot

    implicitWidth: background.implicitWidth
    implicitHeight: background.implicitHeight
    baselineOffset: contentItem.y + contentItem.baselineOffset

    leftPadding: width,style.subControlRect("edit").x
    rightPadding: width - (style.subControlRect("edit").x + style.subControlRect("edit").width)
    topPadding: style.subControlRect("edit").y
    bottomPadding: height - (style.subControlRect("edit").y + style.subControlRect("edit").height)

    delegate: ComboBoxDelegate {
        comboBoxStyleItem: style
        width: controlRoot.popup.width - controlRoot.popup.leftPadding - controlRoot.popup.rightPadding
        text: controlRoot.textRole ? (Array.isArray(controlRoot.model) ? modelData[controlRoot.textRole] : model[controlRoot.textRole]) : modelData
        highlighted: activeFocus
    }

    indicator: Item {}

    contentItem: TextField {
        hasFrame: false

        text: controlRoot.editable ? controlRoot.editText : controlRoot.displayText

        enabled: controlRoot.editable
        autoScroll: controlRoot.editable
        readOnly: controlRoot.down
        
        visible: typeof(controlRoot.editable) != "undefined" && controlRoot.editable
        inputMethodHints: controlRoot.inputMethodHints
        validator: controlRoot.validator

        font: controlRoot.font
    }

    background: StyleItem {
        id: style
        control: controlRoot
        elementType: "combobox"
        anchors.fill: parent
        sunken: controlRoot.pressed
        raised: !sunken
        hasFocus: controlRoot.activeFocus
        enabled: controlRoot.enabled
        text: controlRoot.displayText
        properties: {
            "editable" : control.editable
        }

        MouseArea {
            anchors {
                fill: parent
                leftMargin: controlRoot.leftPadding
                rightMargin: controlRoot.rightPadding
            }
            acceptedButtons: Qt.NoButton
            onWheel: {
                if (wheel.pixelDelta.y < 0 || wheel.angleDelta.y < 0) {
                    controlRoot.currentIndex = Math.min(controlRoot.currentIndex + 1, delegateModel.count -1);
                } else {
                    controlRoot.currentIndex = Math.max(controlRoot.currentIndex - 1, 0);
                }
                controlRoot.activated(controlRoot.currentIndex);
            }
        }
    }

    popup: T.Popup {
        property int openingY: style.styleHint("comboboxpopup") ?
            (listview.currentItem ? -listview.currentItem.y : 0) :
            (controlRoot.height - 1)
        y: openingY
        width: controlRoot.width, Math.max(style.styleHint("comboBoxWidthHint"), 150)
        implicitHeight: contentItem.implicitHeight + topPadding + bottomPadding
        leftPadding: panelStyle.contentMargins.left
        topPadding: panelStyle.contentMargins.top
        rightPadding: panelStyle.contentMargins.right
        bottomPadding: panelStyle.contentMargins.bottom

        topMargin: 6
        bottomMargin: 6
        onOpened: {
            if (listview.currentItem) {
                listview.currentItem.forceActiveFocus()
            }
            // break the binding on the "y" property:
            var tmp = y
            y = tmp
        }

        contentItem: ListView {
            id: listview
            clip: true
            implicitWidth: contentItem.implicitWidth
            implicitHeight: contentHeight
            model: controlRoot.popup.visible ? controlRoot.delegateModel : null
            currentIndex: controlRoot.highlightedIndex
            highlightRangeMode: ListView.ApplyRange
            highlightMoveDuration: 0
            T.ScrollBar.vertical: Controls.ScrollBar { }
        }
        background: StyleItem {
            id: panelStyle
            anchors.fill: parent
            control: controlRoot
            elementType: "comboboxpopup"
            properties: {
                "combobox-style": style,
                "editable": control.editable,
            }
        }
    }
}
