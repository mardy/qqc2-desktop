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

#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickItem>
#include <QQuickStyle>
#include <QTest>

class PluginTest: public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testAvailability();
    void testUse();
};

void PluginTest::testAvailability()
{
    QStringList styles = QQuickStyle::availableStyles();
    QVERIFY(styles.contains("Desktop"));
}

void PluginTest::testUse()
{
    QQuickStyle::setStyle("Desktop");

    QQmlApplicationEngine engine;
    QQmlComponent component(&engine);
    component.setData("import QtQuick.Controls 2.2\nButton { text: \"Hello world!\" }", QUrl());
    QQuickItem *item = qobject_cast<QQuickItem *>(component.create());
    QVERIFY(item);
}

QTEST_MAIN(PluginTest)

#include "tst_plugin.moc"
