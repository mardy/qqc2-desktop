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

#include "styleitem_p.h"

#include "icon_p.h"

#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QPixmapCache>
#include <QQuickWindow>
#include <QStringBuilder>
#include <QStyle>
#include <QStyleOption>
#include <QTextDocument>
#include <QTimer>
#include <QToolBar>
#include <QtMath>
#include <QtQuick/qsgninepatchnode.h>

#define LINEEDIT_HORIZONAL_MARGIN 2
#define LINEEDIT_VERTICAL_MARGIN 1

StyleItem::StyleItem(QQuickItem *parent):
    QQuickItem(parent),
    m_styleoption(nullptr),
    m_control(nullptr),
    m_itemType(Undefined),
    m_sunken(false),
    m_raised(false),
    m_active(true),
    m_selected(false),
    m_focus(false),
    m_hover(false),
    m_on(false),
    m_horizontal(true),
    m_transient(false),
    m_sharedWidget(false),
    m_minimum(0),
    m_maximum(100),
    m_value(0),
    m_step(0),
    m_paintMargins(0),
    m_contentWidth(0),
    m_contentHeight(0),
    m_textureWidth(0),
    m_textureHeight(0),
    m_lastFocusReason(Qt::NoFocusReason)
{
    m_font = qApp->font();
    setFlag(QQuickItem::ItemHasContents, true);
    setSmooth(false);
}

StyleItem::~StyleItem()
{
    if (const QStyleOptionButton *aux =
        qstyleoption_cast<const QStyleOptionButton*>(m_styleoption))
        delete aux;
    else if (const QStyleOptionViewItem *aux =
             qstyleoption_cast<const QStyleOptionViewItem*>(m_styleoption))
        delete aux;
    else if (const QStyleOptionHeader *aux =
             qstyleoption_cast<const QStyleOptionHeader*>(m_styleoption))
        delete aux;
    else if (const QStyleOptionToolButton *aux =
             qstyleoption_cast<const QStyleOptionToolButton*>(m_styleoption))
        delete aux;
    else if (const QStyleOptionToolBar *aux =
             qstyleoption_cast<const QStyleOptionToolBar*>(m_styleoption))
        delete aux;
    else if (const QStyleOptionTab *aux =
             qstyleoption_cast<const QStyleOptionTab*>(m_styleoption))
        delete aux;
    else if (const QStyleOptionFrame *aux =
             qstyleoption_cast<const QStyleOptionFrame*>(m_styleoption))
        delete aux;
    else if (const QStyleOptionFocusRect *aux =
             qstyleoption_cast<const QStyleOptionFocusRect*>(m_styleoption))
        delete aux;
    else if (const QStyleOptionTabWidgetFrame *aux =
             qstyleoption_cast<const QStyleOptionTabWidgetFrame*>(m_styleoption))
        delete aux;
    else if (const QStyleOptionMenuItem *aux =
             qstyleoption_cast<const QStyleOptionMenuItem*>(m_styleoption))
        delete aux;
    else if (const QStyleOptionComboBox *aux =
             qstyleoption_cast<const QStyleOptionComboBox*>(m_styleoption))
        delete aux;
    else if (const QStyleOptionSpinBox *aux =
             qstyleoption_cast<const QStyleOptionSpinBox*>(m_styleoption))
        delete aux;
    else if (const QStyleOptionSlider *aux =
             qstyleoption_cast<const QStyleOptionSlider*>(m_styleoption))
        delete aux;
    else if (const QStyleOptionProgressBar *aux =
             qstyleoption_cast<const QStyleOptionProgressBar*>(m_styleoption))
        delete aux;
    else if (const QStyleOptionGroupBox *aux =
             qstyleoption_cast<const QStyleOptionGroupBox*>(m_styleoption))
        delete aux;
    else if (const QStyleOptionTitleBar *aux =
             qstyleoption_cast<const QStyleOptionTitleBar*>(m_styleoption))
        delete aux;
    else
        delete m_styleoption;

    m_styleoption = nullptr;
}

void StyleItem::componentComplete()
{
    connect(this, &StyleItem::visibleChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::enabledChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::infoChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::onChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::selectedChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::activeChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::textChanged,
            this, &StyleItem::updateSizeHint);
    connect(this, &StyleItem::textChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::activeChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::raisedChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::sunkenChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::hoverChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::maximumChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::minimumChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::valueChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::horizontalChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::transientChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::activeControlChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::hasFocusChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::activeControlChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::hintChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::propertiesChanged,
            this, &StyleItem::updateSizeHint);
    connect(this, &StyleItem::propertiesChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::elementTypeChanged,
            this, &StyleItem::updateItem);
    connect(this, &StyleItem::contentWidthChanged,
            this, &StyleItem::updateSizeHint);
    connect(this, &StyleItem::contentHeightChanged,
            this, &StyleItem::updateSizeHint);
    connect(this, &StyleItem::widthChanged,
            this, &StyleItem::updateRect);
    connect(this, &StyleItem::heightChanged,
            this, &StyleItem::updateRect);

    connect(this, &StyleItem::heightChanged,
            this, &StyleItem::updateBaselineOffset);
    connect(this, &StyleItem::contentHeightChanged,
            this, &StyleItem::updateBaselineOffset);

    connect(this, &StyleItem::textChanged,
            this, &StyleItem::updateRendersText);
    connect(this, &StyleItem::propertiesChanged,
            this, &StyleItem::updateRendersText);

    updateRendersText();
    updateItem();
    updateSizeHint();
    QQuickItem::componentComplete();
}

void StyleItem::setSunken(bool sunken)
{
    if (m_sunken != sunken) {
        m_sunken = sunken;
        Q_EMIT sunkenChanged();
    }
}

void StyleItem::setRaised(bool raised)
{
    if (m_raised!= raised) {
        m_raised = raised;
        Q_EMIT raisedChanged();
    }
}

void StyleItem::setActive(bool active)
{
    if (m_active!= active) {
        m_active = active;
        Q_EMIT activeChanged();
    }
}

void StyleItem::setSelected(bool selected)
{
    if (m_selected!= selected) {
        m_selected = selected;
        Q_EMIT selectedChanged();
    }
}

void StyleItem::setHasFocus(bool focus)
{
    if (m_focus != focus) {
        m_focus = focus;
        Q_EMIT hasFocusChanged();
    }
}

void StyleItem::setOn(bool on)
{
    if (m_on != on) {
        m_on = on;
        Q_EMIT onChanged();
    }
}

void StyleItem::setHover(bool hover)
{
    if (m_hover != hover) {
        m_hover = hover;
        Q_EMIT hoverChanged();
    }
}

void StyleItem::setHorizontal(bool horizontal)
{
    if (m_horizontal != horizontal) {
        m_horizontal = horizontal;
        Q_EMIT horizontalChanged();
    }
}

void StyleItem::setTransient(bool transient)
{
    if (m_transient != transient) {
        m_transient = transient;
        Q_EMIT transientChanged();
    }
}

void StyleItem::setMinimum(int minimum)
{
    if (m_minimum!= minimum) {
        m_minimum = minimum;
        Q_EMIT minimumChanged();
    }
}

void StyleItem::setMaximum(int maximum)
{
    if (m_maximum != maximum) {
        m_maximum = maximum;
        Q_EMIT maximumChanged();
    }
}

void StyleItem::setValue(int value)
{
    if (m_value!= value) {
        m_value = value;
        Q_EMIT valueChanged();
    }
}

void StyleItem::setStep(int step)
{
    if (m_step != step) {
        m_step = step;
        Q_EMIT stepChanged();
    }
}

void StyleItem::setPaintMargins(int value)
{
    if (m_paintMargins!= value) {
        m_paintMargins = value;
        Q_EMIT paintMarginsChanged();
    }
}

void StyleItem::setText(const QString &str)
{
    if (m_text != str) {
        m_text = str;
        Q_EMIT textChanged();
    }
}

void StyleItem::setActiveControl(const QString &str)
{
    if (m_activeControl != str) {
        m_activeControl = str;
        Q_EMIT activeControlChanged();
    }
}

void StyleItem::setProperties(const QVariantMap &props)
{
    if (m_properties != props) {
        m_properties = props;
        Q_EMIT propertiesChanged();
    }
}

