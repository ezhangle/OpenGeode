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

#include <geode/basic/identifier.h>
#include <geode/basic/pimpl.h>

#include <geode/mesh/common.h>
#include <geode/mesh/core/grid.h>

namespace geode
{
    FORWARD_DECLARATION_DIMENSION_CLASS( Point );
    FORWARD_DECLARATION_DIMENSION_CLASS( Vector );
    class AttributeManager;
} // namespace geode

namespace geode
{
    template < index_t dimension >
    class LightRegularGrid : public Grid< dimension >, public Identifier
    {
    public:
        static constexpr auto dim = dimension;
        using CellIndices = typename Grid< dimension >::CellIndices;
        using VertexIndices = typename Grid< dimension >::VertexIndices;
        using VerticesAroundVertex =
            absl::InlinedVector< index_t, 2 * dimension >;

        LightRegularGrid( Point< dimension > origin,
            std::array< index_t, dimension > cells_number,
            std::array< double, dimension > cells_length );
        LightRegularGrid( Point< dimension > origin,
            std::array< index_t, dimension > cells_number,
            std::array< Vector< dimension >, dimension > directions );
        LightRegularGrid( LightRegularGrid&& other ) noexcept;
        ~LightRegularGrid();

        static absl::string_view native_extension_static()
        {
            static const auto extension =
                absl::StrCat( "og_lrgd", dimension, "d" );
            return extension;
        }

        absl::string_view native_extension() const
        {
            return native_extension_static();
        }

        index_t vertex_index( const VertexIndices& index ) const override;

        VertexIndices vertex_indices( index_t index ) const override;

        index_t cell_index( const CellIndices& index ) const override;

        CellIndices cell_indices( index_t index ) const override;

        Point< dimension > point( index_t vertex_id ) const;

        VerticesAroundVertex vertices_around_vertex( index_t vertex_id ) const;

        AttributeManager& cell_attribute_manager() const override;

        AttributeManager& grid_vertex_attribute_manager() const override;

    private:
        friend class bitsery::Access;
        template < typename Archive >
        void serialize( Archive& archive );

    private:
        IMPLEMENTATION_MEMBER( impl_ );
    };
    ALIAS_2D_AND_3D( LightRegularGrid );
} // namespace geode
