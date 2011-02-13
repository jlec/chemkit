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

#include <chemkit/molecule.h>
#include <chemkit/coordinatematrix.h>

class CoordinateMatrixTest : public QObject
{
    Q_OBJECT

    private slots:
        void basic();
        void setPosition();
        void append();
        void insert();
        void remove();
        void center();
        void multiply();
        void distanceMatrix();
};

void CoordinateMatrixTest::basic()
{
    chemkit::Molecule molecule;
    chemkit::CoordinateMatrix matrix(&molecule);
    QCOMPARE(matrix.size(), 0);
    QCOMPARE(matrix.isEmpty(), true);

    chemkit::Atom *C1 = molecule.addAtom("C");
    chemkit::Atom *C2 = molecule.addAtom("C");
    chemkit::Atom *C3 = molecule.addAtom("C");
    C1->setPosition(2, 1, 0);
    C2->setPosition(3, -2, -4);
    C3->setPosition(0, 0, 0);
    matrix = chemkit::CoordinateMatrix(&molecule);
    QCOMPARE(matrix.size(), 3);
    QCOMPARE(matrix.isEmpty(), false);
    QCOMPARE(matrix.position(0), chemkit::Point(2, 1, 0));
    QCOMPARE(matrix.position(1), chemkit::Point(3, -2, -4));
    QCOMPARE(matrix.position(2), chemkit::Point(0, 0, 0));
}

void CoordinateMatrixTest::setPosition()
{
    chemkit::CoordinateMatrix matrix(5);
    QCOMPARE(matrix.position(0), chemkit::Point(0, 0, 0));

    matrix.setPosition(1, chemkit::Point(1, 2, 3));
    QCOMPARE(matrix.position(1), chemkit::Point(1, 2, 3));

    matrix.setPosition(2, -5, 8, 0.5);
    QCOMPARE(matrix.position(2), chemkit::Point(-5, 8, 0.5));
}

void CoordinateMatrixTest::append()
{
    chemkit::CoordinateMatrix matrix;
    QCOMPARE(matrix.size(), 0);

    matrix.append(1, 2, 3);
    QCOMPARE(matrix.size(), 1);
    QCOMPARE(matrix.position(0), chemkit::Point(1, 2, 3));

    matrix.append(4, 5, 6);
    QCOMPARE(matrix.size(), 2);
    QCOMPARE(matrix.position(0), chemkit::Point(1, 2, 3));
    QCOMPARE(matrix.position(1), chemkit::Point(4, 5, 6));
}

void CoordinateMatrixTest::insert()
{
    chemkit::CoordinateMatrix matrix(3);
    matrix.setPosition(0, 1.0, 2.0, 3.0);
    matrix.setPosition(1, 4.0, 5.0, 6.0);
    matrix.setPosition(2, 7.0, 8.0, 9.0);

    matrix.insert(3, -1.0, -2.0, -3.0);
    QCOMPARE(matrix.size(), 4);
    QCOMPARE(matrix.position(3), chemkit::Point(-1.0, -2.0, -3.0));
    QCOMPARE(matrix.position(2), chemkit::Point(7.0, 8.0, 9.0));

    matrix.insert(1, 0.5, 1.5, 2.5);
    QCOMPARE(matrix.size(), 5);
    QCOMPARE(matrix.position(0), chemkit::Point(1.0, 2.0, 3.0));
    QCOMPARE(matrix.position(1), chemkit::Point(0.5, 1.5, 2.5));
    QCOMPARE(matrix.position(2), chemkit::Point(4.0, 5.0, 6.0));
    QCOMPARE(matrix.position(3), chemkit::Point(7.0, 8.0, 9.0));
}