void StyleItem::initStyleOption()
{
    QStyle *style = qApp->style();
    if (m_styleoption)
        m_styleoption->state = 0;

    QRect rect;

    switch (m_itemType) {
    case Button:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionButton();

            QStyleOptionButton *opt =
                qstyleoption_cast<QStyleOptionButton*>(m_styleoption);
            opt->text = text();

            const QVariant icon = m_properties[QStringLiteral("icon")];
            if (icon.canConvert<QIcon>()) {
                opt->icon = icon.value<QIcon>();
            } else if (icon.canConvert<QString>()) {
                opt->icon = QIcon::fromTheme(icon.value<QString>());
            }
            int e = style->pixelMetric(QStyle::PM_ButtonIconSize,
                                       m_styleoption, nullptr);
            opt->iconSize = QSize(e, e);
            opt->features = activeControl() == QLatin1String("default") ?
                        QStyleOptionButton::DefaultButton :
                        QStyleOptionButton::None;
            const QFont font = qApp->font("QPushButton");
            opt->fontMetrics = QFontMetrics(font);
            QObject *menu =
                m_properties[QStringLiteral("menu")].value<QObject *>();
            if (menu) {
                opt->features |= QStyleOptionButton::HasMenu;
            }
        }
        break;
    case ComboBoxDelegate:
        {
            if (!m_styleoption) {
                m_styleoption = new QStyleOptionViewItem();
            }
            QStyleOptionViewItem *opt =
                qstyleoption_cast<QStyleOptionViewItem*>(m_styleoption);
            opt->features = QStyleOptionViewItem::HasDisplay;
            opt->text = text();
            opt->textElideMode = Qt::ElideRight;
            opt->displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;
            opt->decorationAlignment = Qt::AlignCenter;
            const QFont font = qApp->font("QAbstractItemView");
            opt->font = font;
            opt->fontMetrics = QFontMetrics(font);
        }
        break;
    case ItemRow:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionViewItem();

            QStyleOptionViewItem *opt =
                qstyleoption_cast<QStyleOptionViewItem*>(m_styleoption);
            opt->features = 0;
            if (activeControl() == QLatin1String("alternate"))
                opt->features |= QStyleOptionViewItem::Alternate;
        }
        break;

    case Splitter:
        {
            if (!m_styleoption) {
                m_styleoption = new QStyleOption;
            }
        }
        break;

    case Item:
        {
            if (!m_styleoption) {
                m_styleoption = new QStyleOptionViewItem();
            }
            QStyleOptionViewItem *opt =
                qstyleoption_cast<QStyleOptionViewItem*>(m_styleoption);
            opt->features = QStyleOptionViewItem::HasDisplay;
            opt->text = text();
            opt->textElideMode = Qt::ElideRight;
            opt->displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;
            opt->decorationAlignment = Qt::AlignCenter;
            const QFont font = qApp->font("QAbstractItemView");
            opt->font = font;
            opt->fontMetrics = QFontMetrics(font);
        }
        break;
    case ItemBranchIndicator:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOption;

            m_styleoption->state = QStyle::State_Item; /* We don't want to
                                                        * fully support Win 95
                                                        */
            if (m_properties.value(QStringLiteral("hasChildren")).toBool())
                m_styleoption->state |= QStyle::State_Children;
            // Even this one could go away
            if (m_properties.value(QStringLiteral("hasSibling")).toBool())
                m_styleoption->state |= QStyle::State_Sibling;
            if (m_on)
                m_styleoption->state |= QStyle::State_Open;
        }
        break;
    case Header:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionHeader();

            QStyleOptionHeader *opt =
                qstyleoption_cast<QStyleOptionHeader*>(m_styleoption);
            opt->text = text();
            opt->textAlignment = static_cast<Qt::AlignmentFlag>(m_properties.value(QStringLiteral("textalignment")).toInt());
            opt->sortIndicator = activeControl() == QLatin1String("down") ?
                QStyleOptionHeader::SortDown :
                activeControl() == QLatin1String("up") ?
                    QStyleOptionHeader::SortUp : QStyleOptionHeader::None;
            QString headerpos = m_properties.value(QStringLiteral("headerpos")).toString();
            if (headerpos == QLatin1String("beginning"))
                opt->position = QStyleOptionHeader::Beginning;
            else if (headerpos == QLatin1String("end"))
                opt->position = QStyleOptionHeader::End;
            else if (headerpos == QLatin1String("only"))
                opt->position = QStyleOptionHeader::OnlyOneSection;
            else
                opt->position = QStyleOptionHeader::Middle;

            const QFont font = qApp->font("QHeaderView");
            opt->fontMetrics = QFontMetrics(font);
        }
        break;
    case ToolButton:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionToolButton();

            QStyleOptionToolButton *opt =
                qstyleoption_cast<QStyleOptionToolButton*>(m_styleoption);
            opt->subControls = QStyle::SC_ToolButton;
            opt->state |= QStyle::State_AutoRaise;
            opt->activeSubControls = QStyle::SC_ToolButton;
            opt->text = text();

            it::mardy::Icon icon(m_properties[QStringLiteral("icon")]);
            if (!icon.name().isEmpty()) {
                opt->icon = QIcon::fromTheme(icon.name());
            } else if (!icon.source().isEmpty()) {
                QUrl source = icon.source();
                opt->icon = source.scheme() == QStringLiteral("qrc") ?
                    QIcon(source.toString().mid(3)) :
                    QIcon(source.toLocalFile());
            }

            if (m_properties.value(QStringLiteral("menu")).toBool()) {
                opt->subControls |= QStyle::SC_ToolButtonMenu;
                opt->features = QStyleOptionToolButton::HasMenu;
            }

            QVariant buttonStyle =
                m_properties.value(QStringLiteral("display"));
            opt->toolButtonStyle =
                buttonStyle.canConvert<Qt::ToolButtonStyle>() ?
                buttonStyle.value<Qt::ToolButtonStyle>() :
                Qt::ToolButtonTextBesideIcon;
            if (opt->icon.isNull()) {
                opt->toolButtonStyle = Qt::ToolButtonTextOnly;
            }

            QStyle::PixelMetric metric = hasAncestor("QQuickToolBar") ?
                QStyle::PM_ToolBarIconSize : QStyle::PM_ButtonIconSize;
            int e = style->pixelMetric(metric, m_styleoption, nullptr);
            opt->iconSize = QSize(e, e);

            const QFont font = qApp->font("QToolButton");
            opt->font = font;
            opt->fontMetrics = QFontMetrics(font);
        }
        break;
    case ToolBar:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionToolBar();
            QStyleOptionToolBar *opt =
                qstyleoption_cast<QStyleOptionToolBar*>(m_styleoption);
            opt->state |= QStyle::State_Horizontal;
            opt->lineWidth =
                style->pixelMetric(QStyle::PM_ToolBarFrameWidth, 0);
            int position =
                m_properties.value(QStringLiteral("position")).toInt();
            if (position == 0) { // top
                opt->toolBarArea = Qt::TopToolBarArea;
            } else if (position == 1) { // bottom
                opt->toolBarArea = Qt::BottomToolBarArea;
            } else {
                opt->toolBarArea = Qt::NoToolBarArea;
            }
            opt->positionWithinLine = QStyleOptionToolBar::OnlyOne;
            opt->positionOfLine = QStyleOptionToolBar::OnlyOne;
        }
        break;
    case Tab:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionTab();

            QStyleOptionTab *opt =
                qstyleoption_cast<QStyleOptionTab*>(m_styleoption);
            opt->text = text();

            if (m_properties.value(QStringLiteral("hasFrame")).toBool())
                opt->features |= QStyleOptionTab::HasFrame;

            QString orientation =
                m_properties.value(QStringLiteral("orientation")).toString();
            QString position =
                m_properties.value(QStringLiteral("tabpos")).toString();
            QString selectedPosition =
                m_properties.value(QStringLiteral("selectedpos")).toString();

            opt->shape = orientation == QLatin1String("Bottom") ?
                QTabBar::RoundedSouth : QTabBar::RoundedNorth;
            if (position == QLatin1String("beginning"))
                opt->position = QStyleOptionTab::Beginning;
            else if (position == QLatin1String("end"))
                opt->position = QStyleOptionTab::End;
            else if (position == QLatin1String("only"))
                opt->position = QStyleOptionTab::OnlyOneTab;
            else
                opt->position = QStyleOptionTab::Middle;

            if (selectedPosition == QLatin1String("next"))
                opt->selectedPosition = QStyleOptionTab::NextIsSelected;
            else if (selectedPosition == QLatin1String("previous"))
                opt->selectedPosition = QStyleOptionTab::PreviousIsSelected;
            else
                opt->selectedPosition = QStyleOptionTab::NotAdjacent;
        }
        break;
    case ComboBoxPopup: // fall through
    case Frame:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionFrame();

            QStyleOptionFrame *opt =
                qstyleoption_cast<QStyleOptionFrame*>(m_styleoption);
            opt->frameShape = QFrame::StyledPanel;
            opt->lineWidth = 1;
            opt->midLineWidth = 1;

            StyleItem *comboBox = qobject_cast<StyleItem*>(
                m_properties.value(QStringLiteral("combobox-style")).
                value<QObject*>());
            if (comboBox) {
                opt->midLineWidth = 0;
                int frameStyle =
                    style->styleHint(QStyle::SH_ComboBox_PopupFrameStyle,
                                     comboBox->m_styleoption);
                opt->frameShape =
                    QFrame::Shape(frameStyle & QFrame::Shape_Mask);
            }
        }
        break;
    case FocusRect:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionFocusRect();
            // Needed on windows
            m_styleoption->state |= QStyle::State_KeyboardFocusChange;
        }
        break;
    case TabFrame:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionTabWidgetFrame();
            QStyleOptionTabWidgetFrame *opt =
                qstyleoption_cast<QStyleOptionTabWidgetFrame*>(m_styleoption);
            QQuickItem *tabBar = qobject_cast<QQuickItem*>(
                m_properties[QStringLiteral("tabBar")].value<QObject*>());
            if (tabBar) {
                QQuickItem *selectedTab =
                    tabBar->property("currentItem").value<QQuickItem*>();
                if (selectedTab) {
                    opt->selectedTabRect = QRect(selectedTab->x(),
                                                 selectedTab->y(),
                                                 selectedTab->width(),
                                                 selectedTab->height());
                }
                opt->tabBarSize = QSize(tabBar->implicitWidth(),
                                        tabBar->implicitHeight());
            }
            opt->shape =
                m_properties[QStringLiteral("orientation")] == Qt::BottomEdge ?
                QTabBar::RoundedSouth : QTabBar::RoundedNorth;
            // oxygen style needs this hack
            opt->leftCornerWidgetSize = QSize(value(), 0);
            opt->lineWidth =
                style->pixelMetric(QStyle::PM_DefaultFrameWidth, opt);
        }
        break;
    case MenuBar:
        if (!m_styleoption) {
            QStyleOptionMenuItem *menuOpt = new QStyleOptionMenuItem();
            menuOpt->menuItemType = QStyleOptionMenuItem::EmptyArea;
            m_styleoption = menuOpt;
        }
        break;
    case MenuBarItem:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionMenuItem();

            QStyleOptionMenuItem *opt =
                qstyleoption_cast<QStyleOptionMenuItem*>(m_styleoption);
            opt->text = text();
            opt->menuItemType = QStyleOptionMenuItem::Normal;
            setProperty("_q_showUnderlined",
                        m_hints[QStringLiteral("showUnderlined")].toBool());

            const QFont font = qApp->font("QMenuBar");
            opt->font = font;
            opt->fontMetrics = QFontMetrics(font);
            m_font = opt->font;
        }
        break;
    case Menu:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionMenuItem();
        }
        break;
    case MenuItem:
    case ComboMenuDelegate:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionMenuItem();

            QStyleOptionMenuItem *opt =
                qstyleoption_cast<QStyleOptionMenuItem*>(m_styleoption);
            // For GTK style. See below, in setElementType()
            setProperty("_q_isComboBoxPopupItem", m_itemType == ComboMenuDelegate);

            StyleItem::MenuItemType type =
                static_cast<StyleItem::MenuItemType>(
                    m_properties[QStringLiteral("type")].toInt());
            if (type == StyleItem::ScrollIndicatorType) {
                int scrollerDirection =
                    m_properties[QStringLiteral("scrollerDirection")].toInt();
                opt->menuItemType = QStyleOptionMenuItem::Scroller;
                opt->state |= scrollerDirection == Qt::UpArrow ?
                    QStyle::State_UpArrow : QStyle::State_DownArrow;
            } else if (type == StyleItem::SeparatorType) {
                opt->menuItemType = QStyleOptionMenuItem::Separator;
            } else {
                opt->text = text();

                if (type == StyleItem::MenuType) {
                    opt->menuItemType = QStyleOptionMenuItem::SubMenu;
                } else {
                    opt->menuItemType = QStyleOptionMenuItem::Normal;

                    QString shortcut =
                        m_properties[QStringLiteral("shortcut")].toString();
                    if (!shortcut.isEmpty()) {
                        opt->text += QLatin1Char('\t') + shortcut;
                        opt->tabWidth = qMax(opt->tabWidth,
                                             qRound(textWidth(shortcut)));
                    }

                    if (m_properties[QStringLiteral("checkable")].toBool()) {
                        opt->checked = on();
                        QVariant exclusive =
                            m_properties[QStringLiteral("exclusive")];
                        opt->checkType = exclusive.toBool() ?
                            QStyleOptionMenuItem::Exclusive :
                            QStyleOptionMenuItem::NonExclusive;
                    }
                }
                if (m_properties[QStringLiteral("icon")].canConvert<QIcon>())
                    opt->icon = m_properties[QStringLiteral("icon")].
                        value<QIcon>();
                setProperty("_q_showUnderlined",
                            m_hints[QStringLiteral("showUnderlined")].toBool());

                const QFont font = qApp->font(m_itemType == ComboMenuDelegate ?
                                              "QComboMenuItem" : "QMenu");
                opt->font = font;
                opt->fontMetrics = QFontMetrics(font);
                m_font = opt->font;
            }
        }
        break;
    case CheckBox:
    case RadioButton:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionButton();

            QStyleOptionButton *opt =
                qstyleoption_cast<QStyleOptionButton*>(m_styleoption);
            if (m_properties.value(QStringLiteral("partiallyChecked")).toBool()) {
                opt->state |= QStyle::State_NoChange;
            } else {
                opt->state |= on() ? QStyle::State_On : QStyle::State_Off;
            }
            opt->text = text();
        }
        break;
    case Edit:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionFrame();

            QStyleOptionFrame *opt =
                qstyleoption_cast<QStyleOptionFrame*>(m_styleoption);
            opt->lineWidth = m_properties.value(QStringLiteral("hasFrame")).toBool() ?
                style->pixelMetric(QStyle::PM_DefaultFrameWidth, opt) : 0;
            opt->midLineWidth = 0;
            opt->state |= QStyle::State_Sunken;
            /* TODO
            if (d->control->isReadOnly())
                opt->state |= QStyle::State_ReadOnly;
                */
            opt->features = QStyleOptionFrame::None;
        }
        break;
    case ComboBox:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionComboBox();

            QStyleOptionComboBox *opt =
                qstyleoption_cast<QStyleOptionComboBox*>(m_styleoption);
            opt->currentText = text();
            opt->editable = m_properties[QStringLiteral("editable")].toBool();
        }
        break;
    case SpinBox:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionSpinBox();

            QStyleOptionSpinBox *opt = qstyleoption_cast<QStyleOptionSpinBox*>(m_styleoption);
            opt->frame = true;
            opt->subControls =
                QStyle::SC_SpinBoxFrame | QStyle::SC_SpinBoxEditField;
            if (value() & 0x1)
                opt->activeSubControls = QStyle::SC_SpinBoxUp;
            else if (value() & (1<<1))
                opt->activeSubControls = QStyle::SC_SpinBoxDown;
            opt->subControls = QStyle::SC_All;
            opt->stepEnabled = 0;
            if (value() & (1<<2))
                opt->stepEnabled |= QAbstractSpinBox::StepUpEnabled;
            if (value() & (1<<3))
                opt->stepEnabled |= QAbstractSpinBox::StepDownEnabled;
        }
        break;
    case Slider:
    case Dial:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionSlider();

            QStyleOptionSlider *opt =
                qstyleoption_cast<QStyleOptionSlider*>(m_styleoption);
            opt->orientation = horizontal() ? Qt::Horizontal : Qt::Vertical;
            opt->upsideDown = !horizontal();
            opt->minimum = minimum();
            opt->maximum = maximum();
            opt->sliderPosition = value();
            opt->singleStep = step();

            if (opt->singleStep) {
                qreal numOfSteps =
                    (opt->maximum - opt->minimum) / opt->singleStep;
                // at least 5 pixels between tick marks
                qreal extent = horizontal() ? width() : height();
                if (numOfSteps && (extent / numOfSteps < 5))
                    opt->tickInterval =
                        qRound((5 * numOfSteps / extent) + 0.5) * step();
                else
                    opt->tickInterval = opt->singleStep;
            } else { // default Qt-components implementation
                opt->tickInterval = opt->maximum != opt->minimum ?
                    1200 / (opt->maximum - opt->minimum) : 0;
            }

            opt->sliderValue = value();
            opt->subControls =
                QStyle::SC_SliderGroove | QStyle::SC_SliderHandle;
            opt->tickPosition = activeControl() == QLatin1String("ticks") ?
                QSlider::TicksBelow : QSlider::NoTicks;
            if (opt->tickPosition != QSlider::NoTicks)
                opt->subControls |= QStyle::SC_SliderTickmarks;

            opt->activeSubControls = QStyle::SC_SliderHandle;
        }
        break;
    case ProgressBar:
        {
            // TODO: find a better place to do this
            m_text = progressBarComputeText();

            if (!m_styleoption)
                m_styleoption = new QStyleOptionProgressBar();

            QStyleOptionProgressBar *opt =
                qstyleoption_cast<QStyleOptionProgressBar*>(m_styleoption);
            opt->orientation = horizontal() ? Qt::Horizontal : Qt::Vertical;
            opt->minimum = minimum();
            opt->maximum = maximum();
            opt->progress = value();
            opt->text = text();
            opt->textVisible =
                m_properties[QStringLiteral("textVisible")].toBool();
        }
        break;
    case GroupBox:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionGroupBox();

            QStyleOptionGroupBox *opt =
                qstyleoption_cast<QStyleOptionGroupBox*>(m_styleoption);
            opt->text = text();
            opt->lineWidth = 1;
            opt->midLineWidth = 0;
            opt->subControls = QStyle::SC_GroupBoxFrame;
            if (!opt->text.isEmpty()) {
                opt->subControls |= QStyle::SC_GroupBoxLabel;
            }
            opt->features = 0;
            if (m_properties[QStringLiteral("checkable")].toBool())
                opt->subControls |= QStyle::SC_GroupBoxCheckBox;
        }
        break;
    case ScrollBar:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionSlider();

            QStyleOptionSlider *opt =
                qstyleoption_cast<QStyleOptionSlider*>(m_styleoption);
            opt->minimum = minimum();
            opt->maximum = maximum();
            opt->pageStep = qMax(0, int(horizontal() ? width() : height()));
            opt->orientation = horizontal() ? Qt::Horizontal : Qt::Vertical;
            opt->sliderPosition = value();
            opt->sliderValue = value();
            opt->activeSubControls = (activeControl() == QLatin1String("up")) ?
                QStyle::SC_ScrollBarSubLine :
                (activeControl() == QLatin1String("down")) ?
                    QStyle::SC_ScrollBarAddLine :
                    (activeControl() == QLatin1String("handle")) ?
                        QStyle::SC_ScrollBarSlider : hover() ?
                            QStyle::SC_ScrollBarGroove : QStyle::SC_None;
            if (raised())
                opt->state |= QStyle::State_On;

            opt->sliderValue = value();
            opt->subControls = QStyle::SC_All;

            setTransient(style->styleHint(QStyle::SH_ScrollBar_Transient, m_styleoption));
        }
        break;
    case TitleBar:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionTitleBar();

            QStyleOptionTitleBar *opt =
                qstyleoption_cast<QStyleOptionTitleBar*>(m_styleoption);
            opt->text = text();
            opt->titleBarFlags = Qt::SubWindow | Qt::WindowTitleHint;
            opt->subControls = QStyle::SC_All;
            opt->activeSubControls = QStyle::SC_None;
            const int border = 4;
            int titleHeight =
                style->pixelMetric(QStyle::PM_TitleBarHeight, m_styleoption);
            rect = QRect(border, border, width() - 2 * border, titleHeight);
        }
        break;
    case WindowFrame:
        {
            if (!m_styleoption)
                m_styleoption = new QStyleOptionFrame();

            QStyleOptionFrame *opt =
                qstyleoption_cast<QStyleOptionFrame*>(m_styleoption);
            opt->lineWidth =
                style->pixelMetric(QStyle::PM_MdiSubWindowFrameWidth);
        }
        break;
    default:
        break;
    }

    if (!m_styleoption)
        m_styleoption = new QStyleOption();

    if (!rect.isNull()) {
        m_styleoption->rect = rect;
    }
    initStyleOption(m_styleoption);
}

