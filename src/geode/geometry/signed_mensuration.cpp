/*
 * Copyright (c) 2019 - 2022 Geode-solutions
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <geode/geometry/signed_mensuration.h>

#include <geode/geometry/basic_objects/tetra.h>
#include <geode/geometry/basic_objects/triangle.h>
#include <geode/geometry/perpendicular.h>

namespace geode
{
    template < index_t dimension >
    double triangle_area( const Triangle< dimension >& triangle )
    {
        const auto& tri_v = triangle.vertices();
        // Heron's formula
        const auto l0 =
            geode::Vector< dimension >{ tri_v[0], tri_v[1] }.length();
        const auto l1 =
            geode::Vector< dimension >{ tri_v[1], tri_v[2] }.length();
        const auto l2 =
            geode::Vector< dimension >{ tri_v[2], tri_v[0] }.length();
        const auto p = ( l0 + l1 + l2 ) / 2;
        return std::sqrt( p * ( p - l0 ) * ( p - l1 ) * ( p - l2 ) );
    }

    double triangle_signed_area(
        const Triangle3D& triangle, const Vector3D& direction )
    {
        const auto area = triangle_area( triangle );
        try
        {
            if( const auto area_normal = triangle.new_normal() )
            {
                return direction.dot( area_normal.value() ) > 0 ? area : -area;
            }
            return area;
        }
        catch( const OpenGeodeException& )
        {
            return area;
        }
    }

    double triangle_signed_area( const Triangle2D& triangle )
    {
        return dot_perpendicular(
                   { triangle.vertices()[0], triangle.vertices()[1] },
                   { triangle.vertices()[0], triangle.vertices()[2] } )
               / 2.;
    }

    double tetra_signed_volume( const Tetra& tetra )
    {
        return Vector3D{ tetra.vertices()[0], tetra.vertices()[1] }.dot(
                   Vector3D{ tetra.vertices()[0], tetra.vertices()[2] }.cross(
                       { tetra.vertices()[0], tetra.vertices()[3] } ) )
               / 6.;
    }

    double tetra_volume( const Tetra& tetra )
    {
        return std::fabs( tetra_signed_volume( tetra ) );
    }

    template double opengeode_geometry_api triangle_area( const Triangle2D& );

    template double opengeode_geometry_api triangle_area( const Triangle3D& );
} // namespace geode