void CoordinateMatrixTest::remove()
{
    chemkit::CoordinateMatrix matrix(3);
    matrix.setPosition(0, 1.0, 2.0, 3.0);
    matrix.setPosition(1, 4.0, 5.0, 6.0);
    matrix.setPosition(2, 7.0, 8.0, 9.0);

    matrix.remove(0);
    QCOMPARE(matrix.size(), 2);
    QCOMPARE(matrix.position(0), chemkit::Point(4.0, 5.0, 6.0));
    QCOMPARE(matrix.position(1), chemkit::Point(7.0, 8.0, 9.0));

    matrix.remove(1);
    QCOMPARE(matrix.size(), 1);
    QCOMPARE(matrix.position(0), chemkit::Point(4.0, 5.0, 6.0));

    matrix.remove(0);
    QCOMPARE(matrix.size(), 0);
}

void CoordinateMatrixTest::center()
{
    chemkit::CoordinateMatrix matrix;
    QCOMPARE(matrix.center(), chemkit::Point(0, 0, 0));

    matrix = chemkit::CoordinateMatrix(2);
    matrix.setPosition(0, chemkit::Point(0, 0, 0));
    matrix.setPosition(1, chemkit::Point(0, 5, 0));
    QCOMPARE(matrix.center(), chemkit::Point(0, 2.5, 0));
}

void CoordinateMatrixTest::multiply()
{
    chemkit::CoordinateMatrix a(7);
    a.setPosition(0, chemkit::Point(5, 5, 5));
    a.setPosition(1, chemkit::Point(8, -2, 1.5));
    a.setPosition(2, chemkit::Point(0, 4, 1));
    a.setPosition(3, chemkit::Point(-1, -3, 8));
    a.setPosition(4, chemkit::Point(2, 10, 15));
    a.setPosition(5, chemkit::Point(-1, 2.5, 3));
    a.setPosition(6, chemkit::Point(0, -9, 11.75));

    chemkit::CoordinateMatrix b(7);
    b.setPosition(0, chemkit::Point(19, 12, 1));
    b.setPosition(1, chemkit::Point(0, 0, 0));
    b.setPosition(2, chemkit::Point(-8, -9, 13));
    b.setPosition(3, chemkit::Point(9, 8, 1.4));
    b.setPosition(4, chemkit::Point(6.7, -3, -4.2));
    b.setPosition(5, chemkit::Point(0, 8, 9));
    b.setPosition(6, chemkit::Point(-2.5, 1.5, 0));

    chemkit::StaticMatrix<chemkit::Float, 3, 3> product = a.multiply(&b);
    QCOMPARE(product(0, 0), chemkit::Float(99.4));
    QCOMPARE(product(0, 1), chemkit::Float(38.0));
    QCOMPARE(product(0, 2), chemkit::Float(-13.8));
    QCOMPARE(product(1, 0), chemkit::Float(125.5));
    QCOMPARE(product(1, 1), chemkit::Float(-23.5));
    QCOMPARE(product(1, 2), chemkit::Float(33.3));
    QCOMPARE(product(2, 0), chemkit::Float(230.125));
    QCOMPARE(product(2, 1), chemkit::Float(111.625));
    QCOMPARE(product(2, 2), chemkit::Float(-6.8));
}

void CoordinateMatrixTest::distanceMatrix()
{
    chemkit::CoordinateMatrix coordinates(4);
    coordinates.setPosition(0, chemkit::Point(1, 0, 0));
    coordinates.setPosition(1, chemkit::Point(2, 0, 0));
    coordinates.setPosition(2, chemkit::Point(0, 5, 0));
    coordinates.setPosition(3, chemkit::Point(10, 5, 2));

    chemkit::Matrix distances = coordinates.distanceMatrix();
    QCOMPARE(distances.rowCount(), 4);
    QCOMPARE(distances.columnCount(), 4);
    QCOMPARE(distances(0, 0), chemkit::Float(0));
    QCOMPARE(distances(0, 1), chemkit::Float(1));
    QCOMPARE(distances(1, 0), chemkit::Float(1));
}

QTEST_APPLESS_MAIN(CoordinateMatrixTest)
#include "coordinatematrixtest.moc"