void StyleItem::initStyleOption(QStyleOption *opt) const
{
    resolvePalette(opt);
    opt->styleObject = const_cast<StyleItem*>(this);
    opt->direction = qApp->layoutDirection();

    int w = width();
    int h = height();

    if (opt->rect.isNull()) {
        opt->rect = QRect(m_paintMargins, 0,
                          w - 2 * m_paintMargins, h);
    }

    if (isEnabled()) {
        opt->state |= QStyle::State_Enabled;
        opt->palette.setCurrentColorGroup(QPalette::Active);
    } else {
        opt->palette.setCurrentColorGroup(QPalette::Disabled);
    }
    if (m_active)
        opt->state |= QStyle::State_Active;
    else
        opt->palette.setCurrentColorGroup(QPalette::Inactive);
    if (m_sunken)
        opt->state |= QStyle::State_Sunken;
    if (m_raised)
        opt->state |= QStyle::State_Raised;
    if (m_selected)
        opt->state |= QStyle::State_Selected;
    if (m_focus)
        opt->state |= QStyle::State_HasFocus;
    if (m_on)
        opt->state |= QStyle::State_On;
    if (m_hover)
        opt->state |= QStyle::State_MouseOver;
    if (m_horizontal)
        opt->state |= QStyle::State_Horizontal;

    // some styles don't draw a focus rectangle if
    // QStyle::State_KeyboardFocusChange is not set
    if (window()) {
        if (m_lastFocusReason == Qt::TabFocusReason ||
            m_lastFocusReason == Qt::BacktabFocusReason) {
            opt->state |= QStyle::State_KeyboardFocusChange;
        }
    }

    QString sizeHint = m_hints.value(QStringLiteral("size")).toString();
    if (sizeHint == QLatin1String("mini")) {
        opt->state |= QStyle::State_Mini;
    } else if (sizeHint == QLatin1String("small")) {
        opt->state |= QStyle::State_Small;
    }
}

const char *StyleItem::classNameForItem() const
{
    switch(m_itemType) {
    case Label:
        return "QLabel";
    case Button:
        return "QPushButton";
    case RadioButton:
        return "QRadioButton";
    case CheckBox:
        return "QCheckBox";
    case ComboBox:
        return "QComboBox";
    case ComboMenuDelegate:
        return "QComboMenuItem";
    case ToolBar:
        return "";
    case ToolButton:
        return "QToolButton";
    case Tab:
        return "QTabButton";
    case TabFrame:
        return "QTabBar";
    case Edit:
        return "QTextEdit";
    case GroupBox:
        return "QGroupBox";
    case Header:
        return "QHeaderView";
    case Item:
    case ItemRow:
        return "QAbstractItemView";
    case Menu:
    case MenuItem:
        return "QMenu";
    case MenuBar:
    case MenuBarItem:
        return "QMenuBar";
    case TitleBar:
    case WindowFrame:
        return "QMdiSubWindow";
    default:
        return "";
    }
    Q_UNREACHABLE();
}

bool StyleItem::hasAncestor(const char *name) const
{
    const QQuickItem *parent = this;
    while ((parent = parent->parentItem())) {
        if (parent->inherits(name)) {
            return true;
        }
    }
    return false;
}

void StyleItem::resolvePalette(QStyleOption *opt) const
{
    if (QCoreApplication::testAttribute(Qt::AA_SetPalette))
        return;

    const QVariant controlPalette = m_control ?
        m_control->property("palette") : QVariant();
#if (QT_VERSION >= QT_VERSION_CHECK(5, 11, 0))
    if (controlPalette.isValid()) {
        opt->palette = controlPalette.value<QPalette>();
    } else {
        opt->palette = QApplication::palette(classNameForItem());
    }
#else
    opt->palette = QApplication::palette(classNameForItem());
#endif
}

/*
 *   Property style
 *
 *   Returns a simplified style name.
 *
 *   QMacStyle = "mac"
 *   QWindowsXPStyle = "windowsxp"
 *   QFusionStyle = "fusion"
 */
QString StyleItem::style() const
{
    QString style =
        QString::fromLatin1(qApp->style()->metaObject()->className());
    style = style.toLower();
    if (style.startsWith(QLatin1Char('q')))
        style = style.right(style.length() - 1);
    if (style.endsWith(QLatin1String("style")))
        style = style.left(style.length() - 5);
    return style;
}

QString StyleItem::hitTest(int px, int py)
{
    QStyle::SubControl subcontrol = QStyle::SC_All;
    switch (m_itemType) {
    case SpinBox:
        {
            subcontrol =
                qApp->style()->hitTestComplexControl(QStyle::CC_SpinBox,
                                                     qstyleoption_cast<QStyleOptionComplex*>(m_styleoption),
                                                     QPoint(px, py),
                                                     nullptr);
            if (subcontrol == QStyle::SC_SpinBoxUp)
                return QStringLiteral("up");
            else if (subcontrol == QStyle::SC_SpinBoxDown)
                return QStringLiteral("down");
        }
        break;

    case Slider:
        {
            subcontrol =
                qApp->style()->hitTestComplexControl(QStyle::CC_Slider,
                                                     qstyleoption_cast<QStyleOptionComplex*>(m_styleoption),
                                                     QPoint(px, py),
                                                     nullptr);
            if (subcontrol == QStyle::SC_SliderHandle)
                return QStringLiteral("handle");
        }
        break;

    case ScrollBar:
        {
            subcontrol =
                qApp->style()->hitTestComplexControl(QStyle::CC_ScrollBar,
                                                     qstyleoption_cast<QStyleOptionComplex*>(m_styleoption),
                                                     QPoint(px, py),
                                                     nullptr);
            switch (subcontrol) {
            case QStyle::SC_ScrollBarSlider:
                return QStringLiteral("handle");
            case QStyle::SC_ScrollBarSubLine:
                return QStringLiteral("up");
            case QStyle::SC_ScrollBarSubPage:
                return QStringLiteral("upPage");
            case QStyle::SC_ScrollBarAddLine:
                return QStringLiteral("down");
            case QStyle::SC_ScrollBarAddPage:
                return QStringLiteral("downPage");
            default:
                break;
            }
        }
        break;

    default:
        break;
    }
    return QStringLiteral("none");
}

