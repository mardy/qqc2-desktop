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

#include "icon_p.h"

#include <QDebug>
#include <QVariant>
#include <QMetaObject>
#include <QMetaProperty>
#include <QMetaType>

using namespace it::mardy;

Icon::Icon(const QVariant &variant):
    m_gadget(variant.constData()),
    m_meta(QMetaType::metaObjectForType(variant.userType()))
{
}

Icon::~Icon()
{
}

QVariant Icon::readProperty(const char *name) const
{
    if (!m_gadget || !m_meta) return QVariant();

    QMetaProperty sourceProperty =
        m_meta->property(m_meta->indexOfProperty(name));
    return sourceProperty.readOnGadget(m_gadget);
}

QString Icon::name() const
{
    return readProperty("name").toString();
}

QUrl Icon::source() const
{
    return readProperty("source").toUrl();
}

int Icon::width() const
{
    return readProperty("width").toInt();
}

int Icon::height() const
{
    return readProperty("height").toInt();
}

QColor Icon::color() const
{
    return readProperty("color").value<QColor>();
}

QIcon Icon::toQIcon() const
{
    QIcon icon;

    if (!name().isEmpty()) {
        icon = QIcon::fromTheme(name());
    } else if (!source().isEmpty()) {
        QUrl url = source();
        icon = url.scheme() == QStringLiteral("qrc") ?
            QIcon(url.toString().mid(3)) :
            QIcon(url.toLocalFile());
    }

    return icon;
}
