/*
 * Copyright 2017 by Marco Martin <mart@kde.org>
 * Copyright 2017 by David Edmundson <davidedmundson@kde.org>
 * Copyright (C) 2016 The Qt Company Ltd.
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

#ifndef KQUICKPADDING_H
#define KQUICKPADDING_H

#include <QtCore/qobject.h>
#include <QQmlEngine>

class KQuickPadding : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int left READ left WRITE setLeft NOTIFY leftChanged)
    Q_PROPERTY(int top READ top WRITE setTop NOTIFY topChanged)
    Q_PROPERTY(int right READ right WRITE setRight NOTIFY rightChanged)
    Q_PROPERTY(int bottom READ bottom WRITE setBottom NOTIFY bottomChanged)

    int m_left;
    int m_top;
    int m_right;
    int m_bottom;

public:
    KQuickPadding(QObject *parent = nullptr) :
        QObject(parent),
        m_left(0),
        m_top(0),
        m_right(0),
        m_bottom(0) {}

    int left() const { return m_left; }
    int top() const { return m_top; }
    int right() const { return m_right; }
    int bottom() const { return m_bottom; }

public slots:
    void setLeft(int arg) { if (m_left != arg) {m_left = arg; emit leftChanged();}}
    void setTop(int arg) { if (m_top != arg) {m_top = arg; emit topChanged();}}
    void setRight(int arg) { if (m_right != arg) {m_right = arg; emit rightChanged();}}
    void setBottom(int arg) {if (m_bottom != arg) {m_bottom = arg; emit bottomChanged();}}

signals:
    void leftChanged();
    void topChanged();
    void rightChanged();
    void bottomChanged();

private:
    Q_DISABLE_COPY(KQuickPadding)
};

QML_DECLARE_TYPE(KQuickPadding)

#endif // QQUICKPADDING_H