QSize StyleItem::sizeFromContents(int width, int height)
{
    initStyleOption();

    QStyle *style = qApp->style();
    QSize size;
    switch (m_itemType) {
    case Label:
        if (m_rendersText) {
            /* The code in QLabelPrivate::sizeForWidth() is way more
             * complex than this; we only cover the case of simple text
             * format. */
            QRect br;
            QFont font = m_control ?
                m_control->property("font").value<QFont>():
                qApp->font("QPushButton");
            QFontMetrics fm = QFontMetrics(font);
            int flags = textFlags();
            int w = widthValid() ? this->width() : 2000;
            br = fm.boundingRect(0, 0, w, 2000, flags, text());
            size = br.size();

            /*
             * Workaround for
             * https://bugreports.qt.io/browse/QTBUG-72071
             */
            if (m_control) {
                QTimer::singleShot(0, m_control, [this,size]() {
                    m_control->setImplicitWidth(size.width());
                    m_control->setImplicitHeight(size.height());
                });
            }
        }
        break;
    case RadioButton:
    case CheckBox:
        {
            QStyleOptionButton *opt = qstyleoption_cast<QStyleOptionButton*>(m_styleoption);
            QSize sz = style->itemTextRect(opt->fontMetrics, QRect(),
                                           Qt::TextShowMnemonic, false,
                                           text()).size();

            if (!opt->icon.isNull()) {
                sz = QSize(sz.width() + opt->iconSize.width() + 4, qMax(sz.height(), opt->iconSize.height()));
            }
            QStyle::ContentsType type = m_itemType == RadioButton ?
                QStyle::CT_RadioButton : QStyle::CT_CheckBox;
            size = (style->sizeFromContents(type, opt, sz)
                    .expandedTo(QApplication::globalStrut()));
        }
        break;
    case ToolBar:
        {
            int margin =
                style->pixelMetric(QStyle::PM_ToolBarItemMargin, m_styleoption) +
                style->pixelMetric(QStyle::PM_ToolBarFrameWidth, m_styleoption);
            int handleExtent =
                style->pixelMetric(QStyle::PM_ToolBarHandleExtent, m_styleoption);

            size = QSize(width + margin * 2,
                         qMax(height, handleExtent) + margin * 2);
        }
        break;
    case ToolButton:
        {
            QStyleOptionToolButton *btn =
                qstyleoption_cast<QStyleOptionToolButton*>(m_styleoption);
            int w = 0;
            int h = 0;
            if (btn->toolButtonStyle != Qt::ToolButtonTextOnly) {
                QSize icon = btn->iconSize;
                w = icon.width();
                h = icon.height();
            }
            if (btn->toolButtonStyle != Qt::ToolButtonIconOnly) {
                QSize textSize = btn->fontMetrics.size(Qt::TextShowMnemonic,
                                                       btn->text);
                textSize.setWidth(textSize.width() +
                                  btn->fontMetrics.width(QLatin1Char(' ')) * 2);
                if (btn->toolButtonStyle == Qt::ToolButtonTextUnderIcon) {
                    h += 4 + textSize.height();
                    if (textSize.width() > w)
                        w = textSize.width();
                } else if (btn->toolButtonStyle == Qt::ToolButtonTextBesideIcon) {
                    w += 4 + textSize.width();
                    if (textSize.height() > h)
                        h = textSize.height();
                } else { // TextOnly
                    w = textSize.width();
                    h = textSize.height();
                }
            }
            btn->rect.setSize(QSize(w, h));
            size = style->sizeFromContents(QStyle::CT_ToolButton,
                                           m_styleoption,
                                           QSize(w, h));
        }
        break;
    case ToolSeparator:
        {
            const int extent =
                style->pixelMetric(QStyle::PM_ToolBarSeparatorExtent,
                                   m_styleoption);
            size = QSize(extent, extent);
        }
        break;
    case Button:
        {
            QStyleOptionButton *btn =
                qstyleoption_cast<QStyleOptionButton*>(m_styleoption);

            int w = 0, h = 0;
            if (!btn->icon.isNull()) {
                // +4 matches a hardcoded value in QStyle and acts as a margin
                // between the icon and the text.
                w += btn->iconSize.width() + 4;
                h = btn->iconSize.height();
            }
            QSize sz = btn->fontMetrics.size(Qt::TextShowMnemonic, btn->text);
            w += sz.width();
            h = qMax(h, sz.height());
            int newWidth = qMax(width, w);
            int newHeight = qMax(height, h);
            size = style->sizeFromContents(QStyle::CT_PushButton,
                                           m_styleoption,
                                           QSize(newWidth, newHeight));
        }
        break;
    case ComboBox:
        {
            QStyleOptionComboBox *opt =
                qstyleoption_cast<QStyleOptionComboBox*>(m_styleoption);
            const QFontMetrics &fm = opt->fontMetrics;
            int w = qMax(width, fm.boundingRect(opt->currentText).width());
            int h = qMax(height, qCeil(fm.height()) + 2);
            if (m_control) {
                int count = m_control->property("count").toInt();
                for (int i = 0; i < count; i++) {
                    QString text;
                    bool ok =
                        QMetaObject::invokeMethod(m_control.data(),
                                                  "textAt",
                                                  Q_RETURN_ARG(QString, text),
                                                  Q_ARG(int, i));
                    if (ok) {
                        w = qMax(w, fm.boundingRect(text).width());
                    }
                }
            }
            size = style->sizeFromContents(QStyle::CT_ComboBox,
                                           m_styleoption,
                                           QSize(w, h));
        }
        break;
    case ComboBoxDelegate:
        {
            QStyleOptionViewItem *opt =
                qstyleoption_cast<QStyleOptionViewItem*>(m_styleoption);
            const QFontMetrics &fm = opt->fontMetrics;
            int w = qMax(width, fm.boundingRect(opt->text).width());
            int h = qMax(height, qCeil(fm.height()));
            size = QSize(w, h);
        }
        break;
    case Tab:
        {
            QStyleOptionTab *tab =
                qstyleoption_cast<QStyleOptionTab*>(m_styleoption);
            int hframe = style->pixelMetric(QStyle::PM_TabBarTabHSpace, tab);
            int vframe = style->pixelMetric(QStyle::PM_TabBarTabVSpace, tab);

            QSize textSize =
                tab->fontMetrics.size(Qt::TextShowMnemonic, tab->text);
            int newWidth = qMax(width, textSize.width()) + hframe;
            int newHeight = qMax(height, textSize.height()) + vframe;
            size = style->sizeFromContents(QStyle::CT_TabBarTab,
                                           m_styleoption,
                                           QSize(newWidth, newHeight));
        }
        break;
    case TabFrame:
        {
            size = style->sizeFromContents(QStyle::CT_TabWidget,
                                           m_styleoption,
                                           QSize(width, height));
        }
        break;
    case Slider:
        {
            const int SliderLength = 84, TickSpace = 5;
            int thick = style->pixelMetric(QStyle::PM_SliderThickness,
                                           m_styleoption);
            QStyleOptionSlider *opt =
                qstyleoption_cast<QStyleOptionSlider*>(m_styleoption);
            if (opt->tickPosition != QSlider::NoTicks) {
                thick += TickSpace;
            }

            if (horizontal()) {
                width = SliderLength;
                height = thick;
            } else {
                width = thick;
                height = SliderLength;
            }
            size = style->sizeFromContents(QStyle::CT_Slider,
                                           m_styleoption,
                                           QSize(width, height)).
                expandedTo(QApplication::globalStrut());;
        }
        break;
    case ProgressBar:
        {
            QStyleOptionProgressBar *opt =
                qstyleoption_cast<QStyleOptionProgressBar*>(m_styleoption);
            int cw = style->pixelMetric(QStyle::PM_ProgressBarChunkWidth, opt);
            const QFontMetrics &fm = opt->fontMetrics;
            size = QSize(qMax(9, cw) * 7 + fm.width(QLatin1Char('0')) * 4,
                         fm.height() + 8);
            if (opt->orientation == Qt::Vertical)
                size = size.transposed();
            size = style->sizeFromContents(QStyle::CT_ProgressBar,
                                           opt, size);
        }
        break;
    case SpinBox:
        {
            const QFontMetrics &fm = m_styleoption->fontMetrics;
            int w = 0;
            QString fixedContent(QLatin1Char(' '));
            const QStringList minMaxTexts = text().split(QLatin1Char('_'));
            for (const QString &t: minMaxTexts) {
                QString s(t + fixedContent);
                s.truncate(18);
                w = qMax(w, fm.width(s));
            }
            w += 2; // cursor blinking space

            QSize sizeW(qMax(w, width), height);
            size = style->sizeFromContents(QStyle::CT_SpinBox,
                                           m_styleoption,
                                           sizeW)
                .expandedTo(QApplication::globalStrut());
        }
        break;
    case Edit:
        {
            const int verticalMargin = LINEEDIT_VERTICAL_MARGIN;
            const QFontMetrics &fm = m_styleoption->fontMetrics;
            int h = fm.height() + qMax(2*verticalMargin, fm.leading());
            int w = fm.maxWidth();

            size = QSize(qMax(w, width), qMax(h, height)).
                expandedTo(QApplication::globalStrut());
            size = style->sizeFromContents(QStyle::CT_LineEdit,
                                           m_styleoption, size);
        }
        break;
    case GroupBox:
        {
            QStyleOptionGroupBox *box =
                qstyleoption_cast<QStyleOptionGroupBox*>(m_styleoption);
            QFontMetrics metrics(box->fontMetrics);
            int baseWidth = metrics.width(box->text) +
                metrics.width(QLatin1Char(' '));
            int baseHeight = metrics.height() + m_contentHeight;
            if (box->subControls & QStyle::SC_GroupBoxCheckBox) {
                baseWidth += style->pixelMetric(QStyle::PM_IndicatorWidth);
                baseWidth += style->pixelMetric(QStyle::PM_CheckBoxLabelSpacing);
                baseHeight =
                    qMax(baseHeight, style->pixelMetric(QStyle::PM_IndicatorHeight));
            }
            size = style->sizeFromContents(QStyle::CT_GroupBox, m_styleoption,
                                           QSize(baseWidth, baseHeight));
            // QStyleCOmmon adds 16 to thewidth if the widget is a non-flat QGroupBox
            // looks like a bug in Qt, they could check the feature flag!
            // This has been fixed with
            // https://codereview.qt-project.org/#/c/247699/, which will
            // likely be in Qt 5.13
#if (QT_VERSION < QT_VERSION_CHECK(5, 13, 0))
            size += QSize(16, 0);
#endif
        }
        break;
    case Header:
        size = style->sizeFromContents(QStyle::CT_HeaderSection,
                                       m_styleoption,
                                       QSize(width, height));
        break;
    case ItemRow:
    case Item: //fall through
        size = style->sizeFromContents(QStyle::CT_ItemViewItem,
                                       m_styleoption,
                                       QSize(width, height));
        break;
    case MenuBarItem:
        size = style->sizeFromContents(QStyle::CT_MenuBarItem,
                                       m_styleoption,
                                       QSize(width, height));
        break;
    case MenuBar:
        size = style->sizeFromContents(QStyle::CT_MenuBar,
                                       m_styleoption,
                                       QSize(width, height));
        break;
    case Menu:
        size = style->sizeFromContents(QStyle::CT_Menu,
                                       m_styleoption,
                                       QSize(width, height));
        break;
    case MenuItem:
        if (static_cast<QStyleOptionMenuItem *>(m_styleoption)->menuItemType ==
                QStyleOptionMenuItem::Scroller) {
            size.setHeight(qMax(QApplication::globalStrut().height(),
                                style->pixelMetric(QStyle::PM_MenuScrollerHeight,
                                                   nullptr, nullptr)));
        } else {
            size = style->sizeFromContents(QStyle::CT_MenuItem,
                                           m_styleoption,
                                           QSize(width, height));
        }
        break;
    case ComboMenuDelegate:
        size = style->sizeFromContents(QStyle::CT_MenuItem,
                                       m_styleoption,
                                       m_styleoption->rect.size());
        break;
    case ScrollBar:
        {
            int scrollBarExtent =
                style->pixelMetric(QStyle::PM_ScrollBarExtent,
                                   m_styleoption);
            int scrollBarSliderMin =
                style->pixelMetric(QStyle::PM_ScrollBarSliderMin,
                                   m_styleoption);
            if (horizontal()) {
                size = QSize(scrollBarExtent * 2 + scrollBarSliderMin, scrollBarExtent);
            } else {
                size = QSize(scrollBarExtent, scrollBarExtent * 2 + scrollBarSliderMin);
            }

            size = style->sizeFromContents(QStyle::CT_ScrollBar,
                                           m_styleoption, size)
                .expandedTo(QApplication::globalStrut());
        }
        break;
    case TitleBar:
        {
            int margin = style->pixelMetric(QStyle::PM_MdiSubWindowFrameWidth);
            int titleHeight =
                style->pixelMetric(QStyle::PM_TitleBarHeight, m_styleoption);
            size = QSize(margin * 2, titleHeight + margin);
        }
        break;
    default:
        break;
    }
    return size.expandedTo(QSize(m_contentWidth, m_contentHeight));
}

