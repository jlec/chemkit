/******************************************************************************
**
** Copyright (C) 2009-2011 Kyle Lutz <kyle.r.lutz@gmail.com>
**
** This file is part of chemkit. For more information see
** <http://www.chemkit.org>.
**
** chemkit is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** chemkit is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with chemkit. If not, see <http://www.gnu.org/licenses/>.
**
******************************************************************************/

#include <QtTest>

#include <chemkit/vector.h>

class VectorTest : public QObject
{
    Q_OBJECT

    private slots:
        void constructor();
        void value();
        void length();
        void isNull();
        void normalize();
};

void VectorTest::constructor()
{
    chemkit::Vector empty;
    QCOMPARE(qRound(empty.x()), 0);
    QCOMPARE(qRound(empty.y()), 0);
    QCOMPARE(qRound(empty.z()), 0);

    chemkit::Vector vector123(1, 2, 3);
    QCOMPARE(qRound(vector123.x()), 1);
    QCOMPARE(qRound(vector123.y()), 2);
    QCOMPARE(qRound(vector123.z()), 3);
}

void VectorTest::value()
{
    chemkit::Vector vector;
    QCOMPARE(qRound(vector.value(0)), 0);
    QCOMPARE(qRound(vector.value(1)), 0);
    QCOMPARE(qRound(vector.value(2)), 0);

    vector.setValue(0, 1);
    QCOMPARE(qRound(vector.value(0)), 1);

    vector.value(1) = 3;
    QCOMPARE(qRound(vector.value(1)), 3);

    vector.value(2) = -5;
    QCOMPARE(qRound(vector.value(2)), -5);

    vector.value(0) = vector.value(1);
    QCOMPARE(qRound(vector.value(0)), 3);
}

void VectorTest::length()
{
    chemkit::Vector vector;
    QCOMPARE(qRound(vector.length()), 0);

    vector = chemkit::Vector(1, 0, 0);
    QCOMPARE(qRound(vector.x()), 1);
    QCOMPARE(qRound(vector.y()), 0);
    QCOMPARE(qRound(vector.z()), 0);
    QCOMPARE(qRound(vector.length()), 1);
}

void VectorTest::isNull()
{
    chemkit::Vector vector;
    QCOMPARE(vector.isNull(), true);

    vector = chemkit::Vector(1, 2, 3);
    QCOMPARE(vector.isNull(), false);
}

void VectorTest::normalize()
{
    chemkit::Vector vector(2, 0, 0);
    QCOMPARE(qRound(vector.length()), 2);

    vector.normalize();
    QCOMPARE(qRound(vector.length()), 1);
    QCOMPARE(qRound(vector.x()), 1);

    chemkit::Vector nullVector;
    QCOMPARE(qRound(nullVector.length()), 0);
    nullVector.normalize();
    QCOMPARE(qRound(nullVector.length()), 0);
}

QTEST_APPLESS_MAIN(VectorTest)
#include "vectortest.moc"
