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

#ifndef STYLEITEM_P_H
#define STYLEITEM_P_H

#include <QImage>
#include <QPointer>
#include <QQuickItem>
#include <QQuickImageProvider>
#include "padding_p.h"

class QWidget;
class QStyleOption;

class QQuickTableRowImageProvider1: public QQuickImageProvider
{
public:
    QQuickTableRowImageProvider1():
        QQuickImageProvider(QQuickImageProvider::Pixmap) {}
    QPixmap requestPixmap(const QString &id, QSize *size,
                          const QSize &requestedSize) override;
};

class StyleItem: public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(Padding *border READ border CONSTANT)
    Q_PROPERTY(Padding *contentMargins READ contentMargins CONSTANT)

    Q_PROPERTY(bool sunken READ sunken WRITE setSunken NOTIFY sunkenChanged)
    Q_PROPERTY(bool raised READ raised WRITE setRaised NOTIFY raisedChanged)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(bool selected READ selected WRITE setSelected
               NOTIFY selectedChanged)
    Q_PROPERTY(bool hasFocus READ hasFocus WRITE setHasFocus
               NOTIFY hasFocusChanged)
    Q_PROPERTY(bool on READ on WRITE setOn NOTIFY onChanged)
    Q_PROPERTY(bool hover READ hover WRITE setHover NOTIFY hoverChanged)
    Q_PROPERTY(bool horizontal READ horizontal WRITE setHorizontal
               NOTIFY horizontalChanged)
    Q_PROPERTY(bool isTransient READ isTransient WRITE setTransient
               NOTIFY transientChanged)

    Q_PROPERTY(QString elementType READ elementType WRITE setElementType
               NOTIFY elementTypeChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString activeControl READ activeControl WRITE setActiveControl
               NOTIFY activeControlChanged)
    Q_PROPERTY(QString style READ style NOTIFY styleChanged)
    Q_PROPERTY(QVariantMap hints READ hints WRITE setHints NOTIFY hintChanged
               RESET resetHints)
    Q_PROPERTY(QVariantMap properties READ properties WRITE setProperties
               NOTIFY propertiesChanged)
    Q_PROPERTY(QVariantMap outputProperties READ outputProperties
               NOTIFY outputPropertiesChanged)
    Q_PROPERTY(QFont font READ font NOTIFY fontChanged)

    /* For Label: tells whether the test is going to be rendered by this item */
    Q_PROPERTY(bool rendersText READ rendersText NOTIFY rendersTextChanged)

    // For range controls
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(int step READ step WRITE setStep NOTIFY stepChanged)
    Q_PROPERTY(int paintMargins READ paintMargins WRITE setPaintMargins
               NOTIFY paintMarginsChanged)

    Q_PROPERTY(int contentWidth READ contentWidth WRITE setContentWidth
               NOTIFY contentWidthChanged)
    Q_PROPERTY(int contentHeight READ contentHeight WRITE setContentHeight
               NOTIFY contentHeightChanged)

    Q_PROPERTY(int textureX READ textureX WRITE setTextureX
               NOTIFY textureXChanged)
    Q_PROPERTY(int textureY READ textureY WRITE setTextureY
               NOTIFY textureYChanged)
    Q_PROPERTY(int textureWidth READ textureWidth WRITE setTextureWidth
               NOTIFY textureWidthChanged)
    Q_PROPERTY(int textureHeight READ textureHeight WRITE setTextureHeight
               NOTIFY textureHeightChanged)

    Q_PROPERTY(QQuickItem *control READ control WRITE setControl
               NOTIFY controlChanged)

    Padding *border() { return &m_border; }
    Padding *contentMargins() { return &m_contentMargins; }