qreal StyleItem::baselineOffset()
{
    QRect r;
    bool ceilResult = true; // By default baseline offset rounding is done upwards
    switch (m_itemType) {
    case RadioButton:
        r = qApp->style()->subElementRect(QStyle::SE_RadioButtonContents,
                                          m_styleoption);
        break;
    case Button:
        r = qApp->style()->subElementRect(QStyle::SE_PushButtonContents,
                                          m_styleoption);
        break;
    case CheckBox:
        r = qApp->style()->subElementRect(QStyle::SE_CheckBoxContents,
                                          m_styleoption);
        break;
    case Edit:
        r = qApp->style()->subElementRect(QStyle::SE_LineEditContents,
                                          m_styleoption);
        break;
    case ComboBox:
        if (const QStyleOptionComboBox *combo =
            qstyleoption_cast<const QStyleOptionComboBox *>(m_styleoption)) {
            r = qApp->style()->subControlRect(QStyle::CC_ComboBox,
                                              combo,
                                              QStyle::SC_ComboBoxEditField);
            if (style() != QLatin1String("mac"))
                r.adjust(0, 0, 0, 1);
        }
        break;
    case SpinBox:
        if (const QStyleOptionSpinBox *spinbox =
            qstyleoption_cast<const QStyleOptionSpinBox *>(m_styleoption)) {
            r = qApp->style()->subControlRect(QStyle::CC_SpinBox,
                                              spinbox,
                                              QStyle::SC_SpinBoxEditField);
            ceilResult = false;
        }
        break;
    default:
        break;
    }
    if (r.height() > 0) {
        const QFontMetrics &fm = m_styleoption->fontMetrics;
        int surplus = r.height() - fm.height();
        if ((surplus & 1) && ceilResult)
            surplus++;
        int result = r.top() + surplus/2 + fm.ascent();
        return result;
    }

    return 0.;
}

void StyleItem::updateBaselineOffset()
{
    const qreal baseline = baselineOffset();
    if (baseline > 0)
        setBaselineOffset(baseline);
}

void StyleItem::setContentWidth(int arg)
{
    if (m_contentWidth != arg) {
        m_contentWidth = arg;
        Q_EMIT contentWidthChanged(arg);
    }
}

void StyleItem::setContentHeight(int arg)
{
    if (m_contentHeight != arg) {
        m_contentHeight = arg;
        Q_EMIT contentHeightChanged(arg);
    }
}

void StyleItem::updateSizeHint()
{
    QSize implicitSize = sizeFromContents(m_contentWidth, m_contentHeight);
    // We assume that initStyleOption has been called in sizeFromContents()
    updateContentMargins();

    setImplicitSize(implicitSize.width(), implicitSize.height());
}

void StyleItem::updateContentMargins()
{
    QStyle *style = qApp->style();
    QRect cr;

    switch (m_itemType) {
    case ComboBoxPopup:
    case Frame:
        {
            /* Logic copied from QFramePrivate::updateStyledFrameWidths() */
            QStyleOptionFrame *opt =
                qstyleoption_cast<QStyleOptionFrame*>(m_styleoption);
            cr = style->subElementRect(QStyle::SE_ShapedFrameContents, opt);
        }
        break;
    case GroupBox:
        {
            /* Logic copied from QGroupBoxPrivate::calculateFrame() */
            QRect contentsRect =
                style->subControlRect(QStyle::CC_GroupBox,
                    qstyleoption_cast<QStyleOptionComplex*>(m_styleoption),
                    QStyle::SC_GroupBoxContents);
            int w = width();
            int h = height();
            m_contentMargins.setLeft(contentsRect.left());
            m_contentMargins.setTop(contentsRect.top());
            /* we use "width/height - 1" because QRect::right/bottom()
             * works that way*/
            m_contentMargins.setRight(w - 1 - contentsRect.right());
            m_contentMargins.setBottom(h - 1 - contentsRect.bottom());
        }
        break;
    case TabFrame:
        {
            cr = style->subElementRect(QStyle::SE_TabWidgetTabContents,
                                       m_styleoption);
        }
        break;
    case ToolBar:
        {
            int margin =
                style->pixelMetric(QStyle::PM_ToolBarItemMargin, m_styleoption) +
                style->pixelMetric(QStyle::PM_ToolBarFrameWidth, m_styleoption);
            m_contentMargins.setLeft(margin);
            m_contentMargins.setTop(margin);
            m_contentMargins.setRight(margin);
            m_contentMargins.setBottom(margin);
        }
    default:
        return;
    }

    if (!cr.isNull()) {
        m_contentMargins.setLeft(cr.left() - m_styleoption->rect.left());
        m_contentMargins.setTop(cr.top() - m_styleoption->rect.top());
        m_contentMargins.setRight(m_styleoption->rect.right() - cr.right());
        m_contentMargins.setBottom(m_styleoption->rect.bottom() - cr.bottom());
    }
}

void StyleItem::updateRect()
{
    m_styleoption->rect.setWidth(width());
    m_styleoption->rect.setHeight(height());
}

int StyleItem::pixelMetric(const QString &metric)
{
    if (metric == QLatin1String("scrollbarExtent"))
        return qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent);
    else if (metric == QLatin1String("defaultframewidth"))
        return qApp->style()->pixelMetric(QStyle::PM_DefaultFrameWidth, m_styleoption);
    else if (metric == QLatin1String("taboverlap"))
        return qApp->style()->pixelMetric(QStyle::PM_TabBarTabOverlap);
    else if (metric == QLatin1String("tabbaseoverlap"))
        return qApp->style()->pixelMetric(QStyle::PM_TabBarBaseOverlap, m_styleoption);
    else if (metric == QLatin1String("tabhspace"))
        return qApp->style()->pixelMetric(QStyle::PM_TabBarTabHSpace);
    else if (metric == QLatin1String("indicatorwidth"))
        return qApp->style()->pixelMetric(QStyle::PM_ExclusiveIndicatorWidth);
    else if (metric == QLatin1String("tabvspace"))
        return qApp->style()->pixelMetric(QStyle::PM_TabBarTabVSpace);
    else if (metric == QLatin1String("tabbaseheight"))
        return qApp->style()->pixelMetric(QStyle::PM_TabBarBaseHeight);
    else if (metric == QLatin1String("tabvshift"))
        return qApp->style()->pixelMetric(QStyle::PM_TabBarTabShiftVertical);
    else if (metric == QLatin1String("menubarhmargin"))
        return qApp->style()->pixelMetric(QStyle::PM_MenuBarHMargin);
    else if (metric == QLatin1String("menubarvmargin"))
        return qApp->style()->pixelMetric(QStyle::PM_MenuBarVMargin);
    else if (metric == QLatin1String("menubarpanelwidth"))
        return qApp->style()->pixelMetric(QStyle::PM_MenuBarPanelWidth);
    else if (metric == QLatin1String("menubaritemspacing"))
        return qApp->style()->pixelMetric(QStyle::PM_MenuBarItemSpacing);
    else if (metric == QLatin1String("spacebelowmenubar"))
        return qApp->style()->styleHint(QStyle::SH_MainWindow_SpaceBelowMenuBar,
                                        m_styleoption);
    else if (metric == QLatin1String("menuhmargin"))
        return qApp->style()->pixelMetric(QStyle::PM_MenuHMargin);
    else if (metric == QLatin1String("menuvmargin"))
        return qApp->style()->pixelMetric(QStyle::PM_MenuVMargin);
    else if (metric == QLatin1String("menupanelwidth"))
        return qApp->style()->pixelMetric(QStyle::PM_MenuPanelWidth);
    else if (metric == QLatin1String("submenuoverlap"))
        return qApp->style()->pixelMetric(QStyle::PM_SubMenuOverlap);
    else if (metric == QLatin1String("splitterwidth"))
        return qApp->style()->pixelMetric(QStyle::PM_SplitterWidth);
    else if (metric == QLatin1String("scrollbarspacing"))
        return abs(qApp->style()->pixelMetric(QStyle::PM_ScrollView_ScrollBarSpacing));
    else if (metric == QLatin1String("treeviewindentation"))
        return qApp->style()->pixelMetric(QStyle::PM_TreeViewIndentation);
    else if (metric == QLatin1String("layouthorizontalspacing"))
        return qApp->style()->pixelMetric(QStyle::PM_LayoutHorizontalSpacing);
    else if (metric == QLatin1String("layoutverticalspacing"))
        return qApp->style()->pixelMetric(QStyle::PM_LayoutVerticalSpacing);
    else if (metric == QLatin1String("layoutleftmargin"))
        return qApp->style()->pixelMetric(QStyle::PM_LayoutLeftMargin);
    else if (metric == QLatin1String("layouttopmargin"))
        return qApp->style()->pixelMetric(QStyle::PM_LayoutTopMargin);
    else if (metric == QLatin1String("layoutrightmargin"))
        return qApp->style()->pixelMetric(QStyle::PM_LayoutRightMargin);
    else if (metric == QLatin1String("layoutbottommargin"))
        return qApp->style()->pixelMetric(QStyle::PM_LayoutBottomMargin);
    return 0;
}

QVariant StyleItem::styleHint(const QString &metric)
{
    initStyleOption();
    if (metric == QLatin1String("comboboxpopup")) {
        return qApp->style()->styleHint(QStyle::SH_ComboBox_Popup, m_styleoption);
    } else if (metric == QLatin1String("highlightedTextColor")) {
        return m_styleoption->palette.highlightedText().color().name();
    } else if (metric == QLatin1String("textColor")) {
        QPalette pal = m_styleoption->palette;
        pal.setCurrentColorGroup(active()? QPalette::Active : QPalette::Inactive);
        return pal.text().color().name();
    } else if (metric == QLatin1String("focuswidget")) {
        return qApp->style()->styleHint(QStyle::SH_FocusFrame_AboveWidget);
    } else if (metric == QLatin1String("tabbaralignment")) {
        int result = qApp->style()->styleHint(QStyle::SH_TabBar_Alignment);
        if (result == Qt::AlignCenter)
            return QStringLiteral("center");
        return QStringLiteral("left");
    } else if (metric == QLatin1String("externalScrollBars")) {
        return qApp->style()->styleHint(QStyle::SH_ScrollView_FrameOnlyAroundContents);
    } else if (metric == QLatin1String("scrollToClickPosition"))
        return qApp->style()->styleHint(QStyle::SH_ScrollBar_LeftClickAbsolutePosition);
    else if (metric == QLatin1String("activateItemOnSingleClick"))
        return qApp->style()->styleHint(QStyle::SH_ItemView_ActivateItemOnSingleClick);
    else if (metric == QLatin1String("submenupopupdelay"))
        return qApp->style()->styleHint(QStyle::SH_Menu_SubMenuPopupDelay, m_styleoption);
    else if (metric == QLatin1String("wheelScrollLines"))
        return qApp->wheelScrollLines();
    else if (metric == QLatin1String("comboBoxWidthHint"))
        return comboBoxWidthHint();
    return 0;

    // Add SH_Menu_SpaceActivatesItem
}

