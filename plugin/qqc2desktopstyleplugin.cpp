/*
 * Copyright 2017 by Marco Martin <mart@kde.org>
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

#include "qqc2desktopstyleplugin.h"
#include "styleitem_p.h"

#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickItem>

void QQc2DesktopStylePlugin::registerTypes(const char *uri)
{
    qmlRegisterType<KQuickPadding>();
    qmlRegisterType<KQuickStyleItem>(uri, 1, 0, "StyleItem");
}
