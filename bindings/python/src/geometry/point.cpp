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

#include "../common.hpp"

#include <geode/geometry/point.hpp>

#define PYTHON_POINT( dimension )                                              \
    const auto name##dimension = "Point" + std::to_string( dimension ) + "D";  \
    pybind11::class_< Point##dimension##D >( module, name##dimension.c_str() ) \
        .def( pybind11::init<>() )                                             \
        .def( pybind11::init< std::array< double, dimension > >() )            \
        .def( "inexact_equal", &Point##dimension##D::inexact_equal )           \
        .def( pybind11::self == pybind11::self )                               \
        .def( pybind11::self != pybind11::self )                               \
        .def( pybind11::self* double() )                                       \
        .def( pybind11::self / double() )                                      \
        .def( pybind11::self + pybind11::self )                                \
        .def( pybind11::self - pybind11::self )                                \
        .def( pybind11::self *= double() )                                     \
        .def( pybind11::self /= double() )                                     \
        .def( pybind11::self += pybind11::self )                               \
        .def( pybind11::self -= pybind11::self )                               \
        .def( "value", &Point##dimension##D::value )                           \
        .def( "string", &Point##dimension##D::string )                         \
        .def( "set_value", &Point##dimension##D::set_value )

namespace geode
{
    void define_point( pybind11::module& module )
    {
        PYTHON_POINT( 2 );
        PYTHON_POINT( 3 );
    }
} // namespace geode
