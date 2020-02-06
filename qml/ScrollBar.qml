/*
 * Copyright 2017 Marco Martin <mart@kde.org>
 * Copyright 2017 The Qt Company Ltd.
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
import it.mardy.Desktop.private 1.0

T.ScrollBar {
    id: controlRoot

    implicitWidth: background.implicitWidth
    implicitHeight: background.implicitHeight

    visible: controlRoot.size < 1.0
    stepSize: 0.02

    background: MouseArea {
        id: mouseArea

        property real length: controlRoot.orientation == Qt.Horizontal ? controlRoot.width : controlRoot.height
        anchors.fill: parent
        visible: controlRoot.size < 1.0
        hoverEnabled: true
        state: "inactive"
        onPositionChanged: style.activeControl = style.hitTest(mouse.x, mouse.y)
        onExited: style.activeControl = "groove";
        onPressed: {
            if (style.activeControl == "down") {
                buttonTimer.increment = 1;
                controlRoot.increase();
                buttonTimer.restart()
                mouse.accepted = true
            } else if (style.activeControl == "up") {
                buttonTimer.increment = -1;
                controlRoot.decrease();
                buttonTimer.restart()
                mouse.accepted = true
            } else {
                mouse.accepted = false
            }
        }
        onReleased: {
            buttonTimer.running = false;
            mouse.accepted = false
        }
        onCanceled: buttonTimer.running = false;

        implicitWidth: style.implicitWidth
        implicitHeight: style.implicitHeight

        StyleItem {
            id: style
            property real size: controlRoot.size > 0 ? controlRoot.size : 0.5
            control: controlRoot
            anchors.fill: parent
            elementType: "scrollbar"
            hover: activeControl != "none"
            activeControl: "none"
            sunken: controlRoot.pressed
            minimum: 0
            maximum: parent.length / size
            step: controlRoot.stepSize * parent.length / size
            value: controlRoot.position * (parent.length/size)
            horizontal: controlRoot.orientation == Qt.Horizontal
            enabled: controlRoot.enabled

            visible: controlRoot.size < 1.0
            opacity: 1

            Timer {
                id: buttonTimer
                property real increment
                repeat: true
                interval: 150
                onTriggered: {
                    if (increment > 0) {
                        controlRoot.increase();
                    } else {
                        controlRoot.decrease();
                    }
                }
            }
        }
        StyleItem {
            id: inactiveStyle
            anchors.fill: parent
            control: controlRoot
            elementType: "scrollbar"
            activeControl: "none"
            sunken: false
            minimum: 0
            maximum: style.maximum
            step: style.step
            value: style.value
            horizontal: style.horizontal
            enabled: controlRoot.enabled

            visible: controlRoot.size < 1.0
            opacity: 1
        }
        states: [
            State {
                name: "hover"
                when: mouseArea.containsMouse
                PropertyChanges {
                    target: style
                    opacity: 1
                }
                PropertyChanges {
                    target: inactiveStyle
                    opacity: 0
                }
            },
            State {
                name: "inactive"
                when: !mouseArea.containsMouse
                PropertyChanges {
                    target: style
                    opacity: 0
                }
                PropertyChanges {
                    target: inactiveStyle
                    opacity: 1
                }
            }
        ]
        transitions: [
            Transition {
                ParallelAnimation {
                    NumberAnimation {
                        target: style
                        property: "opacity"
                        duration: 50
                        easing.type: Easing.InOutQuad
                    }
                    NumberAnimation {
                        target: inactiveStyle
                        property: "opacity"
                        duration: 50
                        easing.type: Easing.InOutQuad
                    }
                }
            }
        ]
    }

    contentItem: Item {}
}
