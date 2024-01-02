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

#include <geode/geometry/basic_objects/segment.h>
#include <geode/geometry/common.h>

namespace geode
{
    class opengeode_geometry_api Cylinder
    {
    public:
        Cylinder( Segment3D axis, double radius );

        Cylinder( const Cylinder& other );
        Cylinder& operator=( const Cylinder& other );
        Cylinder( Cylinder&& other ) noexcept;
        Cylinder& operator=( Cylinder&& other ) noexcept;

        const Segment3D& axis() const;
        double radius() const;

    private:
        Segment3D axis_;
        double radius_{ 0 };
    };
} // namespace geode