void StyleItem::setHints(const QVariantMap &str)
{
    if (m_hints != str) {
        m_hints = str;
        initStyleOption();
        updateSizeHint();
        if (m_styleoption->state & QStyle::State_Mini) {
            m_font.setPointSize(9.);
            Q_EMIT fontChanged();
        } else if (m_styleoption->state & QStyle::State_Small) {
            m_font.setPointSize(11.);
            Q_EMIT fontChanged();
        } else {
            Q_EMIT hintChanged();
        }
    }
}

void StyleItem::resetHints()
{
    m_hints.clear();
}


void StyleItem::setElementType(const QString &str)
{
    if (m_type == str)
        return;

    m_type = str;

    Q_EMIT elementTypeChanged();
    if (m_styleoption) {
        delete m_styleoption;
        m_styleoption = nullptr;
    }

    // Only enable visible if the widget can animate
    if (str == QLatin1String("menu")) {
        m_itemType = Menu;
    } else if (str == QLatin1String("menuitem")) {
        m_itemType = MenuItem;
    } else if (str == QLatin1String("item") ||
               str == QLatin1String("itemrow") ||
               str == QLatin1String("header")) {
        if (str == QLatin1String("header")) {
            m_itemType = Header;
        } else {
            m_itemType = str == QLatin1String("item") ? Item : ItemRow;
        }
    } else if (str == QLatin1String("itembranchindicator")) {
        m_itemType = ItemBranchIndicator;
    } else if (str == QLatin1String("groupbox")) {
        m_itemType = GroupBox;
    } else if (str == QLatin1String("tab")) {
        m_itemType = Tab;
    } else if (str == QLatin1String("tabframe")) {
        m_itemType = TabFrame;
    } else if (str == QLatin1String("comboboxdelegate"))  {
        m_itemType = ComboBoxDelegate;
    } else if (str == QLatin1String("comboboxpopup"))  {
        m_itemType = ComboBoxPopup;
    } else if (str == QLatin1String("combomenudelegate"))  {
        m_itemType = ComboMenuDelegate;
    } else if (str == QLatin1String("toolbar")) {
        m_itemType = ToolBar;
    } else if (str == QLatin1String("toolbutton")) {
        m_itemType = ToolButton;
    } else if (str == QLatin1String("toolseparator")) {
        m_itemType = ToolSeparator;
    } else if (str == QLatin1String("slider")) {
        m_itemType = Slider;
    } else if (str == QLatin1String("frame")) {
        m_itemType = Frame;
    } else if (str == QLatin1String("combobox")) {
        m_itemType = ComboBox;
    } else if (str == QLatin1String("splitter")) {
        m_itemType = Splitter;
    } else if (str == QLatin1String("progressbar")) {
        m_itemType = ProgressBar;
    } else if (str == QLatin1String("label")) {
        m_itemType = Label;
    } else if (str == QLatin1String("button")) {
        m_itemType = Button;
    } else if (str == QLatin1String("checkbox")) {
        m_itemType = CheckBox;
    } else if (str == QLatin1String("radiobutton")) {
        m_itemType = RadioButton;
    } else if (str == QLatin1String("edit")) {
        m_itemType = Edit;
    } else if (str == QLatin1String("spinbox")) {
        m_itemType = SpinBox;
    } else if (str == QLatin1String("scrollbar")) {
        m_itemType = ScrollBar;
    } else if (str == QLatin1String("widget")) {
        m_itemType = Widget;
    } else if (str == QLatin1String("focusframe")) {
        m_itemType = FocusFrame;
    } else if (str == QLatin1String("focusrect")) {
        m_itemType = FocusRect;
    } else if (str == QLatin1String("dial")) {
        m_itemType = Dial;
    } else if (str == QLatin1String("statusbar")) {
        m_itemType = StatusBar;
    } else if (str == QLatin1String("machelpbutton")) {
        m_itemType = MacHelpButton;
    } else if (str == QLatin1String("scrollareacorner")) {
        m_itemType = ScrollAreaCorner;
    } else if (str == QLatin1String("menubar")) {
        m_itemType = MenuBar;
    } else if (str == QLatin1String("menubaritem")) {
        m_itemType = MenuBarItem;
    } else if (str == QLatin1String("titlebar")) {
        m_itemType = TitleBar;
    } else if (str == QLatin1String("windowframe")) {
        m_itemType = WindowFrame;
    } else {
        m_itemType = Undefined;
    }
    updateSizeHint();
}

QRectF StyleItem::subControlRect(const QString &subcontrolString)
{
    QStyle::ComplexControl control = QStyle::CC_CustomBase;
    QStyle::SubControl subcontrol = QStyle::SC_None;
    initStyleOption();
    switch (m_itemType) {
    case ComboBox:
        {
            control = QStyle::CC_ComboBox;
            if (subcontrolString == QLatin1String("edit")) {
                subcontrol = QStyle::SC_ComboBoxEditField;
            }
        }
        break;
    case Edit:
        if (subcontrolString == QStringLiteral("edit")) {
            QRect r = qApp->style()->subElementRect(QStyle::SE_LineEditContents,
                                                    m_styleoption);
            r.adjust(LINEEDIT_HORIZONAL_MARGIN, LINEEDIT_VERTICAL_MARGIN,
                     -LINEEDIT_HORIZONAL_MARGIN, -LINEEDIT_VERTICAL_MARGIN);
            return r;
        }
        break;
    case GroupBox:
        {
            control = QStyle::CC_GroupBox;
            if (subcontrolString == QLatin1String("label")) {
                subcontrol = QStyle::SC_GroupBoxLabel;
            } else if (subcontrolString == QLatin1String("frame")) {
                subcontrol = QStyle::SC_GroupBoxFrame;
            }
        }
        break;
    case SpinBox:
        {
            control = QStyle::CC_SpinBox;
            if (subcontrolString == QLatin1String("down"))
                subcontrol = QStyle::SC_SpinBoxDown;
            else if (subcontrolString == QLatin1String("up"))
                subcontrol = QStyle::SC_SpinBoxUp;
            else if (subcontrolString == QLatin1String("edit")){
                subcontrol = QStyle::SC_SpinBoxEditField;
            }
        }
        break;
    case Slider:
        {
            control = QStyle::CC_Slider;
            if (subcontrolString == QLatin1String("handle"))
                subcontrol = QStyle::SC_SliderHandle;
            else if (subcontrolString == QLatin1String("groove"))
                subcontrol = QStyle::SC_SliderGroove;
        }
        break;
    case ScrollBar:
        {
            control = QStyle::CC_ScrollBar;
            if (subcontrolString == QLatin1String("slider"))
                subcontrol = QStyle::SC_ScrollBarSlider;
            if (subcontrolString == QLatin1String("groove"))
                subcontrol = QStyle::SC_ScrollBarGroove;
            else if (subcontrolString == QLatin1String("handle"))
                subcontrol = QStyle::SC_ScrollBarSlider;
            else if (subcontrolString == QLatin1String("add"))
                subcontrol = QStyle::SC_ScrollBarAddPage;
            else if (subcontrolString == QLatin1String("sub"))
                subcontrol = QStyle::SC_ScrollBarSubPage;
        }
        break;
    case ItemBranchIndicator:
        {
            QStyleOption opt;
            opt.rect = QRect(0, 0, implicitWidth(), implicitHeight());
            return qApp->style()->subElementRect(QStyle::SE_TreeViewDisclosureItem,
                                                 &opt, nullptr);
        }
    default:
        break;
    }
    return subcontrol != QStyle::SC_None ?
        qApp->style()->subControlRect(control,
                                      qstyleoption_cast<QStyleOptionComplex*>(m_styleoption),
                                      subcontrol) :
        QRectF();
}

namespace  {
class QHighDpiPixmapsEnabler1 {
public:
    QHighDpiPixmapsEnabler1(): wasEnabled(false) {
        if (!qApp->testAttribute(Qt::AA_UseHighDpiPixmaps)) {
            qApp->setAttribute(Qt::AA_UseHighDpiPixmaps);
            wasEnabled = true;
        }
    }

    ~QHighDpiPixmapsEnabler1() {
        if (wasEnabled)
            qApp->setAttribute(Qt::AA_UseHighDpiPixmaps, false);
    }

private:
    bool wasEnabled;
};
} // namespace

