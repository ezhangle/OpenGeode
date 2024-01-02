/*
 * Copyright (c) 2019 - 2024 Geode-solutions
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

#pragma once

#include <geode/basic/pimpl.h>

#include <geode/mesh/common.h>
#include <geode/mesh/core/grid.h>

namespace geode
{
    FORWARD_DECLARATION_DIMENSION_CLASS( Point );
    FORWARD_DECLARATION_DIMENSION_CLASS( RegularGrid );
} // namespace geode

namespace geode
{
    template < index_t dimension, index_t point_dimension = dimension >
    class RegularGridPointFunction
    {
    public:
        RegularGridPointFunction(
            RegularGridPointFunction< dimension, point_dimension >&&
                other ) noexcept;
        ~RegularGridPointFunction();

        /*!
         * Create a new object function from a RegularGrid, a name, and a
         * value.
         * Throws an exception if an attribute with the same name exists.
         */
        static RegularGridPointFunction< dimension, point_dimension > create(
            const Grid< dimension >& grid,
            absl::string_view function_name,
            Point< point_dimension > value );

        /*!
         * Finds an object function that already exists in the given
         * RegularGrid, from its given name.
         * Throws an exception if no attribute with the same name exists.
         */
        static RegularGridPointFunction< dimension, point_dimension > find(
            const Grid< dimension >& grid, absl::string_view function_name );

        void set_value(
            const typename Grid< dimension >::VertexIndices& vertex_index,
            Point< point_dimension > value );

        void set_value( index_t vertex_index, Point< point_dimension > value );

        const Point< point_dimension >& value(
            const typename Grid< dimension >::VertexIndices& vertex_index )
            const;

        const Point< point_dimension >& value( index_t vertex_index ) const;

        Point< point_dimension > value( const Point< dimension >& point,
            const typename Grid< dimension >::CellIndices& grid_cell_indices )
            const;

    private:
        RegularGridPointFunction(
            const Grid< dimension >& grid, absl::string_view function_name );

        RegularGridPointFunction( const Grid< dimension >& grid,
            absl::string_view function_name,
            Point< point_dimension > value );

    private:
        IMPLEMENTATION_MEMBER( impl_ );
    };
    ALIAS_2D_AND_3D( RegularGridPointFunction );
} // namespace geode