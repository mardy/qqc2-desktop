/*
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

#include <QHash>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickItem>
#include <QQuickStyle>
#include <QScopedPointer>
#include <QScreen>
#include <QStyle>
#include <QTemporaryDir>
#include <QTest>
#include <QUiLoader>
#include <QWindow>

struct InputEvent {
    enum Type {
        None = 0,
        KeyClick,
        KeyPress,
        KeyRelease,
        MouseMove,
        MouseClick,
    };

    InputEvent(): type(None) {}

    InputEvent(Qt::Key key,
               Qt::KeyboardModifiers mod = Qt::NoModifier):
        type(KeyClick), key(key), modifier(mod) {}

    InputEvent(Type type,
               Qt::Key key,
               Qt::KeyboardModifiers mod = Qt::NoModifier):
        type(type), key(key), modifier(mod) {}

    InputEvent(Type type, const QPoint &p):
        type(type), button(Qt::LeftButton), point(p) {}

    Type type;
    Qt::Key key;
    Qt::KeyboardModifiers modifier;
    Qt::MouseButton button;
    QPoint point;
};
Q_DECLARE_METATYPE(InputEvent)

typedef QList<InputEvent> InputEvents;
typedef QHash<QString, QImage> SnapShots;

class ConformanceTest: public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void init();
    void cleanup();
    void testBaseline_data();
    void testBaseline();
    void testPixelByPixel_data();
    void testPixelByPixel();
    void testPixelByPixelMasked_data();
    void testPixelByPixelMasked();

protected:
    SnapShots createAndCapture(const QString &baseName,
                               const InputEvents &inputEvents);

private:
    QTemporaryDir *m_tmp;
};

SnapShots ConformanceTest::createAndCapture(const QString &baseName,
                                            const InputEvents &inputEvents)
{
    QHash<QString, QImage> snapShots;

    /* Load the QtWidgets window */
    QUiLoader loader;
    QFile file(QString(DATA_DIR "/%1.ui").arg(baseName));
    file.open(QFile::ReadOnly);
    QScopedPointer<QWidget> widget(loader.load(&file));
    file.close();

    if (!loader.errorString().isEmpty()) {
        qWarning() << "Failed to load QWidget" << loader.errorString();
        return snapShots;
    }
    widget->show();

    /* Load the QML window */
    QQmlApplicationEngine engine(QString(DATA_DIR "/%1.qml").arg(baseName));
    while (engine.rootObjects().isEmpty()) {
        QTest::qWait(10);
    }

    /* Give it some time to process the events: without this, it can happen
     * that the QtQuick window gets shown later, while we are handling the
     * QtWidgets one in the loop below, causing it to lose the focus.
     */
    QTest::qWait(50);

    /* Get a handle to the windows */
    while (QGuiApplication::topLevelWindows().count() != 2) {
        QTest::qWait(10);
    }

    /* Get a snapshot of each window */
    for (QWindow *window: QGuiApplication::topLevelWindows()) {
        /* Let's focus the window */
        window->requestActivate();
        window->raise();
        while (!window->isActive()) {
            QTest::qWait(10);
        }

        for (const auto &event: inputEvents) {
            if (event.type == InputEvent::KeyClick) {
                QTest::keyClick(window, event.key, event.modifier);
            } else if (event.type == InputEvent::KeyPress) {
                QTest::keyPress(window, event.key, event.modifier);
            } else if (event.type == InputEvent::KeyRelease) {
                QTest::keyRelease(window, event.key, event.modifier);
            } else if (event.type == InputEvent::MouseMove) {
                QTest::mouseMove(window, event.point);
            } else if (event.type == InputEvent::MouseClick) {
                QTest::mouseClick(window, event.button,
                                  event.modifier, event.point);
            }
        }

        // Give it some time to process the events and repaint
        QTest::qWait(50);

        QScreen *screen = window->screen();
        QPixmap pixmap = screen->grabWindow(window->winId());
        QImage image = pixmap.toImage();
        snapShots[window->objectName()] = image;

        image.save(m_tmp->path() + '/' + window->objectName() + ".bmp", "BMP");
    }

    return snapShots;
}

void ConformanceTest::initTestCase()
{
    QCoreApplication::setAttribute(Qt::AA_Use96Dpi, false);
    QQuickStyle::setStyle("Desktop");

    qDebug() << "current style:" <<
        QApplication::style()->metaObject()->className();
}

void ConformanceTest::init()
{
    m_tmp = new QTemporaryDir();
    QVERIFY(m_tmp->isValid());
}

void ConformanceTest::cleanup()
{
    if (QTest::currentTestFailed()) {
        m_tmp->setAutoRemove(false);
        qDebug() << "Temporary files have been left in" << m_tmp->path();
    }

    delete m_tmp;
    m_tmp = nullptr;
}

void ConformanceTest::testBaseline_data()
{
    QTest::addColumn<QString>("baseName");

    QTest::newRow("label") <<
        "Label";

    QTest::newRow("button") <<
        "Button";

    QTest::newRow("radio button") <<
        "RadioButton";

    QTest::newRow("checkbox") <<
        "CheckBox";
}

