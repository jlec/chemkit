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

#include <chemkit/staticmatrix.h>

class StaticMatrixTest : public QObject
{
    Q_OBJECT

    private slots:
        void multiply();
        void determinant();
        void invert();
};

void StaticMatrixTest::multiply()
{
    chemkit::StaticMatrix<chemkit::Float, 2, 3> a;
    a(0, 0) = 8;
    a(0, 1) = -6;
    a(0, 2) = 1;
    a(1, 0) = 4;
    a(1, 1) = 7;
    a(1, 2) = -2;

    chemkit::StaticMatrix<chemkit::Float, 3, 2> b;
    b(0, 0) = 0;
    b(0, 1) = 3;
    b(1, 0) = 3;
    b(1, 1) = 4;
    b(2, 0) = 7;
    b(2, 1) = -2;

    // c = a * b
    chemkit::StaticMatrix<chemkit::Float, 2, 2> c = a.multiply(b);
    QCOMPARE(c(0, 0), chemkit::Float(-11.0));
    QCOMPARE(c(0, 1), chemkit::Float(-2.0));
    QCOMPARE(c(1, 0), chemkit::Float(7.0));
    QCOMPARE(c(1, 1), chemkit::Float(44.0));

    // d = b * a
    chemkit::StaticMatrix<chemkit::Float, 3, 3> d = b.multiply(a);
    QCOMPARE(d(0, 0), chemkit::Float(12.0));
    QCOMPARE(d(0, 1), chemkit::Float(21.0));
    QCOMPARE(d(0, 2), chemkit::Float(-6.0));
    QCOMPARE(d(1, 0), chemkit::Float(40.0));
    QCOMPARE(d(1, 1), chemkit::Float(10.0));
    QCOMPARE(d(1, 2), chemkit::Float(-5.0));
    QCOMPARE(d(2, 0), chemkit::Float(48.0));
    QCOMPARE(d(2, 1), chemkit::Float(-56.0));
    QCOMPARE(d(2, 2), chemkit::Float(11.0));
}

void StaticMatrixTest::determinant()
{
    // 3x3 matrix filled with 2's
    chemkit::StaticMatrix<chemkit::Float, 3, 3> matrix3;
    matrix3.fill(2);
    QCOMPARE(qRound(matrix3.determinant()), 0);

    // another matrix
    matrix3.fill(0);
    matrix3(0, 0) = 6;
    matrix3(0, 1) = 3;
    matrix3(0, 2) = 2;
    matrix3(1, 0) = 4;
    matrix3(1, 1) = -3;
    matrix3(1, 2) = 2;
    matrix3(2, 0) = -1;
    matrix3(2, 1) = 9;
    matrix3(2, 2) = -2;
    QCOMPARE(qRound(matrix3.determinant()), 12);

    // change last row
    matrix3(2, 0) = 0;
    matrix3(2, 1) = 4;
    matrix3(2, 2) = 0;
    QCOMPARE(qRound(matrix3.determinant()), -16);

    // change first row
    matrix3(0, 0) = 0;
    matrix3(0, 1) = 4;
    matrix3(0, 2) = 0;
    QCOMPARE(qRound(matrix3.determinant()), 0);
}

void StaticMatrixTest::invert()
{
    chemkit::StaticMatrix<chemkit::Float, 3, 3> matrix3;
    matrix3(0, 0) = 1;
    matrix3(0, 1) = 2;
    matrix3(0, 2) = 3;
    matrix3(1, 0) = 0;
    matrix3(1, 1) = 1;
    matrix3(1, 2) = 0;
    matrix3(2, 0) = 4;
    matrix3(2, 1) = 0;
    matrix3(2, 2) = 4;

    chemkit::StaticMatrix<chemkit::Float, 3, 3> inverse3 = matrix3.inverted();
    QCOMPARE(inverse3(0, 0), chemkit::Float(-0.5));
    QCOMPARE(inverse3(0, 1), chemkit::Float(1.0));
    QCOMPARE(inverse3(0, 2), chemkit::Float(0.375));
    QCOMPARE(inverse3(1, 0), chemkit::Float(0.0));
    QCOMPARE(inverse3(1, 1), chemkit::Float(1.0));
    QCOMPARE(inverse3(1, 2), chemkit::Float(0.0));
    QCOMPARE(inverse3(2, 0), chemkit::Float(0.5));
    QCOMPARE(inverse3(2, 1), chemkit::Float(-1.0));
    QCOMPARE(inverse3(2, 2), chemkit::Float(-0.125));
}

QTEST_APPLESS_MAIN(StaticMatrixTest)
#include "staticmatrixtest.moc"
