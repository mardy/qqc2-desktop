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

#include "style_p.h"

#include <QApplication>
#include <QDebug>
#include <cstring>

using namespace it::mardy;

Style::Style(QObject *parent):
    QObject(parent),
    m_style(qApp->style())
{
    memset(m_pixelMetrics, -1, sizeof(m_pixelMetrics));
}

Style::~Style()
{
}

int Style::layoutLeftMargin() const
{
    return loadMetric(QStyle::PM_LayoutLeftMargin);
}

int Style::layoutTopMargin() const
{
    return loadMetric(QStyle::PM_LayoutTopMargin);
}

int Style::layoutRightMargin() const
{
    return loadMetric(QStyle::PM_LayoutRightMargin);
}

int Style::layoutBottomMargin() const
{
    return loadMetric(QStyle::PM_LayoutBottomMargin);
}

int Style::layoutVerticalSpacing() const
{
    return loadMetric(QStyle::PM_LayoutVerticalSpacing);
}

int Style::layoutHorizontalSpacing() const
{
    return loadMetric(QStyle::PM_LayoutHorizontalSpacing);
}

int Style::loadMetric(QStyle::PixelMetric metric) const
{
    int &field = m_pixelMetrics[metric];
    if (field == -1) {
        field = m_style->pixelMetric(metric);
    }
    return field;
}
