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

#include "graphicsbonditem.h"

#include "graphicsray.h"
#include "graphicspoint.h"
#include "graphicsvector.h"
#include "graphicspainter.h"
#include "graphicsmoleculeitem.h"

#include <chemkit/atom.h>
#include <chemkit/bond.h>

namespace chemkit {

// === GraphicsBondItemPrivate ============================================= //
class GraphicsBondItemPrivate
{
    public:
        const Bond *bond;
        GraphicsFloat radius;
        GraphicsFloat maximumRadius;
        GraphicsVector normal;
        bool bondOrderVisible;
        bool atomColored;
};

// === GraphicsBondItem ==================================================== //
/// \class GraphicsBondItem graphicsbonditem.h chemkit/graphicsbonditem.h
/// \ingroup chemkit-graphics
/// \brief The GraphicsBondItem visually represents a chemical bond.
///
/// The GraphicsBondItem class displays a single bond using a
/// cylinder.

// --- Construction and Destruction ---------------------------------------- //
/// Creates a new bond item for \p bond with a cylinder of the given
/// \p radius.
GraphicsBondItem::GraphicsBondItem(const Bond *bond, GraphicsFloat radius)
    : GraphicsItem(BondItem),
      d(new GraphicsBondItemPrivate)
{
    d->bond = bond;
    d->radius = radius;
    d->maximumRadius = 0.5;
    d->normal = -GraphicsVector::Z();
    d->bondOrderVisible = true;
    d->atomColored = true;
}

/// Destoys the bond item.
GraphicsBondItem::~GraphicsBondItem()
{
    delete d;
}

// --- Properties ---------------------------------------------------------- //
/// Sets the bond item that is displayed to \p bond.
void GraphicsBondItem::setBond(const Bond *bond)
{
    d->bond = bond;
}

/// Returns the bond being displayed by the item or \c 0 if no bond
/// is being displayed.
const Bond* GraphicsBondItem::bond() const
{
    return d->bond;
}

/// Sets the radius of the cylinder to \p radius.
void GraphicsBondItem::setRadius(GraphicsFloat radius)
{
    d->radius = radius;
}

/// Returns the radius of the cylinder.
GraphicsFloat GraphicsBondItem::radius() const
{
    return d->radius;
}

void GraphicsBondItem::setMaximumRadius(GraphicsFloat radius)
{
    d->maximumRadius = radius;
}

GraphicsFloat GraphicsBondItem::maximumRadius() const
{
    return d->maximumRadius;
}

void GraphicsBondItem::setNormal(const GraphicsVector &normal)
{
    d->normal = normal;
}

GraphicsVector GraphicsBondItem::normal() const
{
    return d->normal;
}

void GraphicsBondItem::setAtomColored(bool atomColored)
{
    d->atomColored = atomColored;
}

bool GraphicsBondItem::atomColored() const
{
    return d->atomColored;
}

void GraphicsBondItem::setBondOrderVisible(bool visible)
{
    d->bondOrderVisible = visible;
}

bool GraphicsBondItem::bondOrderVisible() const
{
    return d->bondOrderVisible;
}

// --- Intersection -------------------------------------------------------- //
bool GraphicsBondItem::intersects(const GraphicsRay &ray, GraphicsFloat *distance) const
{
    GraphicsFloat intersectionRadius = qMin(d->radius, d->maximumRadius);

    return ray.intersectsCylinder(d->bond->atom1()->position(),
                                  d->bond->atom2()->position(),
                                  intersectionRadius,
                                  distance);
}

// --- Drawing ------------------------------------------------------------- //
void GraphicsBondItem::paint(GraphicsPainter *painter)
{
    const Atom *atom1 = d->bond->atom1();
    const Atom *atom2 = d->bond->atom2();
    int bondOrder = d->bond->order();

    // draw multiple cylinders
    if(d->bondOrderVisible && bondOrder > 1){
        // radius of each cylinder, clamped to be under
        // the total maximum radius if necessary
        GraphicsFloat radius = d->radius;
        int radiiCount = 2 * bondOrder - 1;
        if(radius * radiiCount > d->maximumRadius)
            radius = d->maximumRadius / radiiCount;

        // distance between the center's of each adjacent cylinder
        GraphicsFloat offset = 3 * radius;

        // distance from the atom's positions to the
        // center of the topmost cylinder
        GraphicsFloat initialOffset = 1.5 * (bondOrder - 1) * radius;

        // a vector pointing to the right (with normal pointing up)
        GraphicsVector right = GraphicsVector(GraphicsPoint(atom2->position()) - GraphicsPoint(atom1->position())).cross(d->normal);

        // positions for the first cylinder
        GraphicsPoint a = GraphicsPoint(atom1->position()).movedBy(-initialOffset, right);
        GraphicsPoint b = GraphicsPoint(atom2->position()).movedBy(-initialOffset, right);

        // draw each cylinder
        for(int i = 0; i < bondOrder; i++){
            if(d->atomColored){
                if(atom1->atomicNumber() == atom2->atomicNumber()){
                    painter->setColor(GraphicsMoleculeItem::atomColor(atom1));
                    painter->drawCylinder(a, b, radius);
                }
                else{
                    GraphicsPoint midpoint = GraphicsPoint::midpoint(a, b);
                    painter->setColor(GraphicsMoleculeItem::atomColor(atom1));
                    painter->drawCylinder(a, midpoint, radius);
                    painter->setColor(GraphicsMoleculeItem::atomColor(atom2));
                    painter->drawCylinder(midpoint, b, radius);
                }
            }
            else{
                painter->setColor(Qt::darkGray);
                painter->drawCylinder(a, b, radius);
            }

            // move the positions for the next cylinder
            a.moveBy(offset, right);
            b.moveBy(offset, right);
        }
    }

    // draw a single cylinder
    else{
        GraphicsFloat radius = qMin(d->radius, d->maximumRadius);

        if(d->atomColored){
            if(atom1->atomicNumber() == atom2->atomicNumber()){
                painter->setColor(GraphicsMoleculeItem::atomColor(atom1));
                painter->drawCylinder(atom1->position(), atom2->position(), radius);
            }
            else{
                GraphicsPoint midpoint = atom1->position().midpoint(atom2->position());
                painter->setColor(GraphicsMoleculeItem::atomColor(atom1));
                painter->drawCylinder(atom1->position(), midpoint, radius);
                painter->setColor(GraphicsMoleculeItem::atomColor(atom2));
                painter->drawCylinder(midpoint, atom2->position(), radius);
            }
        }
        else{
            painter->setColor(Qt::darkGray);
            painter->drawCylinder(atom1->position(), atom2->position(), radius);
        }
    }
}

} // end chemkit namespace
