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

#ifndef ICON_P_H
#define ICON_P_H

#include <QColor>
#include <QIcon>
#include <QString>
#include <QUrl>

struct QMetaObject;
class QVariant;

namespace it {
namespace mardy {

class Icon
{
public:
    Icon(const QVariant &variant);
    ~Icon();

    QString name() const;
    QUrl source() const;
    int width() const;
    int height() const;
    QColor color() const;

    QIcon toQIcon() const;

protected:
    QVariant readProperty(const char *name) const;

private:
    const void *m_gadget;
    const QMetaObject *m_meta;
};

} // namespace
} // namespace

#endif // ICON_P_H
