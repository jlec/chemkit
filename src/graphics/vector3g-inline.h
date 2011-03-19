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

#ifndef CHEMKIT_VECTOR3G_INLINE_H
#define CHEMKIT_VECTOR3G_INLINE_H

#include "vector3g.h"

namespace chemkit {

// === Vector3g ============================================================ //
/// \class Vector3g vector3g.h chemkit/vector3g.h
/// \ingroup chemkit-graphics
/// \brief The Vector3g class represents a direction in
///        three-dimensional space.

// --- Construction and Destruction ---------------------------------------- //
/// Create a new vector containing (\c 0, \c 0, \c 0).
inline Vector3g::Vector3g()
    : GenericVector<GraphicsFloat>()
{
}

/// Create a new vector containing (\p x, \p y, \p z).
inline Vector3g::Vector3g(GraphicsFloat x, GraphicsFloat y, GraphicsFloat z)
    : GenericVector<GraphicsFloat>(x, y, z)
{
}

inline Vector3g::Vector3g(const GenericVector<float> &vector)
    : GenericVector<GraphicsFloat>(vector)
{
}

inline Vector3g::Vector3g(const GenericVector<double> &vector)
    : GenericVector<GraphicsFloat>(vector)
{
}

inline Vector3g::Vector3g(const StaticVector<float, 3> &vector)
    : GenericVector<GraphicsFloat>(vector)
{
}

inline Vector3g::Vector3g(const StaticVector<double, 3> &vector)
    : GenericVector<GraphicsFloat>(vector)
{
}

} // end chemkit namespace

#endif // CHEMKIT_VECTOR3G_INLINE_H
