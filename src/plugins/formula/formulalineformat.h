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

#ifndef FORMULALINEFORMAT_H
#define FORMULALINEFORMAT_H

#include <QtCore>

#include <chemkit/lineformat.h>

class FormulaLineFormat : public chemkit::LineFormat
{
    public:
        FormulaLineFormat();

        chemkit::Molecule* read(const QString &formula);
        QString write(const chemkit::Molecule *molecule);
};

#endif // FORMULALINEFORMAT_H
