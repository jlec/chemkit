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

#ifndef CHEMKIT_GRAPHICSSPHERE_H
#define CHEMKIT_GRAPHICSSPHERE_H

#include "graphics.h"

namespace chemkit {

class GraphicsRay;
class GraphicsVertexBuffer;

class CHEMKIT_GRAPHICS_EXPORT GraphicsSphere
{
    public:
        // construction and destruction
        GraphicsSphere();
        GraphicsSphere(GraphicsFloat radius);
        ~GraphicsSphere();

        // properties
        void setRadius(const GraphicsFloat radius);
        GraphicsFloat radius() const;

        // intersection
        bool intersects(const GraphicsRay &ray, GraphicsFloat *distance = 0) const;

        // tesselation
        GraphicsVertexBuffer* tesselate(int subdivisions = 3) const;

    private:
        GraphicsFloat m_radius;
};

} // end chemkit namespace

#endif // CHEMKIT_GRAPHICSSPHERE_H
