/*
 * Copyright (C) 2019 Alberto Mardegan <mardy@users.sourceforge.net>
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

#ifndef STYLE_P_H
#define STYLE_P_H

#include <QStyle>

class QWidget;
class QStyleOption;

namespace it {
namespace mardy {

/* This is intended to be used as a singleton class (namespace) */
class Style: public QObject
{
    Q_OBJECT

    Q_PROPERTY(int layoutLeftMargin READ layoutLeftMargin CONSTANT)
    Q_PROPERTY(int layoutTopMargin READ layoutTopMargin CONSTANT)
    Q_PROPERTY(int layoutRightMargin READ layoutRightMargin CONSTANT)
    Q_PROPERTY(int layoutBottomMargin READ layoutBottomMargin CONSTANT)
    Q_PROPERTY(int layoutVerticalSpacing READ layoutVerticalSpacing CONSTANT)

public:
    Style(QObject *parent = nullptr);
    ~Style();

    int layoutLeftMargin() const;
    int layoutTopMargin() const;
    int layoutRightMargin() const;
    int layoutBottomMargin() const;
    int layoutVerticalSpacing() const;

private:
    inline int loadMetric(QStyle::PixelMetric metric) const;

private:
    QStyle *m_style;
    mutable int m_pixelMetrics[QStyle::PM_TitleBarButtonSize + 1];
};

} // namespace
} // namespace

#endif // STYLE_P_H
