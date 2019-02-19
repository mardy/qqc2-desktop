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

pragma Singleton
import QtQuick 2.0

QtObject {
    property SystemPalette active: SystemPalette { colorGroup: SystemPalette.Active }
    property SystemPalette disabled: SystemPalette { colorGroup: SystemPalette.Disabled }

    function alternateBase(enabled) { return enabled ? active.alternateBase : disabled.alternateBase }
    function base(enabled) { return enabled ? active.base : disabled.base }
    function button(enabled) { return enabled ? active.button : disabled.button }
    function buttonText(enabled) { return enabled ? active.buttonText : disabled.buttonText }
    function dark(enabled) { return enabled ? active.dark : disabled.dark }
    function highlight(enabled) { return enabled ? active.highlight : disabled.highlight }
    function highlightedText(enabled) { return enabled ? active.highlightedText : disabled.highlightedText }
    function light(enabled) { return enabled ? active.light : disabled.light }
    function mid(enabled) { return enabled ? active.mid : disabled.mid }
    function midlight(enabled) { return enabled ? active.midlight : disabled.midlight }
    function shadow(enabled) { return enabled ? active.shadow : disabled.shadow }
    function text(enabled) { return enabled ? active.text : disabled.text }
    function window(enabled) { return enabled ? active.window : disabled.window }
    function windowText(enabled) { return enabled ? active.windowText : disabled.windowText }
}