public:
    StyleItem(QQuickItem *parent = nullptr);
    ~StyleItem() override;

    enum MenuItemType {
        ItemType = 0,
        SeparatorType,
        MenuType,
        ScrollIndicatorType,
    };
    Q_ENUM(MenuItemType)

    enum Type {
        Undefined,
        Label,
        Button,
        RadioButton,
        CheckBox,
        ComboBox,
        ComboBoxDelegate,
        ComboBoxPopup,
        ComboMenuDelegate,
        Dial,
        ToolBar,
        ToolButton,
        ToolSeparator,
        Tab,
        TabFrame,
        Frame,
        FocusFrame,
        FocusRect,
        SpinBox,
        Slider,
        ScrollBar,
        ProgressBar,
        Edit,
        GroupBox,
        Header,
        Item,
        ItemRow,
        ItemBranchIndicator,
        Splitter,
        Menu,
        MenuItem,
        Widget,
        StatusBar,
        ScrollAreaCorner,
        MacHelpButton,
        MenuBar,
        MenuBarItem,
        TitleBar,
        WindowFrame,
    };

    void paint(QPainter *);

    void setSunken(bool sunken);
    bool sunken() const { return m_sunken; }

    void setRaised(bool raised);
    bool raised() const { return m_raised; }

    void setActive(bool active);
    bool active() const { return m_active; }

    void setSelected(bool selected);
    bool selected() const { return m_selected; }

    void setHasFocus(bool focus);
    bool hasFocus() const { return m_focus; }

    void setOn(bool on);
    bool on() const { return m_on; }

    void setHover(bool hover);
    bool hover() const { return m_hover; }

    void setHorizontal(bool horizontal);
    bool horizontal() const { return m_horizontal; }

    void setTransient(bool transient);
    bool isTransient() const { return m_transient; }

    void setMinimum(int minimum);
    int minimum() const { return m_minimum; }

    void setMaximum(int maximum);
    int maximum() const { return m_maximum; }

    void setValue(int value);
    int value() const { return m_value; }

    void setStep(int step);
    int step() const { return m_step; }

    void setPaintMargins(int value);
    int paintMargins() const { return m_paintMargins; }

    void setElementType(const QString &str);
    QString elementType() const { return m_type; }

    void setText(const QString &str);
    QString text() const { return m_text; }

    void setActiveControl(const QString &str);
    QString activeControl() const { return m_activeControl; }

    void setHints(const QVariantMap &str);
    QVariantMap hints() const { return m_hints; }
    void resetHints();

    void setProperties(const QVariantMap &props);
    QVariantMap properties() const { return m_properties; }

    QVariantMap outputProperties() const { return m_outputProperties; }

    QFont font() const { return m_font;}
    bool rendersText() const { return m_rendersText; }
    QString style() const;


    void setContentWidth(int arg);
    int contentWidth() const { return m_contentWidth; }

    void setContentHeight(int arg);
    int contentHeight() const { return m_contentHeight; }

    virtual void initStyleOption ();
    void initStyleOption(QStyleOption *opt) const;
    void resolvePalette(QStyleOption *opt) const;

    Q_INVOKABLE qreal textWidth(const QString &);
    Q_INVOKABLE qreal textHeight(const QString &);

    void setTextureX(int x);
    int textureX() const { return m_textureX; }

    void setTextureY(int y);
    int textureY() const { return m_textureY; }

    void setTextureWidth(int w);
    int textureWidth() const { return m_textureWidth; }

    void setTextureHeight(int h);
    int textureHeight() const { return m_textureHeight; }

    void setControl(QQuickItem *control);
    QQuickItem *control() const;

public Q_SLOTS:
    int pixelMetric(const QString &);
    QVariant styleHint(const QString &);
    void updateSizeHint();
    void updateContentMargins();
    void updateRect();
    void updateBaselineOffset();
    void updateItem(){polish();}
    QString hitTest(int x, int y);
    QRectF subControlRect(const QString &subcontrolString);
    QString elidedText(const QString &text, int elideMode, int width);
    bool hasThemeIcon(const QString &) const;
    void sendKeyRelease(Qt::Key key);

Q_SIGNALS:
    void elementTypeChanged();
    void textChanged();
    void sunkenChanged();
    void raisedChanged();
    void activeChanged();
    void selectedChanged();
    void hasFocusChanged();
    void onChanged();
    void hoverChanged();
    void horizontalChanged();
    void transientChanged();
    void minimumChanged();
    void maximumChanged();
    void stepChanged();
    void valueChanged();
    void activeControlChanged();
    void infoChanged();
    void styleChanged();
    void paintMarginsChanged();
    void hintChanged();
    void propertiesChanged();
    void outputPropertiesChanged();
    void fontChanged();
    void rendersTextChanged();
    void controlChanged();

    void contentWidthChanged(int arg);
    void contentHeightChanged(int arg);

    void textureXChanged();
    void textureYChanged();
    void textureWidthChanged(int w);
    void textureHeightChanged(int h);

protected:
    void componentComplete() override;
    bool event(QEvent *) override;
    void geometryChanged(const QRectF &newGeometry,
                         const QRectF &oldGeometry) override;
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;
    void updatePolish() override;
    bool eventFilter(QObject *watched, QEvent *event) override;

    void setOutputProperty(const QString &name, const QVariant &value);

private:
    const char *classNameForItem() const;
    bool hasAncestor(const char *name) const;

    QSize sizeFromContents(int width, int height);
    qreal baselineOffset();
    QString progressBarComputeText() const;
    int textFlags() const;
    int comboBoxWidthHint() const;

    bool buttonFilter(QObject *watched, QEvent *event);

    void lineEditPaint(QPainter *painter);
    void updateRendersText();
    void resizeTabBar(const QRectF &ourGeometry);

protected:
    QStyleOption *m_styleoption;
    QPointer<QQuickItem> m_control;
    QPointer<QWindow> m_window;
    Type m_itemType;

    QString m_type;
    QString m_text;
    QString m_activeControl;
    QVariantMap m_hints;
    QVariantMap m_properties;
    QVariantMap m_outputProperties;
    QFont m_font;

    bool m_sunken;
    bool m_raised;
    bool m_active;
    bool m_selected;
    bool m_focus;
    bool m_hover;
    bool m_on;
    bool m_horizontal;
    bool m_transient;
    bool m_sharedWidget;
    bool m_rendersText;

    int m_minimum;
    int m_maximum;
    int m_value;
    int m_step;
    int m_paintMargins;

    int m_contentWidth;
    int m_contentHeight;

    int m_textureX;
    int m_textureY;
    int m_textureWidth;
    int m_textureHeight;

    Qt::FocusReason m_lastFocusReason;

    QImage m_image;
    Padding m_border;
    Padding m_contentMargins;
};

#endif // STYLEITEM_P_H
