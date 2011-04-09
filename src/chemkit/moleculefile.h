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

#ifndef CHEMKIT_MOLECULEFILE_H
#define CHEMKIT_MOLECULEFILE_H

#include "chemkit.h"

#include <string>
#include <vector>

#include <QtCore>

namespace chemkit {

class Molecule;
class MoleculeFileFormat;
class MoleculeFilePrivate;

class CHEMKIT_EXPORT MoleculeFile
{
    public:
        // construction and destruction
        MoleculeFile();
        MoleculeFile(const std::string &fileName);
        ~MoleculeFile();

        // properties
        void setFileName(const std::string &fileName);
        std::string fileName() const;
        void setFormat(MoleculeFileFormat *format);
        bool setFormat(const std::string &name);
        MoleculeFileFormat* format() const;
        std::string formatName() const;
        int size() const;
        bool isEmpty() const;

        // file contents
        void addMolecule(Molecule *molecule);
        bool removeMolecule(Molecule *molecule);
        bool deleteMolecule(Molecule *molecule);
        std::vector<Molecule *> molecules() const;
        int moleculeCount() const;
        Molecule* molecule(int index = 0) const;
        bool contains(const Molecule *molecule) const;
        void clear();

        // file data
        void setFileData(const std::string &name, const QVariant &value);
        QVariant fileData(const std::string &name) const;
        void setMoleculeData(const Molecule *molecule, const std::string &name, const QVariant &value);
        QVariant moleculeData(const Molecule *molecule, const std::string &name) const;

        // input and output
        bool read();
        bool read(const std::string &fileName);
        bool read(const std::string &fileName, const std::string &format);
        bool read(QIODevice *iodev, const std::string &format);
        bool write();
        bool write(const std::string &fileName);
        bool write(const std::string &fileName, const std::string &format);
        bool write(QIODevice *iodev);
        bool write(QIODevice *iodev, const std::string &format);

        // error handling
        std::string errorString() const;

        // static methods
        static std::vector<std::string> formats();
        static Molecule* quickRead(const std::string &fileName);
        static void quickWrite(const Molecule *molecule, const std::string &fileName);

    private:
        void setErrorString(const std::string &error);

    private:
        MoleculeFilePrivate* const d;
};

} // end chemkit namespace

#endif // CHEMKIT_MOLECULEFILE_H