void StyleItem::paint(QPainter *painter)
{
    initStyleOption();
    QStyle *style = qApp->style();
    if (QStyleOptionMenuItem *opt =
        qstyleoption_cast<QStyleOptionMenuItem*>(m_styleoption)) {
        painter->setFont(opt->font);
    } else {
        QFont font;
        if (m_styleoption->state & QStyle::State_Mini) {
            font = qApp->font("QMiniFont");
        } else if (m_styleoption->state & QStyle::State_Small) {
            font = qApp->font("QSmallFont");
        }
        painter->setFont(font);
    }
    painter->setPen(m_styleoption->palette.text().color());
    painter->setBackground(m_styleoption->palette.window());

    // Set AA_UseHighDpiPixmaps when calling style code to make QIcon return
    // "retina" pixmaps. The flag is controlled by the application so we can't
    // set it unconditinally.
    QHighDpiPixmapsEnabler1 enabler;

    switch (m_itemType) {
    case Label:
        if (m_rendersText) {
            /* TODO: make the font property writable */
            QFont font = m_control->property("font").value<QFont>();
            painter->setFont(font);
            int alignment = textFlags();
            style->drawItemText(painter,
                                m_styleoption->rect,
                                alignment,
                                m_styleoption->palette,
                                isEnabled(),
                                text(),
                                QPalette::Text);
        }
        break;
    case Button:
        painter->setBackground(m_styleoption->palette.brush(QPalette::Button));
        style->drawControl(QStyle::CE_PushButton,
                           m_styleoption, painter);
        break;
    case ComboBoxDelegate:
        // From QItemDelegate::paintEvent()
        {
            QStyleOptionViewItem *opt =
                qstyleoption_cast<QStyleOptionViewItem*>(m_styleoption);
            QPalette::ColorGroup cg = opt->state & QStyle::State_Enabled ?
                QPalette::Normal : QPalette::Disabled;
            if (cg == QPalette::Normal &&
                !(opt->state & QStyle::State_Active)) {
                cg = QPalette::Inactive;
            }

            if (opt->state & QStyle::State_Selected) {
                    QBrush brush = opt->palette.brush(cg, QPalette::Highlight);
                    painter->fillRect(m_styleoption->rect, brush);
                painter->setPen(opt->palette.color(QPalette::HighlightedText));
            } else {
                painter->setPen(opt->palette.color(QPalette::Text));
            }

            const int textMargin =
                style->pixelMetric(QStyle::PM_FocusFrameHMargin) + 1;
            QRect rect = opt->rect.adjusted(textMargin, 0, -textMargin, 0);
            painter->drawText(rect, opt->text);
        }

        // focus rect (QItemDelegate::drawFocus):
        if (m_styleoption->state & QStyle::State_HasFocus) {
            QStyleOptionFocusRect o;
            o.QStyleOption::operator=(*m_styleoption);
            o.state |= QStyle::State_KeyboardFocusChange;
            o.state |= QStyle::State_Item;
            QPalette::ColorGroup cg = o.state & QStyle::State_Enabled ?
                QPalette::Normal : QPalette::Disabled;
            o.backgroundColor =
                o.palette.color(cg, (o.state & QStyle::State_Selected) ?
                                QPalette::Highlight : QPalette::Window);
            style->drawPrimitive(QStyle::PE_FrameFocusRect,
                                 &o, painter);
        }
        break;
    case ComboBoxPopup:
        {
            StyleItem *comboBox = qobject_cast<StyleItem*>(
                m_properties.value(QStringLiteral("combobox-style")).
                value<QObject*>());
            if (comboBox &&
                style->styleHint(QStyle::SH_ComboBox_Popup,
                                 comboBox->m_styleoption)) {
                QStyleOption opt;
                initStyleOption(&opt);
                style->drawPrimitive(QStyle::PE_PanelMenu, &opt, painter);
                /* The Fusion and Pixmap styles treat
                 * QComboBoxPrivateContainer specially: avoid
                 * printing the CE_ShapedFrame in those styles.
                 */
                QString styleName = this->style();
                if (styleName == QStringLiteral("fusion") ||
                    styleName == QStringLiteral("pixmap"))
                    return;
            }
            painter->fillRect(m_styleoption->rect,
                              m_styleoption->palette.brush(QPalette::Base));
            style->drawControl(QStyle::CE_ShapedFrame,
                               m_styleoption, painter);
        }
        break;
    case ComboMenuDelegate:
        painter->fillRect(m_styleoption->rect,
                          m_styleoption->palette.background());
        style->drawControl(QStyle::CE_MenuItem, m_styleoption, painter);
        break;
    case ItemRow:
        {
            QPixmap pixmap;
            // Only draw through style once
            const QString pmKey =
                QLatin1Literal("itemrow") %
                QString::number(m_styleoption->state,16) %
                activeControl();
            if (!QPixmapCache::find(pmKey, pixmap) ||
                pixmap.width() < width() ||
                height() != pixmap.height()) {
                int newSize = width();
                pixmap = QPixmap(newSize, height());
                pixmap.fill(Qt::transparent);
                QPainter pixpainter(&pixmap);
                style->drawPrimitive(QStyle::PE_PanelItemViewRow,
                                     m_styleoption, &pixpainter);
                if ((this->style() == QLatin1String("mac") ||
                     !style->styleHint(QStyle::SH_ItemView_ShowDecorationSelected)) &&
                    selected()) {
                    QPalette pal = QApplication::palette("QAbstractItemView");
                    pal.setCurrentColorGroup(
                        m_styleoption->palette.currentColorGroup());
                    pixpainter.fillRect(m_styleoption->rect, pal.highlight());
                }
                QPixmapCache::insert(pmKey, pixmap);
            }
            painter->drawPixmap(0, 0, pixmap);
        }
        break;
    case Item:
        style->drawControl(QStyle::CE_ItemViewItem,
                           m_styleoption, painter);
        break;
    case ItemBranchIndicator:
        style->drawPrimitive(QStyle::PE_IndicatorBranch,
                             m_styleoption, painter);
        break;
    case Header:
        style->drawControl(QStyle::CE_Header, m_styleoption, painter);
        break;
    case ToolButton:
        style->drawComplexControl(QStyle::CC_ToolButton,
                                  qstyleoption_cast<QStyleOptionComplex*>(m_styleoption),
                                  painter);
        break;
    case ToolSeparator:
        style->drawPrimitive(QStyle::PE_IndicatorToolBarSeparator,
                             m_styleoption, painter);
        break;
    case Tab:
        style->drawControl(QStyle::CE_TabBarTab,
                           m_styleoption, painter);
        break;
    case Frame:
        style->drawControl(QStyle::CE_ShapedFrame,
                           m_styleoption, painter);
        break;
    case FocusFrame:
        style->drawControl(QStyle::CE_FocusFrame,
                           m_styleoption, painter);
        break;
    case FocusRect:
        style->drawPrimitive(QStyle::PE_FrameFocusRect,
                             m_styleoption, painter);
        break;
    case TabFrame:
        {
            QStyleOptionTabWidgetFrame *cast =
                qstyleoption_cast<QStyleOptionTabWidgetFrame*>(m_styleoption);
            QStyleOptionTabWidgetFrame opt(*cast);
            opt.rect =
                style->subElementRect(QStyle::SE_TabWidgetTabPane, &opt);
            style->drawPrimitive(QStyle::PE_FrameTabWidget, &opt, painter);
        }
        break;
    case MenuBar:
        style->drawControl(QStyle::CE_MenuBarEmptyArea,
                           m_styleoption, painter);
        break;
    case MenuBarItem:
        style->drawControl(QStyle::CE_MenuBarItem,
                           m_styleoption, painter);
        break;
    case MenuItem:
        {
            QStyle::ControlElement menuElement =
                static_cast<QStyleOptionMenuItem *>(m_styleoption)->menuItemType == QStyleOptionMenuItem::Scroller ?
                QStyle::CE_MenuScroller : QStyle::CE_MenuItem;
            style->drawControl(menuElement, m_styleoption, painter);
        }
        break;
    case CheckBox:
        painter->setBackground(m_styleoption->palette.brush(QPalette::Button));
        style->drawControl(QStyle::CE_CheckBox,
                           m_styleoption, painter);
        break;
    case RadioButton:
        painter->setBackground(m_styleoption->palette.brush(QPalette::Button));
        style->drawControl(QStyle::CE_RadioButton,
                           m_styleoption, painter);
        break;
    case Edit:
        lineEditPaint(painter);
        break;
    case MacHelpButton:
        //Not managed as mac is not supported
        break;
    case Widget:
        style->drawPrimitive(QStyle::PE_Widget,
                             m_styleoption, painter);
        break;
    case ScrollAreaCorner:
        style->drawPrimitive(QStyle::PE_PanelScrollAreaCorner,
                             m_styleoption, painter);
        break;
    case Splitter:
        if (m_styleoption->rect.width() == 1)
            painter->fillRect(0, 0, width(), height(),
                              m_styleoption->palette.dark().color());
        else
            style->drawControl(QStyle::CE_Splitter,
                               m_styleoption, painter);
        break;
    case ComboBox:
        {
            style->drawComplexControl(QStyle::CC_ComboBox,
                                      qstyleoption_cast<QStyleOptionComplex*>(m_styleoption),
                                      painter);
            // This is needed on mac as it will use the painter color and
            // ignore the palette
            QPen pen = painter->pen();
            painter->setPen(m_styleoption->palette.text().color());
            style->drawControl(QStyle::CE_ComboBoxLabel,
                               m_styleoption, painter);
            painter->setPen(pen);
        }
        break;
    case SpinBox:
#ifdef Q_OS_MAC
        // macstyle depends on the embedded qlineedit to fill the editfield background
        if (this->style() == QLatin1String("mac")) {
            QRect editRect = style->subControlRect(QStyle::CC_SpinBox,
                                                   qstyleoption_cast<QStyleOptionComplex*>(m_styleoption),
                                                   QStyle::SC_SpinBoxEditField);
            painter->fillRect(editRect.adjusted(-1, -1, 1, 1), m_styleoption->palette.base());
        }
#endif
        style->drawComplexControl(QStyle::CC_SpinBox,
                                  qstyleoption_cast<QStyleOptionComplex*>(m_styleoption),
                                  painter);
        break;
    case Slider:
        style->drawComplexControl(QStyle::CC_Slider,
                                  qstyleoption_cast<QStyleOptionComplex*>(m_styleoption),
                                  painter);
        break;
    case Dial:
        style->drawComplexControl(QStyle::CC_Dial,
                                  qstyleoption_cast<QStyleOptionComplex*>(m_styleoption),
                                  painter);
        break;
    case ProgressBar:
        style->drawControl(QStyle::CE_ProgressBar,
                           m_styleoption, painter);
        break;
    case ToolBar:
        {
            // Hack: the Windows style look for the widget's ancestry
            QMainWindow window;
            QToolBar *toolBar = window.addToolBar(QStringLiteral(""));
            style->drawControl(QStyle::CE_ToolBar, m_styleoption,
                               painter, toolBar);
        }
        break;
    case StatusBar:
        {
            painter->fillRect(m_styleoption->rect,
                              m_styleoption->palette.window().color());
            painter->setPen(m_styleoption->palette.dark().color().darker(120));
            painter->drawLine(m_styleoption->rect.topLeft(),
                              m_styleoption->rect.topRight());
            style->drawPrimitive(QStyle::PE_PanelStatusBar,
                                 m_styleoption, painter);
        }
        break;
    case GroupBox:
        style->drawComplexControl(QStyle::CC_GroupBox,
                                  qstyleoption_cast<QStyleOptionComplex*>(m_styleoption),
                                  painter);
        break;
    case ScrollBar:
        style->drawComplexControl(QStyle::CC_ScrollBar,
                                  qstyleoption_cast<QStyleOptionComplex*>(m_styleoption),
                                  painter);
        break;
    case Menu:
        {
            QStyleHintReturnMask val;
            style->styleHint(QStyle::SH_Menu_Mask,
                             m_styleoption, nullptr, &val);
            painter->save();
            painter->setClipRegion(val.region);
            painter->fillRect(m_styleoption->rect,
                              m_styleoption->palette.window());
            painter->restore();
            style->drawPrimitive(QStyle::PE_PanelMenu,
                                 m_styleoption, painter);

            if (int fw = style->pixelMetric(QStyle::PM_MenuPanelWidth)) {
                QStyleOptionFrame frame;
                frame.state = QStyle::State_None;
                frame.lineWidth = fw;
                frame.midLineWidth = 0;
                frame.rect = m_styleoption->rect;
                frame.styleObject = this;
                frame.palette = m_styleoption->palette;
                style->drawPrimitive(QStyle::PE_FrameMenu,
                                     &frame, painter);
            }
        }
        break;
    case TitleBar:
        {
            QStyleOptionTitleBar *opt =
                qstyleoption_cast<QStyleOptionTitleBar*>(m_styleoption);
            int titleHeight =
                style->pixelMetric(QStyle::PM_TitleBarHeight, m_styleoption);
            m_styleoption->rect.setHeight(titleHeight);
            style->drawComplexControl(QStyle::CC_TitleBar, opt, painter);
        }
        break;
    case WindowFrame:
        painter->fillRect(m_styleoption->rect,
                          m_styleoption->palette.window());
        style->drawPrimitive(QStyle::PE_FrameWindow, m_styleoption, painter);
        break;
    default:
        break;
    }
}

qreal StyleItem::textWidth(const QString &text)
{
    QFontMetricsF fm = QFontMetricsF(m_styleoption->fontMetrics);
    return fm.boundingRect(text).width();
}

qreal StyleItem::textHeight(const QString &text)
{
    QFontMetricsF fm = QFontMetricsF(m_styleoption->fontMetrics);
    return text.isEmpty() ? fm.height() :
                            fm.boundingRect(text).height();
}

QString StyleItem::elidedText(const QString &text,
                                    int elideMode, int width)
{
    return m_styleoption->fontMetrics.elidedText(text,
                                                 Qt::TextElideMode(elideMode),
                                                 width);
}

bool StyleItem::hasThemeIcon(const QString &icon) const
{
    return QIcon::hasThemeIcon(icon);
}

void StyleItem::sendKeyRelease(Qt::Key key)
{
    QKeyEvent event(QEvent::KeyRelease, key, Qt::NoModifier);
    qApp->sendEvent(m_control, &event);
}

bool StyleItem::event(QEvent *ev)
{
    if (ev->type() == QEvent::StyleAnimationUpdate) {
        if (isVisible()) {
            ev->accept();
            polish();
        }
        return true;
    } else if (ev->type() == QEvent::StyleChange) {
        if (m_itemType == ScrollBar)
            initStyleOption();
    }
    return QQuickItem::event(ev);
}

void StyleItem::setTextureWidth(int w)
{
    if (m_textureWidth == w)
        return;
    m_textureWidth = w;
    Q_EMIT textureWidthChanged(m_textureWidth);
    update();
}

void StyleItem::setTextureHeight(int h)
{
    if (m_textureHeight == h)
        return;
    m_textureHeight = h;
    Q_EMIT textureHeightChanged(m_textureHeight);
    update();
}

QQuickItem *StyleItem::control() const
{
    return m_control;
}

void StyleItem::setControl(QQuickItem *control)
{
    if (control == m_control) {
        return;
    }

    if (m_control) {
        m_control->removeEventFilter(this);
        disconnect(m_control, 0, this, 0);
    }

    m_control = control;

    if (m_control) {
        m_control->installEventFilter(this);

        if (m_control->window()) {
            m_window = m_control->window();
            m_window->installEventFilter(this);
        }
        connect(m_control, &QQuickItem::windowChanged, this,
                [this](QQuickWindow *window) {
            if (m_window) {
                m_window->removeEventFilter(this);
            }
            m_window = window;
            if (m_window) {
                m_window->installEventFilter(this);
            }
        });
    }

    Q_EMIT controlChanged();
}

