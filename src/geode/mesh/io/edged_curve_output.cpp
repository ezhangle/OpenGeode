/*
 * Copyright (c) 2019 - 2023 Geode-solutions
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

#include <geode/mesh/io/edged_curve_output.h>

#include <absl/strings/string_view.h>

#include <geode/basic/detail/geode_output_impl.h>

#include <geode/mesh/core/edged_curve.h>

namespace geode
{
    template < index_t dimension >
    void save_edged_curve(
        const EdgedCurve< dimension >& edged_curve, absl::string_view filename )
    {
        try
        {
            detail::geode_object_output_impl<
                EdgedCurveOutputFactory< dimension > >(
                absl::StrCat( "EdgedCurve", dimension, "D" ), edged_curve,
                filename );
        }
        catch( const OpenGeodeException& e )
        {
            Logger::error( e.what() );
            throw OpenGeodeException{ "Cannot save EdgedCurve in file: ",
                filename };
        }
    }

    template < index_t dimension >
    bool is_edged_curve_saveable(
        const EdgedCurve< dimension >& edged_curve, absl::string_view filename )
    {
        const auto output = detail::geode_object_output_writer<
            EdgedCurveOutputFactory< dimension > >( filename );
        return output->is_saveable( edged_curve );
    }

    template void opengeode_mesh_api save_edged_curve(
        const EdgedCurve< 2 >&, absl::string_view );
    template void opengeode_mesh_api save_edged_curve(
        const EdgedCurve< 3 >&, absl::string_view );

    template bool opengeode_mesh_api is_edged_curve_saveable(
        const EdgedCurve< 2 >&, absl::string_view );
    template bool opengeode_mesh_api is_edged_curve_saveable(
        const EdgedCurve< 3 >&, absl::string_view );
} // namespace geode
