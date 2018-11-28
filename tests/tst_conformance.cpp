/*
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

#include <QHash>
#include <QImage>
#include <QPixmap>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickItem>
#include <QQuickStyle>
#include <QScopedPointer>
#include <QScreen>
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
        Mouse,
    };

    InputEvent(): type(None) {}

    InputEvent(Qt::Key key,
               Qt::KeyboardModifiers mod = Qt::NoModifier):
        type(KeyClick), key(key), modifier(mod) {}

    InputEvent(Type type,
               Qt::Key key,
               Qt::KeyboardModifiers mod = Qt::NoModifier):
        type(type), key(key), modifier(mod) {}

    Type type;
    Qt::Key key;
    Qt::KeyboardModifiers modifier;
};
Q_DECLARE_METATYPE(InputEvent)

typedef QList<InputEvent> InputEvents;

class ConformanceTest: public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void init();
    void cleanup();
    void testPixelByPixel_data();
    void testPixelByPixel();

private:
    QTemporaryDir *m_tmp;
};

void ConformanceTest::initTestCase()
{
    QCoreApplication::setAttribute(Qt::AA_Use96Dpi, false);
    QQuickStyle::setStyle("Desktop");
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

void ConformanceTest::testPixelByPixel_data()
{
    QTest::addColumn<QString>("baseName");
    QTest::addColumn<InputEvents>("inputEvents");

    QTest::newRow("label") <<
        "Label" <<
        InputEvents {};

    QTest::newRow("button") <<
        "Button" <<
        InputEvents {};

    QTest::newRow("checkbox") <<
        "CheckBox" <<
        InputEvents {};

    QTest::newRow("checkbox, checked") <<
        "CheckBox" <<
        InputEvents {
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
}

void ConformanceTest::testPixelByPixel()
{
    QFETCH(QString, baseName);
    QFETCH(InputEvents, inputEvents);

    /* Load the QtWidgets window */
    QUiLoader loader;
    QFile file(QString(DATA_DIR "/%1.ui").arg(baseName));
    file.open(QFile::ReadOnly);
    QScopedPointer<QWidget> widget(loader.load(&file));
    file.close();

    QCOMPARE(loader.errorString(), QString());
    QVERIFY(widget);
    widget->show();

    /* Load the QML window */
    QQmlApplicationEngine engine(QString(DATA_DIR "/%1.qml").arg(baseName));
    QTRY_VERIFY(!engine.rootObjects().isEmpty());

    /* Give it some time to process the events: without this, it can happen
     * that the QtQuick window gets shown later, while we are handling the
     * QtWidgets one in the loop below, causing it to lose the focus.
     */
    QTest::qWait(50);

    /* Get a handle to the windows */
    QTRY_COMPARE(QGuiApplication::topLevelWindows().count(), 2);

    /* Get a snapshot of each window */
    QHash<QString, QImage> snapShots;
    for (QWindow *window: QGuiApplication::topLevelWindows()) {
        /* Let's focus the window */
        window->requestActivate();
        window->raise();
        QTRY_VERIFY(window->isActive());

        for (const auto &event: inputEvents) {
            if (event.type == InputEvent::KeyClick) {
                QTest::keyClick(window, event.key, event.modifier);
            } else if (event.type == InputEvent::KeyPress) {
                QTest::keyPress(window, event.key, event.modifier);
            } else if (event.type == InputEvent::KeyRelease) {
                QTest::keyRelease(window, event.key, event.modifier);
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

    const QImage &qmlWindow = snapShots.value("qmlWindow");
    const QImage &widgetWindow = snapShots.value("widgetWindow");

    /* The conversion to 4-bit depth helps working around minor
     * differences in the pixels of labels */
    QCOMPARE(qmlWindow.convertToFormat(QImage::Format_RGB444),
             widgetWindow.convertToFormat(QImage::Format_RGB444));
}

QTEST_MAIN(ConformanceTest)

#include "tst_conformance.moc"