void ConformanceTest::testBaseline()
{
    QFETCH(QString, baseName);

    QQmlApplicationEngine engine(QString(DATA_DIR "/%1.qml").arg(baseName));
    QTRY_COMPARE(engine.rootObjects().count(), 1);

    QObject *root = engine.rootObjects().first();
    QQuickItem *item = root->findChild<QQuickItem*>("control");
    QVERIFY(item);

    // This should darken the line just above the baseline
    item->setProperty("text", QString("LLLLLLLLLLL"));

    // Give it some time to process the events and repaint
    QTest::qWait(50);

    QWindow *window = qobject_cast<QWindow*>(root);
    QVERIFY(window);
    QScreen *screen = window->screen();
    QPixmap pixmap = screen->grabWindow(window->winId());
    QImage image = pixmap.toImage();

    int baselineOffset = item->property("baselineOffset").toInt();
    QVERIFY(baselineOffset > 0);
    int x0 = item->x();
    int y0 = item->y() + baselineOffset;

    qreal lightnessBaseline = 0;
    qreal lightnessText = 0;
    for (int x = 0; x < item->width(); x++) {
        lightnessBaseline += image.pixelColor(x + x0, y0).lightnessF();
        lightnessText += image.pixelColor(x + x0, y0 - 1).lightnessF();
    }
    QPainter p(&image);
    p.setPen(Qt::red);
    p.drawLine(x0, y0, image.width(), y0);
    p.end();
    image.save(m_tmp->path() + '/' + window->objectName() + ".bmp", "BMP");

    QVERIFY(lightnessBaseline > lightnessText * 2);
}

void ConformanceTest::testPixelByPixel_data()
{
    QTest::addColumn<QString>("baseName");
    QTest::addColumn<InputEvents>("inputEvents");

    QTest::newRow("all, disabled") <<
        "AllDisabled" <<
        InputEvents {};

    QTest::newRow("label") <<
        "Label" <<
        InputEvents {};

    QTest::newRow("label, rich") <<
        "LabelRichText" <<
        InputEvents {};

    QTest::newRow("button") <<
        "Button" <<
        InputEvents {};

    QTest::newRow("button, hovered") <<
        "Button" <<
        InputEvents {
            InputEvent(InputEvent::MouseMove, QPoint(4,8)),
            InputEvent(InputEvent::MouseMove, QPoint()),
        };

    QTest::newRow("checkbox") <<
        "CheckBox" <<
        InputEvents {};

    QTest::newRow("checkbox, hovered") <<
        "CheckBox" <<
        InputEvents {
            InputEvent(InputEvent::MouseMove, QPoint(4,8)),
            InputEvent(InputEvent::MouseMove, QPoint()),
        };

    QTest::newRow("checkbox, half checked") <<
        "CheckBox" <<
        InputEvents {
            InputEvent(Qt::Key_Space),
        };

    QTest::newRow("checkbox, checked") <<
        "CheckBox" <<
        InputEvents {
            InputEvent(Qt::Key_Space),
            InputEvent(Qt::Key_Space),
        };

    QTest::newRow("checkbox, pressed") <<
        "CheckBox" <<
        InputEvents {
            InputEvent(InputEvent::KeyPress, Qt::Key_Space),
        };

    QTest::newRow("combobox") <<
        "ComboBox" <<
        InputEvents {};

    QTest::newRow("combobox, hovered") <<
        "ComboBox" <<
        InputEvents {
            InputEvent(InputEvent::MouseMove, QPoint(4,8)),
            InputEvent(InputEvent::MouseMove, QPoint()),
        };

    QTest::newRow("combobox, editable") <<
        "ComboBoxEditable" <<
        InputEvents {};

    QTest::newRow("radio button") <<
        "RadioButton" <<
        InputEvents {};

    QTest::newRow("radio button, hovered") <<
        "RadioButton" <<
        InputEvents {
            InputEvent(InputEvent::MouseMove, QPoint(4,8)),
            InputEvent(InputEvent::MouseMove, QPoint()),
        };

    QTest::newRow("radio button, checked") <<
        "RadioButton" <<
        InputEvents {
            InputEvent(Qt::Key_Space),
        };

    QTest::newRow("radio button, pressed") <<
        "RadioButton" <<
        InputEvents {
            InputEvent(InputEvent::KeyPress, Qt::Key_Space),
        };

    QTest::newRow("frame") <<
        "Frame" <<
        InputEvents {};

    QTest::newRow("groupbox") <<
        "GroupBox" <<
        InputEvents {};

    QTest::newRow("groupbox, long title") <<
        "GroupBoxLongTitle" <<
        InputEvents {};

    QTest::newRow("progress bar") <<
        "ProgressBar" <<
        InputEvents {};

    QTest::newRow("text field") <<
        "TextField" <<
        InputEvents {};

    QTest::newRow("text field, input") <<
        "TextField" <<
        InputEvents {
            InputEvent(InputEvent::KeyPress, Qt::Key_H),
        };

    QTest::newRow("spinbox") <<
        "SpinBox" <<
        InputEvents {};

    QTest::newRow("spinbox, writing") <<
        "SpinBox" <<
        InputEvents {
            InputEvent(InputEvent::KeyPress, Qt::Key_4),
            InputEvent(InputEvent::KeyClick, Qt::Key_Delete),
        };

    QTest::newRow("slider") <<
        "Slider" <<
        InputEvents {};

    QTest::newRow("scrollbar, vertical") <<
        "ScrollBarVertical" <<
        InputEvents {};

    QTest::newRow("scrollbar, horizontal") <<
        "ScrollBarHorizontal" <<
        InputEvents {};

    QTest::newRow("scrollbar, click") <<
        "ScrollBarHorizontal" <<
        InputEvents {
            InputEvent(InputEvent::MouseMove, QPoint(2,2)),
            InputEvent(InputEvent::MouseMove, QPoint(5,5)),
            InputEvent(InputEvent::MouseClick, QPoint(5,5)),
        };

    QTest::newRow("row layout") <<
        "RowLayout" <<
        InputEvents {};

    QTest::newRow("grid layout") <<
        "GridLayout" <<
        InputEvents {};
}

