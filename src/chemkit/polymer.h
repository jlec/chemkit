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

#ifndef CHEMKIT_POLYMER_H
#define CHEMKIT_POLYMER_H

#include "chemkit.h"

#include <QtCore>

#include "molecule.h"

namespace chemkit {

class PolymerChain;
class PolymerPrivate;

class CHEMKIT_EXPORT Polymer : public Molecule
{
    public:
        // construction and destruction
        Polymer();
        ~Polymer();

        // structure
        PolymerChain* addChain();
        void removeChain(PolymerChain *chain);
        PolymerChain* chain(int index = 0) const;
        QList<PolymerChain *> chains() const;
        int chainCount() const;

    private:
        PolymerPrivate* const d;
};

} // end chemkit namespace

#endif // CHEMKIT_POLYMER_H