QSGNode *StyleItem::updatePaintNode(QSGNode *node, UpdatePaintNodeData *)
{
    if (m_image.isNull()) {
        delete node;
        return nullptr;
    }

    QSGNinePatchNode *styleNode = static_cast<QSGNinePatchNode *>(node);
    if (!styleNode)
        styleNode = window()->createNinePatchNode();

#ifdef QSG_RUNTIME_DESCRIPTION
    qsgnode_set_description(styleNode,
                            QString::fromLatin1("%1:%2, '%3'")
                            .arg(style())
                            .arg(elementType())
                            .arg(text()));
#endif

    styleNode->setTexture(
        window()->createTextureFromImage(m_image,
                                         QQuickWindow::TextureCanUseAtlas));
    QRectF rect = boundingRect();
    if (m_border.left() == 0 &&
        m_border.right() == 0 &&
        m_border.top() == 0 &&
        m_border.bottom() == 0) {
        rect.setSize(m_image.size()); // prevent scaling
    }
    styleNode->setBounds(rect);
    styleNode->setDevicePixelRatio(window()->devicePixelRatio());
    styleNode->setPadding(m_border.left(), m_border.top(),
                          m_border.right(), m_border.bottom());
    styleNode->update();

    return styleNode;
}

void StyleItem::geometryChanged(const QRectF &newGeometry,
                                const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    if (widthValid()) {
        switch (m_itemType) {
        case Label:
            updateSizeHint();
            break;
        case TabFrame:
            updateSizeHint();
            resizeTabBar(newGeometry);
            break;
        default:
            break;
        }
    }
    updateItem();
}

void StyleItem::updatePolish()
{
    if (width() >= 1 && height() >= 1) { // Note these are reals so 1 pixel is minimum
        float devicePixelRatio = window() ?
            window()->devicePixelRatio() : qApp->devicePixelRatio();
        int w = m_textureWidth > 0 ? m_textureWidth : width();
        int h = m_textureHeight > 0 ? m_textureHeight : height();
        m_image = QImage(w * devicePixelRatio,
                         h * devicePixelRatio,
                         QImage::Format_ARGB32_Premultiplied);
        m_image.setDevicePixelRatio(devicePixelRatio);
        m_image.fill(Qt::transparent);
        QPainter painter(&m_image);
        painter.setLayoutDirection(qApp->layoutDirection());
        paint(&painter);
        QQuickItem::update();
    } else if (!m_image.isNull()) {
        m_image = QImage();
        QQuickItem::update();
    }
}

bool StyleItem::buttonFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress ||
        event->type() == QEvent::KeyRelease) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return) {
            QKeyEvent key(keyEvent->type(),
                          Qt::Key_Space,
                          keyEvent->modifiers(),
                          keyEvent->nativeScanCode(),
                          keyEvent->nativeVirtualKey(),
                          keyEvent->nativeModifiers(),
                          keyEvent->text(),
                          keyEvent->isAutoRepeat(),
                          keyEvent->count());
            qApp->sendEvent(watched, &key);
            return true;
        }
    }
    return QQuickItem::eventFilter(watched, event);
}

bool StyleItem::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_control) {
        if (event->type() == QEvent::FocusIn ||
            event->type() == QEvent::FocusOut) {
            QFocusEvent *fe = static_cast<QFocusEvent *>(event);
            m_lastFocusReason = fe->reason();
        }
        if (m_itemType == ComboBoxDelegate ||
            m_itemType == ComboMenuDelegate) {
            return buttonFilter(watched, event);
        }
    } else if (watched == m_window.data()) {
        if (event->type() == QEvent::KeyPress ||
            event->type() == QEvent::KeyRelease) {
            QKeyEvent *ke = static_cast<QKeyEvent *>(event);
            if (ke->key() == Qt::Key_Alt) {
                updateItem();
            }
        }
    }

    return QQuickItem::eventFilter(watched, event);
}

QPixmap QQuickTableRowImageProvider1::requestPixmap(const QString &id,
                                                    QSize *size,
                                                    const QSize &requestedSize)
{
    Q_UNUSED (requestedSize);
    int width = 16;
    int height = 16;
    if (size)
        *size = QSize(width, height);

    QPixmap pixmap(width, height);

    QStyleOptionViewItem opt;
    opt.state |= QStyle::State_Enabled;
    opt.rect = QRect(0, 0, width, height);
    QString style =
        QString::fromLatin1(qApp->style()->metaObject()->className());
    opt.features = 0;

    if (id.contains(QLatin1String("selected")))
        opt.state |= QStyle::State_Selected;

    if (id.contains(QLatin1String("active"))) {
        opt.state |= QStyle::State_Active;
        opt.palette.setCurrentColorGroup(QPalette::Active);
    } else
        opt.palette.setCurrentColorGroup(QPalette::Inactive);

    if (id.contains(QLatin1String("alternate")))
        opt.features |= QStyleOptionViewItem::Alternate;

    QPalette pal = QApplication::palette("QAbstractItemView");
    if (opt.state & QStyle::State_Selected &&
        (style.contains(QLatin1String("Mac")) ||
         !qApp->style()->styleHint(QStyle::SH_ItemView_ShowDecorationSelected))) {
        pal.setCurrentColorGroup(opt.palette.currentColorGroup());
        pixmap.fill(pal.highlight().color());
    } else {
        pixmap.fill(pal.base().color());
        QPainter pixpainter(&pixmap);
        qApp->style()->drawPrimitive(QStyle::PE_PanelItemViewRow,
                                     &opt, &pixpainter);
    }
    return pixmap;
}

void StyleItem::lineEditPaint(QPainter *painter)
{
    QPainter &p = *painter; // just renaming, closer to QLineEdit code
    qApp->style()->drawPrimitive(QStyle::PE_PanelLineEdit,
                                 m_styleoption, painter);

    QRect r = qApp->style()->subElementRect(QStyle::SE_LineEditContents,
                                            m_styleoption);
    p.setClipRect(r);

    const QFontMetrics &fm = m_styleoption->fontMetrics;
    int vscroll;
    const int horizontalMargin = LINEEDIT_HORIZONAL_MARGIN;
    const int verticalMargin = LINEEDIT_VERTICAL_MARGIN;
    Qt::AlignmentFlag vertical = static_cast<Qt::AlignmentFlag>(
        m_properties.value(QStringLiteral("verticalAlignment")).
        toInt());
    switch (vertical) {
    case Qt::AlignBottom:
        vscroll = r.y() + r.height() - fm.height() - verticalMargin;
        break;
    case Qt::AlignTop:
        vscroll = r.y() + verticalMargin;
        break;
    default:
        //center
        vscroll = r.y() + (r.height() - fm.height() + 1) / 2;
        break;
    }
    QRect lineRect(r.x() + horizontalMargin, vscroll,
                   r.width() - 2 * horizontalMargin, fm.height());

    Qt::AlignmentFlag alignment = static_cast<Qt::AlignmentFlag>(
        m_properties.value(QStringLiteral("horizontalAlignment")).
        toInt());
    bool shouldShowPlaceholderText =
        text().isEmpty() && !((alignment & Qt::AlignHCenter) && m_focus);
    QString placeholderText =
        m_properties.value(QStringLiteral("placeholderText")).toString();

    if (shouldShowPlaceholderText && !placeholderText.isEmpty()) {
        const Qt::LayoutDirection layoutDir =
            placeholderText.isRightToLeft() ?
            Qt::RightToLeft : Qt::LeftToRight;
        const Qt::Alignment alignPhText =
            QStyle::visualAlignment(layoutDir, QFlag(alignment));
#if (QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)) // See QTBUG-74178
        const QColor col = m_styleoption->palette.placeholderText().color();
#else
        QColor col = m_styleoption->palette.text().color();
        col.setAlpha(128);
#endif
        QPen oldpen = p.pen();
        p.setPen(col);
        Qt::LayoutDirection oldLayoutDir = p.layoutDirection();
        p.setLayoutDirection(layoutDir);

        const QString elidedText = fm.elidedText(placeholderText,
                                                 Qt::ElideRight,
                                                 width());
        p.drawText(lineRect, alignPhText, elidedText);
        p.setPen(oldpen);
        p.setLayoutDirection(oldLayoutDir);
    }
}

void StyleItem::updateRendersText()
{
    Qt::TextFormat format =
        m_properties.value(QStringLiteral("textFormat"), Qt::AutoText).
        value<Qt::TextFormat>();
    bool rendersText =
        format == Qt::PlainText ||
        (format == Qt::AutoText && !Qt::mightBeRichText(text()));
    if (rendersText != m_rendersText) {
        m_rendersText = rendersText;
        Q_EMIT rendersTextChanged();
    }
}

QString StyleItem::progressBarComputeText() const
{
    if ((m_maximum == 0 && m_minimum == 0) || m_value < m_minimum
            || (m_value == INT_MIN && m_minimum == INT_MIN))
        return QString();

    qint64 totalSteps = qint64(m_maximum) - m_minimum;

    QLocale locale;
    QString format = QLatin1String("%p") + locale.percent();
    QString result = format;
    // Omit group separators for compatibility with previous versions that were non-localized.
    locale.setNumberOptions(locale.numberOptions() |
                            QLocale::OmitGroupSeparator);
    result.replace(QLatin1String("%m"), locale.toString(totalSteps));
    result.replace(QLatin1String("%v"), locale.toString(m_value));

    // If max and min are equal and we get this far, it means that the
    // progress bar has one step and that we are on that step. Return
    // 100% here in order to avoid division by zero further down.
    if (totalSteps == 0) {
        result.replace(QLatin1String("%p"), locale.toString(100));
        return result;
    }

    const auto progress =
        static_cast<int>((qint64(m_value) - m_minimum) * 100.0 / totalSteps);
    result.replace(QLatin1String("%p"), locale.toString(progress));
    return result;
}

int StyleItem::textFlags() const
{
    int flags =
        m_properties.value(QStringLiteral("horizontalAlignment")).toInt();
    switch (m_properties.value(QStringLiteral("wrapMode")).toInt()) {
    case 0: // NoWrap
        flags |= Qt::TextSingleLine; break;
    case 3: // WrapAnywhere
        flags |= Qt::TextWrapAnywhere; break;
    case 1: // WordWrap
    case 4: // Wrap
    default:
        flags |= Qt::TextWordWrap; break;
    }
    return flags;
}

int StyleItem::comboBoxWidthHint() const
{
    QStyle *style = qApp->style();
    if (style->styleHint(QStyle::SH_ComboBox_Popup, m_styleoption)) {
        // from QComboBoxPrivate::computeWidthHint()
        const QFontMetrics &fm = m_styleoption->fontMetrics;
        int w = 0;
        if (!m_control) return 0;
        int count = m_control->property("count").toInt();
        for (int i = 0; i < count; i++) {
            QString text;
            bool ok =
                QMetaObject::invokeMethod(m_control.data(),
                                          "textAt",
                                          Q_RETURN_ARG(QString, text),
                                          Q_ARG(int, i));
            if (ok) {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 11, 0))
                w = qMax(w, fm.horizontalAdvance(text));
#else
                w = qMax(w, fm.width(text));
#endif
            }
        }
        QSize tmp(w, 0);
        tmp = style->sizeFromContents(QStyle::CT_ComboBox, m_styleoption, tmp);
        return tmp.width();
    } else {
        // from QComboBox::showPopup()
        QStyleOptionComboBox *opt =
            qstyleoption_cast<QStyleOptionComboBox*>(m_styleoption);
        QRect listRect(style->subControlRect(QStyle::CC_ComboBox, opt,
                                             QStyle::SC_ComboBoxListBoxPopup));
        return listRect.width();
    }
}

void StyleItem::resizeTabBar(const QRectF &ourGeometry)
{
    QQuickItem *tabBar =
        qobject_cast<QQuickItem*>(m_properties[QStringLiteral("tabBar")].
                                  value<QObject*>());
    if (tabBar) {
        tabBar->setWidth(ourGeometry.width());
    }
}