void ConformanceTest::testPixelByPixel()
{
    QFETCH(QString, baseName);
    QFETCH(InputEvents, inputEvents);

    if (qstrcmp(QTest::currentDataTag(), "label, rich") == 0) {
        QSKIP("Size for rich text labels is not computed, underline is wrong");
    }

    SnapShots snapShots = createAndCapture(baseName, inputEvents);

    const QImage &qmlWindow = snapShots.value("qmlWindow");
    const QImage &widgetWindow = snapShots.value("widgetWindow");

    QCOMPARE(qmlWindow.size(), widgetWindow.size());

    QImage diff(qmlWindow);
    QPainter p(&diff);
    p.setCompositionMode(QPainter::CompositionMode_Difference);
    p.drawImage(QPoint(0, 0), widgetWindow);
    p.end();
    diff.save(m_tmp->path() + "/diff.bmp", "BMP");

    int mildDiffCount = 0;
    int seriousDiffCount = 0;
    for (int x = 0; x < diff.width(); x++)
        for (int y = 0; y < diff.height(); y++) {
            QColor c = diff.pixelColor(x, y);
            float l = c.lightnessF();
            QVERIFY(l < 0.2);
            if (l > 0.08) seriousDiffCount++;
            else if (l > 0.03) mildDiffCount++;
        }
    int totalPixelCount = diff.width() * diff.height();
    QVERIFY(mildDiffCount < qMin(100, int(totalPixelCount * 0.03)));
    QVERIFY(seriousDiffCount < totalPixelCount * 0.003);
}

void ConformanceTest::testPixelByPixelMasked_data()
{
    QTest::addColumn<QString>("baseName");
    QTest::addColumn<InputEvents>("inputEvents");
    QTest::addColumn<QList<QRect>>("maskedRects");

    // QWidgets draws the caret *under* the placeholder text
    QList<QRect> rects;
    if (QApplication::style()->metaObject()->className() == QStringLiteral("QWindowsStyle")) {
        rects.append(QRect(4, 6, 0, 3));
    } else {
        rects.append(QRect(3, 6, 0, 3));
    }
    QTest::newRow("text field, placeholder") <<
        "TextFieldWithPlaceholder" <<
        InputEvents {} <<
        rects;
}

void ConformanceTest::testPixelByPixelMasked()
{
    QFETCH(QString, baseName);
    QFETCH(InputEvents, inputEvents);
    QFETCH(QList<QRect>, maskedRects);

    SnapShots snapShots = createAndCapture(baseName, inputEvents);

    for (auto i = snapShots.begin(); i != snapShots.end(); i++) {
        QImage &image = i.value();
        QPainter p(&image);
        p.setBrush(QBrush(Qt::red));
        p.setPen(Qt::red);
        for (const QRect &rect: maskedRects) {
            p.drawRect(rect);
        }
        p.end();
        image.save(m_tmp->path() + '/' + i.key() + ".bmp", "BMP");
    }

    const QImage &qmlWindow = snapShots.value("qmlWindow");
    const QImage &widgetWindow = snapShots.value("widgetWindow");

    QCOMPARE(qmlWindow.size(), widgetWindow.size());

    QImage diff(qmlWindow);
    QPainter p(&diff);
    p.setCompositionMode(QPainter::CompositionMode_Difference);
    p.drawImage(QPoint(0, 0), widgetWindow);
    p.end();
    diff.save(m_tmp->path() + "/diff.bmp", "BMP");

    for (int x = 0; x < diff.width(); x++)
        for (int y = 0; y < diff.height(); y++) {
            QColor c = diff.pixelColor(x, y);
            QVERIFY(c.lightnessF() < 0.02);
        }
}

QTEST_MAIN(ConformanceTest)

#include "tst_conformance.moc"
